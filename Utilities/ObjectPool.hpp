//  ObjectPool.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02

/**
 * ObjectPool Class: Templated Object Pool for efficient object allocation
 *
 * This class provides a pool-based memory management strategy for objects
 * to avoid the overhead of dynamic allocation/deallocation. The class utilizes
 * batch allocation to improve memory locality and provides methods to acquire and release objects.
 * ObjectPool implements batch allocation using 'placement new'.
 *
 * Note: This class assumes that the templated type T has a 'reset' member function.
 */


#pragma once
#include "ofMain.h"
#include <new>




template <class T>
class ObjectPool
{
public:
	// ------------- Constructors and Destructor -------------
	ObjectPool() {}
	
	ObjectPool(size_t size)  // Constructor that pre-allocates 'size' objects
	{
		allocateBatch(size);
	}
	
	
	
	~ObjectPool()  // Destructor that deallocates all batch-allocated objects
	{
		// delete all objects from the pool
		//std::cout << "Starting destructor" << std::endl;
		for (auto block : blocks)
		{
			if (!block)  // Safety check, although this should not happen
			{
				//std::cout << "Null block detected. Skipping." << std::endl;
				continue;
			}
			
			for (size_t i = 0; i < batchSize; ++i)
			{
				// Additional Safety Check
				if (block + i)
				{
					//std::cout << "Destroying object at index " << i << std::endl;
					(block + i)->~T(); // explicit destructor call for each object
				}
			}
			//std::cout << "Deleting block" << std::endl;
			
			//::operator delete(static_cast<void*>(block));  // Deallocate the memory block
		}
		
		blocks.clear();
		//*/
		
		
	}
	
	
	
	
	// ------------- Object Management -------------
	T* acquire() // Acquires an object from the pool
	{
		if (pool.empty())
		{
			cout << "\n\nThe object pool is empty";
			//return nullptr;
		}
		
		auto obj = pool.top();
		pool.pop();
		return obj;
	}
	
	void release(T* obj) // Releases an object back to the pool
	{
		obj->reset();
		pool.push(obj);
	}
	
	
	
	
	
private:
	// ------------- Batch Allocation -------------
	void allocateBatch(size_t size)  // Allocates a batch of 'size' objects
	{
		batchSize = size;
		T* block = static_cast<T*>(::operator new(sizeof(T) * batchSize));
		blocks.emplace_back(block);
		
		// Initialize each object in the block using placement new
		for (size_t i = 0; i < batchSize; ++i)
		{
			new (block + i) T();
			pool.push(block + i);
		}
	}
	
	
	
	
	// ------------- Internal Data Storage -------------
	std::stack<T*> pool;  // Stack holding pointers to available objects
	std::vector<T*> blocks;  // Vector to keep track of allocated blocks
	size_t batchSize;  // Number of objects in each allocation batch
};





template <class T>
static inline void ResetObjectPool(ObjectPool<T> &objectPool, std::vector<T*> &objects);


template <class T>
static inline void ReleaseObjectFromPool(ObjectPool<T> &objectPool, std::vector<T*> &objects, size_t &index);






template <class T>
static inline void ResetObjectPool(ObjectPool<T> &objectPool, std::vector<T*> &objects)
{
	for (auto& obj : objects)
	{
		if(obj)
		{
			objectPool.release(obj);
		}
	}
}




template <class T>
static inline void ReleaseObjectFromPool(ObjectPool<T> &objectPool, std::vector<T*> &objects, size_t &index)
{
	if(objects[index])
	{
		objectPool.release(objects[index]);
	}
}



