#pragma once

#include "../ThreadPool-Lib/ThreadManager.h"

class ThreadManagerTest {
public:
    ThreadManagerTest();
    ~ThreadManagerTest();

    bool TestStopAndStart();

private:
    ThreadManager _t_manager;
    int _incremental_test;

    void _init();
    void _job_one();
    void _job_two();
};

