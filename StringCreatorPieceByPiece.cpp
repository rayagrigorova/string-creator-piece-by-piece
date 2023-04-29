#include "StringCreatorPieceByPiece.h"

void StringCreatorPieceByPiece::free() {
	// The pieces are created using operator new 
	for (int i = 0; i < _numberOfPieces; i++) {
		delete _pieces[i];
	}

	// Delete the array of pointers (created using new[])
	delete[] _pieces;

	_pieces = nullptr;
	_numberOfPieces = _capacity = 0;
}

void StringCreatorPieceByPiece::resize() {
	_capacity *= 2;
	StringPiece** newArr = new StringPiece*[_capacity]{nullptr};

	// Copy the old array of pointers to the new one 
	for (int i = 0; i < _numberOfPieces; i++) {
		newArr[i] = _pieces[i];
	}

	// Delete the old array of pointers but not the actual data
	delete[] _pieces;

	// Point to the new array
	_pieces = newArr;
}

void StringCreatorPieceByPiece::copyFrom(const StringCreatorPieceByPiece& other) {
	_numberOfPieces = other._numberOfPieces;
	_capacity = other._capacity;
	_pieces = new StringPiece*[_capacity]{nullptr};

	for (int i = 0; i < _capacity; i++) {
		_pieces[i] = other._pieces[i];
	}
}

StringCreatorPieceByPiece::StringCreatorPieceByPiece(const StringCreatorPieceByPiece& other) {
	copyFrom(other);
}

StringCreatorPieceByPiece& StringCreatorPieceByPiece::operator=(const StringCreatorPieceByPiece& other){
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

StringCreatorPieceByPiece::~StringCreatorPieceByPiece() {
	free();
}

StringCreatorPieceByPiece::StringCreatorPieceByPiece(unsigned capacity) {
	// Creating an array of size 0 shouldn't be possible
	if (capacity == 0) {
		return;
	}

	_capacity = capacity;
	_pieces = new StringPiece * [capacity] {nullptr};
}

void StringCreatorPieceByPiece::addPiece(const char* str) {
	if (_numberOfPieces >= _capacity) {
		resize();
	}

	_pieces[_numberOfPieces++] = new StringPiece(str);
}

void StringCreatorPieceByPiece::swap(size_t ind1, size_t ind2) {
	if (ind1 >= _numberOfPieces || ind2 >= _numberOfPieces || ind1 == ind2) {
		return;
	}

	// Only pointers are swapped 
	StringPiece* temp;
	temp = _pieces[ind1];
	_pieces[ind1] = _pieces[ind2];
	_pieces[ind2] = temp;
}

void StringCreatorPieceByPiece::remove(size_t ind) {
	if (ind >= _numberOfPieces) {
		return;
	}

	// created using new -> delete 
	delete _pieces[ind];
	// Mark the piece as deleted 
	_pieces[ind] = nullptr;
}

void StringCreatorPieceByPiece::addPiece(const char* str, size_t ind) {
	if (ind >= _numberOfPieces) {
		return;
	}
	 
	// Delete the old piece in case it exists
	// If it doesn't, the pointer is set to nullptr
	// and delete will not do anything. 
	delete _pieces[ind];
	_pieces[ind] =  new StringPiece(str);
}

unsigned StringCreatorPieceByPiece::length() const {
	unsigned len = 0;

	// Sum the length of all the pieces 
	for (int i = 0; i < _numberOfPieces; i++) {
		len += _pieces[i]->getLength();
	}

	return len;
}

const size_t NUMBER_OF_SPACES = 20;

MyString StringCreatorPieceByPiece::getString() const {
	unsigned size = 0;

	// Create an array with the sizes of the pieces 
	size_t* pieceSizes = new size_t[_numberOfPieces];

	for (int i = 0; i < _numberOfPieces; i++) {
		pieceSizes[i] = _pieces[i]->getLength();

		// Initialize the size of the string to be created
		if (_pieces[i] == nullptr && i != _numberOfPieces - 1) {
			size += NUMBER_OF_SPACES;
		}

		else {
			size += pieceSizes[i];
		}
	}

	// The string is null terminated, so + 1 for '\0'
	char* arr = new char[size + 1];
	char* ptr = arr;

	for (int i = 0; i < _numberOfPieces; i++) {
		if (_pieces[i] != nullptr) {
			_pieces[i]->writeDataToString(ptr);

			ptr += pieceSizes[i];
		}

		// The piece was deleted 
		else {
			for (int j = 0; j < NUMBER_OF_SPACES; j++) {
				*(ptr + j) = ' ';
			}
			ptr += NUMBER_OF_SPACES;
		}

	}

	arr[size] = '\0';

	delete[] pieceSizes;
	return MyString(arr);
}


StringPiåce& StringCreatorPieceByPiece::operator[](size_t index) {
	return *_pieces[index];
}
