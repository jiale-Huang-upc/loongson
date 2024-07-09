#include "set_triger_vol.h"
#include "ui_set_triger_vol.h"

set_triger_vol::set_triger_vol(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::set_triger_vol)
{
    ui->setupUi(this);
    connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(close_slv()));
    connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(send_slv()));
    connect(ui->pushButton_3, SIGNAL(clicked()),this, SLOT(append_0()));
    connect(ui->pushButton_4, SIGNAL(clicked()),this, SLOT(append_1()));
    connect(ui->pushButton_5, SIGNAL(clicked()),this, SLOT(append_2()));
    connect(ui->pushButton_6, SIGNAL(clicked()),this, SLOT(append_3()));
    connect(ui->pushButton_7, SIGNAL(clicked()),this, SLOT(append_4()));
    connect(ui->pushButton_8, SIGNAL(clicked()),this, SLOT(append_5()));
    connect(ui->pushButton_9, SIGNAL(clicked()),this, SLOT(append_6()));
    connect(ui->pushButton_10, SIGNAL(clicked()),this, SLOT(append_7()));
    connect(ui->pushButton_11, SIGNAL(clicked()),this, SLOT(append_8()));
    connect(ui->pushButton_12, SIGNAL(clicked()),this, SLOT(append_9()));
    connect(ui->pushButton_13, SIGNAL(clicked()),this, SLOT(append_10()));
    connect(ui->pushButton_14, SIGNAL(clicked()),this, SLOT(clear()));
    connect(ui->pushButton_15, SIGNAL(clicked()),this, SLOT(append_fu()));
}

set_triger_vol::~set_triger_vol()
{
    delete ui;
}
void set_triger_vol::doubleSpinBoxValueChanged(double value)
{
    int m =value*25.5;
    this->ui->lineEdit->setText(tr("%1").arg(0));
}

void set_triger_vol::send_slv()
{
    this->vol=this->svol.toFloat();
    if( this->vol>5.0)
         this->vol=5.0;
    if( this->vol<-5.0)
         this->vol=-5.0;
    this->AD=(this->vol+5)*25.5;
    this->ui->lineEdit->setText(tr("%1").arg(this->AD));
//    set_tri_vol(this->AD);
}

void set_triger_vol::close_slv()
{
    this->close();
    this->svol="";
}
void set_triger_vol::append_0()
{
    this->ui->textBrowser->insertPlainText("0");
    this->svol=this->svol+"0";
}
void set_triger_vol::append_1()
{
    this->ui->textBrowser->insertPlainText("1");
    this->svol=this->svol+"1";
}
void set_triger_vol::append_2()
{
    this->ui->textBrowser->insertPlainText("2");
    this->svol=this->svol+"2";
}
void set_triger_vol::append_3()
{
    this->ui->textBrowser->insertPlainText("3");
    this->svol=this->svol+"3";
}
void set_triger_vol::append_4()
{
    this->ui->textBrowser->insertPlainText("4");
    this->svol=this->svol+"4";
}
void set_triger_vol::append_5()
{
    this->ui->textBrowser->insertPlainText("5");
    this->svol=this->svol+"5";
}
void set_triger_vol::append_6()
{
    this->ui->textBrowser->insertPlainText("6");
    this->svol=this->svol+"6";
}
void set_triger_vol::append_7()
{
    this->ui->textBrowser->insertPlainText("7");
    this->svol=this->svol+"7";
}
void set_triger_vol::append_8()
{
    this->ui->textBrowser->insertPlainText("8");
    this->svol=this->svol+"8";
}
void set_triger_vol::append_9()
{
    this->ui->textBrowser->insertPlainText("9");
    this->svol=this->svol+"9";
}
void set_triger_vol::append_10()
{
    this->ui->textBrowser->insertPlainText(".");
    this->svol=this->svol+".";
}
void set_triger_vol::clear()
{
    this->ui->textBrowser->clear();
    this->svol="";
}
void set_triger_vol::append_fu()
{
    this->ui->textBrowser->insertPlainText("-");
    this->svol=this->svol+"-";
}
