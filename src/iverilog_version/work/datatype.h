#ifndef DATATYPE_H
#define DATATYPE_H

#include<vector>
#include<string>
#include<map>
#include"vpi_user.h"
#include"sv_vpi_user.h"
#include<unordered_map>



//typedef vector<string>   StrVec;
//typedef vector<int> IntVec;
//该部分定义了一个实例的类，包含门类型、实例名称、节点名称信息，能够根据输入的字符串对数据进行初始化， 并且输出实例的信息
class GateInst
{
public:
    GateInst(const char* pName)
    {
        _instName = pName ? pName : "Unknown";
    }

    void setGateType(const char* pName)
    {
        _gateType = pName ? pName : "Unknown";
    }

    void addNodeIdx(const int& pIdx, int type, int& port_index)
    {
        if (type == vpiInput) {
            _instNodes_in.push_back(pIdx);
            port_direct[pIdx] = port_index;//获取port的序号
            port_index++;
        }
        else _instNodes_out.push_back(pIdx);
    }

    void dumpInst()
    {
        printf("%-5s  %s  input: ", _gateType.c_str(), _instName.c_str());
        for (unsigned ii = 0; ii != _instNodes_in.size(); ++ii)
        {
            printf("%d  ", _instNodes_in[ii]);
        }
        printf("output: ");
        for (unsigned ii = 0; ii != _instNodes_out.size(); ++ii)
        {
            printf("%d  ", _instNodes_out[ii]);
        }
        printf("\n");
    }

    std::string  _gateType;
    std::string  _instName;
    std::vector<int>  _instNodes_in;
    std::vector<int>  _instNodes_out;
    std::map<int, int>port_direct;//用于定位每个wire的port
};

typedef std::vector<GateInst*>  GateInstVec;


//定义了网表模块类，包含模块的名称和包含实例的vec。含有相应的析构函数和初始化函数，能够输出模块中的实例(通过分别调用实例类的输出函数)
class NetlistModule
{
public:
    ~NetlistModule()//析构函数
    {
        for (unsigned ii = 0; ii != _instVec.size(); ++ii)
        {
            delete _instVec[ii];
        }
    }

    void setModuleName(const char* pName)
    {
        if (pName)
            _moduelName = pName;
    }

    void addInst(GateInst* pInst)
    {
        _instVec.push_back(pInst);
    }

    void dumpInst()
    {
        for (unsigned ii = 0; ii != _instVec.size(); ++ii)
        {
            GateInst* pInst = _instVec[ii];
            if (pInst)
            {
                printf("%-3d: ", ii);
                pInst->dumpInst();
            }
        }
    }

    std::string      _moduelName;
    GateInstVec _instVec;
};

#endif // !DATATYPE_H
