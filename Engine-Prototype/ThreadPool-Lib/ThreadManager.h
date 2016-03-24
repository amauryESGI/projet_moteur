#pragma once

#include <thread>
#include <condition_variable>
#include <functional>

class ThreadManager {
public:
    ThreadManager();
    virtual ~ThreadManager();

    void start();
    void stop();
    void join();

    void setJob(const std::function<void(void)>& f);

private:
    void _work();
    std::function<void(void)> _doJob;

    bool        _isStoped;
    bool        _isJoin;
    bool        _hasJob;
    bool        _isRunning;
    bool        _isDetached;
    std::thread _t;
    std::mutex  _mutex;
    std::condition_variable _condition_variable;
};