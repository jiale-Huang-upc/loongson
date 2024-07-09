#include "measure.h"
#include "ui_measure.h"

measure::measure(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::measure)
{
    this->ui->setupUi(this);
    this->ui->lineEdit->setText(tr("%1").arg(5)+"  V");
    this->ui->lineEdit_2->setText(tr("%1").arg(-5)+"  V");
    this->ui->lineEdit_3->setText(tr("%1").arg(10)+"  V");
    this->ui->lineEdit_4->setText(tr("%1").arg(0)+"  V");
    this->ui->lineEdit_5->setText(tr("%1").arg(100)+"  us");
    this->ui->lineEdit_6->setText(tr("%1").arg(100)+" HZ");
}

measure::~measure()
{
    delete ui;
}
void measure::comdata(float v_max,float v_min,float frequency,int mul)
{
    this->ui->lineEdit->setText(tr("%1").arg(v_max)+"  V");
    this->ui->lineEdit_2->setText(tr("%1").arg(v_min)+"  V");
    this->ui->lineEdit_3->setText(tr("%1").arg(v_max-v_min)+"  V");
    this->ui->lineEdit_4->setText(tr("%1").arg(v_max+v_min)+"  V");
    switch(mul)
    {
        case 1:this->ui->lineEdit_6->setText(tr("%1").arg(frequency)+" HZ");
               this->ui->lineEdit_5->setText(tr("%1").arg(float(1000/frequency))+"  ms"); break;
        case 1000:this->ui->lineEdit_6->setText(tr("%1").arg(frequency/1000)+" KHZ");
               this->ui->lineEdit_5->setText(tr("%1").arg(float(1000000/frequency))+"  us"); break;
        case 1000000:this->ui->lineEdit_6->setText(tr("%1").arg(frequency/1000000)+" MHZ");
               this->ui->lineEdit_5->setText(tr("%1").arg(float(1000000/frequency))+"  us"); break;
        default:break;
    }
}
