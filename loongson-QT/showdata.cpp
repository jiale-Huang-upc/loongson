#include "showdata.h"
#include "ui_showdata.h"
#include"math.h"
showdata::showdata(QWidget *parent) :
    QWidget(parent),
    ui2(new Ui::showdata)
{
    ui2->setupUi(this);
}

showdata::~showdata()
{
    delete ui2;
}
//可以在这ms、us
void showdata::settext_1(float value)
{
    if(value>1000)
    {
        ui2->lineEdit->setText(tr("%1").arg(value/1000)+"   ms");
    }
    else if(value<0.1)
    {
        ui2->lineEdit->setText(tr("%1").arg(value*1000)+"   ns");
    }
    else
        ui2->lineEdit->setText(tr("%1").arg(value)+"   us");
}
void showdata::settext_2(float value)
{
     if(value>1000)
     {
        ui2->lineEdit_2->setText(tr("%1").arg(value/1000)+"   ms");
     }
     else if(value<0.1)
     {
         ui2->lineEdit_2->setText(tr("%1").arg(value*1000)+"   ns");
     }
     else
        ui2->lineEdit_2->setText(tr("%1").arg(value)+"   us");
}
void showdata::settext_3(float value)
{
    if(value*value<0.01)
    {
        ui2->lineEdit_3->setText(tr("%1").arg(value*1000)+"   mv");
    }
    else
         ui2->lineEdit_3->setText(tr("%1").arg(value)+"   V");
}
void showdata::settext_4(float value)
{
    if(value*value<0.01)
    {
        ui2->lineEdit_4->setText(tr("%1").arg(value*1000)+"   mv");
    }
    else
         ui2->lineEdit_4->setText(tr("%1").arg(value)+"   V");
}
void showdata::settext_5(float value)
{
    if(value>1000||value<-1000)
    {
        ui2->lineEdit_5->setText(tr("%1").arg(value/1000)+"   ms");
    }
    else if(value*value<0.01)
    {
        ui2->lineEdit_5->setText(tr("%1").arg(value*1000)+"   ns");
    }
    else
        ui2->lineEdit_5->setText(tr("%1").arg(value)+"   us");
}
void showdata::settext_6(float value)
{
    if(value*value<0.01)
    {
        ui2->lineEdit_6->setText(tr("%1").arg(value*1000)+"   mv");
    }
    else
        ui2->lineEdit_6->setText(tr("%1").arg(value)+"   V");
}
