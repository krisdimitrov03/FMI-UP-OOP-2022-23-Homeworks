#pragma once
#include <string>

#include "Row.h"

class Table {
	Alignment alignments[sizes::MAX_COLUMNS] = { Alignment::left };
	size_t alignmentsCount = 0;
	Row heading;
	Row rows[sizes::MAX_ROWS];
	size_t rowsCount = 0;

	void writeAlignments(std::ofstream& file) const;
	void readAlignments(std::ifstream& file);
public:
	Table() = default;

	void readFromFile(const char* fileName);
	void print();
	void changeColumnName(const char* oldName, const char* newName);
	void addRow(const Row& row);
	void changeValue(size_t row, const char* column, const char* _newValue);
	void changeValue(const char* column, const char* value, const char* newValue);
	void printSelectedRows(const char* value, const char* column);
	void writeToFile(const char* fileName) const;
};