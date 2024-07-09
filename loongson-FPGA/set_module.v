`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/08/13 21:29:32
// Design Name: 
// Module Name: set_module
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


module set_module(
    
    input clk,
    input rst_n,
    input [63:0] input_data,
    input wr_en,
    
    output reg [7:0] data_out
    );
    
    reg  pulse_r1,  pulse_r2;     //中间信号
    wire pos_edge,  neg_edge;
    
  always@(posedge clk or negedge rst_n)begin
    if(!rst_n) begin
      pulse_r1 <= 0;
      pulse_r2 <= 0;
    end
    else begin
      pulse_r1 <= wr_en;
      pulse_r2 <= pulse_r1;
    end
  end

  assign pos_edge = (pulse_r1 && ~pulse_r2) ? 1 : 0;  //检测到上升沿时, pos_edge输出一个时钟周期的高电平
  assign neg_edge = (~pulse_r1 && pulse_r2) ? 1 : 0;  //检测到下降沿时，neg_edge输出一个时钟周期的高电平
    
    reg [7:0] output_data;

    always @(*) begin
        output_data <= {input_data[56], input_data[57], input_data[58], input_data[59], 
                       input_data[60], input_data[61], input_data[62], input_data[63]};
    end
    
    reg  [3:0]              state               ;
     //---------------------<状态机参数>-------------------------------------//
    localparam S0           = 4'b0001           ;
    localparam S1           = 4'b0010           ;
    localparam S2           = 4'b0100           ;
    localparam S3           = 4'b1000           ;
    
    reg [7:0] data_reg;
    reg [7:0] data_reg_n;
    
    always@(posedge clk or negedge rst_n)
     begin
        if (!rst_n)
            data_reg <= 8'd0;
        else begin
            data_reg <= output_data;
        end
     end
    
    always@(posedge clk or negedge rst_n)begin
     if(!rst_n)begin
         state   <= S0;
         data_out <= 8'd127;
         data_reg_n <= 8'd127;
     end
     else begin
         case(state)
             S0: begin
                 if(data_reg != output_data && output_data < 8'd255 && output_data > 8'd0)begin
                    data_out <= data_reg_n;
                    state   <= S1;
                 end
                 else begin
                    data_out <= data_reg_n;
                    state   <= S0;
                 end
             end
             S1: begin
                 if(neg_edge)begin
                    data_out <= output_data;
                    data_reg_n <= output_data;
                    state   <= S0;
                 end
                 else begin
                    data_out <= data_reg_n;
                    state   <= S1;
                 end
             end
             default:state  <= S0;
             endcase
         end
     end
endmodule
