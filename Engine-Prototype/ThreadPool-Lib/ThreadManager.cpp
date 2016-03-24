#include "ThreadManager.h"

#include "ThreadManagerExceptions.hpp"


ThreadManager::ThreadManager() : _isStoped(true), _isJoin(false), _hasJob(false) {
    _t = std::thread(std::bind(&ThreadManager::_work, this));
}

ThreadManager::~ThreadManager() {
    join();
}

void ThreadManager::start() {
    _isStoped = false;
    _condition_variable.notify_one();
}

void ThreadManager::stop() {
    /*if (_isJoin) // can't stop if is join
        throw ThreadManagerExceptions(0);*/
    _isStoped = true;
}

void ThreadManager::join() {
    _isJoin = true;
    if (_isStoped)
        start();

    _t.join();
}

void ThreadManager::setJob(const std::function<void(void)>& f) {
    if (_hasJob)
        throw ThreadManagerExceptions(0);
    _doJob = f;
    _hasJob = true;
}

void ThreadManager::_work() {
    std::unique_lock<std::mutex> locker(_mutex);
    _condition_variable.wait(locker);

    do {
        if (_hasJob) {
            _doJob();
            _hasJob = false;
        } else
            std::this_thread::yield();

        if (_isStoped && !_isJoin)
            _condition_variable.wait(locker);

    } while (!_isJoin);
}


//void f() {
//
//    ThreadManager m;
//
//    try {
//        m.setJob(nullptr);
//    } catch (const ThreadManagerExceptions& e) {
//        e.what();
//    }
//    catch (const std::exception& e) {
//        e.what();
//    }
//}