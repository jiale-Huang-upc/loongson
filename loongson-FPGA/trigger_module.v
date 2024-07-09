`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/08/11 20:27:23
// Design Name: 
// Module Name: trigger_module
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module trigger(
  I_CLK           ,   // clock, posedge valid
  I_RST           ,   // reset, high level reset
  I_DIN           ,
  I_DEN           ,
  I_TRIG_V_MAX    ,   // trigger range max value 
  I_TRIG_V_MIN    ,   // trigger range min value 
  I_T_MODE        ,   // trigger mode 00 free trig , 01 value inc trig,  10 value dec trig, 11 value trig both inc or dec
  O_DOUT          ,
  O_DOV           ,
  O_TRIG_ON       );     

parameter  DWL = 8;
localparam DMAX = (1 << DWL) - 1;

input            I_CLK         ;
input            I_RST         ;

input  [DWL-1:0] I_DIN           ;
input            I_DEN           ;
input  [2-1:0]   I_T_MODE        ;
input  [DWL-1:0] I_TRIG_V_MAX    ;
input  [DWL-1:0] I_TRIG_V_MIN    ;
output [DWL-1:0] O_DOUT          ;
output           O_DOV           ;
output           O_TRIG_ON       ;



reg   [DWL-1:0] din_Z1R            ; // previous din
reg   [DWL-1:0] din_d1R, din_d2R, din_Z1d1R ; 
reg             den_d1R, den_d2R            ;
reg   [DWL-1:0] t_v_max_R, t_v_min_R;
reg  W_trig_on;
reg  W_in_trig_range, W_din_increase, W_din_decrease;
reg  O_TRIG_ON;


assign O_DOUT = din_d2R;
assign O_DOV  = den_d2R;

// pipeline design
// I_DIN | din_d1R, din_Z1d1R | din_d2R
// I_DEN | den_d1R            | den_d2R
//       | W_in_trig_range    | O_DOUT   
//       | W_din_increase     | O_DOV    
//       | W_din_decrease     | O_TRIG_ON
//       | W_trig_on          |

always @ (posedge I_CLK ) begin
    t_v_max_R <= I_TRIG_V_MAX ;
    t_v_min_R <= I_TRIG_V_MIN ;
    din_d1R <= I_DIN;
    den_d1R <= I_DEN;
    din_d2R <= din_d1R;
    den_d2R <= den_d1R;
    O_TRIG_ON <= W_trig_on;
    din_Z1d1R <= din_Z1R;
    if(I_DEN) din_Z1R <= I_DIN;
end // always

always @ (*) begin
  if((din_d1R >= t_v_min_R) && (din_d1R <= t_v_max_R)) begin
    W_in_trig_range = 1'b1;
  end
  else begin
    W_in_trig_range = 1'b0;
  end
  if(din_d1R > din_Z1d1R) W_din_increase = 1'b1; else W_din_increase = 1'b0;
  if(din_d1R < din_Z1d1R) W_din_decrease = 1'b1; else W_din_decrease = 1'b0;
  // trigger mode 00 free trig , 01 value inc trig,  10 value dec trig, 11 value trig both inc or dec
  case (I_T_MODE)
    2'b00:  begin W_trig_on = 1'b1; end
    2'b01:  begin W_trig_on = (W_din_increase && W_in_trig_range); end
    2'b10:  begin W_trig_on = (W_din_decrease && W_in_trig_range); end
    2'b11:  begin W_trig_on = (den_d1R && W_in_trig_range) ; end
  endcase
end // always
endmodule // module 
