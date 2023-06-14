#pragma once

#include "StringPiece.h"
#include "./External Resources/MyString.h"

namespace globals {
	const int INTERVALS_COUNT = 20;
}

class StringCreatorPieceByPiece
{
	StringPiece** pieces = { nullptr };
	size_t count = 0;
	size_t capacity = 0;

	void free();
	void copyFrom(const StringCreatorPieceByPiece& other);
public:
	StringCreatorPieceByPiece() = default;
	StringCreatorPieceByPiece(size_t _capacity);
	StringCreatorPieceByPiece(const StringCreatorPieceByPiece& other);
	~StringCreatorPieceByPiece();

	StringCreatorPieceByPiece& operator=(const StringCreatorPieceByPiece& other);

	void addPiece(const char* str = "");
	void addPiece(size_t idx, const char* str = "");
	void swapPieces(size_t left, size_t right);
	void removePiece(size_t idx);
	size_t getLength() const;
	MyString getString() const;

	StringPiece& operator[](size_t idx) const;
};

