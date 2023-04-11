#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <vector>
#include <thread>
#include <memory>
#include <functional>
#include <atomic>
#include "taskQueue.h"

// implement a class to manage a group of threads
class ThreadPool {
public:
	// define "Task" as a functor without parameters and return nothing
	using Task = std::function<void()>;
	// default get CPU number of cores  -> 4
	ThreadPool(int numThreads = std::thread::hardware_concurrency());
	void start(int numThreads); // start specific number thread pool manually
	void stop();  // stop thread pool manually, call once function "stopThreads"
	void AddTask(const Task &task);  // lv-ref add task to taskqueue of thread pool
	void AddTask(Task &&task); // rl-ref add task to taskqueue of thread pool
private:
	const unsigned int kMaxTaskSize_ = 80;  // define max number of tasks in task queue
	TaskQueue<Task> taskQueue_;  // save tasks
	std::vector<std::shared_ptr<std::thread>> threads_; // a group of threads, use smart ptr to manage thread
	std::atomic<bool> running_;  // atomic symbol presents thread pool running status
	std::once_flag stop_once_flag_; // when stop thread pool, we only need to stop once, enven if many threads call stop
	void RunTask();  // if running is true, cycle run task in thread pool
	void stopThreads(); // stop thread pool and recycle resources
};
#endif


