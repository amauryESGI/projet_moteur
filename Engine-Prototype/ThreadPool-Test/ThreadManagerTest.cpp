//#include "ThreadManagerTest.h"
//
//#include "../ThreadPool-Lib/ThreadManagerExceptions.hpp"
//#include "../ThreadPool-Lib/ThreadManager.h"
//
//
//ThreadManagerTest::ThreadManagerTest() {}
//
//ThreadManagerTest::~ThreadManagerTest() {}
//
//
//void ThreadManagerTest::_job_one() {
//	for (; _incremental_test < 60; ++_incremental_test)
//		std::this_thread::sleep_for(std::chrono::milliseconds(100));
//}
//
//void ThreadManagerTest::_job_two() {
//}
//
//bool ThreadManagerTest::TestStopAndStart() {
//	ThreadManager t_manager{};
//	_incremental_test = 0;
//
//    t_manager.SetJob(&Job(&ThreadManagerTest::_job_one));
//	t_manager.start();
//    std::this_thread::sleep_for(std::chrono::milliseconds(500));
//
//	t_manager.stop();
//    std::this_thread::sleep_for(std::chrono::milliseconds(500));
//
//    int checker = _incremental_test;
//    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//
//    if (checker != _incremental_test)
//        return false;
//
//    return true;
//}
//
//bool ThreadManagerTest::TestSetJobSucceed()
//{
//	auto retour(false);
//	ThreadManager t_manager{};
//	
//	try {
//        t_manager.SetJob(&Job(&ThreadManagerTest::_job_two));
//		std::this_thread::sleep_for(std::chrono::milliseconds(500));
//        t_manager.SetJob(&Job(&ThreadManagerTest::_job_two));
//
//		retour = true;
//	} catch (const ThreadManagerExceptions& m) {
//	} catch (const std::exception& e) {}
//
//	return retour;
//}
//
//bool ThreadManagerTest::TestSetJobFailed()
//{
//	auto retour(false);
//	ThreadManager t_manager{};
//
//	try {
//        t_manager.SetJob(&Job(&ThreadManagerTest::_job_one));
//		std::this_thread::sleep_for(std::chrono::milliseconds(500));
//        t_manager.SetJob(&Job(&ThreadManagerTest::_job_two));
//	} catch (const ThreadManagerExceptions& e) {
//		retour = true;
//	} catch (const std::exception& e) {}
//
//	return retour;
//}