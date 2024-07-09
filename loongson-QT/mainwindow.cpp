#include "mainwindow.h"
#include "ui_mainwindow.h"
//200 jiaohao
#define TIMER_TIMEOUT  100
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //chu shi hua fpga lian jie
    if(!fpgainit())
    {
        QMessageBox::warning(this, "WARNING", "Unable to connect to FPGA");
    }
    timer->start(TIMER_TIMEOUT);
    chart->setBackgroundVisible(false);
    //ui->widget->setStyleSheet(" background-image:url(:/home/linaro/Desktop/loongson.png);");
    //ui->widget->setStyleSheet(R"( background-image:url(:/home/linaro/Desktop/loongson.png);)");
    connect(timer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    connect(ui->dial,SIGNAL(sliderMoved(int)),this,SLOT(dialChanged(int)));
    connect(ui->dial_2,SIGNAL(sliderMoved(int)),this,SLOT(dial2Changed(int)));
    connect(ui->dial_3,SIGNAL(sliderMoved(int)),this,SLOT(dial3Changed(int)));
    connect(ui->dial_4,SIGNAL(sliderMoved(int)),this,SLOT(dial4Changed(int)));
    connect(ui->pushButton_6, SIGNAL(clicked()),this, SLOT(runorstop()));
    connect(ui->pushButton_7, SIGNAL(clicked()),this, SLOT(save()));
    connect(ui->pushButton_8, SIGNAL(clicked()),this, SLOT(open()));
    connect(ui->pushButton_9, SIGNAL(clicked()),this, SLOT(reset()));
    connect(ui->pushButton_10, SIGNAL(clicked()),this, SLOT(FFT_WAVE()));
    connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(cursor()));
    connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(set_triger_fun()));
    connect(ui->pushButton_3, SIGNAL(clicked()),this, SLOT(measure_fun()));
    connect(ui->pushButton_4, SIGNAL(clicked()),this, SLOT(single()));
    huitu();
    //she zhi chu shi zhi
    ui->dial->setValue(100);
    ui->dial->setRange(0,200);
    ui->dial->setNotchesVisible(true);
    ui->dial->setSingleStep(20);
    ui->dial_2->setValue(100);
    ui->dial_2->setRange(0,200);
    ui->dial_2->setNotchesVisible(true);
    ui->dial_2->setSingleStep(20);
    ui->dial_3->setValue(100);
    ui->dial_3->setRange(0,200);
    ui->dial_3->setNotchesVisible(true);
    ui->dial_3->setSingleStep(20);
    ui->dial_4->setValue(100);
    ui->dial_4->setRange(0,200);
    ui->dial_4->setNotchesVisible(true);
    ui->dial_4->setSingleStep(20);

    voltage = new QButtonGroup(this);
    voltage->addButton(ui->radioButton,0);
    voltage->addButton(ui->radioButton_2,1);
    voltage->addButton(ui->radioButton_3,2);
    voltage->addButton(ui->radioButton_7,3);

    time = new QButtonGroup(this);
    time->addButton(ui->radioButton_4,0);
    time->addButton(ui->radioButton_5,1);    chart->addSeries(series_fft);
    float FFT_real[256]={0};
    float FFT_image[256]={0};
    float amp[256]={0};
    float real_freq[256]={0};
    QList<QPointF> oldData = series->points();
    QList<QPointF> Data;
    for(int i =0;i<oldData.size();i++)
    {
        FFT_real[i]=oldData.at(i).y();
    }
    FFT(FFT_real,FFT_image,256);
    for (int i = 0; i < 256; i++)
    {
            amp[i] = 2*(sqrt(((FFT_real[i])*(FFT_real[i]) + (FFT_image[i])*(FFT_image[i])))/256);
            real_freq[i] = 200 * i / 256;
            Data.append(QPointF(real_freq[i],amp[i]));
    }
    series_fft->replace(Data);
    time->addButton(ui->radioButton_6,2);
    time->addButton(ui->radioButton_8,3);
    ui->radioButton->setChecked(1);
    ui->radioButton_5->setChecked(1);

    connect(voltage, SIGNAL(buttonClicked(int)), this, SLOT(voltageClicked(int)));
    connect(time, SIGNAL(buttonClicked(int)), this, SLOT(timeClicked(int)));
}

MainWindow::~MainWindow()
{
    /* 打断线程再退出 */
    worker->stopWork();
    workerThread.quit();
    /* 阻塞线程 2000ms，判断线程是否结束 */
    if (workerThread.wait(2000))
    {
        qDebug()<<"线程结束"<<endl;
    }
    delete ui;
}
//修改光标线的位置
void MainWindow::diff()
{
    m.settext_5(cursor_x1-cursor_x2);
    m.settext_6(cursor_y1-cursor_y2);
}
void MainWindow::huizhishuxian_x1(int x)
{
    QList<QPointF> Data;
    Data.append(QPointF(x,5));
    Data.append(QPointF(x,-5));
    series_x1->replace(Data);
    cursor_x1=(float)x;
    switch(maxx)
    {
        case 3:cursor_x1=cursor_x1/10*diff_cursor_x;break;
        case 1:cursor_x1=cursor_x1*4*diff_cursor_x;break;
        case 4:cursor_x1=cursor_x1*4*diff_cursor_x;break;
        case 200:cursor_x1=cursor_x1*1000*diff_cursor_x;break;
    }
    m.settext_1(cursor_x1);
    diff();
}
void MainWindow::huizhishuxian_x2(int x)
{
    QList<QPointF> Data;
    Data.append(QPointF(x,5));
    Data.append(QPointF(x,-5));
    series_x2->replace(Data);
    cursor_x2=(float)x;
    switch(maxx)
    {
        case 3:cursor_x2=cursor_x2/10*diff_cursor_x;break;  //2US  20
        case 1:cursor_x2=cursor_x2*diff_cursor_x;break;                           //20US  200
        case 8:cursor_x2=cursor_x2*8*diff_cursor_x;break; //320US  3200
        case 200:cursor_x2=cursor_x2*1000*diff_cursor_x;break; //20MS  200000
    }
    m.settext_2(cursor_x2);
    diff();
}
void MainWindow::huizhishuxian_y1(int y)
{
    QList<QPointF> Data;
    float y1=(float)(y-100)/20;
    Data.append(QPointF(1,y1));
    cursor_y1=y1/max_y;
    m.settext_3(cursor_y1);
    Data.append(QPointF(200,y1));
    series_y1->replace(Data);
    diff();
}
void MainWindow::huizhishuxian_y2(int y)
{
    QList<QPointF> Data;
    float y2=(float)(y-100)/20;
    cursor_y2=y2/max_y;
    Data.append(QPointF(1,y2));
    m.settext_4(cursor_y2);
    Data.append(QPointF(200,y2));
    series_y2->replace(Data);
    diff();
}

void MainWindow::huitu()
{
        QFont labelsFont;
        labelsFont.setPixelSize(15);   //参数字号，数字越小，字就越小

        axisX = new QValueAxis();//X轴
        axisX->setRange(0,10);            //设置X轴范围
        axisX->setTitleText("时间");      //设置X轴标题
        //axisX->setMinorTickCount(20);
        axisX->setLabelsFont(labelsFont);
        axisY = new QValueAxis();//定义Y轴
        axisY->setRange(-4,4);           //设置Y轴范围
        axisY->setTitleText("电压值");      //设置Y轴标题
        axisY->setTickCount(9);
        axisY->setMinorTickCount(10);
        axisX->setTickCount(11);
//        axisX->setMinorTickCount(10);
        axisY->setLabelsFont(labelsFont);
        chart->addAxis(axisX,Qt::AlignBottom);//把横轴添加到图表
        chart->addAxis(axisY,Qt::AlignLeft);//把纵轴添加到图表

         series_fft->attachAxis(axisX);
         series_fft->attachAxis(axisX);

        // 使用append添加数据点
        for (double i = 0; i < max_x; i+=1)
        {
            series->append(i, 8*sin(i*3.14*4/180));
        }
        // 设置折线的标题
        series->setName("龙芯国产示波器");
        // 折线系列添加到图表,//openGl 加速
        //series->setUseOpenGL(true);
        chart->addSeries(series);
        // 基于已添加到图表的 series 来创建默认的坐标轴
//        chart->createDefaultAxes();
        // chart图表添加到ChartView的对象
        ui->widget->setChart(chart);
//        ui->widget->chart()->setTheme(QChart::ChartThemeBlueCerulean);
}

void MainWindow::updateData(float max_data,unsigned char m,int maxy)
{
    int i;
    QList<QPointF> oldData = series->points();
    QList<QPointF> data;
//    if (oldData.size() < 200)
//    {
//        data = series->points();
//    }
//    else
//    {
//        for (i = 1; i < oldData.size(); ++i)
//        {
//            data.append(QPointF(i - 1 , oldData.at(i).y()));
//        }
//    }
//    qint64 size = data.size();
    /* 这里表示插入新的数据，因为每次只插入1个，这里为i < 1,
     * 但为了后面方便插入多个数据，先这样写
     */
    for(i = 0; i < 200; ++i){
        data.append(QPointF(i,max_data*0.9*maxy*sin(3.14 * i / 200*m+count)));
        count++;
    }
    series->replace(data);
}
void MainWindow::showvf()
{
    int mul=1;
    if(frequency > 1000000)
    {
         ui->lineEdit->setText(tr("%1").arg((float)frequency/1000000)+"  MHZ");
         mul=1000000;
    }
    else if (frequency > 1000)
    {
         ui->lineEdit->setText(tr("%1").arg((float)frequency/1000)+"  kHZ");
         mul=1000;
    }
    else
    {
         ui->lineEdit->setText(tr("%1").arg((float)frequency)+"  HZ");
         mul=1;
    }
    max_data=max_data*0.95;
    ui->lineEdit_2->setText(tr("%1").arg(max_data)+"  v");
    if(mes.isVisible())
    {
        mes.comdata(max_data,min_data,frequency,mul);
    }
}
void MainWindow::updateData2(int m,int maxy)
{
    int i;
    float data_fpga[200]={0};
    QList<QPointF> data;
    int max;
    unsigned char stat;
    if(m==3)
    {
        stat=getdata_fpga(data_fpga,&frequency,1,stv.AD);
    }
    else
        stat=getdata_fpga(data_fpga,&frequency,m,stv.AD);
    if(m<9)
    {
        if(m==3)
            max=8*stat;
        else
           max=(float)8/m*stat;
    }
    else
         max=stat;
    for(i = 0; i < max; ++i)
     {
            if(data_fpga[i]>max_data)
                max_data=data_fpga[i];
            if(data_fpga[i]<min_data)
                min_data=data_fpga[i];
            if(m==3)
                data.append(QPointF(i ,data_fpga[i/20]*2*maxy));
            else
                data.append(QPointF(i ,data_fpga[i]*2*maxy));
     }
     series->replace(data);
     showvf();
     max_data=0;
     min_data=0;
}
void MainWindow::updateData_sigle(int m,int maxy)
{
    int i;
    float data_fpga[200]={0};
    QList<QPointF> data;
    int max;
    unsigned char stat;
    if(m==3)
    {
        stat=getdata_fpga_sigle(data_fpga,&frequency,1,stv.AD);
    }
    else
        stat=getdata_fpga_sigle(data_fpga,&frequency,m,stv.AD);
    if(m<9)
    {
        if(m==3)
            max=8*stat;
        else
           max=(float)8/m*stat;
    }
    else
         max=stat;
    for(i = 0; i < max; ++i)
     {
            if(data_fpga[i]>max_data)
                max_data=data_fpga[i];
            if(data_fpga[i]<min_data)
                min_data=data_fpga[i];
            if(m==3)
                data.append(QPointF(i ,data_fpga[i/20]*2*maxy));
            else
                data.append(QPointF(i ,data_fpga[i]*2*maxy));
     }
     series->replace(data);
     showvf();
     max_data=0;
     min_data=0;
}
void MainWindow::handleTimeout()
 {
    if(isrun)
    {
        updateData2(maxx,max_y);
    }
    if(frequency<11000)
    {
        ui->radioButton_4->setText("2us/div");
        ui->radioButton_5->setText("100ns/div");
        ui->radioButton_8->setText("10us/div");
        ui->radioButton_6->setText("20ms/div");
        diff_cursor_x=10;
        //diff_cursor_x=(float)1.0/30;
    }
    else if(frequency<500000)
    {
        ui->radioButton_4->setText("2us/div");
        ui->radioButton_5->setText("100ns/div");
        ui->radioButton_8->setText("10us/div");
        ui->radioButton_6->setText("20ms/div");
        diff_cursor_x=1;
        //diff_cursor_x=(float)1.0/30;
    }
    else if(frequency<5000000)
    {
        ui->radioButton_4->setText("2us/div");
        ui->radioButton_5->setText("100ns/div");
        ui->radioButton_8->setText("10us/div");
        ui->radioButton_6->setText("20ms/div");
        diff_cursor_x=(float)1.0/30;
        //diff_cursor_x=1;
    }
    else
    {
        float diff_fre=(float)frequency/50000;
        QString str1 = QString::number((2/diff_fre)*1000, 'f', 2);
        ui->radioButton_4->setText(tr("%1").arg(str1+"ns/div"));
        QString str2 = QString::number((20/diff_fre)*1000, 'f', 2);
        ui->radioButton_5->setText(tr("%1").arg(str2+"ns/div"));
        QString str3 = QString::number(320/diff_fre, 'f', 2);
        ui->radioButton_8->setText(tr("%1").arg(str3+"us/div"));
        QString str4 = QString::number(20/diff_fre, 'f', 2);
        ui->radioButton_6->setText(tr("%1").arg(str4+"ms/div"));
        diff_cursor_x=1.0/(20*(float)frequency/1000000);
    }
 }
void MainWindow::dialChanged(int value)
{
//    ui->lineEdit->setText(tr("%1").arg(value));
    if(cursor_run)
    {
        huizhishuxian_x1(value);
    }
    else
    {
        if(value>lastvalue)
            chart->zoom(1.12);
        else if(value<lastvalue)
            chart->zoom(0.9);
        lastvalue=value;
    }
}
void MainWindow::dial2Changed(int value)
{
    if(cursor_run)
    {
        huizhishuxian_y2(value);
    }
    else
    {
      if(value>lastx_position)
            chart->scroll(-3,0);
      else
            chart->scroll(3,0);
      lastx_position=value;
    }
}
void MainWindow::dial3Changed(int value)
{
    if(cursor_run)
    {
        huizhishuxian_y1(value);
    }
    else
    {
        if(value>lasty_position)
              chart->scroll(0,-3);
        else
              chart->scroll(0,3);
        lasty_position=value;
    }
}
//波形的扩张显示
void MainWindow::dial4Changed(int value)
{
    if(cursor_run)
    {
        huizhishuxian_x2(value);
    }
    else
    {
        QList<QPointF> oldData = series->points();
        QList<QPointF> data;
        for(int i = 0; i < oldData.size(); ++i){
            data.append(QPointF(i*value/50,oldData.at(i).y()));
        series->replace(data);
        }
    }
}
//void MainWindow::dial4Changed(int value)
//{
//    QList<QPointF> oldData = series->points();
//    QList<QPointF> data;
//    for(int i = 0; i < oldData.size(); ++i){
//        data.append(QPointF(i*value/50,oldData.at(i).y()));
//    series->replace(data);
//    }
//}
void MainWindow::reset()
{
    chart->zoomReset();
    ui->dial->setValue(100);
    ui->dial_2->setValue(100);
    ui->dial_3->setValue(100);
    ui->dial_4->setValue(100);
    chart->removeSeries(series_fft);
    one->close();
}
//void MainWindow::handleResults(const QString & results)
//{
// /* 打印线程的状态 */
// qDebug()<<"线程的状态："<<results<<endl;
//}
void MainWindow::runorstop()
{
    if(isrun)
    {
       isrun=0;
    }
    else
       isrun=1;
}
void MainWindow::save()
{
    QString SaveFile;
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap p = screen->grabWindow(ui->widget->winId());
    QImage image = p.toImage();
    //image.save("/home/linaro/Desktop/chart.png");
    SaveFile =QFileDialog::getSaveFileName(this,tr("保存文件"),"wave.jpg");
    if (SaveFile != "")
    {
        image.save(SaveFile);
    }
    else
    {
         QMessageBox::warning(this, "WARNING", "Incorrect file name");
    }
}

void MainWindow::open()
{
//QLabel * one = new QLabel;
one->resize(780,540);
QString OpenFile;
QImage image;
QColor oldColor;
OpenFile = QFileDialog::getOpenFileName(this,
            "please choose an image file",
            "",
            "Image Files(*.jpg *.png *.bmp *.pgm *.pbm);;All(*.*)");
if (OpenFile != "")
        {
            if (image.load(OpenFile))
            {
                one->setPixmap(QPixmap::fromImage(image).scaled(one->size()));
                one->show();
            }
        }
else
    {
            QMessageBox::warning(this, "WARNING", "Incorrect file name");
    }

}
void MainWindow::voltageClicked(int m)
{
    switch(m)
    {
        case 0:max_y=1;break; //1v
        case 1:max_y=1;break;  //0.1v
        case 2:max_y=1;break;   //0.002v
        case 3:max_y=1;break;
    }
}
void MainWindow::timeClicked(int m)
{
    //ui->lineEdit_2->setText(tr("%1").arg(m));
    switch(m)
    {
        case 0:maxx=16;break; //2us   20
        case 1:maxx=32;break; //20us  200
        case 2:maxx=8;break;//20ms
        case 3:maxx=16;break;//320us;  3200
    }
}

void MainWindow::FFT_WAVE()
{
    series_fft->setName("FFT_WAVE");
    chart->addSeries(series_fft);
    float FFT_real[256]={0};
    float FFT_image[256]={0};
    float amp[256]={0};
    float real_freq[256]={0};
    QList<QPointF> oldData = series->points();
    QList<QPointF> Data;
    for(int i =0;i<oldData.size();i++)
    {
        FFT_real[i]=oldData.at(i).y();
    }
    FFT(FFT_real,FFT_image,256);
    for (int i = 0; i < 256; i++)
    {
            amp[i] = 2*(sqrt(((FFT_real[i])*(FFT_real[i]) + (FFT_image[i])*(FFT_image[i])))/256);
            real_freq[i] = 200 * i / 256;
            Data.append(QPointF(real_freq[i],amp[i]));
    }
    series_fft->replace(Data);
}
void MainWindow::cursor()
{
    if(cursor_run==0)
    {
        m.show();
        chart->addSeries(series_x1);
        series_x1->attachAxis(axisX);
        series_x1->attachAxis(axisX);
        m.settext_1(90.0);
        series_x1->append(90,5);
        series_x1->append(90,-5);
        chart->addSeries(series_x2);
        series_x2->attachAxis(axisX);
        series_x2->attachAxis(axisX);
        m.settext_2(110.0);
        series_x2->append(110,5);
        series_x2->append(110,-5);

        chart->addSeries(series_y1);
        series_y1->attachAxis(axisX);
        series_y1->attachAxis(axisX);
        series_y1->attachAxis(axisY);
        series_y1->attachAxis(axisY);
        m.settext_3(3.0);
        series_y1->append(1,3);
        series_y1->append(200,3);
        chart->addSeries(series_y2);
        series_y2->attachAxis(axisX);
        series_y2->attachAxis(axisX);
        series_y2->attachAxis(axisY);
        series_y2->attachAxis(axisY);
        series_y2->setColor(QColor(Qt::red));
        m.settext_4(-3.0);
        series_y2->append(1,-3);
        series_y2->append(200,-3);
        cursor_run=1;
        m.settext_5(-20.0);
        m.settext_6(6.0);
    }
    else
    {
        m.close();
        chart->removeSeries(series_x1);
        series_x1->clear();
        chart->removeSeries(series_x2);
        series_x2->clear();
        chart->removeSeries(series_y1);
        series_y1->clear();
        chart->removeSeries(series_y2);
        series_y2->clear();
        cursor_run=0;
    }
}
void MainWindow::set_triger_fun()
{
    if(stv.isVisible())
    {
        stv.close();
    }
    else
    {
        stv.show();
//        QRectF rect = chart->geometry();
//        int x = rect.x() + this->width() /2;
//        int y = rect.y() + this->height()/2;
//        stv.move(x,y);
    }
}
void MainWindow::measure_fun()
{
    if(mes.isVisible())
    {
        mes.close();
    }
    else
    {
        mes.show();
        QRectF rect = chart->geometry();
        int x = rect.width()/2-250;
        int y = rect.height()/2-250 ;
        mes.move(x,y);
    }
}
void MainWindow::single()
{
     updateData_sigle(maxx,max_y);
     isrun=0;
     this->save();
}
