# 设置环境变量
export LD_LIBRARY_PATH := work/minisat_install/lib:work/zlib_install/lib:$(LD_LIBRARY_PATH)
export C_INCLUDE_PATH := work/zlib_install/include:$(C_INCLUDE_PATH)
export LIBRARY_PATH := work/zlib_install/lib:$(LIBRARY_PATH)
export PATH := IVERILOG_PATH/bin:$(PATH)

# 变量定义
CFILES := work/setUpSystemFunc_iverilog.cpp work/findcircle.cpp work/writeresult.cpp \
          work/solver.cpp
VPI := myvpi
CXXFLAGS := -Iwork/minisat_install/include -Iwork/zlib_install/include
LDFLAGS := -Lwork/minisat_install/lib -Lwork/zlib_install/lib
LIBS := -lminisat -lz

BENCHMARKS := S_AAA_1.v S_ACA_1.v S_CCA_1.v T_AAA_1.v T_ACA_1.v T_ACA_2.v \
               T_CCA_1.v gate_100_100_20.v gate_1000_1000_50.v gate_2000_2000_100.v \
               gate_200_200_20.v gate_20_20_10.v gate_20_20_5.v gate_30_30_10.v \
               gate_40_40_10.v gate_500_500_50.v

RESULT_DIR := ../../result

# 默认目标
all: clean compile_vpi run_all

# 清理生成文件
clean:
	rm -rf *.vvp *.vpi obj_dir *.o $(VPI).c
	rm -rf ../../result

# 编译 VPI 模块
compile_vpi: 
	touch $(VPI).c
	g++ -std=c++17 -shared -fPIC -o $(VPI).vpi $(VPI).c $(CFILES) $(CXXFLAGS) $(LDFLAGS) $(LIBS)

# 对每个测试用例运行仿真
run_all: compile_vpi
	@mkdir -p $(RESULT_DIR)
	@for case in $(BENCHMARKS); do \
		echo "Running simulation for $$case..."; \
		iverilog -s combLogic ../../benchmark/testcase/$$case -o testcase.vvp; \
		vvp -M. -m$(VPI) testcase.vvp;  \
		echo "Finished simulation for $$case."; \
		case_name=$$(basename $$case .v); \
		cp -r result result_$$case_name; \
		mv result_$$case_name $(RESULT_DIR)/; \
		echo "Finished move result"; \
	done
