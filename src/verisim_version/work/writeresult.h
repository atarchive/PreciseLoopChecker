#ifndef WRITERESULT_H
#define WRITERESULT_H

#include"datatype.h"

void writeresult(std::unordered_map<int,std::vector<std::vector<std::string>>>conditions,std::unordered_map<int,std::vector<std::string>>buffers,std::vector<std::vector<int>>sccs,std::vector<std::vector<int>>scc_lut,std::vector<int>cannot_ring_circle,const GateInstVec&gates);

#endif 
