/*#ifndef SIGNAL_GENERATION_H
#define SIGNAL_GENERATION_H
#include <QtMath>
#include <QDialog>


class signal : public QObject
{
    Q_OBJECT
private:
    float wavefrequency,
          wavevolume,
          period,*dots;
    int lenght;
public:
    signal();
    ~signal();
    signal(int,float,float);
public slots:
    void setPeriod(float);
    void generationDots(int,float,float);
};


#endif // SIGNAL_GENERATION_H
*/
