#pragma once

const int MAX_LEN = 16;

class StringPiåce {
	char _data[MAX_LEN];

	// My string will not be null terminated 
	const char* _start = _data;
	const char* _end = _data;

public:
	StringPiåce() { _data[0] = '\0'; };

	StringPiåce(const char* data);

	const char* getData() const;
	void setData(const char* data);

	void removeFirstKSymbols(size_t k);
	void removeLastKSymbols(size_t k);

	void changeSymbolAt(size_t ind, char ch);	

	unsigned getLength() const;

	// Save the data contained in the stringPiece to a string 
	void writeDataToString(char* str) const;

	// These functions can be class members because the left argument is a string piece
	StringPiåce& operator <<(const char* str);
	StringPiåce& operator <<(int num); // overload

	friend StringPiåce& operator >> (const char* str, StringPiåce& sp);
	friend StringPiåce& operator >> (int num, StringPiåce& sp); // overload
};