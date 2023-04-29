#pragma once

#include "StringPiåce.h"
#include "MyString.h"

class StringCreaterPieceByPiece {

	// I chose to use an array of pointers to string pieces
	// Motivation: adding and swapping pieces will be easier;
	// resizing is faster because only pointers to strings are being copied;
	// it will be possible to mark a piece as deleted - by setting
	// the corresponding pointer in the array to nullptr. 

	StringPiåce** _pieces = nullptr;
	unsigned _numberOfPieces = 0;
	unsigned _capacity = 0;

	void free();
	void copyFrom(const StringCreaterPieceByPiece& other);
	void resize();

public:
	// Big 4 - the array of pieces is dynamic 
	StringCreaterPieceByPiece() = default;
	StringCreaterPieceByPiece(const StringCreaterPieceByPiece& other);
	StringCreaterPieceByPiece& operator=(const StringCreaterPieceByPiece& other);
	~StringCreaterPieceByPiece();

	StringCreaterPieceByPiece(unsigned capacity);

	void addPiece(const char* str = nullptr);
	void addPiece(const char* str, size_t ind);

	void swap(size_t ind1, size_t ind2);

	void remove(size_t ind);

	unsigned length() const;

	StringPiåce& operator[](size_t index);

	MyString getString() const;
};