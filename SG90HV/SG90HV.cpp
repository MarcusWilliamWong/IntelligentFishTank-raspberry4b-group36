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

    int pin = 12;

    gpioSetMode(pin, PI_OUTPUT);
    gpioSetPWMfrequency(pin, 50);
    gpioSetPWMrange(pin, 100); // 20000us = 20ms
    // int i = 0;
    // gpioPWM(pin, 10);
    for(int i = 48; i <= 120; ++i) {
        cout << i*0.125 << endl;
        gpioPWM(pin, i*0.125);
        gpioSleep(PI_TIME_RELATIVE, 2, 0);
        // if (i == 0) {
        //     gpioPWM(pin, 20);
        //     // i++;
        // } else {
        //     gpioPWM(pin, 0);
        // }
        // gpioPWM(pin, 50);
        // gpioSleep(PI_TIME_RELATIVE, 4gpioDelay(4000);, 0);
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