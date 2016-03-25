#include <iostream>

#include "../ThreadPool-Lib/Job.hpp"
#include "../ThreadPool-Lib/ThreadManager.h"
#include "../ThreadPool-Lib/ThreadPool.h"

void taskTest(int begin, int end) {
    std::cout << "Il est passé par ici (" << begin << "), il repasserat par là (" << end << ")." << std::endl;
}

int main(int agrc, char* argv) {
    ThreadManager t_manager;

    //std::cout << "Expected : 0, Result : " << t_manager.GetState() << std::endl;
    //std::cout << "HasJob(); Expected : 0, Result : " << t_manager.HasJob() << std::endl;

    //Job toto(taskTest, 26, 6);
    //t_manager.SetJob(&toto);
    //std::cout << "HasJob(); Expected : true, Result : " << t_manager.HasJob() << std::endl;

    //std::cout << "Je veux executé ma task." << std::endl;
    //t_manager.start();
    //std::cout << "Oh!" << std::endl;

    //std::cout << "Expected : 1, Result : " << t_manager.GetState() << std::endl;

    //t_manager.join();
    //std::cout << "Expected : -1, Result : " << t_manager.GetState() << std::endl;

    ThreadPool pool;
    std::cout << "Nb thread : " << pool.GetPreferedThreadQuantity() << std::endl;
    
    Job j_un(taskTest, 1, 6);
    Job j_deux(taskTest, 2, 6);
    Job j_trois(taskTest, 3, 6);
    Job j_quatre(taskTest, 4, 6);
    Job j_cinq(taskTest, 5, 6);
    Job j_six(taskTest, 6, 6);

    Job j_sept(taskTest, 7, 10);
    Job j_huit(taskTest, 8, 10);
    Job j_neuf(taskTest, 9, 10);
    Job j_dix(taskTest, 10, 10);

    pool.AddJob(&j_un);
    pool.AddJob(&j_deux);
    pool.AddJob(&j_trois);
    pool.AddJob(&j_quatre);
    pool.AddJob(&j_cinq);
    pool.AddJob(&j_six);

    pool.Start();

    pool.AddJob(&j_sept);
    pool.AddJob(&j_huit);
    pool.AddJob(&j_neuf);
    pool.AddJob(&j_dix);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    pool.Stop();

    getchar();
    return 0;
}