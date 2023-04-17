#include <memory>
#include "app.h"

int main() {
  std::unique_ptr<App> app(new App());
  // app->run();

  return 0;
}