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

	bool isTypeOf(std::string id) const {
		return id == this->TypeName;
	}
};

class MemoryPool
{
public:
	MemoryPool() {}

	template<typename T>
	void Allocate(int count)
	{
		// TODO : For all (T*) => static_cast, const_cast, reinterpret_cast ??
		T* objPtr = (T*)malloc(count * sizeof(T));

		T* endPtr = objPtr;
		for (int i = 0; i < count; ++i)
			++endPtr;

		AllocateMemoryInfos meminfos(objPtr, endPtr, 0, count, typeid(T).name());
		// TODO : FreeList* beginList = static_cast<FreeList*>(malloc(count * sizeof(FreeList)));
		FreeList* beginList = (FreeList*)malloc(count * sizeof(FreeList));
		meminfos.NextFreeElement = beginList;
		meminfos.FreeListStart = beginList;

		FreeList* tmp;
		for (int i = 0; i < count-1; ++i)
		{
			beginList->ElementPtr = objPtr;
			++objPtr;
			tmp = beginList;
			++tmp;
			beginList->NextFreeElement = tmp;
			++beginList;
		}

		AllocationPtr.push_back(meminfos);
	}

	template<typename T>
	T* Instanciate()
	{
		int i = this->GetAllocationPtrIndex(typeid(T).name());

		if (i < this->AllocationPtr.size() )
		{
			T* tmpPtr = (T*)this->AllocationPtr[i].BeginPtr;
				
			tmpPtr = GetNextFreeMemory<T>(this->AllocationPtr[i]);
			if (tmpPtr != nullptr)
			{
				++this->AllocationPtr[i].AllocatedElement;
				new(tmpPtr) T();
			}
			else {
				std::cout << "Stack full" << std::endl;
			}
			return tmpPtr;
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

			RemoveOccupedMemory<T>(this->AllocationPtr[i], obj);

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

	~MemoryPool() {}

private:
	std::vector<AllocateMemoryInfos> AllocationPtr;

	int GetAllocationPtrIndex(const char* typeName)
	{
		int i = -1;
		bool found = false;
		// TODO : while (!found  && i < static_cast<int>(this->AllocationPtr.size()) - 1)
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
		return ptr;
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
			found = false;
			if (currentPtr < previousPtr)
			{
				currentPtr->NextFreeElement = memInfos.NextFreeElement;
				memInfos.NextFreeElement = currentPtr;
				found = true;
			}

			while (!found && nextPtr != nullptr)
			{
				previousPtr = nextPtr;
				nextPtr = previousPtr->NextFreeElement;

				if (currentPtr < nextPtr)
				{
					currentPtr->NextFreeElement = nextPtr;
					previousPtr->NextFreeElement = currentPtr;
					found = true;
				}
				
			}
		}
	}
};

