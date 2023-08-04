#include "StringPiåce.h"

#include <iostream>
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

	void intToString(char* str, int num) {
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

const char* StringPiåce::getData() const {
	static char arr[MAX_LEN + 1];
	writeDataToString(arr);
	return arr;
}

void StringPiåce::writeDataToString(char* str) const {
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

StringPiåce::StringPiåce(const char* data) {
	setData(data);
}

void StringPiåce::setData(const char* data) {
	if (data == nullptr) {
		return;
	}

	unsigned len = myStrlen(data);

	if (len > MAX_LEN) {
		return;
	}

	// Length will be 0 if data is the empty string
	if (len == 0) {
		_data[0] = '\0';
		_start = _end = _data;
		return;
	}

	myStrcpy(_data, data);
	_start = _data;
	_end = _data + len - 1;
}

void StringPiåce::removeFirstKSymbols(size_t k) {
	if (k > getLength()) {
		setData(nullptr);
	}

	else {
		// Increase the start by k 
		_start = _start + k;

		// If the start is past the limit of the array
		if (_start - _data >= MAX_LEN) {
			// Move start to the beginning, a few positions to the right
			// The number of positions to the right is the old position of start - MAX_LEN
			_start = _data + ((_start - _data) - MAX_LEN);
		}
	}
}

void StringPiåce::removeLastKSymbols(size_t k) {
	if (k > getLength()) {
		setData(nullptr);
	}

	else {
		_end = _end - k;

		// If _end is past the limit of the array, move it to the end of the array, a few positions to the left. 
		// The number of positions to the left is MAX_LEN + the difference between _end and data. 
		if (_end - _data < 0) {
			_end = _data + MAX_LEN + (_end - _data);
		}
	}
}

unsigned StringPiåce::getLength() const {
	// The 'this == nullptr' check prevents null pointer dereference
	// when iterating through an array of stringPieces. 
	if (this == nullptr || _start == _end) {
		return 0;
	}

	int diff = _start - _end;

	// _data is the empty string
	if (diff == 0 && _data[0] == '\0') {
		return 0;
	}

	// If diff is > 0, then _start is after _end 
	// In this case, diff - 1 is the number of elements in the array between _start and _end.
	// Then, the length of the array == MAX_LEN - ( diff - 1 ).

	// If diff <= 0, _start is before(or equal to) _end. 
	return diff > 0? MAX_LEN - diff + 1 : diff * -1 + 1;
}

void StringPiåce::changeSymbolAt(size_t ind, char ch) {
	if (ind >= getLength()) {
		return;
	}

	_data[ind] = ch;
}

// Concatenate at the end 
StringPiåce& StringPiåce::operator <<(const char* str) {
	unsigned strLen = myStrlen(str);
	unsigned pieceLen = getLength();

	if (strLen + pieceLen > MAX_LEN) {
		return *this;
	}

	// If the string is empty, start saving data from the first position in the array 
	if (pieceLen == 0) {
		_end--;
	}

	for (int i = 0; i < strLen; i++) {
		// Move _end ptr right
		_end++;

		// If _end goes past the bound of the array, point it to the first position in the array. 
		if (_end - _data > MAX_LEN) {
			_end = _data;
		}

		_data[_end - _data] = str[i];
	}

	return *this;
}

 //Concatenate at the beginning 
StringPiåce& operator >> (const char* str, StringPiåce& sp) {
	unsigned dataLen = sp.getLength();
	unsigned strLen = myStrlen(str);

	if (strLen + dataLen > MAX_LEN) {
		return sp;
	}

	// If the string is empty, start saving data from the first position in the array 
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

		// The string is saved starting from its end. 
		sp._data[sp._start - sp._data] = str[strLen - 1 - i];
	}

	return sp;
}

// The max value of int is 2 147 483 647, which is 10 digits 
// I will add one extra character for the minus sign and one more for '\0'

const int MAX_DIGITS_COUNT = 10;

StringPiåce& StringPiåce::operator <<(int num) {
	static char str[MAX_DIGITS_COUNT + 2];
	intToString(str, num);
	return *this << str;
}

StringPiåce& operator >> (int num, StringPiåce& sp) {
	static char str[MAX_DIGITS_COUNT + 2];
	intToString(str, num);
	return str >> sp;
}

