#ifndef GETDATA_H
#define GETDATA_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <linux/types.h>
void set_tri_vol(unsigned char a);
void chuli(unsigned char *rx_buf,float *rx_buf_float,int start,unsigned char m);
void chuli_2(unsigned char *rx_buf,float *rx_buf_float,int start,unsigned char m,unsigned char offset);
unsigned char getdata_fpga(float *rx_buf_float,int *frequency,int m,unsigned char vol);
unsigned char getdata_fpga_sigle(float *rx_buf_float,int *frequency,int m,unsigned char vol);
unsigned char getdata_fpga_2(float *rx_buf_float,int *frequency,unsigned char m);
unsigned char fpgainit();
#endif // GETDATA_H
