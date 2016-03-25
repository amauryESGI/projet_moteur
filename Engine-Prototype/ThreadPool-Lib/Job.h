#pragma once
#include <functional>
#include <condition_variable>

class Job
{
public:
    Job();
	Job(const std::function<void(void)>& work, int priority = 10);
	~Job();

	int GetCurrentPriority();
    bool isBlocked() { return _mutex.try_lock(); }
    std::function<void(void)> task;

private:
	int _priority;
	unsigned long _old;
    std::mutex  _mutex;
};

