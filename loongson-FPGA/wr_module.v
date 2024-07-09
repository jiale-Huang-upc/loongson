`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/08/13 14:07:21
// Design Name: 
// Module Name: wr_module
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


module wr_module(
    input I_clk,
    input rst_n,
    input [7:0] ad_data,
    input trigger,
    
    output reg wr_en
    );
always @ (posedge trigger or negedge rst_n) 
    begin
        if (!rst_n)
            wr_en <= 0;      
        else begin
            wr_en <= ~wr_en;
        end
    end
endmodule
