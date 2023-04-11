#include <queue>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <utility>
#include "taskQueue.h"

template <typename T>
TaskQueue<T>::TaskQueue(unsigned int maxTaskSize) : TaskQueue<T>::kMaxTaskSize_(maxTaskSize), running_(true) {}

template <typename T>
void TaskQueue<T>::EnTask(const T &task) {
  add(task);
}

template <typename T>
void TaskQueue<T>::EnTask(T &&task) {    
  add(std::forward<T>(task)); //universal ref
}

template <typename T>
void TaskQueue<T>::DeTask(T &task) {
  std::unique_lock<std::mutex> lock(mtx);
  // if queue need run and not empty, thread will take a task to operate and queue remove the task
  // another word if queue is empty, consumer thread will wait
  notEmpty_cv_.wait(lock, [this]{ return !running_ || NotEmpty(); });  //use lambda experssion to give function "wait" a predicate
  // queue is stopped, directly return, even if thread is woked up; avoid later action
  if (!running_) {
    return;
  }
  // assign ref of front task to "task"
  task = std::move(queue_.front());
  // remove front task
  queue_.pop();
  // awake one onwaiting thread which cannot operate because queue is full
  notFull_cv_.notify_one();
}

template <typename T>
void TaskQueue<T>::DeTask(std::list<T> &list) {
  std::unique_lock<std::mutex> lock(mtx_);
  notEmpty_cv_.wait(lock, []{ return !running_ || NotEmpty(); });
  if (!running_) {
    return;
  }
  // move all tasks into list
  list = std::move(queue_);
  notFull_cv_.notify_one();
}

template <typename T>
bool TaskQueue<T>::empty() {
  std::lock_guard<std::mutex> lock(mtx_);
  return queue_.empty();
}

template <typename T>
bool TaskQueue<T>::full() {
  std::lock_guard<std::mutex> lock(mtx_);
  return (size() >= TaskQueue<T>::kMaxTaskSize_);
}

template <typename T>
size_t TaskQueue<T>::size() {
  std::lock_guard<std::mutex> lock(mtx_);
  return queue_.size();
}

template <typename T>
void TaskQueue<T>::NotFull() const {
  bool full = (queque_.size() >= TaskQueue<T>::kMaxTaskSize_);
  if (full) {
    std::cerr << "TaskQueue is full!\n";
  }
  return !full;
}

template <typename T>
void TaskQueue<T>::NotEmpty() const {
  bool empty = queque_.empty();
  if (empty) {
    std::cerr << "TaskQueue is empty!\n";
  }
  return !empty;
}

template <typename T> 
template <typename F>
void TaskQueue<T>::add(F &&f) {
  std::unique_lock<std::mutex> lock(mtx_);
  // if queue need run and not full, thread will continue operating
  notFull_cv_.wait(lock, [this]()->{ return !running_ || NotFull(); });
  // queue is stopped, directly return, even if thread is woked up
  if (!running_) {
    return;
  }
  // add a task
  queue_.push(std::forward<F>(f))
  // release one onwaiting thread which is stopped because of queue empty
  notEmpty_cv_.notify_one();
}

template <typename T>
void TaskQueue<T>::stop() {
  // use block to control lock
  {
    std::lock_guard<std::mutex> lock(mtx_);
    running_ = false; // stop queue
  }
  // release all onwaiting thread
  notEmpty_cv_.notify_all();
  notFull_cv_.notify_all();
}