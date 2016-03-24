#pragma once
class MemoryPool
{
public:
	MemoryPool();

	template<typename T> 
	void Allocate(T object, int count) {
		T* objPtr = (T*)malloc(count * sizeof(T));
		new(objPtr) T();
	}

	~MemoryPool();
};

