#ifndef MYSOLVER_H
#define MYSOLVER_H
#include "datatype.h"


bool solve_ring(std::vector<int>scc,std::vector<std::vector<int>>circles_lut,GateInstVec old_gates,std::vector<int>source,std::vector<int>drain,std::vector<int>&buffer,std::vector<std::vector<std::string>>&conditions);

#endif