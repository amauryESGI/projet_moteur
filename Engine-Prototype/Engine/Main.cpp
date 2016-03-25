#include <iostream>

#include "..\MemoryPool-Lib\MemoryPool.h"
#include "../GameObject-Lib/Scene.h"
#include "../ThreadPool-Lib/ThreadPool.h"

int main(int argc, char* argv)
{
	Scene sc;
	MemoryPool mp;
	ThreadPool tp;

	tp.Stop();

	getchar();

	return 0;
}