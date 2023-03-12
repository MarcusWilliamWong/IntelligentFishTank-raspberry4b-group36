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
    while(1) {
        gpioWrite(pin, PI_HIGH);
        gpioSleep(PI_TIME_RELATIVE, 2, 500000);
        // gpioDelay(2000);
        gpioWrite(pin, PI_LOW);
        // gpioDelay(2000);
        gpioSleep(PI_TIME_RELATIVE, 2, 500000);
    }
    
    cout << "Hello" << endl;

    // gpioPWM(pin, 128);


    // terminate lib
    gpioTerminate();

    return 0;
}