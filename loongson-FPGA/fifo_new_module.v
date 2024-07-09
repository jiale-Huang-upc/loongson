`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/08/13 13:12:21
// Design Name: 
// Module Name: fifo_new_module
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


module fifo_new_module(
    input wr_clk ,//写 FIFO 时钟
    input rd_clk ,//读 FIFO 时钟
    input rst_n ,//复位
    input [7:0] wr_din ,//写入 FIFO 的数据
    input wr_en ,//写使能
    input rd_en ,//读使能
 
    output reg [63:0] rd_dout,//从 FIFO 读出的数据
    output reg rd_out_vld,    //从 FIFO 读出的数据有效指示信号
    output  full_pos_edge,
    output  empty_pos_edge
 );
 
   //信号定义
    wire [7:0] wr_data ;
    wire [63:0] q ;
 
//    wire wr_req ;
    reg wr_req;
    wire rd_req ;
    wire prog_full;
 
    wire rd_empty ;
    wire wr_full ;
 
    wire [12:0] wrusedw ;
    wire [9:0] rdusedw ;
    
    //FIFO 例化
     FIFO  fifo_generator_0_u(
  .rst          (~rst_n     ),
  .clkw       (wr_clk     ),   // input wire wr_clk
  .clkr       (rd_clk     ),   // input wire rd_clk
  .di          (wr_data    ),   // input wire [15 : 0] din
  .we        (wr_req     ),   // input wire wr_en
  .re        (rd_req     ),   // input wire rd_en
  .dout         (q          ),   // output wire [15 : 0] dout
  .full_flag         (wr_full    ),   // output wire full
  .empty_flag        (rd_empty   ),   // output wire empty
  .rdusedw(rdusedw    ),   // output wire [8 : 0] rd_data_count
  .wrusedw(wrusedw    )    // output wire [8 : 0] wr_data_count
);

     reg full_first;
 
 
    reg  [3:0]              state               ;
    //---------------------<状态机参数>-------------------------------------
    localparam S00           = 4'b0000           ;
    localparam S0           = 4'b0001           ;
    localparam S1           = 4'b0010           ;
    localparam S2           = 4'b0100           ;
    

    
    reg  pulse_r1;
    reg  pulse_r2;     //中间信号
    wire  trig_pos_edge;
    wire  full_neg_edge;
  
  always@(posedge wr_clk or negedge rst_n)begin
    if(!rst_n) begin
      pulse_r1 <= 0;
      pulse_r2 <= 0;
    end
    else begin
      pulse_r1 <= wr_en;
      pulse_r2 <= pulse_r1;
    end
  end

  assign trig_pos_edge = (pulse_r1 && ~pulse_r2) ? 1 : 0;  //检测到上升沿时, pos_edge输出一个时钟周期的高电平
    
always@(posedge wr_clk or negedge rst_n)begin
     if(!rst_n)begin
         state   <= S00;
         wr_req  <= 0 ;
     end
     else begin
         case(state)
             S00: begin
                 if(full_neg_edge)begin
                     wr_req  <= 0;
                     state   <= S2;
                 end
                 else begin
                     wr_req  <= 0;
                     state   <= S00;
                 end
             end
             S0: begin
                 if(wr_full  == 1'b1 && full_first)begin
                     wr_req  <= 0;
                     state   <= S1;
                 end
                 else begin
                     wr_req  <= wr_en;
                     state   <= S0;
                 end
             end
             S1: begin
                 if(rdusedw == 10'd24)begin
                     wr_req <= 0;
                     state  <= S2;
                 end
                 else begin
                     wr_req <= 0;
                     state  <= S1;
                 end
             end
             S2: begin
                 if(trig_pos_edge)begin
                     state   <= S0;
                     wr_req  <= wr_en;
                 end
                 else begin
                     state   <= S2;
                     wr_req  <= 0;
                 end
             end
            default:state   <= S0;
         endcase
     end
end
 
  

     assign wr_data = wr_din;//输入的数据
//     assign wr_req = (wr_full  == 1'b0 && ~full_first)?wr_en:1'b0;//非满才写
     assign rd_req = (rd_empty == 1'b0 )?rd_en:1'b0;//非空才读
     
     reg [1:0] D1,D2;
     
     always @(posedge wr_clk or negedge rst_n)begin
	    if(rst_n == 1'b0)begin
	        D1 <= 2'b11;
	        D2 <= 2'b11;
	    end
	    else begin
	        D1 <= {D1[0], wr_full};  	//D[1]表示前一状态，D[0]表示后一状态（新数据） 
	        D2 <= {D2[0], rd_empty};  	//D[1]表示前一状态，D[0]表示后一状态（新数据）
	    end
	end
	
//组合逻辑进行边沿检测

	assign  full_pos_edge = ~D1[1] & D1[0];
	assign  full_neg_edge =  D1[1] & ~D1[0];
	assign  empty_pos_edge = ~D2[1] & D2[0];

    always @(posedge wr_clk or negedge rst_n)begin
	    if(rst_n == 1'b0)begin
	       full_first <= 0;
	    end
	    else if(full_pos_edge)begin
	       full_first <= 1;
	    end
	    else if(full_first && rdusedw == 10'd24) begin
	       full_first <= 0;
	    end
	 end
     
     always @(posedge rd_clk or negedge rst_n)begin
        if(!rst_n)begin
         rd_dout <= 0;
        end
         else begin
         rd_dout <= q;
        end
     end
     always @(posedge rd_clk or negedge rst_n)begin
        if(!rst_n)begin
            rd_out_vld <= 1'b0;
        end
        else begin
            rd_out_vld <= rd_req;
        end
     end
 endmodule
