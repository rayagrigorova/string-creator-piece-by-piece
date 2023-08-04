#pragma once

#include "../StringPiece/StringPiece.h"
#include "../MyString/MyString.h"

class StringCreatorPieceByPiece {

	// I chose to use an array of pointers to string pieces
	// Motivation: adding and swapping pieces will be easier;
	// resizing is faster because only pointers to strings are being copied;
	// it will be possible to mark a piece as deleted - by setting
	// the corresponding pointer in the array to nullptr. 

	StringPiece** _pieces = nullptr;
	unsigned _numberOfPieces = 0;
	unsigned _capacity = 0;

	void free();
	void copyFrom(const StringCreatorPieceByPiece& other);
	void resize();

public:
	// Big 4 - the array of pieces is dynamic 
	StringCreatorPieceByPiece() = default;
	StringCreatorPieceByPiece(const StringCreatorPieceByPiece& other);
	StringCreatorPieceByPiece& operator=(const StringCreatorPieceByPiece& other);
	~StringCreatorPieceByPiece();

	StringCreatorPieceByPiece(unsigned capacity);

	void addPiece(const char* str = nullptr);
	void addPiece(const char* str, size_t ind);

	void swap(size_t ind1, size_t ind2);

	void remove(size_t ind);

	unsigned length() const;

	StringPiece& operator[](size_t index);

	MyString getString() const;
};
