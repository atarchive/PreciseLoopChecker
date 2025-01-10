# 项目说明

此项目用于解决赛题1-4中的环路震荡问题，使用了 `minisat` 和 `zlib` 库，并结合 `verilog` 的 VPI 接口进行模块分析。下面是每个文件的功能说明。

## 文件说明

### `datatype.h`
此文件定义了项目中使用的数据结构，包含了对各类信息的存储和管理方式。

### `findcircle.cpp`
实现了使用 **Tarjan 算法** 寻找强连通分量，并通过高效的 **DFS 算法** 寻找这些强连通分量中的环路。是整个环路震荡检测中的关键步骤。

### `setUpSystemFunc_iverilog.cpp`
该文件是与 Verilog 的 VPI 接口的主要交互代码，包含了 `get_module_vpi` 函数，允许在 Verilog 模块中调用此函数并利用 C 代码进行分析和计算。

### `solver.cpp`
这是项目中最重要的文件，核心解题逻辑实现所在。通过调用 **minisat** 和使用多点 SAT 方法与前后向搜索技术，实现了准确的环路震荡判断和最大震荡条件计算。整个解题过程在此文件中完成。

### `writeresult.cpp`
该文件负责将计算结果输出到相应的 **txt** 文件中，便于后续查看和分析。

### `minisat_install`
包含了 `minisat` 库的安装文件。`minisat` 是一个用于求解 SAT 问题的工具，在本项目中用于环路震荡问题的解决。安装过程中需要确保 `bin` 和 `include` 目录正确配置。

### `zlib_install`
包含了 `zlib` 库的安装文件，`zlib` 库用于数据压缩，在本项目中提供了必要的压缩功能。

## 使用说明

1. 确保已正确安装 `minisat` 和 `zlib` 库，并将其路径添加到 `include` 和 `lib` 目录中。
2. 使用 `setUpSystemFunc_iverilog.cpp` 中提供的 VPI 接口将 C 代码嵌入到 Verilog 模块中，进行环路震荡检测。
3. 在 `solver.cpp` 中设置求解参数，运行 SAT 求解器获取结果。
4. 运行 `writeresult.cpp` 将结果输出到文件。

## 依赖项

- **minisat**：用于 SAT 问题的求解。
- **zlib**：用于数据压缩和解压。
- **iverilog**：用于编译和仿真 Verilog 代码。

## 许可

本项目采用 [MIT 许可证](LICENSE)。

