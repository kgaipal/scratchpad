#include <iostream>
#include <functional>
#include <unordered_map>
#include <string>

#include "boost/functional/hash.hpp"

template <typename Key1, typename Key2>
class Keys
{
public:
        Keys(const Key1& k1, const Key2& k2) : key1(k1), key2(k2) { }

	bool operator==(const Keys& other) const {
		return key1 == other.key1 && key2 == other.key2;
	}

	Key1 key1;
	Key2 key2;
};

template <class T>
class MyHash;

template<typename Key1, typename Key2>
class MyHash< Keys<Key1, Key2> >
{
public:
	std::size_t operator()(Keys<Key1, Key2> const& k) const
	{
		std::size_t seed = 0;
		boost::hash_combine(seed, k.key1);
		boost::hash_combine(seed, k.key2);

		std::cout << "computed ["
			  << k.key1 << ":" << k.key2 << "]=>" << seed <<"\n";
		return seed;
	}
};

int main()
{
	// typedef std::string ID;
	typedef int ID;

	ID s1 = 3;
	ID s2 = 6;

	Keys<ID, ID> n1(s1, s2);

	std::unordered_map<Keys<ID, ID>, std::size_t, MyHash< Keys<ID, ID> > > hashValues;

	n1.key1 = 90;
	n1.key2 = 10;
	std::cout << hashValues[n1] << "\n";

	n1.key1 = 34;
	n1.key2 = 23;
	std::cout << hashValues[n1] << "\n";

	std::cout << "finding\n";
	auto h = hashValues.find(n1);

	// std::cout << "hash(n1) = " << MyHash< Keys<ID, ID> >()(n1) << "\n";

}

// int main()
// {
// 	std::string str = "skill1";
// 	std::string str2 = "skill1";

// 	std::hash<std::string> hash_fn;
// 	std::size_t str_hash = hash_fn(str);

// 	std::cout << hash_fn(str) << '\n' << hash_fn(str2) << std::endl;

// 	std::cout << hash_fn(str) << '\n' << hash_fn(str2) << std::endl;

// 	std::cout << hash_fn(str) << '\n' << hash_fn(str2) << std::endl;
// }
