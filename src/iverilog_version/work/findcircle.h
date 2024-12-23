#ifndef FINDCIRCLE_H
#define FINDCIRCLE_H

#include"datatype.h"

void findAllScc(std::vector<std::vector<int>>&scc,GateInstVec gates,std::vector<std::vector<int>>&source,std::vector<std::vector<int>>&drain,std::vector<std::vector<int>>&my_scc,std::vector<std::vector<std::vector<int>>>&circles,std::vector<std::vector<std::vector<int>>>&circles_lut);

#endif 
