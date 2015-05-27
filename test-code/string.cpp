// comparing size, capacity and max_size
#include <iostream>
#include <string>

int main ()
{
	std::string mystring;
	mystring.reserve(12230);

	// set some content in the vector:
	mystring = "hi";

	std::cout << "size: " << (int) mystring.size() << '\n';
	std::cout << "capacity: " << (int) mystring.capacity() << '\n';
	std::cout << "max_size: " << (unsigned int) mystring.max_size() << '\n';
	std::cout << "\"\".empty()?" << std::string("").empty() << ", empty() ?" << std::string().empty() << std::endl;

	return 0;
}
