/*#include "signal_generation.h"

signal::signal(){
    setPeriod(50);
    generationDots(2048,50,1);
}

signal::signal(int lenght, float frequency, float volume){
    setPeriod(frequency);
    generationDots(lenght,frequency,volume);
}

signal::~signal(){
    delete [] dots;
}

void signal::setPeriod(float frequency){
    period=1/frequency;
}

void signal::generationDots(int lenght, float frequency, float volume){
    dots = new float [lenght];
    int n;
    for(int a=0;a<lenght;a++) //устанавливаем цикл на длину сэмпла
    {
    n=volume*qSin(a*M_PI/period); //вычисление sine-волны
    dots[a]=n; //заносим вычисленное значение в буфер
    }
}*/
