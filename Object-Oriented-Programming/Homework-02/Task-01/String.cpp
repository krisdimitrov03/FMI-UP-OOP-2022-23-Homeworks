#include "String.h"
#include <cstring>

#pragma warning (disable : 4996)

void String::free()
{
	if (isStatic()) {
		for (size_t i = 0; i < sizeof(heapBuff); i++)
			stackBuff[i] = '\0';
	}
	else {
		delete[] heapBuff.data;
		heapBuff.data = nullptr;
		heapBuff.size = 0;
	}
	capacity = 0;
}

void String::copyFrom(const String& other) {
	if (other.isStatic()) {
		for (size_t i = 0; i < sizeof(stackBuff) - 1; i++)
			stackBuff[i] = other.stackBuff[i];
	}
	else {
		heapBuff.size = other.heapBuff.size;
		heapBuff.data = new char[heapBuff.size + 1];
		strcpy(heapBuff.data, other.heapBuff.data);
	}
	capacity = other.capacity;
}

bool String::isStatic() const
{
	return capacity < sizeof(heapBuff);
}

void String::turnToDynamic(const char* _data)
{
	if (!_data)
		throw "Invalid input data.";

	size_t newLen = strlen(stackBuff) + strlen(_data) + 1;

	char* newData = new char[newLen] {'\0'};
	strcpy(newData, stackBuff);
	strcat(newData, _data);

	for (size_t i = 0; i < sizeof(heapBuff); i++)
		stackBuff[i] = '\0';

	heapBuff.data = newData;
	heapBuff.size = newLen;
	capacity = newLen;
	newData = nullptr;
}

String::String() : String(sizeof(heapBuff) - 1)
{
}

String::String(size_t capacity)
{
	if (capacity >= sizeof(heapBuff)) {
		heapBuff.data = new char[capacity + 1] { '\0' };
		heapBuff.size = 0;
	}

	this->capacity = capacity;
}

String::String(const char* data)
{
	size_t length = strlen(data);

	if (length >= sizeof(heapBuff)) {
		heapBuff.data = new char[length + 1] {'\0'};
		strcpy(heapBuff.data, data);
		heapBuff.size = length;
		capacity = length;
	}
	else {
		strcpy(stackBuff, data);
		capacity = sizeof(heapBuff) - 1;
	}
}

String::String(const String& other)
{
	copyFrom(other);
}

String& String::operator=(const String& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

String::~String()
{
	free();
}

size_t String::length() const
{
	if (isStatic()) {
		return strlen(stackBuff);
	}
	else {
		return heapBuff.size;
	}
}

String& String::operator+=(const String& other)
{
	size_t fl = length();
	size_t sl = other.length();

	if (isStatic()) {
		if (other.isStatic()) {
			if (strlen(stackBuff) + other.length() <= sizeof(heapBuff) - 1)
				strcat(stackBuff, other.stackBuff);
			else {
				turnToDynamic(other.stackBuff);
			}
		}
		else {
			turnToDynamic(other.heapBuff.data);
		}
	}
	else {
		char* newData = new char[fl + other.length() + 1] { '\0' };
		strcpy(newData, heapBuff.data);

		if (other.isStatic())
			strcat(newData, other.stackBuff);
		else
			strcat(newData, other.heapBuff.data);

		heapBuff.data = newData;
		heapBuff.size += other.length();
	}
	capacity = fl + sl;

	return *this;
}

String String::substr(size_t begin, size_t count) const
{
	if (begin + count > length())
		throw "Index out of range!";

	String res(count + 1);
	if (isStatic()) {
		for (size_t i = 0; i < count; i++)
			res.stackBuff[i] = stackBuff[i + begin];
	}
	else {
		if (count < sizeof(res.heapBuff)) {
			for (size_t i = 0; i < count; i++)
				res.stackBuff[i] = heapBuff.data[i + begin];
		}
		else {
			res.heapBuff.data = new char[count + 1] {'\0'};
			for (size_t i = 0; i < count; i++)
				res.heapBuff.data[i] = heapBuff.data[i + begin];
		}
	}

	return res;
}

char& String::operator[](size_t index)
{
	if (index > capacity)
		throw "Index out of range!";

	if (isStatic())
		return stackBuff[index];

	return heapBuff.data[index];
}

char String::operator[](size_t index) const
{
	if (index > capacity)
		throw "Index out of range!";

	return isStatic()
		? stackBuff[index]
		: heapBuff.data[index];
}

const char* String::c_str() const
{
	return isStatic()
		? stackBuff
		: heapBuff.data;
}

String operator+(const String& lhs, const String& rhs)
{
	String result(lhs);
	result += rhs;

	return result;
}

std::istream& operator>>(std::istream& is, String& str)
{
	char buff[1024];
	is.getline(buff, 1024);
	size_t length = strlen(buff);
	str.free();

	if (length >= sizeof(str.heapBuff)) {
		str.heapBuff.size = length;
		str.heapBuff.data = new char[length + 1] {'\0'};
		strcpy(str.heapBuff.data, buff);
	}
	else {
		strcpy(str.stackBuff, buff);
	}

	str.capacity = length;

	return is;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	return os << str.c_str();
}

bool operator<(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator>(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator==(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}