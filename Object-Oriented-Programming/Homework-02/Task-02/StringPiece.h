#pragma once

namespace globals {
	const int MAX_STRING_PIECE_SIZE = 16;
	const char INVALID_INPUT_MESSAGE[] = "Invalid input data!";
	const char NO_SPACE_MESSAGE[] = "No space in piece!";
	const char INVALID_INDEX_MESSAGE[] = "Index/es is/are out of array bounds!";
}

class StringPiece
{
	char data[globals::MAX_STRING_PIECE_SIZE + 1]{ '\0' };
	size_t length = 0;

public:
	StringPiece() = default;
	StringPiece(const char* value);

	const char* getData() const;
	void setData(const char* _data);

	//end insert
	friend StringPiece& operator<<(StringPiece& obj, const char* str);
	friend StringPiece& operator<<(StringPiece& obj, double number);

	//beginning insert
	friend StringPiece& operator>>(const char* lhs, StringPiece& obj);
	friend StringPiece& operator>>(double number, StringPiece& obj);

	void removeFirst(int n);
	void removeLast(int n);
	void changeAt(size_t idx, char _data);
	size_t getLength() const;
};
