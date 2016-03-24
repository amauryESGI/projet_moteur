#include "ThreadPool.h"

#include <thread>


ThreadPool::ThreadPool() {
    std::thread t = std::thread();
}


ThreadPool::~ThreadPool() {
}
