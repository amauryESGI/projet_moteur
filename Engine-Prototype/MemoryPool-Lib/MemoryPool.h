#pragma once
#include <vector>
#include <iostream>

struct AllocateMemoryInfos
{
	void* Ptr;
	int Count;
	int AllocatedElement;
	std::string TypeName;

	AllocateMemoryInfos() {}
	AllocateMemoryInfos(void* ptr, int count, int allocatedelement, std::string typeName) : Ptr(ptr), Count(count), AllocatedElement(allocatedelement), TypeName(typeName) {}

	~AllocateMemoryInfos() {}

	bool isTypeOf(std::string id)
	{
		return id == this->TypeName;
	}
};

class MemoryPool
{
public:
	MemoryPool();

	template<typename T>
	void Allocate(int count)
	{
		T* objPtr = (T*)malloc(count * sizeof(T));

		AllocationPtr.push_back(AllocateMemoryInfos(objPtr, count, 0, typeid(T).name()));
	}

	template<typename T>
	T* Instanciate()
	{
		int i = this->GetAllocationPtrIndex(typeid(T).name());

		if (this->AllocationPtr[i].AllocatedElement < this->AllocationPtr[i].Count)
		{
			if (i < this->AllocationPtr.size() )
			{
				T* tmpPtr = (T*)this->AllocationPtr[i].Ptr;
				
				tmpPtr += this->AllocationPtr[i].AllocatedElement;
				++this->AllocationPtr[i].AllocatedElement;
				new(tmpPtr) T();
				return tmpPtr;
			}
		}
		return nullptr;
	}

	template<typename T>
	void Destroy(T* obj)
	{
		int i = this->GetAllocationPtrIndex(typeid(T).name());

		if (i < this->AllocationPtr.size())
		{
			T* beginPtr = (T*)this->AllocationPtr[i].Ptr;
			T* endPtr = (T*)this->AllocationPtr[i].Ptr;

			for (int j = 0; j < this->AllocationPtr[i].Count; ++j)
				++endPtr;

			if (beginPtr < obj || endPtr > obj)
				return;

			obj->~T();
			free(obj);
		}
	}

	template<typename T>
	void Deallocate()
	{

		int i = this->GetAllocationPtrIndex(typeid(T).name());

		if (i < this->AllocationPtr.size())
		{
			T* ptr = (T*)this->AllocationPtr[i].Ptr;
			for (int j = 0; j < this->AllocationPtr[i].Count; ++j)
			{
				ptr->~T();
			}


			free(this->AllocationPtr[i].Ptr);
			this->AllocationPtr[i].Ptr = nullptr;

			this->AllocationPtr[i] = this->AllocationPtr[this->AllocationPtr.size() - 1];
			this->AllocationPtr.resize(this->AllocationPtr.size() - 1);
		}
	}

	~MemoryPool();

private:
	std::vector<AllocateMemoryInfos> AllocationPtr;

	int GetAllocationPtrIndex(const char* typeName)
	{
		int i = -1;
		bool found = false;
		while (!found  && i < (int)this->AllocationPtr.size())
		{
			++i;
			found = this->AllocationPtr[i].isTypeOf(typeName);
		}

		return i;
	}
};

