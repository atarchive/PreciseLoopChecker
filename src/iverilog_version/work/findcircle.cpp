#include"findcircle.h"
#include<stack>
#include<thread>
#include <mutex>
#include <algorithm>
#include<chrono>
#include<iostream>
#include<fstream>
#include<unordered_map>
using namespace std;
//created by ycy 10/16/2024
//使用Johnson算法寻找所有可能的环路
//Tarjan's SCC算法，用于缩点
vector<vector<int> >sccs;//用于保存所有的强连通分量，但注意,为了方便后面寻找环路，每个vector<int>中，将同属于一个scc的点设为了1，其他为0,并且为了方便寻找可行的节点
vector<vector<int>>my_sccs;//所有强连通分量的第一个点
vector<int>low;
vector<int>indx;
vector<bool>onstack;//用来反映节点是否在栈里
stack<int>s;//用栈来存储dfs的节点，当寻找到强连通分量时其父节点必然在当前节点的栈底

int currentidx = 0;
static void dfs(int i, const GateInstVec& gates);
static void findSCC(const GateInstVec& gates) {
    low.assign(gates.size(), -1);
    indx.assign(gates.size(), -1);
    onstack.assign(gates.size(), 0);
    currentidx = 0;
    for (size_t i = 0; i < gates.size(); i++)if (indx[i] == -1)dfs(i, gates);
    //for (size_t i = 0; i < sccs.size(); i++)cout << sccs[i][85] << endl;
}

static void dfs(int i, const GateInstVec& gates) {
    low[i] = indx[i] = currentidx++;
    s.push(i);
    onstack[i] = 1;
    for (size_t j = 0; j < gates[i]->_instNodes_out.size(); j++) {
        int v = gates[i]->_instNodes_out[j];
        if (indx[v] == -1) {
            dfs(v, gates);
            low[i] = min(low[i], low[v]);
        }
        else if (onstack[v])low[i] = min(low[i], indx[v]);
    }
    if (indx[i] == low[i]) {
        int cnt = 0;
        vector<int>scc(gates.size(), 0);
        vector<int>my_scc;
        while (true) {
            cnt++;
            int x = s.top();
            s.pop();
            onstack[x] = 0;
            scc[x] = 1;
            my_scc.push_back(x);
            if (x == i)break;
        }
        if (cnt != 1) {
            sccs.push_back(scc);
            my_sccs.push_back(my_scc);
        }
    }
}

//使用Johnson算法，需要使用两个数据结构block和B，用来防止搜索错误和搜索效率低下，并且需要一个二维向量存储寻找到的环
mutex mtx;

static void unblock(vector<int>& block, vector<vector<int> >& B, int v);
static bool dfsCircle(int scc_idx,GateInstVec gates, vector<vector<vector<int> >>& scc_circles,vector<vector<vector<int>>>&circles_lut, vector<int>& block, vector<vector<int> >& B, stack<int>& s, vector<int>scc, int v);
static void findSccCircle(int scc_idx,vector<int>scc, int start, GateInstVec gates, vector<vector<vector<int>>>& circles,vector<vector<vector<int>>>&circles_lut) {//用于寻找到所有强连通分量中，以初始点开始的环
    vector<int>block;
    vector<vector<int> >B;
    stack<int>s;
    block.assign(gates.size(), 0);
    B.assign(gates.size(), vector<int>());
    dfsCircle(scc_idx,gates, circles, circles_lut,block, B, s, scc, start);
}
static bool dfsCircle(int scc_idx,GateInstVec gates, vector<vector<vector<int> >>& circles,vector<vector<vector<int>>>&circles_lut, vector<int>& block, vector<vector<int> >& B, stack<int>& s, vector<int>scc, int v) {
    //os << _glbNetlistModule._instVec[start]->_instName << " " << _glbNetlistModule._instVec[v]->_instName << endl;;
    block[v] = true;
    s.push(v);
    bool found = false;
    for (size_t i = 0; i < gates[v]->_instNodes_out.size(); i++) {
        if (!scc[gates[v]->_instNodes_out[i]])continue;
        int w = gates[v]->_instNodes_out[i];
        if (block[w]) {
            stack<int>temps = s;
            vector<int>circle;
            vector<int>circle_lut(gates.size(),0);
            while (1) {
                circle.push_back(temps.top());
                circle_lut[temps.top()]=1;
                if (temps.top() == w)break;
                temps.pop();
            }
            reverse(circle.begin(), circle.end());
            {
                mtx.lock();
                circles[scc_idx].push_back(circle);
                circles_lut[scc_idx].push_back(circle_lut);
                mtx.unlock();
            }
            found = true;
        }
        else {
            if (dfsCircle(scc_idx,gates, circles, circles_lut,block, B, s, scc, w))found = true;
        }
    }
    if (found)unblock(block, B, v);
    else {
        for (size_t i = 0; i < gates[v]->_instNodes_out.size(); i++) {
            if (!scc[gates[v]->_instNodes_out[i]])B[v].push_back(gates[v]->_instNodes_out[i]);
        }
    }
    s.pop();
    return found;
}
static void unblock(vector<int>& block, vector<vector<int> >& B, int v) {
    block[v] = false;
    while (!B[v].empty()) {
        int w = B[v].back();
        B[v].pop_back();
        if (block[w])unblock(block, B, w);
    }
}

void findAllScc(vector<vector<int>>& scc, GateInstVec gates,vector<vector<int>>&source,vector<vector<int>>&drain,vector<vector<int>>&my_scc,vector<vector<vector<int>>>&circles,vector<vector<vector<int>>>&circles_lut) {
    findSCC(gates);
    circles.resize(sccs.size());
    circles_lut.resize(sccs.size());
    for (size_t i = 0; i < sccs.size(); i++){
        findSccCircle(i, sccs[i], my_sccs[i][0], gates, std::ref(circles),std::ref(circles_lut));
    }
    source.resize(sccs.size());
    drain.resize(sccs.size());
    for(int i=0;i<sccs.size();i++){
        for(int node:my_sccs[i]){
            if(gates[node]->_gateType=="wire"&&gates[node]->_instNodes_out.size()>1){
                int cnt=0;
                for(auto x:gates[node]->_instNodes_out)if(sccs[i][x])cnt++;
                if(cnt>1)source[i].push_back(node);
            }
            if(gates[node]->_gateType!="wire"&&gates[node]->_gateType!="not1"){
                if(sccs[i][gates[node]->_instNodes_in[0]]&&sccs[i][gates[node]->_instNodes_in[1]]){
                    drain[i].push_back(gates[node]->_instNodes_in[0]);
                    drain[i].push_back(gates[node]->_instNodes_in[1]);
                }
            }
        }
    }
    scc=sccs;
    my_scc=my_sccs;
    return;
}




