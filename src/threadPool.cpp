#include <list>
#include "threadPool.h"
#include "taskQueue.h"

// construct taskQueue_ object
ThreadPool::ThreadPool(int numThreads = std::thread::hardware_concurrency()) : taskQueue_(ThreadPool::kMaxTaskSize_) {
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
  taskQueue_.EnTask(std::forward<Task>(task));
}

void ThreadPool::RunTask() {
  while (running_) {
    // get task from taskqueue
    std::list<Task> tmp_list;
    taskQueue_.DeTask(tmp_list);

    for (auto &task : tmp_list) {
      if (!running_) {
        return; // if stop thread pool, directly return
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