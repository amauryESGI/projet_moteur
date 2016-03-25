#pragma once
#include <functional>
#include <condition_variable>
#include "../GameObject-Lib/Component.h"

class Job
{
public:
    Job(const std::function<void(int, int)> work, int begin, int end, int priority = 10)
        : task(work), _begin(begin), _end(end), _priority(priority) {}
    ~Job() {}

	int GetCurrentPriority();
    bool isBlocked() { return _mutex.try_lock(); }
    std::function<void(int, int)> task;

    int GetBegin()  { return _begin; }
    int GetEnd()    { return _end; }

private:
    int             _begin;
    int             _end;
	int             _priority;
	unsigned long   _old;
    std::mutex      _mutex;
};

