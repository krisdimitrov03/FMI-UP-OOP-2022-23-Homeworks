#pragma once
#include <iostream>

class String
{
	size_t capacity = 0;

	union {
		struct {
			char* data;
			size_t size;
		} heapBuff;

		char stackBuff[sizeof(heapBuff)]{ '\0' };
	};

	void free();
	void copyFrom(const String& other);
	bool isStatic() const;
	void turnToDynamic(const char* _data);
public:
	String();
	String(size_t capacity);
	String(const char* data);
	String(const String& other);
	String& operator=(const String& other);
	~String();

	size_t length() const;
	String& operator+=(const String& other);

	String substr(size_t begin, size_t count) const;

	char& operator[](size_t index);
	char operator[](size_t index) const;

	const char* c_str() const;

	friend String operator+(const String& lhs, const String& rhs);
	friend std::istream& operator>>(std::istream& is, String& str);
};

std::ostream& operator<<(std::ostream& os, const String& str);

bool operator<(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);

