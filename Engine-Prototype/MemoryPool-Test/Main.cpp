#include <iostream>
#include <ctime>

#include "..\MemoryPool-Lib\MemoryPool.h"

struct MaTestStruct
{
	int i1;
	int i2;
};

struct MaTestStruct2
{
	double i1;
	double i2;
	double i3;
	double i4;
	double i5;
	double i6;
	double i7;
	double i8;
	double i9;
	double i10;
};

#define NUMBER_ELEMENT 25000000

void test2()
{
	MemoryPool mp;
	std::vector<MaTestStruct*> elementPool;

	std::cout << "Allocation" << std::endl;
	mp.Allocate<MaTestStruct>(NUMBER_ELEMENT);

	std::cout << "Instanciate" << std::endl;
	elementPool.reserve(NUMBER_ELEMENT);
	for (int i = 0; i < NUMBER_ELEMENT; ++i)
	{
		elementPool.push_back(mp.Instanciate<MaTestStruct>());
	}

	std::cout << "Destroyng" << std::endl;
	MaTestStruct* ptr;
	srand(time(NULL));
	for (int i = 0; i < NUMBER_ELEMENT / 10; ++i)
	{
		ptr = elementPool[rand() % NUMBER_ELEMENT];
		mp.Destroy(ptr);
	}

	std::cout << "ReInstanciate" << std::endl;
	for (int i = 0; i < NUMBER_ELEMENT / 10; ++i)
	{
		mp.Instanciate<MaTestStruct>();
	}

	std::cout << "Deallocation" << std::endl;
	mp.Deallocate<MaTestStruct>();
}

void test1()
{
	MemoryPool mp;

	std::cout << "Allocation MaTestStruct" << std::endl;
	mp.Allocate<MaTestStruct>(3);

	getchar();

	std::cout << "Allocation MaTestStruct2" << std::endl;
	mp.Allocate<MaTestStruct2>(2500000);

	getchar();

	std::vector<MaTestStruct*> vec;
	vec.reserve(3);
	for (int i = 0; i < 3; ++i)
		vec.push_back(mp.Instanciate<MaTestStruct>());

	getchar();

	mp.Destroy(vec[1]);
	mp.Destroy(vec[0]);

	getchar();

	std::cout << "Desallocation MaTestStruct" << std::endl;
	mp.Deallocate<MaTestStruct>();

	getchar();

	std::cout << "Desallocation MaTestStruct2" << std::endl;
	mp.Deallocate<MaTestStruct2>();

	getchar();
}

int main(int agrc, char* argv)
{
	test2();

	std::cout << "Fini" << std::endl;

	getchar();

	return 0;
}