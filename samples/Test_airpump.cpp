#include <pigpio.h>
#include <unistd.h>
#include "myds18b20.h"
#include "airpump.h"
#include "app.h"

int main() {
  App app;
  Airpump ap(4u);
  ap.start();
  ap.stop();

  return 0;
}