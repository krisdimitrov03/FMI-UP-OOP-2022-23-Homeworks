#include <cstring>
#include <string>
#include "StringPiece.h"

#pragma warning (disable : 4996)

namespace {
	void toString(double number, char*& dest) {
		int numInInt = number;
		std::string temp;
		if ((double)numInInt == number)
			temp = std::to_string(numInInt);
		else
			temp = std::to_string(number);

		dest = new char[temp.length() + 1]{ '\0' };
		strcpy(dest, temp.c_str());
	}
}

StringPiece::StringPiece(const char* value)
{
	setData(value);
}

const char* StringPiece::getData() const
{
	return data;
}

void StringPiece::setData(const char* _data)
{
	if (!_data)
		throw globals::INVALID_INPUT_MESSAGE;

	size_t paramLength = strlen(_data);

	if (paramLength > globals::MAX_STRING_PIECE_SIZE)
		throw globals::NO_SPACE_MESSAGE;

	strcpy(data, _data);
	length = paramLength;
}

StringPiece& operator<<(StringPiece& obj, const char* str)
{
	if (!str)
		throw globals::INVALID_INPUT_MESSAGE;

	size_t len = strlen(str);

	if (len + obj.length > globals::MAX_STRING_PIECE_SIZE)
		throw globals::NO_SPACE_MESSAGE;

	strcat(obj.data, str);
	obj.length += len;

	return obj;
}

StringPiece& operator<<(StringPiece& obj, double number) {
	char* str = nullptr;
	toString(number, str);
	obj << str;
	delete[] str;
	return obj;
}

StringPiece& operator>>(const char* str, StringPiece& obj)
{
	if (!str)
		throw globals::INVALID_INPUT_MESSAGE;

	size_t len = strlen(str);

	if (len + obj.length > globals::MAX_STRING_PIECE_SIZE)
		throw globals::NO_SPACE_MESSAGE;

	if (obj.length != 0)
		for (size_t i = 0; i < obj.length; i++)
			obj.data[obj.length - i - 1 + len] = obj.data[obj.length - i - 1];

	for (size_t i = 0; i < len; i++)
		obj.data[i] = str[i];

	obj.length += len;

	return obj;
}

StringPiece& operator>>(double number, StringPiece& obj)
{
	char* str = nullptr;
	toString(number, str);
	str >> obj;
	delete[] str;
	return obj;
}

void StringPiece::removeFirst(int n)
{
	if (n <= 0 || length < n)
		throw globals::INVALID_INDEX_MESSAGE;

	for (size_t i = n; i < length; i++)
		data[i - n] = data[i];

	for (int i = length - 1; i > length - n - 1; i--)
		data[i] = '\0';

	length -= n;
}

void StringPiece::removeLast(int n)
{
	if (n <= 0 || length < n)
		throw globals::INVALID_INDEX_MESSAGE;

	for (int i = length - 1; i > length - n - 1; i--)
		data[i] = '\0';

	length -= n;
}

void StringPiece::changeAt(size_t idx, char _data)
{
	if (idx < 0 || idx > length - 1)
		throw globals::INVALID_INDEX_MESSAGE;

	data[idx] = _data;
}

size_t StringPiece::getLength() const
{
	return length;
}
