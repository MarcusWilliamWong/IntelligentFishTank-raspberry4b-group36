//PWM frequency must be around 50HZ，so that servo get wave of 20ms
//Clockwise, 2%-6%High, 6%-7%Mid, 7%-8%Low
//Anticlockwise, 10%-14%High, 9%-10%Mid, 8%-9%Low


#include <iostream>
#include <pigpio.h>

using namespace std;

int main() {
    if (gpioInitialise() < 0) {
        cout << "Failed" << endl;
    } else {
        cout << "PIGPIO is ready" << endl;
    }
    // const int RANGE = 

    int pin = 4;

    gpioSetMode(pin, PI_OUTPUT);
    // gpioSetPWMfrequency(pin, 200);
    gpioSetPWMrange(pin, 200); // 20000us = 20ms
    int i = 0;
    gpioPWM(pin, 100);
    gpioSleep(PI_TIME_RELATIVE, 4, 0);
    gpioPWM(pin, 200);
    while(0) {
        // if (i == 0) {
        //     gpioPWM(pin, 20);
        //     // i++;
        // } else {
        //     gpioPWM(pin, 0);
        // }
        // gpioPWM(pin, 50);
        // gpioSleep(PI_TIME_RELATIVE, 4, 0);
        // gpioPWM(pin, 50);
        // gpioSleep(PI_TIME_RELATIVE, 4, 0);
        // gpioDelay(4000);
        // gpioPWM(pin, 100);
        // gpioSleep(PI_TIME_RELATIVE, 4, 0);
        // gpioPWM(pin, 15);
        // gpioSleep(PI_TIME_RELATIVE, 4, 0);
        // gpioPWM(pin, 20);
        // gpioSleep(PI_TIME_RELATIVE, 4, 0);
    }

    // terminate lib
    gpioTerminate();

    return 0;
}
