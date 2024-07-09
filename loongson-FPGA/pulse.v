module pulse(
	input rst_n, //系统复位，低电平有效

//	input [13:0] trig_level,
	input ad_clk, //AD9280 驱动时钟
	input [7:0] ad_data, //AD 输入数据

	output ad_pulse //输出的脉冲信号
);
	parameter THR_DATA = 3;
	reg pulse;
 	reg pulse_delay;
 	assign ad_pulse = pulse & pulse_delay;
	parameter trig_level = 8'd127;
 //根据触发电平，将输入的 AD 采样值转换成高低电平
 	always @ (posedge ad_clk or negedge rst_n)begin
 		if(!rst_n)
 			pulse <= 1'b0;
 		else begin
 			if((trig_level >= THR_DATA) && (ad_data < trig_level - THR_DATA))
 				pulse <= 1'b0;
 			else if(ad_data > trig_level + THR_DATA)
 				pulse <= 1'b1;
 		end 
 	end

 //延时一个时钟周期，用于消除抖动
 	always @ (posedge ad_clk or negedge rst_n)begin
		if(!rst_n)
 			pulse_delay <= 1'b0;
		else
 			pulse_delay <= pulse;
 	end

endmodule