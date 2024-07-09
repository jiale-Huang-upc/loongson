module dac(
     input                 clk    ,  //时钟
     input                 rst_n  ,  //复位信号，低电平有效
     
     input        [7:0]    rd_data,  //ROM读出的数据
     output  reg  [7:0]    rd_addr,  //读ROM地址
     //DA芯片接口
     output                da_clk ,  //DA(AD9708)驱动时钟,最大支持125Mhz时钟
     output       [7:0]    da_data   //输出给DA的数据  
     );
     
     
 assign  da_clk = ~clk;       
 assign  da_data = rd_data;   //将读到的ROM数据赋值给DA数据端口
 //读ROM地址
 always @(posedge clk or negedge rst_n) begin
     if(rst_n == 1'b0)
         rd_addr <= 8'd0;
     else begin
             rd_addr <= rd_addr + 8'd1;   
     end            
 end
 

endmodule