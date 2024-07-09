`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/17 20:10:53
// Design Name: 
// Module Name: DA_module
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


module DA_module(
     input                 clk    ,  //时钟
     input                 rst_n  ,  //复位信号，低电平有效
     
     input        [7:0]    rd_data,  //ROM读出的数据
     output  reg  [7:0]    rd_addr,  //读ROM地址
     //DA芯片接口
     output                da_clk ,  //DA(AD9708)驱动时钟,最大支持125Mhz时钟
     output       [7:0]    da_data   //输出给DA的数据  
     );
 
 //parameter
 //频率调节控制
 parameter  FREQ_ADJ = 8'd1;  //频率调节,FREQ_ADJ的值越大,最终输出的频率越低,范围0~255
 
 //reg define
 reg    [7:0]    freq_cnt  ;  //频率调节计数器
 
 //*****************************************************
 //**                    main code
 //*****************************************************
 assign  da_clk = ~clk;       
 assign  da_data = rd_data;   //将读到的ROM数据赋值给DA数据端口
 
 //频率调节计数器
 always @(posedge clk or negedge rst_n) begin
     if(rst_n == 1'b0)
         freq_cnt <= 8'd0;
     else if(freq_cnt == FREQ_ADJ)    
         freq_cnt <= 8'd0;
     else         
         freq_cnt <= freq_cnt + 8'd1;
 end
 
 //读ROM地址
 always @(posedge clk or negedge rst_n) begin
     if(rst_n == 1'b0)
         rd_addr <= 8'd0;
     else begin
         if(freq_cnt == FREQ_ADJ) begin
             rd_addr <= rd_addr + 8'd1;
         end    
     end            
 end
 

endmodule

