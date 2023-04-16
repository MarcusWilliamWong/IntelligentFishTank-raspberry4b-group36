#include <thread>
#include <iostream>
int main() {
  std::cout << std::thread::hardware_concurrency();
  return 0;
}
