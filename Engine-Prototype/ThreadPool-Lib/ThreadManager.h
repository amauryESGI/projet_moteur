#pragma once

#include <thread>
#include <condition_variable>

#include "Job.h"
#include "ThreadState.h"

class ThreadManager {
public:
    ThreadManager();
    virtual ~ThreadManager();

    void start();
    void stop();
    void join();

    void setJob(Job& newJob);
    ThreadState GetState() const {
        if (_currentJob.isBlocked())
            return BLOCK;
        return _currentState;
    }

private:
    void _work();

    Job&        _currentJob;
    ThreadState _currentState;
    bool        _isJoin;
    bool        _hasJob;
    std::thread _t;
    std::mutex  _mutex;
    std::condition_variable _condition_variable;
};
