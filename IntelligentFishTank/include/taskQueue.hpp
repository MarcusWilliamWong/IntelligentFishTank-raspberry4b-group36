#ifndef TASKQUEQUE_H_
#define TASKQUEQUE_H_

#define TAG_TASKQUEUE "taskqueue : "

// Test only
// #define DEBUG
#define DEBUG_TASKQUEUE

#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <utility>

// Implementing a simple sync queue to save tasks as a task buffer in a threadPool ---- producer and comsuer design mode
template <typename T>
class TaskQueue {
public:
	TaskQueue(unsigned int maxTaskSize = 80);
	~TaskQueue() = default;
	void stop(); // stop taskqueue to use
	void EnTask(const T &task); // para is lvalue-ref, use function "add" to add a task to TaskQueue
	void EnTask(T &&task); // para is rvalue-ref, use function "add" to add a task to TaskQueue
	void DeTask(std::list<T> &list); // remove all task to a list
  void DeTask(T &task);  // remove a task from TaskQueue
	bool empty(); // check queue is empty
	bool full(); // check queue is full
	size_t size(); // get current number of tasks

private:
	// the max number of taskqueue can contain
	const unsigned int kMaxTaskSize_;
	// when constructing queue runs; when need stop queue, running false
	bool running_;
	std::list<T> queue_;
	std::mutex mtx_;
	std::condition_variable notEmpty_cv_; // conditionally control consumer thread
	std::condition_variable notFull_cv_;  // conditionally control producer thread
	bool NotFull() const; // after cv get lock to judge queue is not full
	bool NotEmpty() const; // after cv get lock to judge queue is not empty
	template <typename F>
	void add(F &&f); // add a task to queue
};

template <typename T>
TaskQueue<T>::TaskQueue(unsigned int maxTaskSize) : kMaxTaskSize_(maxTaskSize), running_(true) {}

template <typename T>
void TaskQueue<T>::EnTask(const T &task) {
  add(task);
}

template <typename T>
void TaskQueue<T>::EnTask(T &&task) {
  #ifdef DEBUG_TASKQUEUE
  std::cout << TAG_TASKQUEUE << "EnTask here" << std::endl;
  #endif
  add(std::forward<T>(task)); //universal ref
}

template <typename T>
void TaskQueue<T>::DeTask(std::list<T> &list) {
  std::unique_lock<std::mutex> lock(mtx_);
  // if queue is empty, consumer thread will wait
  notEmpty_cv_.wait(lock, [this]{ return !running_ || NotEmpty(); });
  // queue is stopped, directly return, even if thread is woked up; avoid later action
  if (!running_) {
    return;
  }
  // move all tasks into outer list
  list = std::move(queue_);
  notFull_cv_.notify_one();
}

template <typename T>
void TaskQueue<T>::DeTask(T &task) {
  std::unique_lock<std::mutex> lock(mtx_);
  // if queue need run and not empty, thread will take a task to operate and queue remove the task
  // another word if queue is empty, consumer thread will wait
  notEmpty_cv_.wait(lock, [this]{ return !running_ || NotEmpty(); });  //use lambda experssion to give function "wait" a predicate
  // queue is stopped, directly return, even if thread is woked up; avoid later action
  if (!running_) {
    return;
  }
  // assign ref of front task to "task"
  task = queue_.front();
  // remove front task
  queue_.pop_front();
  // awake one awaiting thread which cannot operate because queue is full
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
bool TaskQueue<T>::NotFull() const {
  bool full = (queue_.size() >= kMaxTaskSize_);
  if (full) {
    #ifdef DEBUG
    std::cerr << TAG_TASKQUEUE << "TaskQueue is full!\n";
    #endif
  }
  return !full;
}

template <typename T>
bool TaskQueue<T>::NotEmpty() const {
  bool empty = queue_.empty();
  if (empty) {
    #ifdef DEBUG
    std::cerr << "TaskQueue is empty!\n";
    std::cerr << "Current thread " << std::this_thread::get_id() << " is awaiting!\n";
    #endif
  }
  return !empty;
}

template <typename T>
void TaskQueue<T>::stop() {
  // use block to control lock
  {
    std::lock_guard<std::mutex> lock(mtx_);
    running_ = false; // stop queue
  }
  // release all awaiting thread
  notEmpty_cv_.notify_all();
  notFull_cv_.notify_all();
}

template <typename T>
template <typename F>
void TaskQueue<T>::add(F &&f) {
  std::unique_lock<std::mutex> lock(mtx_);
  // if queue need run and not full, thread will continue operating
  notFull_cv_.wait(lock, [this]{ return !running_ || NotFull(); });
  // queue is stopped, directly return, even if thread is woked up
  if (!running_) {
    return;
  }
  // add a task
  queue_.push_back(std::forward<F>(f));
  // release one awaiting thread which is stopped because of queue empty
  notEmpty_cv_.notify_one();
}
#endif