#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include "threadPool.h"

int main() {
  
  ThreadPool pool;
  int data =0;
  for (int i = 0; i < 50; ++i) {
    
    auto id = std::this_thread::get_id();
    pool.AddTask([id, &data]{
      for (int i = 0; i < 100000; ++i) {
        data++;
        data *= 123;
      } 
      std::mutex mtx;
      
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << id << std::endl; 
      
    });
  }
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return 0;
}