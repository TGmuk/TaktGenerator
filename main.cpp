#include "mbed.h"

DigitalOut takt(PC_7); //Ausgabe Frquenz
DigitalOut LED(PC_1);

InterruptIn hoch(PA_1);
InterruptIn runter(PA_6);

void ausgabe();

int hz = 6;

void init()
{
hoch.mode(PullDown);
hoch.rise(&plus);
hoch.enable_irq();

runter.mode(PullDown);
runter.rise(&plus);
runter.enable_irq();

RCC->APB1ENR |=0b10000;
TIM6->PSC=31999; //Takt 1ms
TIM6->ARR=hz; //ms warten
TIM6->CNT=0; //bei 0 beginnen
TIM6->SR=0; //UIF = 0
TIM6->CR1=1; //CEN=1 start

NVIC_SetVector(TIM6_IRQn,(uint32_t)&ausgabe);
HAL_NVIC_EnableIRQ(TIM6_IRQn);

}

void plus()
{
    if(hz < 480)
    {
        hz = hz + 6;
        TIM6->ARR=hz; //ms warten
    }
    else{}
    }

void minus()
{
    if(hz > 11)
    {
        hz = hz-6;
        TIM6->ARR=hz; //ms warten
    }
    else{}
}

void ausgabe()
{
    takt = !takt;
    LED = !LED;
}

int main()
{
    init();
    while (true) {
        
    }
}

