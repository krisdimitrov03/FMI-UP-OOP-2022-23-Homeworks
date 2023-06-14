#include "helper.h"
#include "constants.h"
#include <iostream>
#include <cstring>

bool str::contains(const char* str, const char* substr) {
	if (str == nullptr || substr == nullptr) {
		std::cout << message::VALIDATION_ERR << std::endl;
		return false;
	}

	size_t strLen = strlen(str);
	size_t substrLen = strlen(substr);

	if (substrLen > strLen)
		return false;

	for (size_t i = 0; i < strLen - substrLen + 1; i++)
	{
		if (str[i] == substr[0]) {
			bool isSame = true;
			for (size_t j = 0; j < substrLen; j++)
			{
				if (str[i + j] != substr[j]) {
					isSame = false;
					break;
				}
			}

			if (isSame)
				return true;
		}
	}

	return false;
}