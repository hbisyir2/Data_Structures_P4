#ifndef HEAP_PRIORITY_QUEUE_H
#define HEAP_PRIORITY_QUEUE_H

// define the class here
#include "abstract_priority_queue.h"
#include "dynamic_array_list.h"




template <typename T>
class HeapPriorityQueue : public AbstractPriorityQueue<T>
{
public:

	// constructor
	HeapPriorityQueue();

	// return true if the priority queue is empty
	bool isEmpty();

	// insert item into the queue
	// may throw on allocation failure
	void add(const T& item);

	// remove highest priority item from the queue
	// throws std::logic_error if queue is empty
	void remove();

	// get the item with the highest priority from the queue
	// throws std::logic_error if queue is empty
	T peek();

private:

	DynamicArrayList<T> list;

	std::size_t goLeft(std::size_t i) {
		return 2 * i + 1;
	}

	std::size_t goRight(std::size_t i) {
		return 2 * i + 2;
	}

	std::size_t goUp(std::size_t i) {
		if (i == 0) return 0;
		return (i - 1) / 2;
	}
};

#include "heap_priority_queue.txx"

#endif // HEAP_PRIORITY_QUEUE_H
