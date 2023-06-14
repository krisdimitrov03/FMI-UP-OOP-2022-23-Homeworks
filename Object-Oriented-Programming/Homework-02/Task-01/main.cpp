#include <iostream>
#include "String.h"

int main()
{
	String s("fjskdfsdgfdhgdsghfdsytrhgf");
	String s2("fdsfsd");
	std::cout << s.length() << std::endl; // 26
	std::cout << s2.length() << std::endl; // 6
	String s3 = s + s2;
	std::cout << s3 << std::endl; // fjskdfsdgfdhgdsghfdsytrhgffdsfsd
	s3 += s;

	String subStr = s3.substr(3, 5);
	std::cout << subStr; // kdfsd
}