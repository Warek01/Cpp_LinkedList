#include <iostream>
#include <string>

#include "LinkedList.h"

int main()
{
	LinkedList<int> list;

	list.append(1);
	list.append(2);
	list.append(-10);
	list.append(12);
	list.append(9);

	list.swap(0, 1);
	list.sort();

	std::cout << list;

	return 0;
}
