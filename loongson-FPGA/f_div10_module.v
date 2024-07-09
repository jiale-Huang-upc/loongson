`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/16 19:31:11
// Design Name: 
// Module Name: f_div10_module
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


module f_div10_module(
	input		clk,
	input		rst_n,
//	input  [63:0] data_fx,
	output reg 	clk_div
);
//参数
parameter N = 4'd10;

//内部信号
reg [3:0]	cnt;

//功能块
always@(posedge clk or negedge rst_n)begin
	if (!rst_n)begin
		cnt <= 0;
	end
	else if(cnt == N - 1 ) begin
		cnt <= 0;
	end
	else begin
		cnt <= cnt + 1;
	end
end

always@(posedge clk or negedge rst_n)begin
	if (!rst_n) begin
		clk_div <= 0;
	end
	else if (cnt <= (N/2)-1) begin
		clk_div <= 1;
	end
	else begin
		clk_div <= 0;
	end
end

endmodule
