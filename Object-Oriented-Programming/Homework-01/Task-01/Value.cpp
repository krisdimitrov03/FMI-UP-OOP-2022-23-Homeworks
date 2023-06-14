#include "Value.h"

Value::Value(const char* text) {
	setText(text);
}

const char* Value::getText() const {
	return this->text;
}

void Value::setText(const char* text) {
	if (text == nullptr) {
		std::cout << message::VALIDATION_ERR << std::endl;
		return;
	}

	strcpy_s(this->text, text);
}

void Value::print(const Alignment& alignment, size_t columnLength) const {
	size_t length = strlen(this->text);

	bool isOdd = (columnLength - length) % 2 != 0;

	if (alignment == Alignment::left) {
		std::cout << this->text;

		for (size_t i = 0; i < columnLength - length; i++)
			std::cout << " ";
	}
	else if (alignment == Alignment::center) {
		for (size_t i = 0; i < (columnLength - length) / 2; i++)
			std::cout << " ";

		std::cout << this->text;

		for (size_t i = 0; i < (columnLength - length) / 2; i++)
			std::cout << " ";
		if (isOdd)
			std::cout << " ";
	}
	else if (alignment == Alignment::right) {
		for (size_t i = 0; i < columnLength - length; i++)
			std::cout << " ";

		std::cout << this->text;
	}
}