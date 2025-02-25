// Gate Level Verilog Code Generated!
// GateLvl:20 GateNum:20 GateInputNum:2
// ****** Basic Gate Module Defination ******
module or2(out, in1, in2);
  output out;
  input in1, in2;
  wire in1, in2, out;
  assign out = in1 || in2;
endmodule

module and2(out, in1, in2);
  output out;
  input in1, in2;
  wire in1, in2, out;
  assign out = in1 && in2;
endmodule

module not1(out, in);
  output out;
  input in;
  wire in,out;
  assign out = ~in;
endmodule

module nand2(out, in1, in2);
  output out;
  input in1, in2;
  wire in1, in2, out;
  assign out = ~(in1 && in2);
endmodule
// ****** Basic Gate Module Defination End ******

// ****** Combined Logic Module Defination ******
module combLogic( w_000_000, w_000_001, w_000_002, w_000_003, w_000_004, w_000_005, w_000_007, w_000_008, w_000_009, w_000_010, w_000_012, w_000_013, w_000_015, w_020_000, w_020_001, w_020_002, w_020_003, w_020_004 );
  inout w_000_000, w_000_001, w_000_002, w_000_003, w_000_004, w_000_005, w_000_007, w_000_008, w_000_009, w_000_010, w_000_012, w_000_013, w_000_015;
  output w_020_000, w_020_001, w_020_002, w_020_003, w_020_004;
  wire w_000_000, w_000_001, w_000_002, w_000_003, w_000_004, w_000_005, w_000_007, w_000_008, w_000_009, w_000_010, w_000_012, w_000_013, w_000_015;
  wire w_001_000;
  wire w_002_000, w_002_001, w_002_002, w_002_004, w_002_006, w_002_007, w_002_008, w_002_009, w_002_010, w_002_011, w_002_013, w_002_015, w_002_017, w_002_018;
  wire w_003_001, w_003_004, w_003_005, w_003_007, w_003_011;
  wire w_004_000, w_004_001;
  wire w_005_000;
  wire w_006_003, w_006_007, w_006_010, w_006_012, w_006_013, w_006_014, w_006_015, w_006_016, w_006_018, w_006_020, w_006_021, w_006_022, w_006_023, w_006_024, w_006_025, w_006_026, w_006_027, w_006_028, w_006_030;
  wire w_007_001, w_007_004, w_007_005, w_007_006, w_007_011, w_007_012;
  wire w_008_001, w_008_003, w_008_004, w_008_005, w_008_008;
  wire w_009_006;
  wire w_010_004, w_010_005, w_010_006, w_010_007, w_010_008, w_010_012, w_010_013, w_010_014, w_010_015, w_010_016, w_010_017, w_010_018, w_010_019, w_010_020, w_010_022;
  wire w_011_002;
  wire w_013_000, w_013_007;
  wire w_014_001;
  wire w_015_004;
  wire w_016_009, w_016_016, w_016_017, w_016_018, w_016_019, w_016_020, w_016_021, w_016_022, w_016_023, w_016_024, w_016_025, w_016_027;
  wire w_017_000;
  wire w_018_000;
  wire w_019_002;
  wire w_020_000, w_020_001, w_020_002, w_020_003, w_020_004;
  not1 I001_000(w_001_000, w_000_000);
  or2  I002_000(w_002_000, w_001_000, w_000_001);
  or2  I002_001(w_002_001, w_000_002, w_000_003);
  nand2 I002_002(w_002_002, w_000_000, w_000_004);
  not1 I002_004(w_002_004, w_001_000);
  or2  I002_006(w_002_006, w_001_000, w_000_007);
  not1 I002_007(w_002_007, w_001_000);
  or2  I002_008(w_002_008, w_001_000, w_000_008);
  not1 I002_009(w_002_009, w_001_000);
  nand2 I002_010(w_002_010, w_000_009, w_001_000);
  not1 I002_011(w_002_011, w_000_001);
  not1 I002_013(w_002_013, w_001_000);
  nand2 I002_015(w_002_015, w_000_010, w_000_000);
  not1 I002_017(w_002_017, w_000_012);
  nand2 I002_018(w_002_018, w_000_013, w_000_007);
  and2 I003_001(w_003_001, w_001_000, w_002_001);
  or2  I003_004(w_003_004, w_002_009, w_001_000);
  and2 I003_005(w_003_005, w_002_013, w_000_005);
  and2 I003_007(w_003_007, w_001_000, w_002_009);
  nand2 I003_011(w_003_011, w_001_000, w_002_008);
  and2 I004_000(w_004_000, w_001_000, w_002_004);
  and2 I004_001(w_004_001, w_002_007, w_000_003);
  nand2 I005_000(w_005_000, w_000_015, w_001_000);
  nand2 I006_003(w_006_003, w_000_009, w_002_004);
  nand2 I006_007(w_006_007, w_000_003, w_002_000);
  not1 I006_010(w_006_010, w_002_017);
  nand2 I006_011(w_006_013, w_003_011, w_006_012);
  nand2 I006_012(w_006_014, w_006_013, w_002_015);
  and2 I006_013(w_006_015, w_006_014, w_005_000);
  not1 I006_014(w_006_016, w_006_015);
  or2  I006_015(w_006_012, w_006_016, w_006_030);
  nand2 I006_016(w_006_021, w_004_001, w_006_020);
  and2 I006_017(w_006_022, w_003_001, w_006_021);
  not1 I006_018(w_006_023, w_006_022);
  nand2 I006_019(w_006_024, w_006_023, w_001_000);
  nand2 I006_020(w_006_025, w_006_024, w_004_001);
  or2  I006_021(w_006_026, w_006_025, w_002_010);
  or2  I006_022(w_006_027, w_003_005, w_006_026);
  nand2 I006_023(w_006_028, w_006_027, w_002_011);
  not1 I006_024(w_006_020, w_006_012);
  and2 I006_025(w_006_030, w_004_001, w_006_028);
  and2 I007_001(w_007_001, w_006_003, w_001_000);
  and2 I007_004(w_007_004, w_003_004, w_000_002);
  or2  I007_005(w_007_005, w_005_000, w_002_018);
  and2 I007_006(w_007_006, w_002_002, w_002_000);
  and2 I007_011(w_007_011, w_003_001, w_000_008);
  not1 I007_012(w_007_012, w_002_006);
  and2 I007_015(w_006_018, w_006_007, w_006_012);
  not1 I008_001(w_008_001, w_007_012);
  not1 I008_003(w_008_003, w_006_018);
  not1 I008_004(w_008_004, w_005_000);
  and2 I008_005(w_008_005, w_001_000, w_003_007);
  and2 I008_008(w_008_008, w_002_000, w_000_002);
  nand2 I009_006(w_009_006, w_001_000, w_008_004);
  nand2 I010_003(w_010_005, w_010_004, w_001_000);
  or2  I010_004(w_010_006, w_008_001, w_010_005);
  and2 I010_005(w_010_007, w_010_006, w_007_004);
  or2  I010_006(w_010_008, w_010_007, w_010_022);
  or2  I010_007(w_010_004, w_010_008, w_005_000);
  and2 I010_008(w_010_013, w_007_006, w_010_012);
  not1 I010_009(w_010_014, w_010_013);
  or2  I010_010(w_010_015, w_008_003, w_010_014);
  not1 I010_011(w_010_016, w_010_015);
  and2 I010_012(w_010_017, w_010_016, w_005_000);
  or2  I010_013(w_010_018, w_004_001, w_010_017);
  not1 I010_014(w_010_019, w_010_018);
  and2 I010_015(w_010_020, w_001_000, w_010_019);
  not1 I010_016(w_010_012, w_010_008);
  and2 I010_017(w_010_022, w_007_001, w_010_020);
  or2  I011_002(w_011_002, w_005_000, w_001_000);
  and2 I013_000(w_013_000, w_001_000, w_009_006);
  not1 I013_007(w_013_007, w_005_000);
  or2  I014_001(w_014_001, w_011_002, w_004_001);
  not1 I015_004(w_015_004, w_008_008);
  and2 I016_009(w_016_009, w_007_005, w_014_001);
  not1 I016_015(w_016_017, w_016_016);
  or2  I016_016(w_016_018, w_016_017, w_001_000);
  or2  I016_017(w_016_019, w_006_010, w_016_018);
  or2  I016_018(w_016_020, w_004_000, w_016_019);
  not1 I016_019(w_016_021, w_016_020);
  or2  I016_020(w_016_022, w_016_021, w_013_000);
  or2  I016_021(w_016_023, w_002_017, w_016_022);
  not1 I016_022(w_016_024, w_016_023);
  and2 I016_023(w_016_025, w_016_024, w_010_019);
  not1 I016_024(w_016_016, w_016_025);
  or2  I017_000(w_017_000, w_005_000, w_008_001);
  and2 I017_017(w_016_027, w_015_004, w_016_016);
  not1 I018_000(w_018_000, w_016_027);
  not1 I019_002(w_019_002, w_005_000);
  or2  I020_000(w_020_000, w_007_011, w_016_009);
  not1 I020_001(w_020_001, w_001_000);
  or2  I020_002(w_020_002, w_013_007, w_019_002);
  not1 I020_003(w_020_003, w_017_000);
  and2 I020_004(w_020_004, w_008_005, w_018_000);

  initial begin
    $get_module_info();
  end
endmodule

// ****** Combined Logic Module Defination ******

// ****** TestBench Module Defination ******

/*
module tb();
  wire  w_000_000, w_000_001, w_000_002, w_000_003, w_000_004, w_000_005, w_000_007, w_000_008, w_000_009, w_000_010, w_000_012, w_000_013, w_000_015, w_020_000, w_020_001, w_020_002, w_020_003, w_020_004 ;
  combLogic I0(  w_000_000, w_000_001, w_000_002, w_000_003, w_000_004, w_000_005, w_000_007, w_000_008, w_000_009, w_000_010, w_000_012, w_000_013, w_000_015, w_020_000, w_020_001, w_020_002, w_020_003, w_020_004  );

  reg r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, rEnd; 

  assign w_000_000 = r0;
  assign w_000_001 = r1;
  assign w_000_002 = r2;
  assign w_000_003 = r3;
  assign w_000_004 = r4;
  assign w_000_005 = r5;
  assign w_000_006 = r6;
  assign w_000_007 = r7;
  assign w_000_008 = r8;
  assign w_000_009 = r9;
  assign w_000_010 = r10;
  assign w_000_011 = r11;
  assign w_000_012 = r12;
  assign w_000_013 = r13;
  assign w_000_014 = r14;
  assign w_000_015 = r15;
  assign w_000_016 = r16;
  assign w_000_017 = r17;

  initial begin 
    r0 = 1'b0; 
    r1 = 1'b0; 
    r2 = 1'b0; 
    r3 = 1'b0; 
    r4 = 1'b0; 
    r5 = 1'b0; 
    r6 = 1'b0; 
    r7 = 1'b0; 
    r8 = 1'b0; 
    r9 = 1'b0; 
    r10 = 1'b0; 
    r11 = 1'b0; 
    r12 = 1'b0; 
    r13 = 1'b0; 
    r14 = 1'b0; 
    r15 = 1'b0; 
    r16 = 1'b0; 
    r17 = 1'b0; 
    $monitor("%t %b %b %b %b %b %b %b %b %b %b %b %b %b %b %b %b %b %b %b %b %b %b %b  ", $time, w_000_000, w_000_001, w_000_002, w_000_003, w_000_004, w_000_005, w_000_006, w_000_007, w_000_008, w_000_009, w_000_010, w_000_011, w_000_012, w_000_013, w_000_014, w_000_015, w_000_016, w_000_017, w_020_000, w_020_001, w_020_002, w_020_003, w_020_004);
    #100;
    $finish;
  end
  always #1 r0 = ~r0;
  always #2 r1 = ~r1;
  always #4 r2 = ~r2;
  always #8 r3 = ~r3;
  always #16 r4 = ~r4;
  always #32 r5 = ~r5;
  always #64 r6 = ~r6;
  always #128 r7 = ~r7;
  always #256 r8 = ~r8;
  always #512 r9 = ~r9;
  always #1024 r10 = ~r10;
  always #2048 r11 = ~r11;
  always #4096 r12 = ~r12;
  always #8192 r13 = ~r13;
  always #16384 r14 = ~r14;
  always #32768 r15 = ~r15;
  always #65536 r16 = ~r16;
  always #131072 r17 = ~r17;
endmodule
*/
// ****** TestBench Module Defination End ******

/*
// ******* The results for this case *********
******* result_1.txt *********
1)
  Loop Signals: w_006_012, w_006_013, w_006_014, w_006_015, w_006_016, 
  Loop Gates: I006_011.port2, I006_012.port1, I006_013.port1, I006_014.port1, I006_015.port1, 

2)
  Loop Signals: w_006_012, w_006_020, w_006_021, w_006_022, w_006_023, w_006_024, w_006_025, w_006_026, w_006_027, w_006_028, w_006_030, 
  Loop Gates: I006_015.port2, I006_016.port2, I006_017.port2, I006_018.port1, I006_019.port1, I006_020.port1, I006_021.port1, I006_022.port2, I006_023.port1, I006_024.port1, I006_025.port2, 

3)
  Loop Signals: w_010_004, w_010_005, w_010_006, w_010_007, w_010_008, 
  Loop Gates: I010_003.port1, I010_004.port2, I010_005.port1, I010_006.port1, I010_007.port1, 

4)
  Loop Signals: w_010_008, w_010_012, w_010_013, w_010_014, w_010_015, w_010_016, w_010_017, w_010_018, w_010_019, w_010_020, w_010_022, 
  Loop Gates: I010_006.port2, I010_008.port2, I010_009.port1, I010_010.port2, I010_011.port1, I010_012.port1, I010_013.port2, I010_014.port1, I010_015.port2, I010_016.port1, I010_017.port2, 

5)
  Loop Signals: w_016_016, w_016_017, w_016_018, w_016_019, w_016_020, w_016_021, w_016_022, w_016_023, w_016_024, w_016_025, 
  Loop Gates: I016_015.port1, I016_016.port1, I016_017.port2, I016_018.port2, I016_019.port1, I016_020.port1, I016_021.port2, I016_022.port1, I016_023.port1, I016_024.port1, 

******* result_2.txt *********
1)
  Loop Signals: w_006_012, w_006_020, w_006_021, w_006_022, w_006_023, w_006_024, w_006_025, w_006_026, w_006_027, w_006_028, w_006_030, 
  Loop Gates: I006_015.port2, I006_016.port2, I006_017.port2, I006_018.port1, I006_019.port1, I006_020.port1, I006_021.port1, I006_022.port2, I006_023.port1, I006_024.port1, I006_025.port2, 

2)
  Loop Signals: w_010_008, w_010_012, w_010_013, w_010_014, w_010_015, w_010_016, w_010_017, w_010_018, w_010_019, w_010_020, w_010_022, 
  Loop Gates: I010_006.port2, I010_008.port2, I010_009.port1, I010_010.port2, I010_011.port1, I010_012.port1, I010_013.port2, I010_014.port1, I010_015.port2, I010_016.port1, I010_017.port2, 

3)
  Loop Signals: w_016_016, w_016_017, w_016_018, w_016_019, w_016_020, w_016_021, w_016_022, w_016_023, w_016_024, w_016_025, 
  Loop Gates: I016_015.port1, I016_016.port1, I016_017.port2, I016_018.port2, I016_019.port1, I016_020.port1, I016_021.port2, I016_022.port1, I016_023.port1, I016_024.port1, 

******* result_3.txt *********
1)
  Loop Signals: w_006_012, w_006_013, w_006_014, w_006_015, w_006_016, 
  Loop Gates: I006_011.port2, I006_012.port1, I006_013.port1, I006_014.port1, I006_015.port1, 
  Loop Conditions: I006_011.port1=1, I006_012.port2=1, I006_013.port2=1, I006_015.port2=0, 
  (Singal Values: w_002_015=1, w_003_011=1, w_005_000=1, w_006_030=0, )

2)
  Loop Signals: w_010_004, w_010_005, w_010_006, w_010_007, w_010_008, 
  Loop Gates: I010_003.port1, I010_004.port2, I010_005.port1, I010_006.port1, I010_007.port1, 
  Loop Conditions: I010_003.port2=1, I010_004.port1=0, I010_005.port2=1, I010_006.port2=0, I010_007.port2=0, 
  (Singal Values: w_001_000=1, w_005_000=0, w_007_004=1, w_008_001=0, w_010_022=0, )

******* result_4.txt *********
1)
  Loop Breaker: w_006_012 

2)
  Loop Breaker: w_010_008 

// ******* The results for this case End *********
*/
