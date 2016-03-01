// GCC 4.7.3 doesnt support emplace() completely
// http://stackoverflow.com/questions/14075128/mapemplace-with-a-custom-value-type

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <sstream>

#define ELEMENTS_COUNT 100
const std::string convert_to_string(int i) {
	std::stringstream ss;
	ss << i;
	return ss.str();
}

unsigned convert_to_int(unsigned i) {
	return i;
}

#define CONVERT_TO_TYPE(val) { convert_to_int(val) }

typedef std::unordered_map<unsigned, int> UNORDERED_MAP;

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

void check_bucket_size(UNORDERED_MAP& uom)
{
	std::cout << "\nbucket_size()" << uom.bucket_count() << "\n";

	for (int i = 0; i < ELEMENTS_COUNT; i++) {
		std::cout
			<< "key " << i
			<< " is in bucket# " << uom.bucket(CONVERT_TO_TYPE(i))
			<< "\n";
	}

	for (unsigned i = 0u; i < uom.bucket_count(); i++) {
		if (uom.bucket_size(i) < 1) {
			continue;
		}
		std::cout << "\nbucket# " << i
			  << " has " << uom.bucket_size(i) << " elements";
	}
}

void check_load_factor(UNORDERED_MAP& uom)
{
	auto print_stats = [&uom] (const std::string& message = "") {
		std::cout << "\n[" << message << "]";
		std::cout << "\tload_factor:" << uom.load_factor();
		std::cout << "\tbucket_count:" << uom.bucket_count();
		std::cout << "\tsize:" << uom.size();
	};

	print_stats("before_insert");
	for (int i = 0; i < ELEMENTS_COUNT; i++) {
		uom[CONVERT_TO_TYPE(i)] = 2*i;
		if (uom.load_factor() > 0.0) {
			std::stringstream ss;
			ss << "middle-" << i;
			print_stats(ss.str());
		}
	}
	print_stats("after_insert");

	check_bucket_size(uom);
	std::cout << "\n=============";

	print_stats("before_remove");
	for (int i = 0; i < ELEMENTS_COUNT; i++) {
		uom.erase(CONVERT_TO_TYPE(i));
		if (uom.load_factor() > 0.8) {
			std::stringstream ss;
			ss << "middle-" << i;
			print_stats(ss.str());
		}
	}
	print_stats("after_remove");

}

int main()
{
	// // Element s(0, "element s");
	// // Element another = s;

	// // std::unordered_map<int, std::string> uomap;
	// // std::map<int, std::string> uomap;
	// // uomap.emplace(1,"string value 1");
	// // uomap.emplace(1, 1,"string value 1");
	// // uomap.emplace(2, 2 ,"string value 2");
	// // uomap.emplace(3, 3 ,"string value 3");
	// std::unique_ptr<Element> e;
	// if (e.get()) {
	//	std::cout << "unique_ptr is non-empty\n";
	// } else {
	//	std::cout << "unique_ptr is empty\n";
	// }

	// std::unordered_map<int, std::unique_ptr<Element> > uomap;
	// // uomap.insert(std::make_pair<int, Element*>(0, Element(1, "string value 1")));
	// uomap[0].reset(new Element(1, "string value 1"));

	UNORDERED_MAP uom;
	check_load_factor(uom);

	std::cout << std::endl;
	return 0;
}
