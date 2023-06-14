#include "StringCreatorPieceByPiece.h"

void StringCreatorPieceByPiece::free()
{
	for (size_t i = 0; i < capacity; i++) {
		if (pieces[i] != nullptr) {
			delete[] pieces[i];
			pieces[i] == nullptr;
		}
	}

	delete[] pieces;
	count = 0;
	capacity = 0;
}

void StringCreatorPieceByPiece::copyFrom(const StringCreatorPieceByPiece& other)
{
	pieces = new StringPiece * [other.capacity]{ nullptr };

	for (size_t i = 0; i < other.capacity; i++)
		pieces[i] = other.pieces[i];

	count = other.count;
	capacity = other.capacity;
}

StringCreatorPieceByPiece::StringCreatorPieceByPiece(size_t _capacity)
{
	pieces = new StringPiece * [_capacity] {nullptr};
	count = 0;
	capacity = _capacity;
}

StringCreatorPieceByPiece::StringCreatorPieceByPiece(const StringCreatorPieceByPiece& other)
{
	copyFrom(other);
}

StringCreatorPieceByPiece::~StringCreatorPieceByPiece()
{
	free();
}

StringCreatorPieceByPiece& StringCreatorPieceByPiece::operator=(const StringCreatorPieceByPiece& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

void StringCreatorPieceByPiece::addPiece(const char* str)
{
	if (!str)
		throw globals::INVALID_INPUT_MESSAGE;

	if (count == capacity) {
		StringPiece** old = pieces;

		pieces = new StringPiece * [capacity + 1]{ nullptr };
		for (size_t i = 0; i < capacity; i++)
			pieces[i] = old[i];

		delete[] old;
		old = nullptr;

		capacity++;
	}

	pieces[count++] = new StringPiece(str);
}

void StringCreatorPieceByPiece::addPiece(size_t idx, const char* str)
{
	if (count == capacity)
		throw globals::NO_SPACE_MESSAGE;

	if (!str)
		throw globals::INVALID_INPUT_MESSAGE;

	if (idx < 0 || idx >= capacity)
		throw globals::INVALID_INDEX_MESSAGE;

	if (!pieces[idx])
		count++;

	pieces[idx] = new StringPiece(str);
}

void StringCreatorPieceByPiece::swapPieces(size_t left, size_t right)
{
	if (left < 0 || left >= capacity || right < 0 || right >= capacity)
		throw globals::INVALID_INDEX_MESSAGE;

	StringPiece* temp = pieces[left];
	pieces[left] = pieces[right];
	pieces[right] = temp;
}

void StringCreatorPieceByPiece::removePiece(size_t idx)
{
	if (idx < 0 || idx >= capacity)
		throw globals::INVALID_INDEX_MESSAGE;

	delete[] pieces[idx];
	pieces[idx] = nullptr;
	count--;
}

size_t StringCreatorPieceByPiece::getLength() const
{
	size_t res = 0;

	for (size_t i = 0; i < count; res += pieces[i++]->getLength());

	return res;
}

MyString StringCreatorPieceByPiece::getString() const
{
	MyString res;
	for (size_t i = 0; i < capacity; i++)
	{
		if (pieces[i]->getData() == nullptr) {
			char str[globals::INTERVALS_COUNT + 1]{ '\0' };
			for (size_t i = 0; i < globals::INTERVALS_COUNT; i++)
				str[i] = ' ';

			res += str;
		}
		else {
			res += pieces[i]->getData();
		}
	}

	return res;
}

StringPiece& StringCreatorPieceByPiece::operator[](size_t idx) const
{
	if (idx < 0 || idx >= capacity)
		throw globals::INVALID_INPUT_MESSAGE;

	return (*pieces[idx]);
}
