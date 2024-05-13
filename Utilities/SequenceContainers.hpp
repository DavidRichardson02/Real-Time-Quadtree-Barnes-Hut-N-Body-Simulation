//  SequenceContainers.hpp
//  Generic Quadtree Barnes-Hut  N-Body Simulator 0_1
//  DavidRichardson02

/**
 dev NOTE:
 This shit ain't ready for release, not to this program anyways, probably could find use for something, but after looking at std::vector there's not much
 I could even feasibly consider doing to make a single improvement for my project's use, I tried exploring this avenue for optimizing performance but
 it just doesn't seem like a worthwhile bottleneck for me to pursure, and now feels like a waste to delete this so I'm keeping this antiquated shit around cuz i feel like it...
 basically, maybe it could be good for something, but I'm not really qualified to offer an opinion on that sentiment.
 */

/**
 * DynamicBufferArray
 *
 * DynamicBufferArray is a templated dynamic array class that
 * provides similar functionalities to the C++ Standard Library's std::vector.
 * It manages its memory internally and resizes the array dynamically, offering
 * better memory management compared to traditional C++ arrays.
 *
 * The class uses a fixed-size buffer for the first `fixed_capacity` elements
 * to avoid heap allocations until necessary. The class adheres to RAII principles.
 */


#pragma once
#include "ofMain.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>




template <typename T>
class DynamicBufferArray
{
public:
	
	// ------------- Constructors and Destructor -------------
	DynamicBufferArray();
	DynamicBufferArray(size_t _capacity) ;
	DynamicBufferArray(const DynamicBufferArray& other);
	DynamicBufferArray& operator=(const DynamicBufferArray& other);
	~DynamicBufferArray();
	
	
	// ------------- Element Access -------------
	T& operator[](size_t index); //must return as reference as array element can be put on left side
	const T& operator[](size_t index) const;
	
	
	// ------------- Capacity and Size -------------
	bool empty() const; // Returns size() == 0.
	int size() const;  // Returns the number of elements in the list.
	
	
	void reserve(size_t _size); //Reserves a minimum capacity for the array.
	void resize(size_t _size, const T& fill); //resizes the list to contain _size elements, filling new elements with fill
	
	
	
	// ------------- Modifiers -------------
	void push_back(const T& _data);
	T pop_back();
	void clear();
	void swap(DynamicBufferArray &other);
	
	template <typename... Args>
	void emplace_back(Args&&... args);
	
	
private:
	// ------------- Internal storage and metadata for DynamicBufferArray. -------------
	
	enum { fixed_cap = 64 };
	struct alignas(16) ListData //is memory-aligned for optimal access speed. In C++11 and newer, you can use the alignas keyword.
	{
	ListData();
	T buffer[fixed_cap];// Stores a fixed-size buffer in advance to avoid requiring a heap allocation until we run out of space.
	T* data;  // Pointer to the actual data
	size_t size;   //total current size of array/vector, i.e., number of elements
	size_t capacity;  // Total capacity of the allocated array, i.e., max size
};
ListData listData;  // Internal data storage


};

