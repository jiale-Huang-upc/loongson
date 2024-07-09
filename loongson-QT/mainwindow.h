#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <getdata.h>
#include <QMainWindow>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QTimer>
#include <QVector>
#include <QThread>
#include <QRadioButton>
#include <cctype>
#include <FFT.h>
#include "showdata.h"
#include "set_triger_vol.h"
#include "measure.h"
QT_CHARTS_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class Worker;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    int count;
    int max_x=200;
    int max_y=1;
    float cursor_x1,cursor_x2,cursor_y1=3.0,cursor_y2=-3.0;
    unsigned char isrun=1;
    float max_data=-4,min_data=4;
    int frequency=0;
    unsigned char lasty_position=100,lastx_position=100;
    unsigned char cursor_run=0;

    QTimer *timer = new QTimer(this);
    //QFile file;
    QChart* chart = new QChart();
    // 创建折线系列对象
    QLineSeries *series = new QLineSeries();
    QLineSeries *series_fft = new QLineSeries();
    QLineSeries *series_x1 = new QLineSeries();
    QLineSeries *series_x2 = new QLineSeries();
    QLineSeries *series_y1 = new QLineSeries();
    QLineSeries *series_y2 = new QLineSeries();
    QValueAxis *axisY,*axisX;
    int lastvalue;
    /* 全局线程 */
    QThread workerThread;
    /* 工人类 */
    Worker *worker;
    QButtonGroup *voltage;
    QButtonGroup *time;
    int maxx=1;
    QLabel * one = new QLabel;
    showdata m;
    set_triger_vol stv;
    measure mes;
    float diff_cursor_x;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();;
    void huitu();
    void updateData(float max_data,unsigned char m,int maxy);
    void updateData2(int maxx,int maxy);
    void huizhishuxian_x1(int x);
    void huizhishuxian_x2(int x);
    void huizhishuxian_y1(int y);
    void huizhishuxian_y2(int y);
    void diff();
    void showvf();
public slots:
    void handleTimeout();
    void dialChanged(int value);
    void dial2Changed(int value);
    void dial3Changed(int value);
    void dial4Changed(int value);
    void runorstop();
    void save();
    void open();
    void reset();
    void voltageClicked(int m);
    void timeClicked(int);
    void updateData_sigle(int m,int maxy);
    void FFT_WAVE();
    void cursor();
    void set_triger_fun();
    void measure_fun();
    void single();
private:
    Ui::MainWindow *ui;
signals:
     /* 工人开始工作（做些耗时的操作 ） */
     void startWork(const QString &);
};
class Worker : public QObject
{
     Q_OBJECT
     private:
     /* 互斥锁 */
     QMutex lock;
     /* 标志位 */
     bool isCanRun;
public slots:
  /* 耗时的工作都放在槽函数下，工人可以有多份不同的工作，但是每次只能去做一份 */
          void doWork1(const QString &parameter)
          {
            while(1)
            {
                qDebug()<<"线程结束"<<endl;
            }
          /* doWork1 运行完成，发送信号 */
          emit resultReady("打断 doWork1 函数");
          }
          // void doWork2();...
 public:
  /* 打断线程（注意此方法不能放在槽函数下） */

      void stopWork()
      {
          qDebug()<<"打断线程"<<endl;

          /* 获取锁后，运行完成后即解锁 */
          QMutexLocker locker(&lock);
          isCanRun = false;
      }
  signals:
  /* 工人工作函数状态的信号 */
        void resultReady(const QString &result);
 };
#endif // MAINWINDOW_H
