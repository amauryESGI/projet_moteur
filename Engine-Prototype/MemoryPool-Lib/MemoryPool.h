#pragma once
#include <vector>
#include <iostream>

struct FreeList
{
	void* ElementPtr;
	FreeList* NextFreeElement;
};

struct AllocateMemoryInfos
{
	void* BeginPtr;
	void* EndPtr;
	int Count;
	int AllocatedElement;
	std::string TypeName;

	FreeList* FreeListStart;
	FreeList* NextFreeElement;

	AllocateMemoryInfos() {}
	AllocateMemoryInfos(void* ptr, void* endPtr, int allocatedElement, int count, std::string typeName) : BeginPtr(ptr), EndPtr(endPtr), AllocatedElement(allocatedElement), Count(count), TypeName(typeName) 
	{

	
	}

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

		T* endPtr = objPtr;
		for (int i = 0; i < count; ++i)
			++endPtr;

		AllocateMemoryInfos meminfos(objPtr, endPtr, 0, count, typeid(T).name());
		FreeList* beginList = (FreeList*)malloc(count * sizeof(FreeList));
		meminfos.NextFreeElement = beginList;
		meminfos.FreeListStart = beginList;

		T* tmpPtr = objPtr;
		FreeList* tmp = beginList;
		for (int i = 0; i < count; ++i)
		{
			tmp->ElementPtr = tmpPtr;
			++tmpPtr;
			tmp->NextFreeElement = tmp + 1;
			++tmp;
		}

		AllocationPtr.push_back(meminfos);
	}

	template<typename T>
	T* Instanciate()
	{
		int i = this->GetAllocationPtrIndex(typeid(T).name());

		if (this->AllocationPtr[i].AllocatedElement < this->AllocationPtr[i].Count)
		{
			if (i < this->AllocationPtr.size() )
			{
				T* tmpPtr = (T*)this->AllocationPtr[i].BeginPtr;
				
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
			T* beginPtr = (T*)this->AllocationPtr[i].BeginPtr;
			T* endPtr = (T*)this->AllocationPtr[i].EndPtr;

			if ( obj < beginPtr || obj > endPtr)
				return;

			free(this->AllocationPtr[i].FreeListStart);

			obj->~T();
			free(obj);

			this->AllocationPtr[i] = this->AllocationPtr[this->AllocationPtr.size() - 1];
			this->AllocationPtr.resize(this->AllocationPtr.size() - 1);

			--this->AllocationPtr[i].AllocatedElement;
		}
	}

	template<typename T>
	void Deallocate()
	{

		int i = this->GetAllocationPtrIndex(typeid(T).name());

		if (i < this->AllocationPtr.size())
		{
			T* ptr = (T*)this->AllocationPtr[i].BeginPtr;
			for (int j = 0; j < this->AllocationPtr[i].Count; ++j)
			{
				ptr->~T();
			}

			free(this->AllocationPtr[i].FreeListStart);

			free(this->AllocationPtr[i].BeginPtr);
			this->AllocationPtr[i].BeginPtr = nullptr;

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
		while (!found  && i < (int)this->AllocationPtr.size() -1 )
		{
			++i;
			found = this->AllocationPtr[i].isTypeOf(typeName);
		}

		return i;
	}

	template<typename T>
	T* GetNextFreeMemory(AllocateMemoryInfos memInfos)
	{
		T* ptr =  (T*)memInfos.NextFreeElement->ElementPtr;
		memInfos.NextFreeElement = memInfos.NextFreeElement->NextFreeElement;
	}

	template<typename T>
	void RemoveOccupedMemory(AllocateMemoryInfos memInfos, T* elementRemoved)
	{
		bool found = false;
		FreeList* currentPtr = memInfos.FreeListStart - 1;
		FreeList* nextPtr = memInfos.NextFreeElement;
		FreeList* previousPtr = memInfos.NextFreeElement;
		int i = 0;
		while (!found && i < memInfos.Count)
		{
			++currentPtr;
			if (currentPtr->ElementPtr == elementRemoved)
				found = true;
			++i;
		}

		if (found)
		{
			while (true)
			{
				if (currentPtr < nextPtr)
				{
					currentPtr->NextFreeElement = nextPtr;
					previousPtr = currentPtr;
				}

				previousPtr = nextPtr;
				nextPtr = previousPtr->NextFreeElement;
				
			}
		}
	}
};

