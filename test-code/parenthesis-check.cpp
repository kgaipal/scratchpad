// check parenthisis
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

class Stack {
public:
	bool empty() const {
		return m_vt.empty();
	}

	void push(int item) {
		m_vt.push_back(item);
	}

	int pop() {
		if (m_vt.empty()) {
			throw std::runtime_error("buffer underrun");
		}

		int item = *m_vt.cbegin();
		m_vt.pop_back();
		return item;
	}

	std::vector<int> m_vt;
};

// parenthisis matching
int matchParen(const std::string& src) {
	Stack st;

	for (auto s = src.begin(); s != src.end(); s++) {
		if (*s == '(') {
			st.push( s - src.begin() );
		} else if (*s == ')') {
			if (st.empty()) {
				return s - src.begin();
			}
			st.pop();
		}
	}

	if (!st.empty()) {
		return st.pop(); // return position of the top stacked item
	}

	return -1; // all goood
}

const std::string fillWhitespace(int pos)
{
	std::string str;
	for (int p = 0; p < pos; p++) {
		str += " ";
	}
	
	return str + "^";
}

int main()
{

	// input string
	std::string str = "f(((g(jh)))))))";
	std::cout << "checking string: " << str;

	int mismatchPos = matchParen(str);

	if (mismatchPos < 0) {
		std::cout << "parenthesis matches";
	} else {
		std::cout << "\nmismatched at  : " << fillWhitespace(mismatchPos);
	}

	std::cout << std::endl;
	return 0;
}
