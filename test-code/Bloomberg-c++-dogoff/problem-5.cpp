/**
5.  Given a const null terminated string containing a sentence, can you
print out the words of the sentence in reverse without changing any data
and without creating a temporary string buffer?  Do not use any helper
functions, write it all out on your own.  (ie "The dog is fast"
becomes "fast is dog The")


Sol:

Two solutions are provided.
sol1: Regular iteration over each character without using any extra buffer string. Space
complexity is best (few variables). Time complexity is O(wk+m) where w is number of words
in input, k is characters in each word (assuming all are same) and m is number of
whitespace characters.

sol2: Stack is used which will store start and end index of each for in the given string.
Space complexity is highest as it will grow as many words in the input string. Time
complexity is O(wk) where w, k are same as in sol1.

Both methods should be able to deal with strings like "The dog is fast " or " The dog is
fast" or " " basically you can have many whitespaces leading trailing in between.

 */

void printReverseString(const char* str)
{
	if (str == nullptr) {
		return;
	}

	// find last non null character index of given string
	// complexity: O(N) where N is the characters in string excluding nullptr
	auto findStringEnd = [&] () {
		int end = 0;
		while (str[end] != nullptr) {
			end++;
		}
		return end;
	};

	auto findTokenInReverse = [str] (int start, char token) {
		int c = start;
		while (0 <= c && str[c] == token) {
			c--;	// eat whitespace
		}
		return c;
	}

	const int stringEnd = findStringEnd();

	// start from reverse and print extract each word and print it iteratively until
	// we reach start of given string again
	int nextWordEnd = stringEnd;

	// Invariant: nextWordEnd is between [-1, stringEnd]
	// Complexity: O(2*wk+m) ~ O(wk+m), where
	//             w is total words,
	//             k is letters in each word (assumption), and
	//             m whitespaces
	// Its 2wk above because we scan each word and iterate characterwise to print it.
	while (nextWordEnd >= 0) {

		// print whitespace only between words
		if (nextWordEnd != stringEnd) {
			std::cout << ' ';
		}

		const int we = findTokenInReverse(nextWordEnd, ' '); // word end
		if (we < 0) {
			break;	// no word available
		}

		int ws = findTokenInReverse(we, ' ');		     // word start
		if (ws < 0) {
			break;	// no word available
		}

		nextWordEnd = ws-1; // preceding word for next iteration (excluding space)

		// print word [ws, we]
		while (ws >= we) {
			std::cout << str[ws++];
		}
	}
}

void printReverseString_stack()
{
	if (str == nullptr) {
		return;
	}

	Stack stack; // stack will store only indices of first character of each word

	int ws = 0;

	// iterate each character to find words from the given string
	// Invariant: 0 <= ws <= string length (including nullptr)
	// Complexity: O(N): where N is the string length
	while (str[ws] != nullptr) {
		// Invariant:
		while (str[ws] != ' ' && str[ws] != nullptr) {
			ws++;
		}
		int we = ws;
		while (str[we] != ' ' && str[we] != nullptr) {
			we++;
		}
		stack.push(std::pair<int, int>(ws, we));
	}

	// Invariant: until stack is empty
	// Complexity: O(wk), where
	//             w is total words,
	//             k is letters in each word (assumption), and
	// Space complexity: O(w)
	while (!stack.empty()) {
		std::pair<int, int> word = stack.pop();

		int i = word.start;

		// Complexity: O(wk)
		while (i < word.second) {
			std::cout << str[i++];
		}
		if (stack.size() > 1) {
			std::cout << " ";
		}
	}
}

int main()
{
	char* str = "The dog is fast";
	printReverseString(str);
	printReverseString_stack(str);
	return 0;
}
