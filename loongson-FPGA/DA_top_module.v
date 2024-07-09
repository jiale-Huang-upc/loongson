`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/17 20:11:53
// Design Name: 
// Module Name: DA_top_module
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


module DA_top_module(
     input                 sys_clk     ,  //系统时钟
     input                 sys_rst_n   ,  //系统复位，低电平有效
     //DA芯片接口
     output                da_clk      ,  //DA(AD9708)驱动时钟,最大支持125Mhz时钟
     output    [7:0]       da_data       //输出给DA的数据
 );
 
 //wire define 
 wire      [7:0]    rd_addr;              //ROM读地址fj
 wire      [7:0]    rd_data;              //ROM读出的数据
 //*****************************************************
 //**                    main code
 //*****************************************************
 
wire clk_out1;
wire clk_out2;
wire locked;
 
 clk_wiz_2 instance_name_da
   (
    // Clock out ports
    .clk0_out(clk_out1),     // output clk_out1
    // Status and control signals
    .clk1_out(clk_out2),   //25.6MHZ
    .reset(~sys_rst_n), // input resetn
    .extlock(locked),       // output locked
   // Clock in ports
    .refclk(sys_clk));      // input clk_in1
 
 //DA数据发送
// DA_module u_da_wave_send(
//     .clk         (sys_clk), 
//     .rst_n       (locked),
//     .rd_data     (rd_data),
//     .rd_addr     (rd_addr),
//     .da_clk      (da_clk),  
//     .da_data     (da_data)
//     );
 

 dac da_wave_send(
     .clk         (clk_out2), 
     .rst_n       (locked),
     .rd_data     (rd_data),
     .rd_addr     (rd_addr),
     .da_clk      (da_clk),  
     .da_data     (da_data)
     );
 //ROM存储波形
// blk_mem_gen_0  u_rom_256x8b (
//   .clka  (clk_out1),    // input wire clka
//   .addra (rd_addr),    // input wire [7 : 0] addra
//   .doa (rd_data)     // output wire [7 : 0] douta
// );
 
 
 blk_mem_gen_0  u_rom_256x8b (
   .clka  (clk_out2),    // input wire clka
   .addra (rd_addr),    // input wire [7 : 0] addra
   .doa (rd_data)     // output wire [7 : 0] douta
 );

endmodule
