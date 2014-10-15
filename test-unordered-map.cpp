// GCC 4.7.3 doesnt support emplace() completely
// http://stackoverflow.com/questions/14075128/mapemplace-with-a-custom-value-type

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

class Element
{
public:
	~Element()
	{
		std::cout << "~Element()\n";
	}

	Element()
		: int_value(-1)
		, string_value("-empty-")
	{
		std::cout << "empty Element():" << int_value << " " << string_value << "\n";
	}

	Element(int i, std::string s)
		: int_value(i)
		, string_value(s)
	{
		std::cout << "Element():" << int_value << " " << string_value << "\n";
	}

	Element(const Element& other)
	{
		int_value = other.int_value;
		string_value = other.string_value;

		std::cout << "Copy-Element():" << int_value << " " << string_value << "\n";
	}

private:
	int int_value;
	std::string string_value;
};

int main()
{
	// Element s(0, "element s");
	// Element another = s;

	// std::unordered_map<int, std::string> uomap;
	// std::map<int, std::string> uomap;
	// uomap.emplace(1,"string value 1");
	// uomap.emplace(1, 1,"string value 1");
	// uomap.emplace(2, 2 ,"string value 2");
	// uomap.emplace(3, 3 ,"string value 3");
	std::unique_ptr<Element> e;
	if (e.get()) {
		std::cout << "unique_ptr is non-empty\n";
	} else {
		std::cout << "unique_ptr is empty\n";
	}

	std::unordered_map<int, std::unique_ptr<Element> > uomap;
	// uomap.insert(std::make_pair<int, Element*>(0, Element(1, "string value 1")));
	uomap[0].reset(new Element(1, "string value 1"));
	return 0;
}
