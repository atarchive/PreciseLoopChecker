#include "solver.h"
#include <iostream>
#include<unordered_map>
#include<vector>
#include<stack>
#include<sstream>
#include<algorithm>
#include "minisat/core/Solver.h"
using namespace std;

static int wires2idx(vector<Minisat::Var>&vars,unordered_map<string,int>&wire2var,string wire,Minisat::Solver &solver,vector<vector<int>>&output_clause,vector<vector<int>>&input_clause){
    if(wire2var.find(wire)!=wire2var.end())return wire2var[wire];
    else {
        vars.push_back(solver.newVar());
        output_clause.push_back(vector<int>{});
        output_clause.push_back(vector<int>{});
        input_clause.push_back(vector<int>{});
        input_clause.push_back(vector<int>{});
        wire2var[wire]=vars.size()-1;
        return vars.size()-1;
    }
}

static void addgates(int idx,GateInstVec gates,Minisat::Solver &solver,vector<Minisat::Var>&vars,unordered_map<string,int>&wire2var,vector<vector<int>>&output_clause,vector<vector<int>>&input_clause,vector<int>my_scc,vector<int>&inputs,vector<vector<int>>&clauses){
    if(gates[idx]->_gateType=="wire")return;
    auto g =gates[idx];
    int in1,in2,out=0;
    in1=wires2idx(vars,wire2var,gates[g->_instNodes_in[0]]->_instName,solver,output_clause,input_clause);
    out=wires2idx(vars,wire2var,gates[g->_instNodes_out[0]]->_instName,solver,output_clause,input_clause);   
    if(g->_gateType!="not1")in2=wires2idx(vars,wire2var,gates[g->_instNodes_in[1]]->_instName,solver,output_clause,input_clause);
    if(!my_scc[g->_instNodes_in[0]])inputs.push_back(in1);
    if(g->_gateType!="not1"&&!my_scc[g->_instNodes_in[1]])inputs.push_back(in2);
    unordered_map<string,int>tmp={{"not1",0},{"and2",1},{"nand2",2},{"or2",3},{"nor2",4}};
    if(tmp.find(g->_gateType)==tmp.end())return;
    if(g->_gateType=="not1"){
        output_clause[out+1].push_back(clauses.size());
        output_clause[out+1].push_back(clauses.size()+1);
        input_clause[in1+1].push_back(clauses.size());
        input_clause[in1+1].push_back(clauses.size()+1);
    }else{
        output_clause[out+1].push_back(clauses.size());
        output_clause[out+1].push_back(clauses.size()+1);
        output_clause[out+1].push_back(clauses.size()+2);
        input_clause[in1+1].push_back(clauses.size());
        input_clause[in1+1].push_back(clauses.size()+2);
        input_clause[in2+1].push_back(clauses.size()+1);
        input_clause[in2+1].push_back(clauses.size()+2);
    }
    switch (tmp[g->_gateType])
    {
    case 0:
        clauses.push_back({-(in1+1),-(out+1)});
        clauses.push_back({in1+1,out+1});
        break;
    case 1:
        clauses.push_back({in1+1,-(out+1)});
        clauses.push_back({in2+1,-(out+1)});
        clauses.push_back({-(in1+1),-(in2+1),out+1});
        break;
    case 2:
        clauses.push_back({in1+1,out+1});
        clauses.push_back({in2+1,out+1});
        clauses.push_back({-(in1+1),-(in2+1),-(out+1)});
    break;
    case 3:
        clauses.push_back({-(in1+1),out+1});
        clauses.push_back({-(in2+1),out+1});
        clauses.push_back({in1+1,in2+1,-(out+1)});
        break;
    default:
        clauses.push_back({-(in1+1),-(out+1)});
        clauses.push_back({-(in2+1),-(out+1)});
        clauses.push_back({in1+1,in2+1,out+1});
        break;
    }

    return;
}

vector<int>visit;
static void dfs(int x,GateInstVec gates,Minisat::Solver &solver,vector<Minisat::Var>&vars,unordered_map<string,int>&wire2var,vector<vector<int>>&output_clause,vector<vector<int>>&input_clause,vector<int>my_scc,vector<int>&inputs,vector<vector<int>>&clauses){
    visit[x]=1;
    addgates(x,gates,solver,vars,wire2var,output_clause,input_clause,my_scc,inputs,clauses);
    for(int out:gates[x]->_instNodes_out){
        if(visit[out]||!my_scc[out])continue;
        dfs(out,gates,solver,vars,wire2var,output_clause,input_clause,my_scc,inputs,clauses);
    }
}

static int cutinput(int idx,GateInstVec gates,Minisat::Solver &solver,vector<Minisat::Var>&vars,unordered_map<string,int>&wire2var,vector<vector<int>>&output_clause,vector<vector<int>>&clauses){
    //断开output
    vars.push_back(solver.newVar());
    wire2var["cut"]=vars.size()-1;
    int index=wire2var[gates[idx]->_instName];
    for(auto clau:output_clause[index+1]){
        int &x=clauses[clau][clauses[clau].size()-1];
        if(abs(x)==index+1)x=(x>0)?vars.size():-(vars.size());
    }
    return vars.size()-1;
}

static int cutoutput(int gate_idx,int wire_idx,GateInstVec gates,Minisat::Solver &solver,vector<Minisat::Var>&vars,unordered_map<string,int>&wire2var,vector<vector<int>>&input_clause,vector<vector<int>>&clauses){
    //断开input
    vars.push_back(solver.newVar());
    wire2var["cut"]=vars.size()-1;
    int index=wire2var[gates[wire_idx]->_instName];
    int output_index=wire2var[gates[gates[gate_idx]->_instNodes_out[0]]->_instName];
    for(auto clau:input_clause[index+1]){
        if(abs(clauses[clau][clauses[clau].size()-1])==output_index+1){
            for(int i=0;i<clauses[clau].size()-1;i++){
                int &x=clauses[clau][i];
                if(abs(x)==index+1)x=(x>0)?vars.size():-(vars.size());
            }
        }
    }
    return vars.size()-1;
}

static inline void addlit(int x,vector<Minisat::Var>&vars,Minisat::vec<Minisat::Lit>&clause){
    if(x>0)clause.push(Minisat::mkLit(vars[abs(x)-1]));
    else clause.push(Minisat::mkLit(vars[abs(x)-1],1));
}

static void addlogic(Minisat::Solver &solver,vector<int>param,string type,vector<Minisat::Var>&vars,Minisat::vec<Minisat::Lit>&clause){
    int x=param[0];int a=param[1];int b=param[2];
    if(type=="and4"){
        int c=param[3];int d=param[4];
        addlit(a,vars,clause);addlit(-x,vars,clause);
        solver.addClause(clause);clause.clear();
        addlit(b,vars,clause);addlit(-x,vars,clause);
        solver.addClause(clause);clause.clear();
        addlit(c,vars,clause);addlit(-x,vars,clause);
        solver.addClause(clause);clause.clear();
        addlit(d,vars,clause);addlit(-x,vars,clause);
        solver.addClause(clause);clause.clear();
        addlit(-a,vars,clause);addlit(-b,vars,clause);addlit(-c,vars,clause);addlit(-d,vars,clause);addlit(x,vars,clause);
        solver.addClause(clause);clause.clear();
        return;
    }else if(type=="and2"){
        addlit(a,vars,clause);addlit(-x,vars,clause);
        solver.addClause(clause);clause.clear();
        addlit(b,vars,clause);addlit(-x,vars,clause);
        solver.addClause(clause);clause.clear();
        addlit(-a,vars,clause);addlit(-b,vars,clause);addlit(x,vars,clause);
        solver.addClause(clause);clause.clear();
        return;
    }else if(type=="or2"){
        addlit(-a,vars,clause);addlit(x,vars,clause);
        solver.addClause(clause);clause.clear();
        addlit(-b,vars,clause);addlit(x,vars,clause);
        solver.addClause(clause);clause.clear();
        addlit(a,vars,clause);addlit(b,vars,clause);addlit(-x,vars,clause);
        solver.addClause(clause);clause.clear();
        return;
    }
}

static void buildsat(Minisat::Solver &solver,vector<int>wires,vector<int>cut_gates,GateInstVec gates,int type,vector<Minisat::Var>&vars,Minisat::vec<Minisat::Lit>&clause,unordered_map<string,int>&wire2var,vector<vector<int>>&input_clause,vector<vector<int>>&output_clause,vector<vector<int>>&clauses,vector<int>&inputs){
    if(!wires.size())return;
    //如果wire中只有一个idx，那么只断开一条边
    vector<int>index;
    if(type==0){
            //type为0的时候，断开output
        for(int i=0;i<wires.size();i++){
            index.push_back(cutinput(wires[i],gates,solver,vars,wire2var,output_clause,clauses));
        }
    }else{
            //type为1的时候，断开input
        for(int i=0;i<wires.size();i++){
            index.push_back(cutoutput(cut_gates[i],wires[i],gates,solver,vars,wire2var,input_clause,clauses));
        }
    }
    //重复电路
    int num=vars.size();
    for(int i=0;i<num;i++)vars.push_back(solver.newVar());
    int cnt=0;
    for(auto clau:clauses){
        for(int lit:clau){
            Minisat::Lit tmp=(lit>0)?Minisat::mkLit(vars[lit-1]):Minisat::mkLit(vars[-lit-1],1);
            int t=(lit>0)?(lit):-(-lit);
            clause.push(tmp);
        }
        solver.addClause(clause);
        clause.clear();
    }
    for(auto clau:clauses){
        for(int lit:clau){
            Minisat::Lit tmp=(lit>0)?Minisat::mkLit(vars[lit-1+num]):Minisat::mkLit(vars[-lit-1+num],1);
            int t=(lit>0)?(lit+num):-(-lit+num);
            clause.push(tmp);
        }
        solver.addClause(clause);
        clause.clear();
    }
    //添加input ports相等
    for(int input:inputs){
        clause.push(Minisat::mkLit(vars[input],1));
        clause.push(Minisat::mkLit(vars[input+num]));
        solver.addClause(clause);
        clause.clear();
        clause.push(Minisat::mkLit(vars[input]));
        clause.push(Minisat::mkLit(vars[input+num],1));
        solver.addClause(clause);
        clause.clear();
    }
    vector<int>myands;//用来记录每个震荡模式
    for(int i=0;i<wires.size();i++){
        int x=vars.size()+1;
        myands.push_back(x);
        vars.push_back(solver.newVar());
        int a=wire2var[gates[wires[i]]->_instName]+1;
        int b=index[i]+1;
        int c=a+num;
        int d=index[i]+num+1;
        vector<int>param1{x,a,-b,-c,d};
        addlogic(solver,param1,"and4",vars,clause);
        x=vars.size()+1;
        myands.push_back(x);
        vars.push_back(solver.newVar());
        vector<int>param2{x,-a,b,c,-d};
        addlogic(solver,param2,"and4",vars,clause);
    }
    //无论如何，第一个条件都是需要的
    addlit(myands[0],vars,clause);
    solver.addClause(clause);
    clause.clear();
    //对于size不同的门，需要分块考虑
    switch (wires.size())
    {
    {case 1:
        //myands中有两个条件，一个条件满足即可,默认为myands[0]
        break;}
    {case 2:
        //myands中有四个条件，需要a(c+d)满足
        int x=vars.size()+1;
        vars.push_back(solver.newVar());
        vector<int>param{x,myands[2],myands[3]};
        addlogic(solver,param,"or2",vars,clause);
        addlit(x,vars,clause);
        solver.addClause(clause);clause.clear();
        break;}
    {default:
        //myands中有6个条件，需要a(ce+cf+de+df)满足
        //4个与
        vector<int>ands;
        for(int i=0;i<4;i++){
            ands.push_back(vars.size()+1);
            vars.push_back(solver.newVar());
            vector<int>param{ands[i],myands[2+i/2],myands[4+i%2]};
            addlogic(solver,param,"and2",vars,clause);
        }
        int out=vars.size()+1;
        vars.push_back(solver.newVar());
        for(auto node:ands){
            addlit(-node,vars,clause);addlit(out,vars,clause);
            solver.addClause(clause);clause.clear();     
        }
        addlit(-out,vars,clause);
        for(auto node:ands){addlit(node,vars,clause);}
        solver.addClause(clause);clause.clear();
        addlit(out,vars,clause);
        solver.addClause(clause);clause.clear();
        break;}
    }
}

//寻找不震荡环路的最大可能震荡门的数目，并记录条件
static int gatesearch(GateInstVec gates,vector<int>path,int value,int start_wire,vector<int>sources,vector<int>drains,vector<string>&condition){
    int cnt=0;
    int need_value=value;
    bool satisfied=0;
    stack<int>q;
    q.push(start_wire);
    while(!q.empty()){
        int x=q.top();
        q.pop();
        if(!satisfied){
            switch (need_value)
            {
            case 0:
                if(gates[x]->_gateType=="and2"||gates[x]->_gateType=="nor2"){
                    satisfied=1;
                    for(int in:gates[x]->_instNodes_in)if(!path[in]){
                        stringstream ss;
                        ss<<gates[x]->_instName<<".port"<<gates[x]->port_direct[in];
                        if(gates[x]->_gateType=="and2")ss<<"=0";
                        else ss<<"=1";
                        condition.push_back(ss.str());
                    }
                }
                break;
            
            default:
                if(gates[x]->_gateType=="nand2"||gates[x]->_gateType=="or2"){
                    satisfied=1;
                    for(int in:gates[x]->_instNodes_in)if(!path[in]){
                        stringstream ss;
                        ss<<gates[x]->_instName<<".port"<<gates[x]->port_direct[in];
                        if(gates[x]->_gateType=="nand2")ss<<"=0";
                        else ss<<"=1";
                        condition.push_back(ss.str());
                    }
                }
                break;
            }
        }else{
            if(gates[x]->_gateType!="wire")cnt++;
            if(gates[x]->_gateType!="not"&&gates[x]->_gateType!="wire"){
                //如果两个输入端有一个在drain里面，那么就终止
                if(drains[gates[x]->_instNodes_in[0]]||drains[gates[x]->_instNodes_in[1]])break;
                for(int in:gates[x]->_instNodes_in)if(!path[in]){

                    stringstream ss;
                    ss<<gates[x]->_instName<<".port"<<gates[x]->port_direct[in];
                    if(gates[x]->_gateType=="nand2"||gates[x]->_gateType=="and2")ss<<"=1";
                    else ss<<"=0";
                    condition.push_back(ss.str());
                }
            }
            if(gates[x]->_gateType[0]=='n')need_value=1-need_value;
        }
        int flag=0;
        for(int v:gates[x]->_instNodes_in){
            if(sources[v]){flag=1;break;}
            if(path[v])q.push(v);
        }
        if(flag)break;
    }

    return cnt;
}

static void copysolver(Minisat::Solver &solver,vector<vector<int>>myclauses,vector<Minisat::Var>&vars,Minisat::vec<Minisat::Lit>&clause){
    vector<Minisat::Var>newvars;
    for(int i=0;i<vars.size();i++)newvars.push_back(solver.newVar());
    //复制
    for(auto clau:myclauses){
        for(int lit:clau){
            Minisat::Lit tmp=(lit>0)?Minisat::mkLit(vars[lit-1]):Minisat::mkLit(vars[-lit-1],1);
            int t=(lit>0)?(lit):-(-lit);
            clause.push(tmp);
        }
        solver.addClause(clause);
        clause.clear();
    }
    return;
}

static int solve_2_rings(int vars_size_cnt,vector<int>drain,GateInstVec gates,vector<int>scc,vector<vector<string>>&conditions,unordered_map<int,vector<int>>match_circles,vector<vector<int>>circles,vector<int>sources,vector<Minisat::Var>&vars,Minisat::vec<Minisat::Lit>&clause,unordered_map<string,int>&wire2var,vector<vector<int>>&input_clause,vector<vector<int>>&output_clause,vector<vector<int>>&clauses,vector<int>&inputs){
    //先构造一个drain的查找表drains
    vector<int>drains(gates.size(),0);
    for(int node:drain)drains[node]=1;

    Minisat::Solver solver;
    vars.clear();
    for(int i=0;i<vars_size_cnt;i++)vars.push_back(solver.newVar());
    vector<vector<int>>clauses_copy=clauses;
    vector<int>cut_gate;
    for(int node:drain){
        for(int out:gates[node]->_instNodes_out){
            if(scc[out]){
                cut_gate.push_back(out);
                break;
            }
        }
    }
    buildsat(solver,drain,cut_gate,gates,1,vars,clause,wire2var,input_clause,output_clause,clauses,inputs);
    if(solver.solve()){
        vector<string>condition;
        int cnt=0;
        for(int i=0;i<scc.size();i++){
            if(!scc[i])continue;
            if(gates[i]->_gateType=="wire")continue;
            cnt++;
            for(int input:gates[i]->_instNodes_in){
                if(!scc[input]){
                    if(gates[i]->_gateType=="not1")continue;
                    stringstream ss;
                    ss<<gates[i]->_instName<<".port"<<gates[i]->port_direct[input];
                    if(gates[i]->_gateType=="nand2"||gates[i]->_gateType=="and2")ss<<"=1";
                    else ss<<"=0";
                    condition.push_back(ss.str());
                }
            }
        }
        conditions.push_back(condition);
        return cnt;
    }
    vector<int>cnt;
    vector<vector<string>>conditions_tmp;
    for(int wire:drain){
        vars.clear();
        Minisat::Solver solver1;
        for(int i=0;i<vars_size_cnt;i++)vars.push_back(solver1.newVar());
        clauses=clauses_copy;
        buildsat(solver1,vector<int>{wire},vector<int>{cut_gate},gates,1,vars,clause,wire2var,input_clause,output_clause,clauses,inputs);
        vector<string>condition;
        if(solver1.solve()){
            int start_gate=0;
            for(int out:gates[wire]->_instNodes_out)if(scc[out]){
                int c=0;
                for(int in:gates[out]->_instNodes_in)if(scc[in])c++;
                if(c==2){start_gate=out;break;}
            }
            int start_wire=(gates[start_gate]->_instNodes_in[0]==wire)?gates[start_gate]->_instNodes_in[1]:gates[start_gate]->_instNodes_in[0];
            int value=(gates[start_gate]->_gateType=="and2"||gates[start_gate]->_gateType=="nand2")?1:0;
            int cnt1=gatesearch(gates,circles[match_circles[start_wire][0]],value,start_wire,sources,drains,condition);
            stack<int>q;
            q.push(start_gate);
            int idx=match_circles[wire][0];
            int cnt3=0;

            vector<int>visit(gates.size(),0);
            
            while(!q.empty()){
                int x=q.top();
                visit[x]=1;
                q.pop();
                if(gates[x]->_gateType!="wire"){
                    cnt3++;
                    if(gates[x]->_gateType!="not1"){
                        for(int input:gates[x]->_instNodes_in)if(!scc[input]){
                            stringstream ss;
                            ss<<gates[x]->_instName<<".port"<<gates[x]->port_direct[input];
                            if(gates[x]->_gateType=="nand2"||gates[x]->_gateType=="and2")ss<<"=1";
                            else ss<<"=0";
                            condition.push_back(ss.str());
                        }
                    }
                }
                int flag=0;
                for(int out:gates[x]->_instNodes_out){
                    if(circles[idx][out]&&!visit[out])q.push(out);
                }
            }
            cnt.push_back(cnt1+cnt3);
            conditions_tmp.push_back(condition);
        }
    }

    if(cnt.size()==0){
        return -1;
    }
    if(cnt.size()==1){
        conditions.push_back(conditions_tmp[0]);
        return cnt[0];
    }else{
        if(cnt[0]>cnt[1]){
            conditions.push_back(conditions_tmp[0]);
            return cnt[0];
        }else if(cnt[0]<cnt[1]){
            conditions.push_back(conditions_tmp[1]);
            return cnt[1];
        }else{
            conditions.push_back(conditions_tmp[0]);
            conditions.push_back(conditions_tmp[1]);
            return cnt[1];
        }
    }
}

static void solve_3_rings(vector<vector<string>>&conditions,int vars_size_cnt, vector<int>drain,vector<int>scc,GateInstVec gates,unordered_map<int,vector<int>>match_circles,vector<vector<int>>circles,vector<int>sources,vector<Minisat::Var>&vars,Minisat::vec<Minisat::Lit>&clause,unordered_map<string,int>&wire2var,vector<vector<int>>&input_clause,vector<vector<int>>&output_clause,vector<vector<int>>&clauses,vector<int>&inputs){
   //目前是只找三种情况的一个震荡环，不进行比较
    //drain查找表
    vector<int >drains(gates.size(),0);
    for( int node:drain)drains[node]=1;
    //首先,建立四个点的震荡影响关系表和震荡传递关系表
    //震荡关系表指的是，某节点震荡则一定能判断震荡的节点表，通过match_circles中的搜索实现
    unordered_map<int,vector<int>>ring_effect(drain.size());
    vector<vector<int>>tmp(circles.size());
    for(auto it:match_circles){
        int node=it.first;
        for(int circle:it.second){
            tmp[circle].push_back(node);
        }
    }
    for(int node:drain){
        for(int circle:match_circles[node]){
            for(int other:tmp[circle])if(other!=node)ring_effect[node].push_back(other);
        }
    }
    //震荡传递关系表指的是某个节点通过一个非确定两输入门能够影响的节点集合，通过dfs实现(建立栈来实现dfs)
    unordered_map<int,vector<int>>ring_trans(drain.size());
    vector<int>ugates;
    for(int wire:drain){
        stack<pair<int,int>>s;//前者存点数目，后者存已经经过的两输入非确定门的数目
        s.push({wire,0});
        while(!s.empty()){
            auto it=s.top();s.pop();
            int x=it.first;int num=it.second;
            if(drains[x]){
                ring_trans[wire].push_back(x);
                continue;
            }
            if(gates[x]->_instNodes_in.size()==2)if(scc[gates[x]->_instNodes_in[0]]&&scc[gates[x]->_instNodes_in[1]]){num++;ugates.push_back(x);}
            if(num==2)continue;
            for(int node:gates[x]->_instNodes_out)if(scc[node]){
                s.push({node,num});
            }
        }
    }
    //建立非确定门信息表，包括输入节点和门的type
    unordered_map<int,pair<int,string>>message;
    unordered_map<int,int>match_gate;
    for(int gate:ugates){
        int a=gates[gate]->_instNodes_in[0];
        int b=gates[gate]->_instNodes_in[1];
        string type=gates[gate]->_gateType;
        if(message.find(a)==message.end())message[a]={b,type};
        if(message.find(b)==message.end())message[b]={a,type};
        if(match_gate.find(a)==match_gate.end())match_gate[a]=gate;
        if(match_gate.find(b)==match_gate.end())match_gate[b]=gate;
    }
    //寻找做sat的三个drain节点
    vector<int>choose;
    vector<int>visited(circles.size(),0);
    for(int node:drain){
        if(choose.size()==3)break;
        if(match_circles[node].size()==2)continue;
        int flag=0;
        for(int circle:match_circles[node]){if(visited[circle]){flag=1;break;}}
        if(flag)continue;
        choose.push_back(node);
        for(int circle:match_circles[node])visited[circle]=1;
    }
    if(choose.size()!=3){{return ;}}
    //做第一次sat，判断三个环能否同时震荡
    Minisat::Solver solver;
    vars.clear();
    for(int i=0;i<vars_size_cnt;i++)vars.push_back(solver.newVar());
    vector<vector<int>>clauses_copy=clauses;
    vector<int>cut_gate;
    for(int wire:choose)cut_gate.push_back(match_gate[wire]);
    buildsat(solver,choose,cut_gate,gates,1,vars,clause,wire2var,input_clause,output_clause,clauses,inputs);
    if(solver.solve()){
        //sat 说明可以继续搜，但是此时需要判断整个环路能不能同时震荡，需要将剩余的一个drain和相关的port相连，再进行求解
        Minisat::Solver solver1;
        vars.clear();
        for(int i=0;i<vars_size_cnt;i++)vars.push_back(solver1.newVar());
        clauses=clauses_copy;
        //寻找空闲边
        int free=0;
        visited.assign(gates.size(),0);
        for(int node:choose)visited[node]=1;
        for(int node:drain)if(!visited[free]){free=node;break;}
        int var1=wire2var[gates[free]->_instName]+1;
        int var2=wire2var[gates[message[free].first]->_instName]+1;
        //添加子句，使得var1和var2相等
        clauses.push_back({var1,-var2});clauses.push_back({-var1,var2});
        buildsat(solver1,choose,cut_gate,gates,1,vars,clause,wire2var,input_clause,output_clause,clauses,inputs);
        int cnt=0;
        if(solver1.solve()){
            vector<string>condition;
            for(int i=0;i<scc.size();i++){
                if(!scc[i])continue;
                if(gates[i]->_gateType=="wire")continue;
                cnt++;
                for(int input:gates[i]->_instNodes_in){
                    if(!scc[input]){
                        if(gates[i]->_gateType=="not1")continue;
                        stringstream ss;
                        ss<<gates[i]->_instName<<".port"<<gates[i]->port_direct[input];
                        if(gates[i]->_gateType=="nand2"||gates[i]->_gateType=="and2")ss<<"=1";
                        else ss<<"=0";
                        condition.push_back(ss.str());
                    }
                }
            }
            conditions.push_back(condition);
            return;
        }else{
            vector<string>condition;
            gatesearch(gates,circles[match_circles[free][0]],match_gate[free],free,sources,drains,condition);
            vector<int>scc_copy=scc;
            stack<int>q;
            q.push(match_gate[free]);
            while(!q.empty()){
                int x=q.top();
                q.pop();
                scc_copy[x]=0;
                if(drains[x])continue;
                if(sources[x])break;
                for(int out:gates[x]->_instNodes_out)if(scc[out])q.push(out);
            }
            for(int i=0;i<scc_copy.size();i++){
                if(scc_copy[i])continue;
                if(gates[i]->_gateType=="wire")continue;
                cnt++;
                for(int input:gates[i]->_instNodes_in){
                    if(!scc_copy[input]){
                        if(gates[i]->_gateType=="not1")continue;
                        stringstream ss;
                        ss<<gates[i]->_instName<<".port"<<gates[i]->port_direct[input];
                        if(gates[i]->_gateType=="nand2"||gates[i]->_gateType=="and2")ss<<"=1";
                        else ss<<"=0";
                        condition.push_back(ss.str());
                    }
                }
            }
            conditions.push_back(condition);
            return;
        }
    }
    
    //三环不符合，需要选两环，使用solve_2_rings函数
    vars.clear();
    clauses=clauses_copy;
    vector<pair<int,int>>per={{0,1},{0,2},{0,3},{1,2},{1,3},{2,3}};
    vector<vector<string>>conditions_tmp;
    int max=0;
    for(auto it:per){
        vector<int>tmp;
        tmp.push_back(drain[it.first]);
        tmp.push_back(drain[it.second]);
        clauses=clauses_copy;
        int cnt=solve_2_rings(vars_size_cnt,tmp,gates,scc,conditions_tmp,match_circles,circles,sources,vars,clause,wire2var,input_clause,output_clause,clauses,inputs);
        if(max<cnt){
            max=cnt;
            conditions=conditions_tmp;
        }
    }
   return;
}

bool solve_ring(vector<int>scc,vector<vector<int>>circles_lut,GateInstVec old_gates,vector<int>source,vector<int>drain,vector<int>&buffer,vector<vector<string>>&conditions){
    vector<bool>sat_situation;//用来记录sat情况的数组
    vector<int>wires=source;
    //针对一个port，需要知道它是属于哪个环的,但是在gatesearch函数中使用的时候，只需要知道其属于的一个环即可，所以使用map进行匹配
    unordered_map<int,vector<int>>match_circles;
    for(int node:drain){
        for(int i=0;i<circles_lut.size();i++)if(circles_lut[i][node]){match_circles[node].push_back(i);break;}
    }
    //建立一个关于source的查询表为sources
    vector<int>sources(old_gates.size(),0);
    for(int node:source)sources[node]=1;
    //复制一份gates
    GateInstVec gates;
    gates.reserve(old_gates.size());  // 预分配空间以提高效率
    for (GateInst* ptr : old_gates) {
        GateInst* newgate = new GateInst(*ptr);  // 分配新内存并复制值
        gates.push_back(newgate);
    }
    vector<Minisat::Var> vars;
    Minisat::vec<Minisat::Lit>clause;
    unordered_map<string,int>wire2var;
    vector<vector<int>>clauses;
    vector<int>inputs;
    vector<int>my_scc;
    vector<vector<int>>output_clause,input_clause;
    Minisat::Solver solver;
    visit.assign(gates.size(),0);
    my_scc=scc;
    //通过dfs来添加电路
    dfs(wires[0],gates,solver,vars,wire2var,output_clause,input_clause,my_scc,inputs,clauses);
    vector<vector<int>>clauses_copy=clauses;
    int vars_size_cnt=vars.size();
    buildsat(solver,wires,vector<int>{},gates,0,vars,clause,wire2var,input_clause,output_clause,clauses,inputs);
    bool sat = solver.solve();
    sat_situation.push_back(sat);
    if(!sat&&wires.size()>1){
        for(int wire:wires){
            Minisat::Solver solver1;
            vars.clear();
            for(int i=0;i<vars_size_cnt;i++)vars.push_back(solver1.newVar());
            clauses=clauses_copy;
            buildsat(solver1,vector<int>{wire},vector<int>{},gates,0,vars,clause,wire2var,input_clause,output_clause,clauses,inputs);
            bool sat_=solver1.solve();
            sat_situation.push_back(sat_);
            sat|=sat_;
        }
    }
    if(sat){
        if(circles_lut.size()==2){
            buffer.push_back(source[0]);
        }else{
            if(!sat_situation[0]&&sat_situation[1]&&!sat_situation[2])buffer.push_back(source[0]);
            else if(!sat_situation[0]&&sat_situation[2]&&!sat_situation[1])buffer.push_back(source[1]);
            else if(!sat_situation[0]&&sat_situation[1]&&sat_situation[2]){
                buffer.push_back(source[0]);
                buffer.push_back(source[1]);
            }else{
                //如果三环同时震荡，那么可以需要判断插一个buffer能不能解决
                int s1=source[0];int s2=source[1];
                //断开s1,判断s2能不能震荡
                Minisat::Solver solver1;
                vars.clear();
                for(int i=0;i<vars_size_cnt;i++)vars.push_back(solver1.newVar());
                clauses=clauses_copy;
                cutinput(s1,gates,solver1,vars,wire2var,output_clause,clauses);
                buildsat(solver1,vector<int>{s2},vector<int>{},gates,0,vars,clause,wire2var,input_clause,output_clause,clauses,inputs);
                if(!solver1.solve()){
                    buffer.push_back(s1);
                }else{
                    //断开s2.判断s1能不能震荡
                    Minisat::Solver solver2;
                    vars.clear();
                    for(int i=0;i<vars_size_cnt;i++)vars.push_back(solver2.newVar());
                    clauses=clauses_copy;
                    cutinput(s2,gates,solver2,vars,wire2var,output_clause,clauses);
                    buildsat(solver2,vector<int>{s1},vector<int>{},gates,0,vars,clause,wire2var,input_clause,output_clause,clauses,inputs);
                    if(!solver2.solve()){
                        buffer.push_back(s2);
                    }else{
                        buffer.push_back(s1);
                        buffer.push_back(s2);
                    }
                }
            }
        }
    }
    
    if(sat){
    clauses=clauses_copy;
    if(drain.size()==2)solve_2_rings(vars_size_cnt,drain,gates,scc,conditions,match_circles,circles_lut,sources,vars,clause,wire2var,input_clause,output_clause,clauses,inputs);
    else solve_3_rings(conditions,vars_size_cnt,drain,scc,gates,match_circles,circles_lut,sources,vars,clause,wire2var,input_clause,output_clause,clauses,inputs);
    }
    vars.clear();
    clause.clear();
    wire2var.clear();
    clauses.clear();
    inputs.clear();
    my_scc.clear();
    output_clause.clear();
    input_clause.clear();
    return sat;
}
