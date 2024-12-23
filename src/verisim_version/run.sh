#!/bin/bash
export LD_LIBRARY_PATH=work/minisat_install/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=work/zlib_install/lib:$LD_LIBRARY_PATH
export C_INCLUDE_PATH=work/zlib_install/include:$C_INCLUDE_PATH
export LIBRARY_PATH=work/zlib_install/lib:$LIBRARY_PATH

# Verisim executable path
verisim=/home/public/software/verisim/bin/verisim

# C++ source files
CFile="work/setUpSystemFunc_verisim.cpp work/findcircle.cpp work/writeresult.cpp \
 work/solver.cpp"
PliMap=work/systf.tab

# Compiler flags
CXXFLAGS="-Iwork/minisat_install/include -Iwork/zlib_install/include"
LDFLAGS="-Lwork/minisat_install/lib -Lwork/zlib_install/lib"
LIBS="-lminisat -lz"

# Clean up previous files
rm -rf verisim_history.db verisim.env verisim.db verisim_work verisim.log

# Compile the shared library
g++ -std=c++11 -shared -fPIC -o myvpi.so ${CFile} ${CXXFLAGS} ${LDFLAGS} ${LIBS}

Case=$1

# Run Verisim with the shared library
${verisim} +acc+c ${Case} -P ${PliMap} -pli_lib myvpi.so -no-mold

# Clean up log files
rm -rf verisim_history.zdb verisim.env verisim.zdb verisim_work verisim.log
