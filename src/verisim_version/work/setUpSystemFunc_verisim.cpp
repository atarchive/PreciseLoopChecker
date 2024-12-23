
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include <thread>
#include <mutex>
#include"datatype.h"
#include"findcircle.h"//找强连通分量，分circle
#include"writeresult.h"//写到result
#include"solver.h"//核心函数，第二三四题
#include<chrono>
using namespace std;


NetlistModule _glbNetlistModule;
//打印网表名称，打印网表所含实例的信息

void printModInfo()
{
    printf("module name is %s\n", _glbNetlistModule._moduelName.c_str());
    _glbNetlistModule.dumpInst();
}

vector<vector<int>>scc;
vector<vector<int>>my_scc_;
//检测不可能发生持续震荡的逻辑环，那么这条路上，n系列加起来是偶数
vector<int>cannot_ring_circle;
void detect_ring(int i) {
    int cnt = 0;
    for (size_t j = 0; j <my_scc_[i].size(); j++) {
        string type = _glbNetlistModule._instVec[my_scc_[i][j]]->_gateType;
        if (type == "not1" || type == "nand2" || type == "nor2")cnt++;
    }
    if (cnt % 2 == 0) cannot_ring_circle[i]=1;
}
mutex mtx1;
void process(int i,vector<int>scc,vector<vector<int>>circles_lut,vector<int>source,vector<int>drain,GateInstVec gates,unordered_map<int,vector<string>>&buffers,unordered_map<int,vector<vector<string>>>&conditions){
    vector<int>buffer;
    vector<vector<string>>conditions_tmp;
    bool flag=solve_ring(scc,circles_lut,gates,source,drain,buffer,conditions_tmp);
    if(!flag){
        std::lock_guard<std::mutex> lock(mtx1);
        cannot_ring_circle[i]=1;
    }else{
        std::lock_guard<std::mutex> lock(mtx1);
        for(int wire:buffer)buffers[i].push_back(gates[wire]->_instName);
        conditions[i]=conditions_tmp;
    }
}

//created by ycy 10/13/2024

//保证对C的兼容性
#ifdef  __cplusplus
extern "C" {
#endif
    //使用了 VPI（Verilog Procedural Interface）API 来获取 Verilog 仿真中的模块、实例以及端口信息，并将其存储到自定义的 C++ 类 NetlistModule 和 GateInst 中
    //录入信息建立map<string,int>，用于将inst名称和对应的门进行对应
    map<string, int>match;
    int get_module_info()
    {
        vpiHandle systf_h = vpi_handle(vpiSysTfCall, NULL);//获取当前的系统任务函数调用的句柄。vpiSysTfCall 是一个特定的 VPI 类型，用于表示系统任务的调用。如果未找到，返回值将是 NULL。
        if (systf_h == NULL)
            return 0;

        vpiHandle modHdl = vpi_handle(vpiScope, systf_h);//根据 systf_h 获取当前的作用域（模块）句柄。
        modHdl = vpi_handle(vpiModule, modHdl);
        char* pModDefName = vpi_get_str(vpiDefName, modHdl);//从模块句柄中获取模块的定义名称，并将其存储在 pModDefName 中。
        _glbNetlistModule.setModuleName(pModDefName);//将获取到的模块名称设置到全局的网络表模块 _glbNetlistModule 中。

        vpiHandle instIter = vpi_iterate(vpiModule, modHdl);//通过模块句柄 modHdl 获取该模块中实例的迭代句柄。
        vpiHandle instHdl = NULL;
        while ((instHdl = vpi_scan(instIter)))//循环扫描模块中的每一个实例。vpi_scan 返回下一个实例的句柄，并在没有更多实例时返回 NULL。
        {
            char* pInstName = vpi_get_str(vpiName, instHdl);
            GateInst* pGateInst = new GateInst(pInstName);
            int idx_gate = _glbNetlistModule._instVec.size();
            _glbNetlistModule.addInst(pGateInst);
            //获取当前实例的名称，并将其存储在 pInstName 中。
            pModDefName = vpi_get_str(vpiDefName, instHdl);
            pGateInst->setGateType(pModDefName);
            //获取gatetype

            vpiHandle portIter = vpi_iterate(vpiPort, instHdl);
            vpiHandle portHdl = NULL;
            int port_index = 1;//用于统计port的序号(注意，只在gate中有用)
            while ((portHdl = vpi_scan(portIter)))
            {
                //获取高连接句柄，添加进node
                vpiHandle highConnHdl = vpi_handle(vpiHighConn, portHdl);
                char* pPortName = vpi_get_str(vpiName, highConnHdl);
                int port_type = vpi_get(vpiDirection, portHdl);

                int idx_node = 0;
                if (match.find(pPortName) != match.end()) {
                    GateInst* g = _glbNetlistModule._instVec[match[pPortName]];
                    if (port_type == vpiInput) g->_instNodes_out.push_back(idx_gate);
                    else g->_instNodes_in.push_back(idx_gate);
                }
                else {
                    //此时获取了wire的名称，需要新建门和更新map
                    match[pPortName] = _glbNetlistModule._instVec.size();
                    GateInst* pWireInst = new GateInst(pPortName);
                    pWireInst->_gateType = "wire";
                    if (port_type == vpiInput)pWireInst->_instNodes_out.push_back(idx_gate);
                    else pWireInst->_instNodes_in.push_back(idx_gate);
                    _glbNetlistModule.addInst(pWireInst);
                }
                idx_node = match[pPortName];

                pGateInst->addNodeIdx(idx_node, port_type, port_index);
            }

        }
        
        unordered_map<int,vector<string>>buffers;
        vector<vector<int>>source,drain;
        vector<vector<vector<int>>>circles,circles_lut;
        findAllScc(scc,_glbNetlistModule._instVec,source,drain,my_scc_,circles,circles_lut);
        vector<int>sat;
        cannot_ring_circle.assign(scc.size(),0);
        unordered_map<int,vector<vector<string>>>conditions;
        vector<int>multi;
        for(int i=0;i<scc.size();i++){
            if(!drain[i].size()){
                detect_ring(i);
                if(!cannot_ring_circle[i]){
                    for(int node:my_scc_[i]){
                        if(_glbNetlistModule._instVec[node]->_gateType=="wire"){
                            buffers[i].push_back(_glbNetlistModule._instVec[node]->_instName);
                            break;
                        }
                    }
                    vector<string>conditions_tmp;
                    for(int node:my_scc_[i]){
                        if(_glbNetlistModule._instVec[node]->_instNodes_in.size()==2){
                            for(int in:_glbNetlistModule._instVec[node]->_instNodes_in){
                                if(!scc[i][in]){
                                    stringstream ss;
                                    ss<<_glbNetlistModule._instVec[node]->_instName<<".port"<<_glbNetlistModule._instVec[node]->port_direct[in];
                                    if(_glbNetlistModule._instVec[node]->_gateType=="nand2"||_glbNetlistModule._instVec[node]->_gateType=="and2")ss<<"=1";
                                    else ss<<"=0";
                                    conditions_tmp.push_back(ss.str());
                                }
                            }
                        }
                    }
                    conditions[i].push_back(conditions_tmp);
                }
            }
            if(!source[i].size())continue;
            multi.push_back(i);
            /*
            vector<int>buffer;
            vector<vector<string>>conditions_tmp;
            if(!solve_ring(scc[i],circles_lut[i],_glbNetlistModule._instVec,source[i],drain[i],buffer,conditions_tmp)){
                cannot_ring_circle[i]=1;
            }else{
                for(int wire:buffer)buffers[i].push_back(_glbNetlistModule._instVec[wire]->_instName);
                conditions[i]=conditions_tmp;
            }*/
        }
        
        vector<thread>threads;
        for(int idx:multi)threads.emplace_back(process,idx,scc[idx],circles_lut[idx],source[idx],drain[idx],_glbNetlistModule._instVec,std::ref(buffers),std::ref(conditions));
        for (auto& th : threads) {
            th.join();
        }
        //for(int idx:multi)process(idx,scc[idx],circles_lut[idx],source[idx],drain[idx],_glbNetlistModule._instVec,buffers,conditions);
        writeresult(conditions,buffers,my_scc_, scc,cannot_ring_circle,_glbNetlistModule._instVec);
        vpi_control(vpiFinish);
        return 0;
    }


#ifdef  __cplusplus
}
#endif