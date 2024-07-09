`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/16 20:26:53
// Design Name: 
// Module Name: ad_delay_module
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


module ad_delay_module(
    input           rst_n       ,
    input           fx_clk      ,
//    input   [63:0]  data_fx     ,
    
//    output          locked_ad   ,
    output          ad_clk
    
    );

    wire clk_40b;
    wire clk_20b;
    wire locked_ad;

    clk_wiz_1 instance_name_my
   (
    // Clock out ports
    .clk1_out(clk_40b),     // output clk_out1
    .clk2_out(clk_20b),     // output clk_out2
    // Status and control signals
    .reset(~rst_n), // input resetn
    .extlock(locked_ad),       // output locked
   // Clock in ports
    .refclk(fx_clk));      // input clk_in1
    
    wire add_cnt0,add_cnt1,end_cnt0,end_cnt1;
    
    reg [9:0] cnt_0;
    reg [9:0] cnt_1;
    
   parameter N = 20;

    always @(posedge clk_20b or negedge locked_ad) begin
        if (!locked_ad) begin
            cnt_0 <= 0;
        end
        else if(add_cnt0) begin
			 if(end_cnt0)
			 cnt_0 <= 0;
		 else
			 cnt_0 <= cnt_0 + 1;
		 end
    end
    assign add_cnt0 = 1 ;
	assign end_cnt0 = add_cnt0 && cnt_0 == N - 1 + 1;
    
//    always @(posedge clk_20b or negedge locked_ad)begin 
//		if(!locked_ad)begin
//		  cnt_1 <= 0;
//		end
//		else if(add_cnt1)begin
//		if(end_cnt1)
//		  cnt_1 <= 0;
//		else
//		  cnt_1 <= cnt_1 + 1;
//		end
//	end
//	assign add_cnt1 = end_cnt0;					//计数器0计数结束时，计数器1计数一次
//	assign end_cnt1 = add_cnt1 && cnt_1 == N - 1 ;//计数器1计数到100时结束
    
    reg [24:0]cnt;	//定义计数器寄存器
	reg EN;
	parameter CNT_MAX = 4'd8;  //0.5ms

	
	always@(posedge clk_20b or negedge locked_ad) begin
	   if(!locked_ad)
		  EN  <= 1'b0;
	   else if(end_cnt0)
		  EN  <= 1'b1;
	   else if(cnt == CNT_MAX)
		  EN  <= 1'b0;
	   else
		  EN  <= EN;
    end
assign ad_clk = EN;	

//计数器计数进程	
	always@(posedge clk_20b or negedge locked_ad ) begin
	   if(!locked_ad)
		  cnt <= 25'd0;
	   else if(cnt == CNT_MAX)
		  cnt <= 25'd0;
	   else if(EN)
		  cnt <= cnt + 1'b1;
	   else
		  cnt <= cnt;
    end
endmodule

