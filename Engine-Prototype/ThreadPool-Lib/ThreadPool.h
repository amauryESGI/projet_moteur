#pragma once

#include <vector>
#include <queue>

#include "Job.hpp"
#include "ThreadManager.h"


class ThreadPool {
public:
    ThreadPool();
    ~ThreadPool();

    void Start()                        { _t = std::thread(std::bind(&ThreadPool::_scheduler, this)); }
    void Stop()                         { _isStoped = true; _t.join(); }
	void AddJob(Job* new_job)           { _queue_job.emplace(new_job); };
	int  GetPreferedThreadQuantity()    { return _nbThreadPref; };

private:
    void _scheduler();
	void _rescueGateway();
	void _run();


    std::thread _t;
    unsigned int                _nbThreadPref;
	bool                        _isStoped;
    std::vector<ThreadManager*> _pool;
    std::queue<Job*>            _queue_job;
};
