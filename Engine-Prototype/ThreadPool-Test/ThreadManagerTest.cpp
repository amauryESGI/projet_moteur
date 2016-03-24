#include "ThreadManagerTest.h"


ThreadManagerTest::ThreadManagerTest() {
    _t_manager = ThreadManager();
    _init();
}

ThreadManagerTest::~ThreadManagerTest() {
}


void ThreadManagerTest::_init() {
    _t_manager.join();
    _t_manager = ThreadManager();
    _incremental_test = 0;
}


bool ThreadManagerTest::TestStopAndStart() {
    _init();

    _t_manager.setJob(&_job_one);
    _t_manager.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    _t_manager.stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    int checker = _incremental_test;
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    if (checker != _incremental_test)
        return false;

    return true;
}

void ThreadManagerTest::_job_one() {
    for (; _incremental_test < 60; ++_incremental_test)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void ThreadManagerTest::_job_two() {
}