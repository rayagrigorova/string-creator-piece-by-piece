#pragma once

const int MAX_LEN = 16;

class StringPi�ce {
	char _data[MAX_LEN];

	// My string will not be null terminated 
	const char* _start = _data;
	const char* _end = _data;

public:
	StringPi�ce() { _data[0] = '\0'; };

	StringPi�ce(const char* data);

	const char* getData() const;
	void setData(const char* data);

	void removeFirstKSymbols(size_t k);
	void removeLastKSymbols(size_t k);

	void changeSymbolAt(size_t ind, char ch);	

	unsigned getLength() const;

	// Save the data contained in the stringPiece to a string 
	void writeDataToString(char* str) const;

	// These functions can be class members because the left argument is a string piece
	StringPi�ce& operator <<(const char* str);
	StringPi�ce& operator <<(int num); // overload

	friend StringPi�ce& operator >> (const char* str, StringPi�ce& sp);
	friend StringPi�ce& operator >> (int num, StringPi�ce& sp); // overload
};