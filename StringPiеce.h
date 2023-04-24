#pragma once

#include <iostream>
#include <sstream>

const int MAX_LEN = 16;

class StringPi�ce {
	char _data[MAX_LEN];

	// My string will not be null terminated 
	// the reason - faster concatenation 
	const char* _start = _data;
	const char* _end = _data;

public:
	StringPi�ce() = default;

	StringPi�ce(const char* data);

	const char* getData() const;
	void setData(const char* data);

	void removeFirstKSymbols(size_t k);
	void removeLastKSymbols(size_t k);

	void changeSymbolAt(size_t ind, char ch);	

	unsigned getLength() const;

	void writeDataToString(char* str) const;

	// This can be a class member because the left argument is a string piece
	StringPi�ce& operator <<(const char* str);

	friend StringPi�ce& operator >> (const char* str, StringPi�ce& sp);

	void print() const;
	void printAll() const;
};
