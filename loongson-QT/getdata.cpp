#include<getdata.h>
#define SPI_IOC_WR 123
int fd;
void set_tri_vol(unsigned char a)
{
    unsigned char rx_buf[8]={0};
    rx_buf[0]=a;
    ioctl(fd, SPI_IOC_WR, rx_buf);
}
void chuli(unsigned char *rx_buf,float *rx_buf_float,int start,unsigned char m)
{
    int stat=start*8 / m;
    for(unsigned int i=0;i<8/m;i++)
    {
        int a=m*i;
        //rx_buf_float[stat]=(float)(rx_buf[a]*16+(rx_buf[a+1]>>4))*5/4096;
        rx_buf_float[stat]=((float)rx_buf[a]*2/256-1)*5;
        stat++;
    }
}
void chuli_2(unsigned char *rx_buf,float *rx_buf_float,int start,unsigned char m,unsigned char offset)
{
    int stat=start*8 / m+offset;
    for(unsigned int i=0;i<8/m;i++)
    {
        int a=m*i;
        //rx_buf_float[stat]=(float)(rx_buf[a]*16+(rx_buf[a+1]>>4))*5/4096;
        rx_buf_float[stat]=((float)rx_buf[a]*2/256-1)*5;
        stat++;
        if(stat>199)
            break;
    }
}
unsigned char fpgainit()
{
    char const *filename = "/dev/spi_fpga";
    fd = open(filename, O_RDWR);
    if(fd < 0)
    {
        return 0;
    }
    else return 1;
}
//yuanlaide
//unsigned char getdata_fpga(float *rx_buf_float,int *frequency,int m)
//{
//    //float rx_buf_float[4] = {0.0}
//    unsigned char rx_buf[8] = {0};
//    int status;
//    int geshu=0;
//    unsigned long val = 0;
//    unsigned char a=0;
//    for(int j = 0;j < 25*m;j++)
//    {
//        val = strtoul("55", NULL, 0);
//        rx_buf[0] = 0;
//        status = ioctl(fd, SPI_IOC_WR, rx_buf);
//        if (status < 0)
//        {
//                //ui->textBrowser->setText("spi ioctl error!\n");
//                return 0;
//        }
//        //de dao frequency
//        int p =rx_buf[0]+rx_buf[1];
//        int n =rx_buf[2]+rx_buf[3];
//        if(p==0&&n==0)
//        {
//            *frequency=rx_buf[5]*256*256+rx_buf[6]*256+rx_buf[7];
//        }
//        else
//        {
//            if(m<8)
//            {
//                chuli(rx_buf,rx_buf_float,geshu,m);
//                geshu++;
//            }
//            else
//            {
//                a=j%(m/8);
//                if(a==0)
//                {
//                    chuli(rx_buf,rx_buf_float,geshu,8);
//                    geshu++;
//                    a=0;
//                }
//            }
//        }
//    }
//    return geshu;
//}

//有问题
unsigned char getdata_fpga_2(float *rx_buf_float,int *frequency,unsigned char m)
{
    //float rx_buf_float[4] = {0.0}
    unsigned char rx_buf[8] = {0};
    int status;
    int geshu=0;
    unsigned char geshu_2=0;
    unsigned long val = 0;
    unsigned char break_flag=0;
    while(1)
    {
        val = strtoul("55", NULL, 0);
        rx_buf[0] = val;
        //status = ioctl(fd, SPI_IOC_WR, rx_buf);
        for(int k=0;k<8;k++)
        {
            if(rx_buf[k]==0)
            {
                for(int q = k;q<8;q++)
                {
                    rx_buf_float[geshu]= ((float)rx_buf[q]*2/256-1)*5;
                    geshu++;
                }
                break_flag=1;
                break;
            }
        }
        if(break_flag==1)break;
    }
    for(int j = 0;j < 25;j++)
    {
        val = strtoul("55", NULL, 0);
        rx_buf[0] = val;
        status = ioctl(fd, SPI_IOC_WR, rx_buf);
        if (status < 0)
        {
                //ui->textBrowser->setText("spi ioctl error!\n");
                return 0;
        }
        //de dao frequency
        int p =rx_buf[0]+rx_buf[1];
        int n =rx_buf[2]+rx_buf[3];
        if(p==0&&n==0)
        {
            *frequency=rx_buf[5]*256*256+rx_buf[6]*256+rx_buf[7];
        }
        else
        {
            //chuli(rx_buf,rx_buf_float,geshu,m);
            for(int e=0;e<8;e++)
            {
               rx_buf_float[geshu]=((float)rx_buf[e]*2/256-1)*5;
               geshu++;
               if(geshu>199)
                   break;
            }
        }
    }
    return geshu;
}
//带触发
/*unsigned char getdata_fpga(float *rx_buf_float,int *frequency,int m,unsigned char vol)
{
    //float rx_buf_float[4] = {0.0}
    unsigned char rx_buf[8] = {0};
    int status;
    int geshu=0;
    unsigned long val = 0;
    unsigned char offset =0;
    unsigned char a=0;
    unsigned char wait=0;
    while(1)
    {
        val = strtoul("55", NULL, 0);
        rx_buf[0] = 0;
        status = ioctl(fd, SPI_IOC_WR, rx_buf);
        unsigned char stop=0;
        if (status < 0)
        {
                //ui->textBrowser->setText("spi ioctl error!\n");
                return 0;
        }
        for(int b=0;b<8;b++)
        {
            //100bijiaohao
            if(wait<120)
            {
                if((abs(rx_buf[b]-vol)<2)&&(b>0))
                {
                    if(rx_buf[b]>rx_buf[b-1])
                    {
                        for(int los=b;los<8;los=los+m)
                        {
                            rx_buf_float[offset]= ((float)rx_buf[los]*2/256-1)*5;
                            offset++;
                        }
                        stop++;
                        break;
                    }
                }
            }
            else
            {
                stop++;
                break;
            }
        }
        wait++;
        if(stop)
            break;
    }
    for(int j = 0;j < 25*m;j++)
    {
        val = strtoul("55", NULL, 0);
        rx_buf[0] = 0;
        status = ioctl(fd, SPI_IOC_WR, rx_buf);
        if (status < 0)
        {
                //ui->textBrowser->setText("spi ioctl error!\n");
                return 0;
        }
        //de dao frequency
        int p =rx_buf[0]+rx_buf[1];
        int n =rx_buf[2]+rx_buf[3];
        if(p==0&&n==0)
        {
            *frequency=rx_buf[5]*256*256+rx_buf[6]*256+rx_buf[7];
        }
        else
        {
            if(m<8)
            {
                chuli_2(rx_buf,rx_buf_float,geshu,m,offset);
                geshu++;
            }
            else
            {
                a=j%(m/8);
                if(a==0)
                {
                    chuli_2(rx_buf,rx_buf_float,geshu,8,offset);
                    geshu++;
                    a=0;
                }
            }
        }
        if(m<8)
        {
            if((geshu*8/m+offset)>199)
                break;
        }
        else
        {
            if((geshu+offset)>199)
                break;
        }
    }
    return geshu;
}*/
unsigned char getdata_fpga(float *rx_buf_float, int *frequency, int m, unsigned char vol) // 带触发功能从 FPGA 设备获取数据，并处理成浮点数格式
{
    unsigned char rx_buf[8] = {0};
    int status;
    int geshu = 0;
    unsigned long val = 0;
    unsigned char offset = 0;
    unsigned char a = 0;
    unsigned char wait = 0;

    // 软件上升沿触发
    int previous_value = -1; // 前一个值，用于比较
    while (1)
    {
        val = strtoul("55", NULL, 0);
        rx_buf[0] = 0;
        status = ioctl(fd, SPI_IOC_WR, rx_buf);
        unsigned char stop = 0;
        if (status < 0)
        {
            // ui->textBrowser->setText("spi ioctl error!\n");
            return 0;
        }
        for (int b = 0; b < 8; b++)
        {
            if (wait < 120)
            {
                if ((rx_buf[b] >= vol) && (previous_value < vol))
                {
                    // 检测到上升沿
                    for (int los = b; los < 8; los += m)
                    {
                        rx_buf_float[offset] = ((float)rx_buf[los] * 2 / 256 - 1) * 5;
                        offset++;
                    }
                    stop++;
                    break;
                }
                previous_value = rx_buf[b]; // 更新前一个值
            }
            else
            {
                stop++;
                break;
            }
        }
        wait++;
        if (stop)
            break;
    }

    // 处理数据
    for (int j = 0; j < 25 * m; j++)
    {
        val = strtoul("55", NULL, 0);
        rx_buf[0] = 0;
        status = ioctl(fd, SPI_IOC_WR, rx_buf);
        if (status < 0)
        {
            // ui->textBrowser->setText("spi ioctl error!\n");
            return 0;
        }

        // 获取频率
        int p = rx_buf[0] + rx_buf[1];
        int n = rx_buf[2] + rx_buf[3];
        if (p == 0 && n == 0)
        {
            *frequency = rx_buf[5] * 256 * 256 + rx_buf[6] * 256 + rx_buf[7];
        }
        else
        {
            if (m < 8)
            {
                chuli_2(rx_buf, rx_buf_float, geshu, m, offset);
                geshu++;
            }
            else
            {
                a = j % (m / 8);
                if (a == 0)
                {
                    chuli_2(rx_buf, rx_buf_float, geshu, 8, offset);
                    geshu++;
                    a = 0;
                }
            }
        }

        if (m < 8)
        {
            if ((geshu * 8 / m + offset) > 199)
                break;
        }
        else
        {
            if ((geshu + offset) > 199)
                break;
        }
    }
    return geshu;
}

unsigned char getdata_fpga_sigle(float *rx_buf_float,int *frequency,int m,unsigned char vol)
{
    //float rx_buf_float[4] = {0.0}
    unsigned char rx_buf[8] = {0};
    int status;
    int geshu=0;
    unsigned long val = 0;
    unsigned char offset =0;
    unsigned char a=0;
    int wait=0;
    while(1)
    {
        val = strtoul("55", NULL, 0);
        rx_buf[0] = 0;
        status = ioctl(fd, SPI_IOC_WR, rx_buf);
        unsigned char stop=0;
        if (status < 0)
        {
                //ui->textBrowser->setText("spi ioctl error!\n");
                return 0;
        }
        for(int b=0;b<8;b++)
        {
            if(wait<500)
            {
                if(rx_buf[b]==vol)
                {
                    if(rx_buf[b]>rx_buf[b-1])
                    {
                        for(int los=b;los<8;los=los+m)
                        {
                            rx_buf_float[offset]= ((float)rx_buf[los]*2/256-1)*5;
                            offset++;
                        }
                        stop++;
                        break;
                    }
                }
            }
            else
            {
                stop++;
                break;
            }
        }
        wait++;
        if(stop)
            break;
    }
    for(int j = 0;j < 25*m;j++)
    {
        val = strtoul("55", NULL, 0);
        rx_buf[0] = 0;
        status = ioctl(fd, SPI_IOC_WR, rx_buf);
        if (status < 0)
        {
                //ui->textBrowser->setText("spi ioctl error!\n");
                return 0;
        }
        //de dao frequency
        int p =rx_buf[0]+rx_buf[1];
        int n =rx_buf[2]+rx_buf[3];
        if(p==0&&n==0)
        {
            *frequency=rx_buf[5]*256*256+rx_buf[6]*256+rx_buf[7];
        }
        else
        {
            if(m<8)
            {
                chuli_2(rx_buf,rx_buf_float,geshu,m,offset);
                geshu++;
            }
            else
            {
                a=j%(m/8);
                if(a==0)
                {
                    chuli_2(rx_buf,rx_buf_float,geshu,8,offset);
                    geshu++;
                    a=0;
                }
            }
        }
        if(m<8)
        {
            if((geshu*8/m+offset)>199)
                break;
        }
        else
        {
            if((geshu+offset)>199)
                break;
        }
    }
    return geshu;
}
