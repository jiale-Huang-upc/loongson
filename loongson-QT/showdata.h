#ifndef SHOWDATA_H
#define SHOWDATA_H

#include <QWidget>

namespace Ui {
class showdata;
}

class showdata : public QWidget
{
    Q_OBJECT

public:
    explicit showdata(QWidget *parent = nullptr);
    ~showdata();
    Ui::showdata *ui2;
    void settext_1(float value);
    void settext_2(float value);
    void settext_3(float value);
    void settext_4(float value);
    void settext_5(float value);
    void settext_6(float value);
};

#endif // SHOWDATA_H
