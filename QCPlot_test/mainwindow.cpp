#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtMath>
#define signal_size 4096
#define Fd 4096
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow ::makePlot();
    setWindowTitle("Plot and analiz");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::makePlot(){
    // generate some data:
    QVector<double> x(4096), y(4096); // initialize with entries 0..100
    for (int i=0; i<4096; ++i)
    {
      x[i] = i; // x goes from -1 to 1
      y[i] = 1 + qSin(x[i]/13);
    }
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("Time");
    ui->customPlot->yAxis->setLabel("Amplitude");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, 512);
    ui->customPlot->yAxis->setRange(-2, 2);

}

void MainWindow::on_pushButton_2_clicked()
{
    QVector<double> x(4096), y(4096); // initialize with entries 0..100
    for (int i=0; i<4096; ++i)
    {
      x[i] = i; // x goes from -1 to 1
      y[i] = qSin(x[i]/13 + 0.7*qSin(x[i]/7) + 0.3*qSin(x[i]/3));
    }
    double ac = 0;
    double sumSqBeg = 0;
    double sumSqEnd = 0;
    QVector <double> acf(signal_size);
    for(int i = 0; i < signal_size; i++)
    {
        ac = 0;
        sumSqBeg = 0;
        sumSqEnd = 0;
        for(int j = 0; j < signal_size - i; j++)
        {
            ac +=(y[j] * y[j + i]);
            sumSqBeg += y[j] * y[j];
            sumSqEnd += y[j + i] * y[j + i];
        }
        acf[i] = ac / sqrt(sumSqBeg * sumSqEnd);   // нормализуем АКФ
    }
    ui->customPlot_3->addGraph();
    ui->customPlot_3->graph(0)->setData(x, acf);
    ui->customPlot_3->xAxis->setLabel("X");
    ui->customPlot_3->yAxis->setLabel("Y");
    ui->customPlot_3->xAxis->setRange(0, 512);
    ui->customPlot_3->yAxis->setRange(-1, 1);
    ui->customPlot_3->replot();

    // поиск локальных минимумов
    int mins[signal_size];  // для хранения индексов локальных минимумов
    int mins_index = 0;
    for(int i = 0; i < signal_size - 1; ++i)
    {
        if(acf[i] < acf[i + 1])
        {
            mins[mins_index++] = i;
        }
        while(acf[i] < acf[i + 1]) i++;
    }

        // расчет частоты
    double rate = 0;
    int q_rate = mins_index;
   /* while (mins_index != 1) {
        mins_index--;
        rate += mins[mins_index] - mins[mins_index - 1];
    }*/
    for (mins_index; mins_index!=1;){
        rate += mins[--mins_index] - mins[--mins_index - 1];
    }
    //double sr_rate = rate/(q_rate - 1);
    //double d_time = (double)1/Fd;
    //double d_time4 = d_time * sr_rate;
    double frequency = (Fd*q_rate-Fd)/rate;
    QString valueFrec = QString::number(frequency);
    ui->label_4->setText(valueFrec);
}
