# 数字电路仿真中组合逻辑环路分析

## 1. 赛题背景

本项目基于2024年中国研究生创“芯”大赛·EDA精英挑战赛的赛题“数字电路仿真中组合逻辑环路分析”。

组合逻辑电路由多个门电路按照特定规则组合而成，用于实现逻辑运算。在这些电路中，可能会形成组合逻辑环路，分为正向反馈和负向反馈两种类型。这些环路在许多实际电路设计中并不需要，可能导致信号震荡或多重驱动等问题，从而影响电路的正确性和功耗。

本赛题要求参赛者基于Verilog仿真器的VPI接口，自动检测门级网表中的组合逻辑环路，分析触发条件并提出解决方案。通过本项目，我们实现了以下任务：

1. 找出所有组合强连通分量
2. 分析哪些强连通分量不会发生持续震荡。
3. 给出可能震荡的强连通分量，并且找到发生使得震荡的门数最多时外部输入的条件。
4. 通过插入最少寄存器，断开强连通分量以避免震荡。
5. 设计等价变换，既能检测震荡，又能保持逻辑正确性。

**代码的具体实现在`src/iverilog_version/work`中，代码解释请参看work文件夹中的README文件**


## 2. 项目结构

本项目的代码和相关资源组织如下：

```
project_root
├── benchmark         # 用于测试的基准用例
├── report            # 项目报告
├── result            # 输出的分析结果文件
├── slides            # 项目相关的演示文档
├── src               # 源代码文件夹
│   ├── iverilog_version   # 基于Icarus Verilog实现的代码
│   ├── verisim_version    # 基于VeriSim实现的代码
```

- **benchmark**：包含多个逻辑门数量不同的Verilog门级网表测试用例，用于验证程序功能和性能。
- **result**：存储程序运行后的结果文件，包括组合逻辑环检测、震荡条件分析等输出。
- **slides**：用于展示和解释项目的背景、方法和结果的演示文档。
- **src/iverilog_version**：基于开源仿真器Icarus Verilog实现的代码。
- **src/verisim_version**：基于VeriSim数字仿真器实现的代码。

## 3. 如何运行

1. 安装必要的工具：
   - **Icarus Verilog** 或 **VeriSim**(***注:VeriSim是概伦电子的产品，比赛后只能使用iverilog仿真***)。
   - C/C++编译器（支持VPI接口）。
   - autoconf/gperf/flex/bison
     如果发现这些工具没有安装，运行(以autoconf为例)
     ```bash
      sudo apt update
      sudo apt install autoconf gperf flex bison
     ```
     即可
2. 运行程序：
   ```bash
   cd src/iverilog_version
   make clean
   make
   ```
   如果直接运行发现vpi报错"vpi error:vpi_get_str……"，是当前配置的iverilog并不支持vpi功能，需要重新安装work目录下的iverilog文件:
   ```bash
   cd work/iverilog
   sh autoconf.sh
   ./configure
   make
   sudo make install
   ```
   再运行iverilog_version中的make即可

3. 查看结果：
   程序将在 `result` 文件夹中生成分析结果文件，`result`文件夹中各个子文件夹是benchmark中相应的组合逻辑电路的赛题1-4的结果，例如 `result_gate_20_20_5/result_1.txt`是benchmark中`gate_20_20_5.v`的赛题1结果。


4. 答案验证：
   赛题方只提供了`gate_**.v`的答案，在相应的verilog代码后面，作为注释存在。

## 4. 技术细节

- **VPI接口**：通过VPI接口获取门级网表的逻辑门和信号连接信息。
- **拓扑分析**：构建网表拓扑，利用深度优先搜索（DFS）检测逻辑环路。
- **逻辑条件分析**：对负向反馈环路，分析可能震荡的输入条件。
- **优化断环方案**：基于最小寄存器插入策略，确保功能正确性。
- **等价变换**：保持逻辑功能的同时，提供震荡检测能力。
- 具体技术细节情参照report 和 slides文件夹中的报告和ppt

## 5. 注意事项

- 测试用例应符合Verilog门级网表格式。
- 请根据使用的仿真器版本选择正确的代码版本（iverilog或verisim）。
- 如果运行时出现问题，请检查VPI接口配置是否正确。
---



