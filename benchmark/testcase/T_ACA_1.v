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
  and2  I1(w1, w9, pin1);
  and2  I2(w2, w1, pin2);
  and2  I3(w3, w2, pin3);
  and2  I4(w4, w3, pin4);
  nand2 I5(w5, w4, pin5);
  and2  I6(w6, w5, pin6);
  and2  I7(w7, w6, pin7);
  and2  I8(w8, w7, pin8);
  and2  I9(w9, w8, pin9);

  and2  Ia1(w11, w4,  pin11);
  and2  Ia2(w12, w11, pin12);
  nand2 Ia3(w13, w12, pin13);
  and2  Ia4(pin2, w13, pin14);

  and2  Ib1(w21, w8,  pin21);
  and2  Ib2(w22, w21, pin22);
  nand2 Ib3(w23, w22, pin23);
  and2  Ib4(pin7, w23, pin24);

endmodule

// ****** Combined Logic Module Defination ******

// ****** TestBench Module Defination ******

module tb();

  wire p1, p2, p3, p4;

  combLogic I0(p1, p2, p3);

  initial begin
      $deposit(I0.w1,  1'b1);
      $deposit(I0.pin2, 1'b1);
      $deposit(I0.pin7, 1'b1);

      $deposit(I0.pin1, 1'b1);
      $deposit(I0.pin3, 1'b1);
      $deposit(I0.pin4, 1'b1);
      $deposit(I0.pin5, 1'b1);
      $deposit(I0.pin6, 1'b1);
      $deposit(I0.pin8, 1'b1);
      $deposit(I0.pin9, 1'b1);

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

