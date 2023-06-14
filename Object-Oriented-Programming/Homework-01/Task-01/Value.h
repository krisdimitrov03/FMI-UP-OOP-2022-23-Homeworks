#pragma once

#include <iostream>
#include "constants.h"
#include "Alignment.h"

struct Value {
private:
	char text[sizes::MAX_VALUE_LEN + 1];

public:
	Value() = default;
	Value(const char* text);

	const char* getText() const;
	void setText(const char* text);

	void print(const Alignment& alignment, size_t columnLength) const;
};