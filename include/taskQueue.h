#ifndef TASKQUEQUE_H_
#define TASKQUEQUE_H_
#include <mutex>
#include <semaphore>
// Implementing a simple thread-safe queue to save tasks
template <typename T>
class TaskQueue {
public:
	TaskQueue();
	~TaskQueue();
	bool empty(); // check queue is empty


private:
	std::queue<T> queque_;
	std::mutex mtx_; // mutex
	{

	}
};
#endif