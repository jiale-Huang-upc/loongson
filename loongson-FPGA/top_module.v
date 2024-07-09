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
     input                 sys_clk      ,   //ϵͳʱ��
     input                 sys_rst_n    ,   //ϵͳ��λ

     input                 sel          ,   //����ģʽѡ��
     input                 sel1         ,   //ʵʱ����Ƶ��ѡ��
     input                 fifo_rst_n   ,   //FIFO���
     input     [7:0]       ad0_data     ,   //AD0����
     input                 fx_clk       ,   //����Ƶ��
       
     input                 sclk_i       ,   //SCK
     input                 cs_n_i       ,   //CS_n
     input                 mosi_i       ,   //MOSI
     output                miso_o       ,   //MISO
     output                ad0_clk      ,  //ʵʱ����ʱ��
     output                ad1_clk      ,    //��Ч����ʱ��
     
     output                da_clk       ,   //DAʱ��
     output   [7:0]        da_data      ,    //DA����


	 output					PULSE_G
     );
    
    wire clk_200m;
    wire clk_50m;
    wire clk_10m;
    wire clk_30m;
    wire clk_1m;
    wire clk_100k;
    wire locked;
   //ʱ�Ӳ���ģ��
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


//ʵ����ת������ģ��
	pulse pulse_get(
	.rst_n(sys_rst_n), //ϵͳ��λ���͵�ƽ��Ч
	.ad_clk(ad0_clk), //AD9280 ����ʱ��
	.ad_data(ad0_data), //AD ��������
	.ad_pulse(PULSE_G) //����������ź�
		);
    //Ƶ�ʲ���ģ��
    f_measure_module #(
    .CLK_FS(64'd50_000_000)) // ��׼ʱ��Ƶ��ֵ
    f_m
    (   //system clock
     .clk_fs (clk_50m),     // ��׼ʱ���ź�
     .rst_n  (locked),     // ��λ�ź�
     .clk_fx (PULSE_G),     // ����ʱ���ź�
     .flag   (flag  ),
	 .data_fx(data_fx)    // ����ʱ��Ƶ�����
);






    wire ad_clk_0;
    wire ad_clk_2;
    
    //����ʵʱ����1Mʱ��
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
    
    //��Ч����ʱ��ģ��
    ad_delay_module ad_delay(
    .fx_clk   (fx_clk),
    .rst_n      (sys_rst_n),
//    .locked_ad    (locked_ad),
    .ad_clk     (ad_clk_1));
    
    //ѡ�������ʽģ��
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

    //AD����ģ��
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
    
    //���CS�����Բ�����ʹ���ź�ģ��
    detect_module csget(
    .clk_200m(clk_200m),
    .rst_n   (locked),
    .cs_n_i  (cs_n_i),
    .rd_en   (rd_en));
    
    wire flag_f;
    
//    FIFOģ��
    fifo_module fifo(
    .wr_clk (ad0_clk) ,//д FIFO ʱ��
    .rd_clk (clk_200m),//�� FIFO ʱ��
    .rst_n  (fifo_rst_n),//��λ
    .wr_din (data_reg) ,//д�� FIFO ������
    .wr_en  (wr_en),//дʹ��
    .rd_en  (rd_en && flag_f),//��ʹ��
    .rd_dout(rd_dout)//�� FIFO ����������
 );
 

 
// fifo_new_module u_fifo(
//    .wr_clk (ad0_clk),//д FIFO ʱ��
//    .rd_clk (clk_200m),//�� FIFO ʱ��
//    .rst_n  (fifo_rst_n),//��λ
//    .wr_din (O_DOUT),//д�� FIFO ������
//    .wr_en  (wr_den),//дʹ��
//    .rd_en  (rd_en && flag_f),//��ʹ��
    
//    .rd_dout(rd_dout)//�� FIFO ����������
// );
 
 
    wire [63:0] out;
    
 
    //Ƶ��ֵ��AD�����л�ģ��
      mux2_module mux(
	.in_f      (data_fx)    ,
	.in_ad     (rd_dout)   ,//�����������
	.rd        (rd_en)    ,
	.rst_n     (locked)    ,
//	sel,//����ѡ���
    .flag_f    (flag_f)    ,
	.out       (out)//����źŶ�
);
 

    //SPI �ӻ�ģ��
    SPI_slave_module spi_slave(
    .clk     (clk_200m),  //50MHzʱ��
    .rst_n   (locked),  //��λ
    .data_in (out),  //Ҫ���͵�����
    .data_out(data_rec),  //���յ�������
    .spi_sck (sclk_i),  //����ʱ��
    .spi_miso(miso_o),  //���մӷ����ӻ���
    .spi_mosi(mosi_i),  //�������գ��ӻ���
    .spi_cs  (cs_n_i),  //����Ƭѡ������Ч���ӻ���
    .tx_en   (rd_en),  //����ʹ��
    .tx_done (),  //������ɱ�־λ
    .rx_done ()   //������ɱ�־λ
);

    //DAģ��
    DA_top_module dac(
    .sys_clk    (clk_50m),  //ϵͳʱ��
    .sys_rst_n  (sys_rst_n),  //ϵͳ��λ���͵�ƽ��Ч
    .da_clk     (da_clk),  //DA(AD9708)����ʱ��,���֧��125Mhzʱ��
    .da_data    (da_data)  //�����DA������
 );

//    //ILA�߼�����ģ��
//ila_0 your_instance_name (
//	.clk(clk_200m), // input wire clk
//	.probe0(ad0_clk), // input wire [0:0] probe0
//	.probe1(data_rec)
//);

endmodule
