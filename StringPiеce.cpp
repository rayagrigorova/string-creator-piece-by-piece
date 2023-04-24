#include "StringPi�ce.h"

#include <cmath>

namespace {

	void myStrcpy(char* dest, const char* src) {
		if (src == nullptr || dest == nullptr) {
			return;
		}

		// The '\0' will not be copied
		while (*src) {
			*dest = *src;

			dest++;
			src++;
		}
	}

	unsigned myStrlen(const char* str) {
		if (str == nullptr) {
			return 0;
		}

		unsigned ctr = 0;
		while (*str) {
			str++;
			ctr++;
		}

		return ctr;
	}

	int digitCount(int num) {
		return int(log10(num) + 1);
	}

	void stringToInt(char* str, int num) {
		if (str == nullptr) {
			return;
		}
		int numberOfDigits = digitCount(num);

		int startInd = 0;
		int endInd = numberOfDigits;

		if (num < 0) {
			str[0] = '-';
			startInd++;
			endInd++;
		}

		for (int i = endInd - 1; i >= startInd; i--) {
			str[i] = num % 10 + '0';
			num /= 10;
		}

		str[endInd] = '\0';
	}
}

const char* StringPi�ce::getData() const {
	unsigned dataLen = getLength();
	
	static char arr[MAX_LEN + 1];

	writeDataToString(arr);

	return arr;
}

void StringPi�ce::writeDataToString(char* str) const {
	if (str == nullptr) {
		return;
	}

	const char* ptrStart = _start;
	const char* ptrEnd = _end;

	unsigned dataLen = getLength();

	for (int i = 0; i < dataLen; i++) {
		str[i] = _data[ptrStart - _data];

		ptrStart++;
		if (ptrStart - _data >= MAX_LEN) {
			ptrStart = _data;
		}
		
	}
}

StringPi�ce::StringPi�ce(const char* data) {
	setData(data);
}

void StringPi�ce::setData(const char* data) {
	unsigned len = myStrlen(data);

	if (len > MAX_LEN || data == nullptr) {
		return;
	}

	if (len == 0) {
		_data[0] = ' ';
		_start = _end = _data;
		return;
	}

	myStrcpy(_data, data);
	_start = _data;
	_end = _data + myStrlen(data) - 1;
}

void StringPi�ce::removeFirstKSymbols(size_t k) {
	if (k > getLength()) {
		// Set the string to the empty string 
		setData(nullptr);
	}

	else {
		// Increase the start by k 
		_start = _start + k;

		// If the start is past the limit of the array
		if (_start - _data >= MAX_LEN) {
			// Move start to the beginning, a few positions to the right
			// The number of positions to the right = the old position of start - MAX_LEN
			_start = _data + ((_start - _data) - MAX_LEN);
		}
	}
}

void StringPi�ce::removeLastKSymbols(size_t k) {
	if (k > getLength()) {
		// Set the string to the empty string 
		setData(nullptr);
	}

	else {
		_end = _end - k;

		if (_end - _data < 0) {
			_end = _data + MAX_LEN + (_end - _data);
		}
	}
}

unsigned StringPi�ce::getLength() const {
	if (this == nullptr || _start == _end) {
		return 0;
	}

	int diff = _start - _end;

	// If diff is > 0, then _start is after _end 
	return diff > 0? MAX_LEN - diff + 1 : diff * -1 + 1;
}

void StringPi�ce::changeSymbolAt(size_t ind, char ch) {
	if (ind >= getLength()) {
		return;
	}

	_data[ind] = ch;
}

// Concatenate at the end 
StringPi�ce& StringPi�ce::operator <<(const char* str) {
	unsigned strLen = myStrlen(str);
	unsigned pieceLen = getLength();

	if (strLen + pieceLen > MAX_LEN) {
		return *this;
	}

	if (pieceLen == 0) {
		_end--;
	}

	for (int i = 0; i < strLen; i++) {
		_end++;

		// If _end goes past the bound of the array, point it to the first position in the array. 
		if (_end - _data > MAX_LEN) {
			_end = _data;
		}

		_data[_end - _data] = str[i];
		// Move _end ptr right
	}

	//_end--;

	//// If _end goes past the bound of the array, point it to the first position in the array. 
	//if (_end - _data < 0) {
	//	_end = _data;
	//}
}


 //Concatenate at the beginning 
StringPi�ce& operator >> (const char* str, StringPi�ce& sp) {
	unsigned dataLen = sp.getLength();
	unsigned strLen = myStrlen(str);

	if (strLen + dataLen > MAX_LEN) {
		return sp;
	}

	if (dataLen == 0) {
		sp._start++;
	}

	for (int i = 0; i < strLen; i++) {
		// Move _start ptr left 
		sp._start--;

		// If _start goes past the bound of the array, point it to the last position in the array. 
		if (sp._start - sp._data < 0) {
			sp._start = sp._data + MAX_LEN - 1;
		}

		sp._data[sp._start - sp._data] = str[strLen - 1 - i];
	}

	//sp._start++;
	//if (sp._start - sp._data > MAX_LEN) {
	//	sp._start = sp._data;
	//}
}

void StringPi�ce::print() const {
	const char* data = getData();
	std::cout << data << std::endl;
}

void StringPi�ce::printAll() const {
	for (int i = 0; i < MAX_LEN; i++) {
		if (_data + i == _end) {
			std::cout << "END";
		}

		if (_data + i == _start) {
			std::cout << "START";
		}
		if (_data[i] == '\0') {
			std::cout << "\\0-";
		}
		else
		std::cout << _data[i] << '-';
	}

	std::cout << std::endl;
}

// The max value of int is 2 147 483 647, which is 10 digits 
// I will add one extra character for the minus sign.
// + 1 for '\0'

const int MAX_DIGITS_COUNT = 10;

StringPi�ce& StringPi�ce::operator <<(int num) {
	static char str[MAX_DIGITS_COUNT + 2];
	stringToInt(str, num);
	return *this << str;
}

StringPi�ce& operator >> (int num, StringPi�ce& sp) {
	static char str[MAX_DIGITS_COUNT + 2];
	stringToInt(str, num);
	return str >> sp;
}
