module get_fre
(
	sys_clk,
	rst    ,
	clk_ext,
	data_fx,				//可以用龙芯计算频率来节省FPGA的资源
    cnt_sys,
    cnt_ext,
    flag
);
output reg   flag;
input sys_clk,rst,clk_ext;
output reg [63:0] data_fx;
output  [63:0] cnt_sys;
output  [63:0] cnt_ext;
//reg [31:0] cnt_sys,cnt_ext;

//parameter DELAY=32'd99_999_999;		//1Hz
parameter DELAY=64'd399_999_999;		//0.5Hz
parameter CLK_FS = 64'd200_000_000;
//parameter DELAY=32'd50;

reg [31:0] ref_door_cnt;		//参考门计数器
reg ref_door;				//参考门
	
always @(posedge sys_clk or negedge rst)
if(!rst)
	ref_door_cnt<=DELAY;
else if(ref_door_cnt==DELAY)
	ref_door_cnt<=0;
else
	ref_door_cnt<=ref_door_cnt+1'b1;

always @(posedge sys_clk or negedge rst)
if(!rst)
	ref_door<=1'b0;
else if(ref_door_cnt==DELAY)
	ref_door<=~ref_door;
else
	ref_door<=ref_door;
	
reg real_door;				//真实门
always @(posedge clk_ext or negedge rst)
if(!rst)
	real_door<=1'b0;
else
	real_door<=ref_door;


reg [63:0] ref_cnt;			//参考时钟记数
always @(posedge sys_clk or negedge rst)
if(!rst)
	ref_cnt<=0;	
else if(!real_door)
	ref_cnt<=0;
else
	ref_cnt<=ref_cnt+1'b1;

reg [63:0] real_cnt;			//待测量信号记数
always @(posedge clk_ext or negedge rst)
if(!rst)
	real_cnt<=0;
else if(!real_door)
	real_cnt<=0;
else
	real_cnt<=real_cnt+1'b1;	

reg [63:0] cnt_ext_0;
reg [63:0] cnt_sys_0;
reg first_in;
always @(posedge sys_clk or negedge rst)
if(!rst)
begin
	cnt_ext_0<=0;
	cnt_sys_0<=0;
	first_in<=1'b1;
end
else if(!real_door)
begin
	first_in<=1'b0;
	if(first_in)
		cnt_ext_0<=real_cnt;
	else
		cnt_ext_0<=cnt_ext_0;
	if(first_in)
		cnt_sys_0<=ref_cnt;
	else
		cnt_sys_0<=cnt_sys_0;
end
else
begin
	cnt_ext_0<=cnt_ext_0;
	cnt_sys_0<=cnt_sys_0;
	first_in<=1'b1;
end

reg [63:0] cnt_ext_1;
reg [63:0] cnt_sys_1;

always @(posedge sys_clk or negedge rst)
if(!rst)
begin
	cnt_ext_1<=0;
	cnt_sys_1<=0;
end
else
begin
	cnt_ext_1<=cnt_ext_0;
	cnt_sys_1<=cnt_sys_0;
end

reg [63:0] cnt_ext_2;
reg [63:0] cnt_sys_2;

always @(posedge sys_clk or negedge rst)
if(!rst)
begin
	cnt_ext_2<=0;
	cnt_sys_2<=0;
end
else
begin
	cnt_ext_2<=cnt_ext_1;
	cnt_sys_2<=cnt_sys_1;
end

reg [63:0] cnt_ext_3;
reg [63:0] cnt_sys_3;

always @(posedge sys_clk or negedge rst)
if(!rst)
begin
	cnt_ext_3<=0;
	cnt_sys_3<=0;
end
else
begin
	cnt_ext_3<=cnt_ext_2;
	cnt_sys_3<=cnt_sys_2;
end

reg [63:0] cnt_ext_4;
reg [63:0] cnt_sys_4;

always @(posedge sys_clk or negedge rst)
if(!rst)
begin
	cnt_ext_4<=0;
	cnt_sys_4<=0;
end
else
begin
	cnt_ext_4<=cnt_ext_3;
	cnt_sys_4<=cnt_sys_3;
end

reg [63:0] cnt_ext;
reg [63:0] cnt_sys;

always @(posedge sys_clk or negedge rst)
if(!rst)
begin
	cnt_ext<=0;
	cnt_sys<=0;
end
else
begin
	cnt_ext<=cnt_ext_4;
	cnt_sys<=cnt_sys_4;
end
//计算被测信号频率
always @(posedge sys_clk or negedge rst) begin
    if(!rst) begin
        data_fx <= 64'd0;
        flag<=0;
    end
    else  begin
        data_fx <= CLK_FS * cnt_ext / cnt_sys ;
        flag<=1;
    end
end
endmodule 
