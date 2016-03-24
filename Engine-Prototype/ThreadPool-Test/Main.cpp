#include <iostream>
#include <string>
#include <functional>

#include "ThreadManagerTest.h"

void Tester (std::function<bool(void)> f, std::string str_name) {
	if (f)
		std::cout << str_name << " Succeed.";
	else
		std::cout << str_name << " Failed.";
}

int main(int agrc, char* argv) {
	ThreadManagerTest t_manager_test{};

	Tester(t_manager_test.TestStopAndStart(), "TestStopAndStart");
	Tester(t_manager_test.TestSetJobSucceed(), "TestSetJobSucceed");
	Tester(t_manager_test.TestSetJobFailed(), "TestSetJobFailed");

    getchar();
    return 0;
}