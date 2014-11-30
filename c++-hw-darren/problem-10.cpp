/**
10. The standard library function of atoi() is not very robust.  How
would you design/implement a better version of it?

sol: expects null terminated strings like "1234" , "-423", "+789" and even floats allowed
"45.2" The last one will return 45 truncating decimal integers. function will return false
in case an invalid input and return a number positive or negative.

*/


bool atoi(const char* str, int len/*includes NULL*/, int& value)
{
	if (str == nullptr && str[0] == '\0') {
		return false;
	}

	int num = 0;
	int radix = 1;		// indicates decimal places

	for (char* c = str[len-2]; c != str; c--, radix = radix * 10) {
		int integer = 0;

		switch (*c) {
		case '.':   // a float string might be supplied but we truncate to integer
			// reset all
			num = 0;
			radix = 0;
			integer = 0;
			break;
		case '-':	// negative character must only be at the begining
			if (c != str) {
				return false;
			}

			// begining
			value = (-1) * num;
			return true;
		case '+':	// positive character must only be at the begining
			if (c != str) {
				return false;
			}

			// begining
			value = num;
			return true;
		case '0':
			integer = 0;
			break;
		case '1':
			integer = 1;
			break;
		case '2':
			integer = 2;
			break;
		case '3':
			integer = 3;
			break;
		case '4':
			integer = 4;
			break;
		case '5':
			integer = 5;
			break;
		case '6':
			integer = 6;
			break;
		case '7':
			integer = 7;
			break;
		case '8':
			integer = 8;
			break;
		case '9':
			integer = 9;
			break;
		default:
			return false; // something else

		}

		// Save upon multiplication of 10 from earlier results, should not compute
		// 10, 100, 1000, ... etc every time. Instead use last saved radix result
		// as we are increasing anyway towards larger decimal places.
		num += (integer * radix);
	}

	value = num;		// update return argument
	return true;
}
