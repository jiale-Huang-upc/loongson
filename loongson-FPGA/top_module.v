`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/07/16 19:59:54
// Design Name: 
// Module Name: top_module
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


module top_module(
     input                 sys_clk      ,   //系统时钟
     input                 sys_rst_n    ,   //系统复位

     input                 sel          ,   //采样模式选择
     input                 sel1         ,   //实时采样频率选择
     input                 fifo_rst_n   ,   //FIFO清空
     input     [7:0]       ad0_data     ,   //AD0数据
     input                 fx_clk       ,   //待测频率
       
     input                 sclk_i       ,   //SCK
     input                 cs_n_i       ,   //CS_n
     input                 mosi_i       ,   //MOSI
     output                miso_o       ,   //MISO
     output                ad0_clk      ,  //实时采样时钟
     output                ad1_clk      ,    //等效采样时钟
     
     output                da_clk       ,   //DA时钟
     output   [7:0]        da_data      ,    //DA数据


	 output					PULSE_G
     );
    
    wire clk_200m;
    wire clk_50m;
    wire clk_10m;
    wire clk_30m;
    wire clk_1m;
    wire clk_100k;
    wire locked;
   //时钟产生模块
    clk_wizz_0 pll_clk
   (
    // Clock out ports
    .clk0_out(clk_200m),     // output clk_out1
    .clk1_out(clk_50m),     // output clk_out2
    .clk2_out(clk_10m),     // output clk_out3
    .clk3_out(clk_30m),     // output clk_out3
    // Status and control signals
    .reset(~sys_rst_n), // input resetn
    .extlock(locked),       // output locked
   // Clock in ports
    .refclk(sys_clk));      // input clk_in1
    
    wire [63:0] data_fx;
    wire flag;
    

	wire PULSE_G;
//	get_fre fre(
//	.sys_clk(clk_200m),
//	.rst(sys_rst_n)    ,
//	.clk_ext(PULSE_G),
//	.data_fx(data_fx),
//    .flag(flag)
//	);


//实例化转换脉冲模块
	pulse pulse_get(
	.rst_n(sys_rst_n), //系统复位，低电平有效
	.ad_clk(ad0_clk), //AD9280 驱动时钟
	.ad_data(ad0_data), //AD 输入数据
	.ad_pulse(PULSE_G) //输出的脉冲信号
		);
    //频率测量模块
    f_measure_module #(
    .CLK_FS(64'd50_000_000)) // 基准时钟频率值
    f_m
    (   //system clock
     .clk_fs (clk_50m),     // 基准时钟信号
     .rst_n  (locked),     // 复位信号
     .clk_fx (PULSE_G),     // 被测时钟信号
     .flag   (flag  ),
	 .data_fx(data_fx)    // 被测时钟频率输出
);






    wire ad_clk_0;
    wire ad_clk_2;
    
    //产生实时采样1M时钟
     f_div10_module f_div(
	.clk(clk_10m),
	.rst_n(locked),
	.clk_div(clk_1m));
	
	 f_div10_module f_div2(
	.clk(clk_1m),
	.rst_n(locked),
	.clk_div(clk_100k));

    assign ad_clk_0 = (data_fx > 64'd11_000)? clk_1m:clk_100k;
//    assign ad_clk_0 = (1)? clk_1m:clk_100k;
    assign ad_clk_2 = (sel1)? clk_30m:ad_clk_0;

    wire ad_clk_1;
    wire locked_ad;
    
    //等效采样时钟模块
    ad_delay_module ad_delay(
    .fx_clk   (fx_clk),
    .rst_n      (sys_rst_n),
//    .locked_ad    (locked_ad),
    .ad_clk     (ad_clk_1));
    
    //选择采样方式模块
    transfer_module transfer(
    .sel        (sel),
    .clk_1      (ad_clk_2),
    .clk_2      (ad_clk_1),
    .ad_clk_fin (ad0_clk)
    );
    
//    assign ad1_clk = ad0_clk;
    assign ad1_clk = clk_30m;
    wire wr_en;
    wire [7:0]data_reg;
    wire fifo_rst;

    //AD驱动模块
    ADC_get_module adget(
   .ad0_clk     (ad0_clk)  ,
   .ad_data     (ad0_data)  ,
   .rst_n       (fifo_rst_n)  ,
   .fifo_rst    (fifo_rst)  ,
   .data_reg    (data_reg)  ,
   .wr_en       (wr_en));
    
    wire [7:0] O_DOUT;
    wire O_TRIG_ON;
    
    wire wr_den;
    wire [63:0] data_rec;
    wire [7:0] data_va;
 
// set_module u_set(
    
//    .clk        (clk_200m),
//    .rst_n      (locked),
//    .input_data (data_rec),
//    .wr_en      (wr_den),
    
//    .data_out   (data_va)
//    );
 
 
    
//    trigger u_trigger(
//   .I_CLK         (ad0_clk),   // clock, posedge valid
//   .I_RST         (),   // reset, high level reset
//   .I_DIN         (data_reg),
//   .I_DEN         (wr_en),
//   .I_TRIG_V_MAX  (8'd255),   // trigger range max value 
//   .I_TRIG_V_MIN  (8'd127),   // trigger range min value 
//   .I_T_MODE      (2'b01),   // trigger mode 00 free trig , 01 value inc trig,  10 value dec trig, 11 value trig both inc or dec
//   .O_DOUT        (O_DOUT),
//   .O_DOV         (),
//   .O_TRIG_ON     (O_TRIG_ON));     
    
   
    
//    wr_module wr_u(
//   .I_clk(ad0_clk),
//   .rst_n(fifo_rst_n),
//   .ad_data(O_DOUT),
//   .trigger(O_TRIG_ON),
   
//   .wr_en(wr_den)
//    );

    
    wire rd_en;
    wire [63:0]rd_dout;
    
    //检测CS边沿以产生读使能信号模块
    detect_module csget(
    .clk_200m(clk_200m),
    .rst_n   (locked),
    .cs_n_i  (cs_n_i),
    .rd_en   (rd_en));
    
    wire flag_f;
    
//    FIFO模块
    fifo_module fifo(
    .wr_clk (ad0_clk) ,//写 FIFO 时钟
    .rd_clk (clk_200m),//读 FIFO 时钟
    .rst_n  (fifo_rst_n),//复位
    .wr_din (data_reg) ,//写入 FIFO 的数据
    .wr_en  (wr_en),//写使能
    .rd_en  (rd_en && flag_f),//读使能
    .rd_dout(rd_dout)//从 FIFO 读出的数据
 );
 

 
// fifo_new_module u_fifo(
//    .wr_clk (ad0_clk),//写 FIFO 时钟
//    .rd_clk (clk_200m),//读 FIFO 时钟
//    .rst_n  (fifo_rst_n),//复位
//    .wr_din (O_DOUT),//写入 FIFO 的数据
//    .wr_en  (wr_den),//写使能
//    .rd_en  (rd_en && flag_f),//读使能
    
//    .rd_dout(rd_dout)//从 FIFO 读出的数据
// );
 
 
    wire [63:0] out;
    
 
    //频率值与AD数据切换模块
      mux2_module mux(
	.in_f      (data_fx)    ,
	.in_ad     (rd_dout)   ,//两个输入变量
	.rd        (rd_en)    ,
	.rst_n     (locked)    ,
//	sel,//数据选择端
    .flag_f    (flag_f)    ,
	.out       (out)//输出信号端
);
 

    //SPI 从机模块
    SPI_slave_module spi_slave(
    .clk     (clk_200m),  //50MHz时钟
    .rst_n   (locked),  //复位
    .data_in (out),  //要发送的数据
    .data_out(data_rec),  //接收到的数据
    .spi_sck (sclk_i),  //主机时钟
    .spi_miso(miso_o),  //主收从发（从机）
    .spi_mosi(mosi_i),  //主发从收（从机）
    .spi_cs  (cs_n_i),  //主机片选，低有效（从机）
    .tx_en   (rd_en),  //发送使能
    .tx_done (),  //发送完成标志位
    .rx_done ()   //接收完成标志位
);

    //DA模块
    DA_top_module dac(
    .sys_clk    (clk_50m),  //系统时钟
    .sys_rst_n  (sys_rst_n),  //系统复位，低电平有效
    .da_clk     (da_clk),  //DA(AD9708)驱动时钟,最大支持125Mhz时钟
    .da_data    (da_data)  //输出给DA的数据
 );

//    //ILA逻辑分析模块
//ila_0 your_instance_name (
//	.clk(clk_200m), // input wire clk
//	.probe0(ad0_clk), // input wire [0:0] probe0
//	.probe1(data_rec)
//);

endmodule
