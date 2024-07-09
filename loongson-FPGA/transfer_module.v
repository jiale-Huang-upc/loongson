`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/16 21:07:38
// Design Name: 
// Module Name: transfer_module
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


module transfer_module(
    input sel,
    input clk_1,
    input clk_2,
    
    output ad_clk_fin
    );
    
    assign ad_clk_fin = (sel)? clk_1:clk_2;
    
endmodule
