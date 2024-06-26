//this resource is from: https://github.com/Angeld55/Object-oriented_programming_FMI/blob/master/Week%2009/SSO/MyStringSso

#include <iostream>
#pragma once
class String
{
	static const short SSO_MAX_SIZE = sizeof(char*) + sizeof(size_t) - 1;

	union
	{
		struct
		{
			char* _data;
			size_t _size;
		};
		char ssoData[String::SSO_MAX_SIZE + 1]{ '\0' };
	};

	bool isSso() const;
	void move(String&& other);
	void copyFrom(const String& other);
	void free();

	explicit String(size_t size);

	void notUsingSso();
public:

	String();
	String(const char* data);

	String(const String& other);
	String& operator=(const String& other);

	String(String&& other) noexcept;
	String& operator=(String&& other) noexcept;

	String& operator+=(const String& other);

	const char* c_str() const;
	size_t length() const;

	char& operator[](size_t index);
	char operator[](size_t index) const;

	~String();

	friend String operator+(const String& lhs, const String& rhs);
};

std::ostream& operator<<(std::ostream& os, const String& obj);

bool operator<(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);