// Gate Level Verilog Code Generated!
// GateLvl:20 GateNum:20 GateInputNum:2
// ****** Basic Gate Module Defination ******
module or2(out, in1, in2);
  output out;
  input in1, in2;
  wire in1, in2, out;
  assign #1 out = in1 || in2;
endmodule

module and2(out, in1, in2);
  output out;
  input in1, in2;
  wire in1, in2, out;
  assign #1 out = in1 && in2;
endmodule

module not1(out, in);
  output out;
  input in;
  wire in,out;
  assign #1 out = ~in;
endmodule

module nand2(out, in1, in2);
  output out;
  input in1, in2;
  wire in1, in2, out;
  assign #1 out = ~(in1 && in2);
endmodule
// ****** Basic Gate Module Defination End ******

// ****** Combined Logic Module Defination ******
// module combLogic(w_003_001, w_003_002, w_003_003, w_003_004, w_003_005, w_003_006, w_003_007, w_003_008);

//   input w_003_001, w_003_002, w_003_003, w_003_004, w_003_005, w_003_006, w_003_007, w_003_008;
//   wire  w_003_001, w_003_002, w_003_003, w_003_004, w_003_005, w_003_006, w_003_007, w_003_008;

//   wire w_000_001, w_000_002, w_000_003, w_000_004, w_000_005;
//   wire w_001_006, w_001_007, w_001_008, w_001_009, w_001_010;
//   wire w_002_012, w_002_013, w_002_014, w_002_015;

//   not1    I001_001(w_000_001, w_000_002);
//   and2    I001_002(w_000_002, w_003_001, w_000_003);
//   and2    I001_003(w_000_004, w_003_002, w_000_005);
//   and2    I001_004(w_001_006, w_000_005, w_003_003);
//   //or2     I001_005(w_001_007, w_003_004, w_000_003);
//   and2     I001_005(w_001_007, w_003_004, w_000_003);
//   and2    I001_006(w_001_008, w_000_001, w_000_004);
//   nand2   I001_007(w_000_005, w_001_009, w_001_010);
//   //or2     I001_008(w_002_012, w_001_006, w_001_007);
//   and2    I001_008(w_002_012, w_001_006, w_001_007);
//   nand2   I001_009(w_000_003, w_002_013, w_002_014);
//   nand2   I001_010(w_001_009, w_003_005, w_001_008);
//   //or2     I002_012(w_001_010, w_002_012, w_003_006);
//   and2     I002_012(w_001_010, w_002_012, w_003_006);
//   and2    I002_013(w_002_013, w_003_007, w_002_012);
//   not1    I002_014(w_002_014, w_002_015);
//   and2    I002_015(w_002_015, w_001_008, w_003_008);

//   initial begin
//     //$get_module_info();
//   end
// endmodule

module Oscillation_LUT (
    input [7:0] w,
    output OscFlag
);

  assign OscFlag = (
    // 8'b00110010
    (~w[7] & ~w[6] &  w[5] &  w[4] & ~w[3] & ~w[2] &  w[1] & ~w[0]) |

    // 8'b00110011
    (~w[7] & ~w[6] &  w[5] &  w[4] & ~w[3] & ~w[2] &  w[1] &  w[0]) |

    // 8'b00110100
    (~w[7] & ~w[6] &  w[5] &  w[4] & ~w[3] &  w[2] & ~w[1] & ~w[0]) |

    // 8'b00110101
    (~w[7] & ~w[6] &  w[5] &  w[4] & ~w[3] &  w[2] & ~w[1] &  w[0]) |

    // 8'b00110110
    (~w[7] & ~w[6] &  w[5] &  w[4] & ~w[3] &  w[2] &  w[1] & ~w[0]) |

    // 8'b00110111
    (~w[7] & ~w[6] &  w[5] &  w[4] & ~w[3] &  w[2] &  w[1] &  w[0]) |

    // 8'b00111010
    (~w[7] & ~w[6] &  w[5] &  w[4] &  w[3] & ~w[2] &  w[1] & ~w[0]) |

    // 8'b00111011
    (~w[7] & ~w[6] &  w[5] &  w[4] &  w[3] & ~w[2] &  w[1] &  w[0]) |

    // 8'b00111100
    (~w[7] & ~w[6] &  w[5] &  w[4] &  w[3] &  w[2] & ~w[1] & ~w[0]) |

    // 8'b00111101
    (~w[7] & ~w[6] &  w[5] &  w[4] &  w[3] &  w[2] & ~w[1] &  w[0]) |

    // 8'b00111110
    (~w[7] & ~w[6] &  w[5] &  w[4] &  w[3] &  w[2] &  w[1] & ~w[0]) |

    // 8'b00111111
    (~w[7] & ~w[6] &  w[5] &  w[4] &  w[3] &  w[2] &  w[1] &  w[0]) |

    // 8'b01110010
    (~w[7] &  w[6] &  w[5] &  w[4] & ~w[3] & ~w[2] &  w[1] & ~w[0]) |

    // 8'b01110100
    (~w[7] &  w[6] &  w[5] &  w[4] & ~w[3] &  w[2] & ~w[1] & ~w[0]) |

    // 8'b01110101
    (~w[7] &  w[6] &  w[5] &  w[4] & ~w[3] &  w[2] & ~w[1] &  w[0]) |

    // 8'b01110110
    (~w[7] &  w[6] &  w[5] &  w[4] & ~w[3] &  w[2] &  w[1] & ~w[0]) |

    // 8'b01110111
    (~w[7] &  w[6] &  w[5] &  w[4] & ~w[3] &  w[2] &  w[1] &  w[0]) |

    // 8'b01111010
    (~w[7] &  w[6] &  w[5] &  w[4] &  w[3] & ~w[2] &  w[1] & ~w[0]) |

    // 8'b01111110
    (~w[7] &  w[6] &  w[5] &  w[4] &  w[3] &  w[2] &  w[1] & ~w[0]) |

    // 8'b10110010
    ( w[7] & ~w[6] &  w[5] &  w[4] & ~w[3] & ~w[2] &  w[1] & ~w[0]) |

    // 8'b10110011
    ( w[7] & ~w[6] &  w[5] &  w[4] & ~w[3] & ~w[2] &  w[1] &  w[0]) |

    // 8'b10110100
    ( w[7] & ~w[6] &  w[5] &  w[4] & ~w[3] &  w[2] & ~w[1] & ~w[0]) |

    // 8'b10110101
    ( w[7] & ~w[6] &  w[5] &  w[4] & ~w[3] &  w[2] & ~w[1] &  w[0]) |

    // 8'b10110110
    ( w[7] & ~w[6] &  w[5] &  w[4] & ~w[3] &  w[2] &  w[1] & ~w[0]) |

    // 8'b10110111
    ( w[7] & ~w[6] &  w[5] &  w[4] & ~w[3] &  w[2] &  w[1] &  w[0]) |

    // 8'b10111010
    ( w[7] & ~w[6] &  w[5] &  w[4] &  w[3] & ~w[2] &  w[1] & ~w[0]) |

    // 8'b10111011
    ( w[7] & ~w[6] &  w[5] &  w[4] &  w[3] & ~w[2] &  w[1] &  w[0]) |

    // 8'b10111100
    ( w[7] & ~w[6] &  w[5] &  w[4] &  w[3] &  w[2] & ~w[1] & ~w[0]) |

    // 8'b10111101
    ( w[7] & ~w[6] &  w[5] &  w[4] &  w[3] &  w[2] & ~w[1] &  w[0]) |

    // 8'b10111110
    ( w[7] & ~w[6] &  w[5] &  w[4] &  w[3] &  w[2] &  w[1] & ~w[0]) |

    // 8'b10111111
    ( w[7] & ~w[6] &  w[5] &  w[4] &  w[3] &  w[2] &  w[1] &  w[0]) |

    // 8'b11110010
    ( w[7] &  w[6] &  w[5] &  w[4] & ~w[3] & ~w[2] &  w[1] & ~w[0]) |

    // 8'b11110011
    ( w[7] &  w[6] &  w[5] &  w[4] & ~w[3] & ~w[2] &  w[1] &  w[0]) |

    // 8'b11110100
    ( w[7] &  w[6] &  w[5] &  w[4] & ~w[3] &  w[2] & ~w[1] & ~w[0]) |

    // 8'b11110101
    ( w[7] &  w[6] &  w[5] &  w[4] & ~w[3] &  w[2] & ~w[1] &  w[0]) |

    // 8'b11110110
    ( w[7] &  w[6] &  w[5] &  w[4] & ~w[3] &  w[2] &  w[1] & ~w[0]) |

    // 8'b11110111
    ( w[7] &  w[6] &  w[5] &  w[4] & ~w[3] &  w[2] &  w[1] &  w[0]) |

    // 8'b11111010
    ( w[7] &  w[6] &  w[5] &  w[4] &  w[3] & ~w[2] &  w[1] & ~w[0]) |

    // 8'b11111011
    ( w[7] &  w[6] &  w[5] &  w[4] &  w[3] & ~w[2] &  w[1] &  w[0]) |

    // 8'b11111100
    ( w[7] &  w[6] &  w[5] &  w[4] &  w[3] &  w[2] & ~w[1] & ~w[0]) |

    // 8'b11111101
    ( w[7] &  w[6] &  w[5] &  w[4] &  w[3] &  w[2] & ~w[1] &  w[0]) |

    // 8'b11111110
    ( w[7] &  w[6] &  w[5] &  w[4] &  w[3] &  w[2] &  w[1] & ~w[0]) |

    // 8'b11111111
    ( w[7] &  w[6] &  w[5] &  w[4] &  w[3] &  w[2] &  w[1] &  w[0])
);

endmodule

module mux(out,in1,in2,s);
    output out;
    input in1,in2,s;
    wire s_,a,b;
    not1 U1(s_,s);
    and2 U2(a,in1,s_);
    and2 U3(b,in2,s);
    or2 U4(out,a,b);
endmodule

module modified_combLogic(w_003_001, w_003_002, w_003_003, w_003_004, w_003_005, w_003_006, w_003_007, w_003_008, oscillation_flag);

  input w_003_001, w_003_002, w_003_003, w_003_004, w_003_005, w_003_006, w_003_007, w_003_008;
  wire [7:0] inputs;
  assign inputs={w_003_001, w_003_002, w_003_003, w_003_004, w_003_005, w_003_006, w_003_007, w_003_008};
  wire  w_003_001, w_003_002, w_003_003, w_003_004, w_003_005, w_003_006, w_003_007, w_003_008;

  wire w_000_001, w_000_002, w_000_003, w_000_004, w_000_005;
  wire w_001_006, w_001_007, w_001_008, w_001_009, w_001_010;
  wire w_002_012, w_002_013, w_002_014, w_002_015;

  wire w_mux_01,w_mux_02;

  not1    I001_001(w_000_001, w_000_002);
  and2    I001_002(w_000_002, w_003_001, w_000_003);
  and2    I001_003(w_000_004, w_003_002, w_000_005);
  and2    I001_004(w_001_006, w_000_005, w_003_003);
  //or2     I001_005(w_001_007, w_003_004, w_000_003);
  and2     I001_005(w_001_007, w_003_004, w_000_003);
  and2    I001_006(w_mux_01, w_000_001, w_000_004);
  nand2   I001_007(w_000_005, w_001_009, w_001_010);
  //or2     I001_008(w_002_012, w_001_006, w_001_007);
  and2    I001_008(w_mux_02, w_001_006, w_001_007);
  nand2   I001_009(w_000_003, w_002_013, w_002_014);
  nand2   I001_010(w_001_009, w_003_005, w_001_008);
  //or2     I002_012(w_001_010, w_002_012, w_003_006);
  and2     I002_012(w_001_010, w_002_012, w_003_006);
  and2    I002_013(w_002_013, w_003_007, w_002_012);
  not1    I002_014(w_002_014, w_002_015);
  and2    I002_015(w_002_015, w_001_008, w_003_008);


  output oscillation_flag;
  Oscillation_LUT LUT(inputs, oscillation_flag);
  mux M1(w_001_008,w_mux_01,1'b0,oscillation_flag);
  mux M2(w_002_012,w_mux_02,1'b0,oscillation_flag);


endmodule


// ****** Combined Logic Module Defination ******

// ****** TestBench Module Defination ******

module tb();
  reg [7:0] inputs;
  wire oscillation_flag;
  wire w_003_001, w_003_002, w_003_003, w_003_004, w_003_005, w_003_006, w_003_007, w_003_008;

  assign {w_003_001, w_003_002, w_003_003, w_003_004, w_003_005, w_003_006, w_003_007, w_003_008}=inputs;

  modified_combLogic I0(w_003_001, w_003_002, w_003_003, w_003_004, w_003_005, w_003_006, w_003_007, w_003_008,oscillation_flag);

  // 定义需要监测的内部信号
  wire [13:0] internal_signals;
  assign internal_signals = {
    I0.w_000_001, I0.w_000_002, I0.w_000_003, I0.w_000_004, I0.w_000_005,
    I0.w_001_006, I0.w_001_007, I0.w_001_008, I0.w_001_009, I0.w_001_010,
    I0.w_002_012, I0.w_002_013, I0.w_002_014, I0.w_002_015
  };

  integer i;
  reg oscillation_detected;
  reg [13:0] prev_internal_signals;
  integer stable_count;
  integer sim_time;

  initial begin
    // 初始化信号
    inputs = 8'b0;
    oscillation_detected = 0;
    stable_count = 0;
    sim_time = 0;

    // 打印表头
    $display("Input Combination\tOscillation Detected\toscillation_flag");

    // 遍历所有输入组合
    for (i = 0; i < 256; i = i + 1) begin
      inputs = i[7:0];

      // 重置检测变量
      oscillation_detected = 0;
      stable_count = 0;
      prev_internal_signals = 14'bX;
      sim_time = 0;

      // 运行一段时间以检测震荡
      fork
        begin : simulation_loop
          repeat (1000) begin
            #1;
            sim_time = sim_time + 1;
            if (internal_signals !== prev_internal_signals) begin
              stable_count = 0;
              prev_internal_signals = internal_signals;
            end else begin
              stable_count = stable_count + 1;
              if (stable_count >= 100) begin
                // 信号已稳定
                disable simulation_loop;
              end
            end
          end
          // 如果循环结束而未稳定，认为发生了震荡
          oscillation_detected = 1;
          disable check_x_values;
        end

        begin : check_x_values
          wait (stable_count >= 100);
          // 检查稳定后的内部信号是否包含'x'
          if (| (internal_signals ^ internal_signals)) begin
            // 存在'x'，判定为震荡
            oscillation_detected = 1;
          end else begin
            // 不存在'x'，不发生震荡
            oscillation_detected = 0;
          end
          disable simulation_loop;
        end
      join

      // 输出结果
      $display("%b\t\t\t%b\t\t\t%b", inputs, oscillation_detected,oscillation_flag);

    end

    $finish;
  end
endmodule
