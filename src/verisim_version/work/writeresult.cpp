#include"writeresult.h"
#include<sstream>
#include<algorithm>
#include<fstream>
using namespace std;
//将答案写入txt中
void writeresult(unordered_map<int,vector<vector<string>>>conditions,unordered_map<int,vector<string>>buffers,vector<vector<int>>sccs,vector<vector<int>>scc_lut,vector<int>cannot_ring_circle,const GateInstVec& gates) {
    vector<vector<string>>wires,gates_;
    ofstream os("result_1.txt");
    for (size_t i = 0; i < sccs.size(); i++) {
        vector<string>circle_str;//用于进行字典序
        os << i + 1 << ")" << endl;
        os << "Loop Signals: ";
        for (size_t j = 0; j < sccs[i].size(); j++) {
            if (gates[sccs[i][j]]->_gateType != "wire")continue;
            circle_str.push_back(gates[sccs[i][j]]->_instName);
        }
        sort(circle_str.begin(), circle_str.end());
        for (size_t j = 0; j < circle_str.size(); j++)os << circle_str[j] << ",";
        wires.push_back(circle_str);
        circle_str.clear();
        os << endl;
        os << "Loop Gates: ";
        for (size_t j = 0; j < sccs[i].size(); j++) {
            if (gates[sccs[i][j]]->_gateType == "wire")continue;
            for(int in:gates[sccs[i][j]]->_instNodes_in)if(scc_lut[i][in]){
                int port_index=gates[sccs[i][j]]->port_direct[in];
                std::ostringstream oss;
                oss << gates[sccs[i][j]]->_instName << ".port";
                oss << port_index;
                circle_str.push_back(oss.str());
            }
        }
        sort(circle_str.begin(), circle_str.end());
        for (size_t j = 0; j < circle_str.size(); j++)os << circle_str[j] << ",";
        gates_.push_back(circle_str);
        circle_str.clear();
        os << endl;
        os << endl;
    }
    os.close();
    
    os.open("result_2.txt");
    int idx = 0;
    for (size_t i = 0; i < sccs.size(); i++) {
        if (!cannot_ring_circle[i])continue;
        os << idx + 1 << ")" << endl;
        idx++;
        os << "Loop Signals: ";
        for(string out:wires[i])os<<out<<",";
        os << endl;
        os << "Loop Gates: ";
        for(string out:gates_[i])os<<out<<",";
        os << endl;
        os << endl;
    }

    os.close();
    idx = 0;
    os.open("result_3.txt");
    for(int i=0;i<sccs.size();i++){
        if(cannot_ring_circle[i])continue;
        os << idx + 1 << ")" << endl;
        idx++;
        os << "Loop Signals: ";
        for(string out:wires[i])os<<out<<",";
        os << endl;
        os << "Loop Gates: ";
        for(string out:gates_[i])os<<out<<",";
        os << endl;
        vector<vector<string>>condition=conditions[i];
        for(auto con:condition){
            os<<"Loop Conditions: ";
            sort(con.begin(),con.end());
            for(string c:con)os<<c<<",";
            os<<endl;
        }
        os<<endl;
    }
    os.close();
    idx=0;
    os.open("result_4.txt");
    for(int i=0;i<sccs.size();i++){
        if(cannot_ring_circle[i])continue;
        os << idx + 1 << ")" << endl;
        idx++;
        os << "Loop Breaker: ";
        for(string out:buffers[i])os<<out<<",";
        os << endl;
        os<<endl;
    }
    os.close();
}