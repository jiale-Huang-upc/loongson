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
     input                 sys_clk     ,  //ϵͳʱ��
     input                 sys_rst_n   ,  //ϵͳ��λ���͵�ƽ��Ч
     //DAоƬ�ӿ�
     output                da_clk      ,  //DA(AD9708)����ʱ��,���֧��125Mhzʱ��
     output    [7:0]       da_data       //�����DA������
 );
 
 //wire define 
 wire      [7:0]    rd_addr;              //ROM����ַfj
 wire      [7:0]    rd_data;              //ROM����������
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
 
 //DA���ݷ���
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
 //ROM�洢����
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
