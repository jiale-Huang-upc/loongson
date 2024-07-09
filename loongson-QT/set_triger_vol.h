#ifndef SET_TRIGER_VOL_H
#define SET_TRIGER_VOL_H

#include <QWidget>
#include "getdata.h"
namespace Ui {
class set_triger_vol;
}

class set_triger_vol : public QWidget
{
    Q_OBJECT

public:
    unsigned char AD=153;
    float vol=1.0;
    QString svol;
    explicit set_triger_vol(QWidget *parent = nullptr);
    ~set_triger_vol();
public slots:
    void close_slv();
    void send_slv();
    void doubleSpinBoxValueChanged(double);
    void append_0();
    void append_1();
    void append_2();
    void append_3();
    void append_4();
    void append_5();
    void append_6();
    void append_7();
    void append_8();
    void append_9();
    void append_10();
    void clear();
    void append_fu();
private:
    Ui::set_triger_vol *ui;
};

#endif // SET_TRIGER_VOL_H
