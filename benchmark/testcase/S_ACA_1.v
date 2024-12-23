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
//

module combLogic( w1, w2, w3 );
  output w1, w2, w3;
  wire w1, w2, w3, w4, w5, w6, w7, w8, w9, wa;
  wire pin1, pin2, pin3, pin4, pin5, pin6, pin7, pin8, pin9;
  wire pin11, pin12, pin13, pin14;
  wire pin21, pin22, pin23, pin24;

  // loopA
  and2  I1(w01, w09, pin01);
  and2  I2(w02, w01, pin02);
  and2  I3(w03, w02, pin03);
  and2  I4(w04, w03, pin04);
  nand2 I5(w05, w04, pin05);
  and2  I6(w06, w05, pin06);
  and2  I7(w07, w06, pin07);
  and2  I8(w08, w07, pin08);
  and2  I9(w09, w08, pin09);

  and2  Ia1(w11,  w07, pin11);
  and2  Ia2(w12,  w11, pin12);
  and2  Ia3(w13,  w12, pin13);
  and2  Ia4(pin02, w13, pin14);

  and2  Ib1(w21,   w08, pin21);
  and2  Ib2(w22,   w21, pin22);
  and2  Ib3(w23,   w22, pin23);
  and2  Ib4(pin03, w23, pin24);

endmodule

// ****** Combined Logic Module Defination ******

// ****** TestBench Module Defination ******
module tb();

  wire p1, p2, p3, p4;

  combLogic I0(p1, p2, p3);

  initial begin
      $deposit(I0.w01,  1'b1);

      $deposit(I0.pin01, 1'b1);
      $deposit(I0.pin02, 1'b1);
      $deposit(I0.pin03, 1'b1);
      $deposit(I0.pin04, 1'b1);
      $deposit(I0.pin05, 1'b1);
      $deposit(I0.pin06, 1'b1);
      $deposit(I0.pin07, 1'b1);
      $deposit(I0.pin08, 1'b1);
      $deposit(I0.pin09, 1'b1);

      $deposit(I0.pin11, 1'b1);
      $deposit(I0.pin12, 1'b1);
      $deposit(I0.pin13, 1'b1);
      $deposit(I0.pin14, 1'b1);

      $deposit(I0.pin21, 1'b1);
      $deposit(I0.pin22, 1'b1);
      $deposit(I0.pin23, 1'b1);
      $deposit(I0.pin24, 1'b1);
#10;
      $finish;
  end
endmodule

