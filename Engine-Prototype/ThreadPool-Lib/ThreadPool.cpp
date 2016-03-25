#include "ThreadPool.h"

#include <thread>


ThreadPool::ThreadPool() : _isStoped(false) {
    _nbThreadPref = std::thread::hardware_concurrency() - 1;

    for (unsigned int i = 0; i < _nbThreadPref * 2; i++)
        _pool.push_back(new ThreadManager());
}


ThreadPool::~ThreadPool() {
    Stop();

    for (unsigned int i = 0; i < _pool.size(); ++i)
        _pool[i]->join();
}

void ThreadPool::_rescueGateway() {
    _pool.push_back(new ThreadManager());
}

void ThreadPool::_scheduler() {
    unsigned int nb_start, nb_blocked;

    while (!_isStoped) {
        nb_start = nb_blocked = 0;

        if (_queue_job.size() > 0) {
            for (unsigned int i = 0; i < _pool.size(); ++i) {
                if (_pool[i]->GetState() == START) {
                    ++nb_start;
                    if (!_pool[i]->HasJob()) {
                        _pool[i]->SetJob(_queue_job.front());
                        _queue_job.pop();
                    }
                    if (_pool[i]->GetState() == BLOCK)
                        ++nb_blocked;
                }
            }

            int tmp = nb_start - nb_blocked;
            if (nb_start - nb_blocked <= 0) {
                if (nb_blocked != _pool.size()) {
                    for (unsigned int i = 0; i < _pool.size(); ++i) {
                        if (_pool[i]->GetState() == STOP || _pool[i]->GetState() == DEFAULT) {
                            _pool[i]->start();
                            break;
                        }
                    }
                } else
                    _rescueGateway();
            } else
                std::this_thread::yield();
        } else
            std::this_thread::yield();
    }
}