#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
#include <functional>
#include <future>
#include "threadPool.h"

int compute(int data) {
  if (1 == data || 0 == data) {
    return 1;
  }
  return compute(data - 1) * data;
}

// use std::bind 
auto f = std::bind(compute, 12);
std::function<int()> task1 = f;
// auto f = std::bind(compute, std::placeholders::_1);
// std::function<int(int)> task2 = f;

// use std::packaged_task
// std::packaged_task<int(int)> task(compute);
// std::future<int> func = task.get_future();


int main() {
  ThreadPool pool;
  // std::cout << task() << "\n";

  for (int i = 0; i < 50; ++i) {
    {
      std::mutex mtx;
      std::lock_guard<std::mutex> lock(mtx);
      std::cout << i << std::endl;
    }
    pool.AddTask(task1);
    pool.AddTask(task1);
    pool.AddTask(task1);

    auto id = std::this_thread::get_id();
    pool.AddTask([id]{
      {
        std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << id << std::endl;
      }
    });

  }
  // std::this_thread::sleep_for(std::chrono::seconds(2));
  return 0;
}