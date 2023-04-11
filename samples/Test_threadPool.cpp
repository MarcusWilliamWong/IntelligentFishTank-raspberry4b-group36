#include <thread>
#include <iostream>
#include "threadPool.h"

int main() {
  ThreadPool pool;
  for (int i = 0; i < 50; ++i) {
    auto id = std::this_thread::get_id();
    pool.AddTask([id]{ std::cout << id << std::endl; });
  }
  
  return 0;
}