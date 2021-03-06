#pragma once

#include <thread>
#include <condition_variable>

#include "Job.hpp"
#include "ThreadState.h"

class ThreadManager {
public:
    ThreadManager();
    virtual ~ThreadManager();

    void start();
    void stop();
    void join();

    bool HasJob() const { return _hasJob; }
    void SetJob(Job* newJob);
    ThreadState GetState() {
        if (_hasJob && !_currentJob->isBlocked())
            return BLOCK;
        return _currentState;
    }

private:
    void _work();

    Job*        _currentJob;
    ThreadState _currentState;
    bool        _isJoin;
    bool        _hasJob;
    std::thread _t;
    std::mutex  _mutex;
    std::condition_variable _condition_variable;
};
