#pragma once

//#include <list>
#include <vector>
#include <queue>

#include "Job.h"
#include "ThreadManager.h"


class ThreadPool {
public:
    ThreadPool();
    ~ThreadPool();

	void Start();
    //void StartWithPriority();

	void Stop()					{ _isStoped = true; }
	void AddJob(Job& new_job)	{ _queue_job.emplace(new_job); };

private:
	void _rescueGateway();
	void _run();

    int  _nbThreadPref;
	bool _isStoped;
	std::vector<ThreadManager&> _pool;
	// std::list<Job>	_list_job; Todo it on ThreadPoolWithPriority
	std::queue<Job&>	_queue_job;
};
