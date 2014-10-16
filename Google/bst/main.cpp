
#include <iostream>
#include <vector>

#include "bst.h"

int main()
{
	BST bst;
	std::vector<int> data = {3,8,9,11,5,2,-1};

	std::cout << "\n== original ==\n";
	bst.insert(data);
	bst.printByLevel();

	std::cout << "\n== after inserting two new (0,99) ==\n";
	bst.insert(0);
	bst.insert(99);
	bst.printByLevel();

	std::cout << "\n== after removing 11 ==\n";
	std::cout << (bst.remove(11)?" ":"not ") << "removed";
	bst.printByLevel();

	// interactively find some value
	int value;
	while(1) {
		std::cout << "\nEnter a value to find:";
		std::cin >> value;
		std::cout << (bst.find(value)?" ":"not ") << "found!";
	}

	return 0;
}
