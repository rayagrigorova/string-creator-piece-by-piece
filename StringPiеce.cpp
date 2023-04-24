#include "StringPiåce.h"

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
}

const char* StringPiåce::getData() const {
	unsigned dataLen = getLength();
	
	static char arr[MAX_LEN + 1];

	writeDataToString(arr);

	return arr;
}

void StringPiåce::writeDataToString(char* str) const {
	if (str == nullptr) {
		return;
	}

	unsigned dataLen = getLength();

	unsigned dataInd;
	if (_start - _end < 0) {
		dataInd = 0;
	}

	else {
		dataInd = _start - _data;
	}

	for (int i = 0; i < dataLen; i++) {
		str[i] = _data[dataInd++];
		dataInd %= MAX_LEN;
	}
}

StringPiåce::StringPiåce(const char* data) {
	setData(data);
}

void StringPiåce::setData(const char* data) {
	unsigned len = myStrlen(data);

	if (len > MAX_LEN) {
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

void StringPiåce::removeFirstKSymbols(size_t k) {
	if (k > getLength()) {
		// Set the string to the empty string 
		setData(nullptr);
	}

	else {
		// Increase the start by k 
		_start = _start + k;

		// If the start is past the limit of the array
		if (_start - _data > MAX_LEN) {
			// Move start to the beginning, a few positions to the right
			// The number of positions to the right = the old position of start - MAX_LEN
			_start = _data + ((_start - _data) - MAX_LEN);
		}
	}
}

void StringPiåce::removeLastKSymbols(size_t k) {
	if (k > getLength()) {
		// Set the string to the empty string 
		setData(nullptr);
	}

	else {
		_end = _end - k;
	}
}

unsigned StringPiåce::getLength() const {
	if (this == nullptr) {
		return 0;
	}

	int diff = _start - _end;

	// If diff is > 0, then _start is after _end 
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
	unsigned ind = _end - _data;

	// Copy the string after the end and increase _end 
	myStrcpy(_data + ind, str);
	_end += (strLen - 1);
	return *this;
}

 //Concatenate at the beginning 
StringPiåce& operator >> (const char* str, StringPiåce& sp) {
	unsigned dataLen = sp.getLength();
	unsigned strLen = myStrlen(str);

	if (strLen + dataLen > MAX_LEN) {
		return sp;
	}

	// If this is the first time concatenating a string at the beginning, 
	// move the _start pointer at the end of the char array, past _end 

	if (sp._start - sp._end < 0) { // _start is before _end 
		sp._start = sp._start + MAX_LEN - strLen; // move to the back of the array
	}

	else { // start is already at the back of the array
		sp._start -= strLen; // move it left 
	}

	myStrcpy(sp._data + (sp._start - sp._data), str);
}

void StringPiåce::print() const {
	const char* data = getData();
	std::cout << data << std::endl;
}

void StringPiåce::printAll() const {
	for (int i = 0; i < MAX_LEN; i++) {
		if (_data + i == _end) {
			std::cout << "END";
		}

		else if (_data + i == _start) {
			std::cout << "START";
		}
		else  if (_data[i] == '\0') {
			std::cout << "\\0-";
		}
		else
		std::cout << _data[i] << '-';
	}

	std::cout << std::endl;
}

