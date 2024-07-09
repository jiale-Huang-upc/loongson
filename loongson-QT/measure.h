#ifndef MEASURE_H
#define MEASURE_H

#include <QWidget>

namespace Ui {
class measure;
}

class measure : public QWidget
{
    Q_OBJECT

public:
    explicit measure(QWidget *parent = nullptr);
    ~measure();
    void comdata(float v_max,float v_min,float frequency,int mul);
private:
    Ui::measure *ui;
};

#endif // MEASURE_H
