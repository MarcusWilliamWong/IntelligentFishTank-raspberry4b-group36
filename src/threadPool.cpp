/*
 * This file is part of OurProject.
 * See LICENSE file in the project root for full license information.
 */
#include <list>
#include "taskQueue.hpp"
#include "threadPool.h"

// construct taskQueue_ object
ThreadPool::ThreadPool(int numThreads) : taskQueue_(kMaxTaskSize_) {
  start(numThreads);  // manually start
}

ThreadPool::~ThreadPool() {
  stop(); // manually stop
}

void ThreadPool::start(int numThreads) {
  running_ = true;
  // create threads
  for (int i = 0; i < numThreads; ++i) {
    threads_.push_back(std::make_shared<std::thread>(&ThreadPool::RunTask, this));
  }
}

void ThreadPool::stop() {
  std::call_once(stop_once_flag_, [this]{ stopThreads(); });
}

void ThreadPool::AddTask(const Task &task) {
  taskQueue_.EnTask(task);
}

void ThreadPool::AddTask(Task &&task) {
  #ifdef DEBUG_THREADPOOL
  std::cout << TAG_THREADPOOL << "AddTask here" << std::endl;
  #endif
  taskQueue_.EnTask(std::forward<Task>(task));
}

void ThreadPool::RunTask() {
  while (running_) {
    std::list<Task> tmp_list;
    // get task from taskqueue
    taskQueue_.DeTask(tmp_list);
    // sequential execution
    for (auto &task : tmp_list) {
      // if stop thread pool, directly return
      if (!running_) {
        return; 
      }
      // operate task
      task();
    }
    
  }
}

void ThreadPool::stopThreads() {
  taskQueue_.stop(); // stop use taskqueue
  running_ = false; // set running

  for (auto thread : threads_) {
    // join all running threads
    if (thread && thread->joinable()) {
      thread->join();
    }
  }
  // clear all object in thread pool
  threads_.clear();
}