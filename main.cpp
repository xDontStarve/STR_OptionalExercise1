#include "mbed.h"
#include "ThisThread.h"

// main() runs in its own thread in the OS

DigitalOut led1(LED1); DigitalOut led2(LED2); DigitalOut led3(LED3);

Ticker timer;

int progress1=0, progress2=0, progress3=0;
int c1=2, c2=3, c3=4;
int p1=8, p2=12, p3=16;
int currentPeriodTime=0;
bool completed1=false, completed2=false, completed3=false;

void execute1(){ led1=1; progress1++;}

void execute2(){ led2=1; progress2++;}

void execute3(){ led3=1; progress3++;}

void period(){
    if (progress1==c1) completed1=true;
    if (progress2==c2) completed2=true;
    if (progress3==c3) completed3=true;
    
    if ((currentPeriodTime%p1==0) && completed1){
        progress1=0;
        completed1=false;
    }

    if ((currentPeriodTime%p2==0) && completed2){
        progress2=0;
        completed2=false;
    }

    if ((currentPeriodTime%p3==0) && completed3){
        progress3=0;
        completed3=false;
    }

    led1=0; led2=0; led3=0;
    currentPeriodTime++;
    if (c1<=c2 && !completed1){
        if (c1<=c3  && !completed1){
            execute1();
        }else if(!completed3){
            execute3();
        }
    }else if (c2<=c3 && !completed2){
        execute2();
    }else if(!completed3){
        execute3();
    }
}

int main()
{
    printf("Default tasks set to: T=((2,8);(3,12);(4,16)), to change this head to the code and change manually the c1-3 and p1-3.");
    timer.attach(&period, 1000ms);
    while (true) {
        printf("Current time: %d\n", currentPeriodTime);
        /*printf("Progress 1 = %d\n", progress1);
        printf("Progress 2 = %d\n", progress2);
        printf("Progress 3 = %d\n", progress3);
        */printf("=========================================\n");
        ThisThread::sleep_for(1000ms);
    }
}