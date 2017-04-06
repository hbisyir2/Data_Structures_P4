// implement the class here

#include "heap_priority_queue.h"


// constructor
template <typename T>
HeapPriorityQueue<T>::HeapPriorityQueue() : list() {}

// is empty
template <typename T>
bool HeapPriorityQueue<T>::isEmpty() {
	if (list.getLength()) return false;
	return true;
}

// add
template <typename T>
void HeapPriorityQueue<T>::add(const T& item) {
	std::size_t i = list.getLength();
	std::size_t j;
	T temp;
	list.insert(list.getLength(), item);
	j = i;
	i = goUp(i);
	temp = list.getEntry(i);

	while (item > temp) {

		list.setEntry(i, item);
		list.setEntry(j, temp);

		if (i == 0) break;

		j = i;
		i = goUp(i);
		temp = list.getEntry(i);
	}
}

// remove
template <typename T>
void HeapPriorityQueue<T>::remove() {
	if (list.getLength() == 0) throw std::logic_error("Cannot remove, queue is empty");
	// set zero position to end value and remove highest value
	list.setEntry(0, list.getEntry(list.getLength() - 1));
	list.remove(list.getLength() - 1);
	// if list is empty, no sorting is needed
	if (list.getLength() == 0) return;

	// gather left and right branches
	std::size_t sorti = 0;
	std::size_t lefti = goLeft(sorti);
	std::size_t righti = goRight(sorti);
	std::size_t comparei;
	T toCompare;
	T toSort = list.getEntry(0);
	std::size_t length = list.getLength();
	while (lefti < length || righti < length) {

		if (lefti < length && righti < length) {
			if (list.getEntry(lefti) > list.getEntry(righti)) {
				toCompare = list.getEntry(lefti);
				comparei = lefti;
			}
			else {
				toCompare = list.getEntry(righti);
				comparei = righti;
			}
		}
		else if (lefti < length) {
			toCompare = list.getEntry(lefti);
			comparei = lefti;
		}
		else if (righti < length) {
			toCompare = list.getEntry(righti);
			comparei = righti;
		}
		else {
			break;
		}

		if (toSort < toCompare) {
			list.setEntry(comparei, toSort);
			list.setEntry(sorti, toCompare);
			sorti = comparei;
		}
		else {
			break;
		}

		lefti = goLeft(sorti);
		righti = goRight(sorti);
	} // end while
}

// peek
template <typename T>
T HeapPriorityQueue<T>::peek() {
	if (list.getLength() == 0) throw std::logic_error("Cannot peek, queue is empty");
	return list.getEntry(0);
}