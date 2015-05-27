/**

def spam(eggs):
    eggs.append(1)
    eggs = [2, 3]

ham = [0]
spam(ham)
print(ham)

 */

#include <vector>
#include <iostream>

typedef std::vector<int> Obj;

void print(const Obj& array)
{
	for (auto v : array) {
		std::cout << v << ",";
	}
	std::cout << "\n";
}

///////////////////////////////////////////

void spam(Obj& eggs)
{
	eggs.push_back(1);
	eggs = Obj({2,3});
}

void spam2(Obj eggs)
{
	eggs.push_back(1);
	eggs = Obj({2,3});
}

int main()
{
	{
		Obj ham({0});
		spam(ham);
		print(ham);

	} {
		Obj ham({0});
		spam2(ham);
		print(ham);
	}

	return 0;
}
