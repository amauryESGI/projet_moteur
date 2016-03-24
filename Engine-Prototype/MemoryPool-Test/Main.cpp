#include <iostream>

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

int main(int agrc, char* argv)
{
	MemoryPool mp;

	std::cout << "Allocation MaTestStruct" << std::endl;
	mp.Allocate<MaTestStruct>(2);

	getchar();

	std::cout << "Allocation MaTestStruct2" << std::endl;
	mp.Allocate<MaTestStruct2>(2500000);

	getchar();

	std::vector<MaTestStruct*> vec;
	vec.reserve(3);
	for (int i = 0; i < 3; ++i)
		vec.push_back(mp.Instanciate<MaTestStruct>());

	getchar();

	for (int i = 0; i < 3; ++i)
		mp.Destroy(vec[i]);

	getchar();

	std::cout << "Desallocation MaTestStruct" << std::endl;
	mp.Deallocate<MaTestStruct>();

	getchar();

	std::cout << "Desallocation MaTestStruct2" << std::endl;
	mp.Deallocate<MaTestStruct2>();

	getchar();

	return 0;
}