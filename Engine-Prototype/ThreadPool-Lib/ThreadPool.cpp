#include "ThreadPool.h"

#include <thread>


ThreadPool::ThreadPool() : _isStoped(false) {
    _nbThreadPref = std::thread::hardware_concurrency() - 1;

    for (size_t i = 0; i < _nbThreadPref * 2; i++)
        _pool.push_back(ThreadManager());
}


ThreadPool::~ThreadPool() {
    Stop();

    //for (auto i = 0; i < _pool.size(); ++i)
        //_pool[i].Join();
}

void ThreadPool::Start() {
    int nb_start, nb_blocked;

    while (!_isStoped) {
        nb_start = nb_blocked = 0;

        if (_queue_job.size() <= 1) {
            for(auto mt : _pool) {
                if (!mt.GetState() == STOP) {
                    ++nb_start;
                    if (mt.HasJob())
                        mt.SetJob(_queue_job.pop());
                    if (mt.GetStat() == BLOCK)
                        ++nb_blocked;
                }
            }

            int tmp = nb_start - nb_blocked;
            if (nb_start - nb_blocked < 0) {
                if (nb_start < _pool.size())
                    for(auto mt : _pool)
                        if (mt.GetState() == STOP) {
                            mt.start();
                            break;
                        }
                    else
                        _rescueGateway();
            } else
                std::this_thread::yield();
        } else
            std::this_thread::yield();
    }
}

void ThreadPool::_rescueGateway() {
    _pool.push_back(ThreadManager());
}
