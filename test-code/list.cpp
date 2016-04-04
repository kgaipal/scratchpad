#include <list>
#include <iostream>

void delete_reverse()
{
	auto print_list = [] (const std::list<int>& alist) {
		for (auto& i : alist) {
			std::cout << i << " ";
		}

		std::cout << std::endl;
	};

	std::list<int> aList = {12, 13, 45, 56, 89, 99, 101};

	print_list(aList);

	std::list<int>::reverse_iterator i = aList.rbegin();
	while (i != aList.rend()) {
		if (*i > 100) { // delete something in the middle
			i++;
			aList.erase(i.base());
		} else {
			i++;
		}
	}

	print_list(aList);
}

int main()
{
	delete_reverse();
	return 0;
}
