#pragma once

#include <iostream>
#include <sstream>

const int MAX_LEN = 16;

class StringPiåce {
	char _data[MAX_LEN];

	// My string will not be null terminated 
	// the reason - faster concatenation 
	const char* _start = _data;
	const char* _end = _data;

public:
	StringPiåce() = default;

	StringPiåce(const char* data);

	const char* getData() const;
	void setData(const char* data);

	void removeFirstKSymbols(size_t k);
	void removeLastKSymbols(size_t k);

	void changeSymbolAt(size_t ind, char ch);	

	unsigned getLength() const;

	void writeDataToString(char* str) const;

	// This can be a class member because the left argument is a string piece
	StringPiåce& operator <<(const char* str);

	friend StringPiåce& operator >> (const char* str, StringPiåce& sp);

	void print() const;
	void printAll() const;
};
