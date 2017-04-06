#include <cxxtest/TestSuite.h>

#include "heap_priority_queue.h"

template class HeapPriorityQueue<int>;

class HeapTests : public CxxTest::TestSuite
{
public:
	void testTODO(void)
	{
		HeapPriorityQueue<int> list1;
		// test is empty
		TS_ASSERT(list1.isEmpty() == true);
		// add one item
		list1.add(5);
		// test is empty when an item is added
		TS_ASSERT(list1.isEmpty() == false);
		// add second item
		list1.add(20);
		// test peek
		TS_ASSERT(list1.peek() == 20);
		// test remove
		list1.remove();
		// test peek after remove
		TS_ASSERT(list1.peek() == 5);
		// test remove with 1 item
		list1.remove();
		// test remove with empty list
		TS_ASSERT_THROWS(list1.remove(), std::logic_error);
		// check for preservation of order
		list1.add(100);
		list1.add(200);
		list1.add(300);
		list1.add(400);
		list1.add(500);
		list1.add(900);
		list1.add(700);
		list1.add(600);
		list1.add(800);
		TS_ASSERT(list1.peek() == 900);
		list1.remove();
		TS_ASSERT(list1.peek() == 800);
		list1.remove();
		TS_ASSERT(list1.peek() == 700);
		list1.remove();
		TS_ASSERT(list1.peek() == 600);
		list1.remove();
		TS_ASSERT(list1.peek() == 500);
		list1.add(1000);
		TS_ASSERT(list1.peek() == 1000);
		list1.remove();
		list1.add(350);
		TS_ASSERT(list1.peek() == 500);
		list1.remove();
		TS_ASSERT(list1.peek() == 400);
		list1.remove();
		TS_ASSERT(list1.peek() == 350);
		list1.remove();
		TS_ASSERT(list1.peek() == 300);
		list1.remove();
		TS_ASSERT(list1.peek() == 200);
		list1.remove();
		TS_ASSERT(list1.peek() == 100);
		list1.add(100);
		list1.remove();
		TS_ASSERT(list1.peek() == 100);
		list1.remove();
		TS_ASSERT_THROWS(list1.remove(), std::logic_error);
		TS_ASSERT_THROWS(list1.peek(), std::logic_error);
	}
};
