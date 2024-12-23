# #!\\bin\\bash
# export LD_LIBRARY_PATH=work\\minisat_install\\lib:$LD_LIBRARY_PATH
# export LD_LIBRARY_PATH=work\\zlib_install\\lib:$LD_LIBRARY_PATH
# export C_INCLUDE_PATH=work\\zlib_install\\include:$C_INCLUDE_PATH
# export LIBRARY_PATH=work\\zlib_install\\lib:$LIBRARY_PATH

# # Verisim executable path
# verisim=\\home\\public\\software\\verisim\\bin\\verisim

# # C++ source files
# CFile="work\\setUpSystemFunc_verisim.cpp work\\findcircle.cpp work\\writeresult.cpp \\
#  work\\solver.cpp"
# PliMap=work\\systf.tab

# # Compiler flags
# CXXFLAGS="-Iwork\\minisat_install\\include -Iwork\\zlib_install\\include"
# LDFLAGS="-Lwork\\minisat_install\\lib -Lwork\\zlib_install\\lib"
# LIBS="-lminisat -lz"

# # Clean up previous files
# rm -rf verisim_history.db verisim.env verisim.db verisim_work verisim.log

# # Compile the shared library
# g++ -std=c++11 -shared -fPIC -o myvpi.so ${CFile} ${CXXFLAGS} ${LDFLAGS} ${LIBS}

# Case=$1

# # Run Verisim with the shared library
# ${verisim} +acc+c ${Case} -P ${PliMap} -pli_lib myvpi.so -no-mold

# # Clean up log files
# rm -rf verisim_history.zdb verisim.env verisim.zdb verisim_work verisim.log
#!\\bin\\bash

# 设置库路径
# export LD_LIBRARY_PATH=work\\minisat_install\\lib:$LD_LIBRARY_PATH
# export LD_LIBRARY_PATH=work\\zlib_install\\lib:$LD_LIBRARY_PATH
# export C_INCLUDE_PATH=work\\zlib_install\\include:$C_INCLUDE_PATH
# export LIBRARY_PATH=work\\zlib_install\\lib:$LIBRARY_PATH

# # iverilog 可执行文件路径
# # iverilog=\\usr\\bin\\iverilog
# # vvp=\\usr\\bin\\vvp

# # C++源文件
# CFile="work\\setUpSystemFunc_iverilog.cpp work\\findcircle.cpp work\\writeresult.cpp \\
#  work\\solver.cpp"

# # 编译VPI库的映射文件
# PliMap=work\\systf.tab

# # 编译器选项
# CXXFLAGS="-Iwork\\minisat_install\\include -Iwork\\zlib_install\\include"
# LDFLAGS="-Lwork\\minisat_install\\lib -Lwork\\zlib_install\\lib"
# LIBS="-lminisat -lz"

# # 清理之前的文件
# rm -rf simulation.log myvpi.so

# # 编译共享库
# g++ -std=c++11 -shared -fPIC -o myvpi.so ${CFile} ${CXXFLAGS} ${LDFLAGS} ${LIBS}

# # 仿真文件
# Case=$1
# if [ -z "$Case" ]; then
#   echo "Usage: $0 <testbench.v>"
#   exit 1
# fi

# # 运行 iverilog 编译
# iverilog -o simulation.out -DPLI -P ${PliMap} ${Case} -l myvpi.so
# if [ $? -ne 0 ]; then
#   echo "iverilog compilation failed"
#   exit 1
# fi

# # 执行仿真
# vvp -M. -m myvpi simulation.out > simulation.log
# if [ $? -ne 0 ]; then
#   echo "Simulation failed"
#   exit 1
# fi

# # 清理日志文件
# echo "Simulation completed. Check simulation.log for details."
#!\\bin\\bash

export LD_LIBRARY_PATH=work\\minisat_install\\lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=work\\zlib_install\\lib:$LD_LIBRARY_PATH
export C_INCLUDE_PATH=work\\zlib_install\\include:$C_INCLUDE_PATH
export LIBRARY_PATH=work\\zlib_install\\lib:$LIBRARY_PATH

export PATH=IVERILOG_PATH\\bin:${PATH}

source caseSetup.sh


CFile="work\\setUpSystemFunc_iverilog.cpp work\\findcircle.cpp work\\writeresult.cpp \\
 work\\solver.cpp"


VPI=myvpi

CXXFLAGS="-Iwork\\minisat_install\\include -Iwork\\zlib_install\\include"
LDFLAGS="-Lwork\\minisat_install\\lib -Lwork\\zlib_install\\lib"
LIBS="-lminisat -lz"


rm -rf *.vvp *.vpi obj_dir *.o ${VPI}.c

touch ${VPI}.c

iverilog ${Case} -o testcase.vvp
#iverilog-vpi -L. -std=gnu++11 ${VPI}.c ${CFile} 
g++ -std=c++17 -shared -fPIC -o ${VPI}.vpi ${VPI}.c ${CFile} ${CXXFLAGS} ${LDFLAGS} ${LIBS}
vvp -M. -m${VPI} testcase.vvp

rm -rf *.vvp *.vpi obj_dir *.o ${VPI}.c
