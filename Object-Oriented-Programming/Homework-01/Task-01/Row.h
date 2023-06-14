#pragma once

#include <fstream>
#include "Value.h"

class Row {
	Value columns[sizes::MAX_COLUMNS];
	size_t columnsCount = 0;

public:
	Row() = default;

	void readFromFile(std::ifstream& file);
	void print(const Alignment* alignments, const size_t* columnsLengths);
	void changeColumnName(const char* oldName, const char* newName);
	void changeValue(size_t columnIndex, const char* newValue);
	void writeToFile(std::ofstream& file) const;
	size_t getColumnLength(size_t index) const;
	size_t getColumnIndex(const char* columnName) const;
	bool checkValue(size_t index, const char* value);
	bool isEmpty();
};