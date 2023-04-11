#ifndef TASKQUEQUE_H_
#define TASKQUEQUE_H_

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

// Implementing a simple sync queue to save tasks as a task buffer in a threadPool ---- producer and comsuer design mode
template <typename T>
class TaskQueue {
public:
	TaskQueue(unsigned  int maxTaskSize);
	~TaskQueue() = default;
	void stop(); // stop taskqueue to use
	void EnTask(const T &task); // para is lvalue-ref, use function "add" to add a task to TaskQueue
	void EnTask(T &&task); // para is rvalue-ref, use function "add" to add a task to TaskQueue
	void DeTask(T &task);  // remove a task from TaskQueue
	void DeTask(std::list<T> &list); // remove all task to a list
	bool empty(); // check queue is empty
	bool full(); // check queue is full
	size_t size(); // get current number of tasks

private:
	// the max number of taskqueue can contain
	const unsinged int kMaxTaskSize_;
	// when constructing queue runs; when need stop queue, running false
	bool running_;
	std::queue<T> queue_;
	std::mutex mtx_;
	std::condition_variable notEmpty_cv_; // conditionally control consumer thread
	std::condition_variable notFull_cv_;  // conditionally control producer thread
	void NotFull() const; // after cv get lock to judge queue is not full
	void NotEmpty() const; // after cv get lock to judge queue is not empty
	template <typename F>
	void add(F &&f); // add a task to queue
};
#endif