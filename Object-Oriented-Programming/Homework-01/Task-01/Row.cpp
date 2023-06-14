#include <iostream>
#include "Row.h"

void Row::readFromFile(std::ifstream& file) {
	char current;
	file.get(current);
	while (current != '\n' && !file.eof()) {
		if (current == '|' || current == ' ') {
			while (current == '|' || current == ' ') {
				file.get(current);
				if (file.eof())
					break;
			}
		}
		else {
			char currentWord[sizes::MAX_VALUE_LEN + 1]{ '\0' };
			for (size_t i = 0; i < sizes::MAX_VALUE_LEN; i++)
			{
				if (current == ' ') {
					file.get(current);
					size_t destPos = file.tellg();
					if (current == ' ' || current == '|') {

						file.seekg(destPos - 1, std::ios::beg);
						break;
					}
					file.seekg(destPos - 1, std::ios::beg);
					current = ' ';
				}

				if (current == '|') {
					break;
				}

				currentWord[i] = current;
				file.get(current);
			}

			this->columns[this->columnsCount++].setText(currentWord);
		}
	}
}

void Row::print(const Alignment* alignments, const size_t* columnsLengths) {
	std::cout << "|";
	for (size_t i = 0; i < this->columnsCount; i++)
	{
		std::cout << " ";
		this->columns[i].print(alignments[i], columnsLengths[i]);
		std::cout << " |";
	}

	std::cout << std::endl;
}

bool Row::isEmpty() {
	if (this->columnsCount == 0)
		return true;

	return false;
}

size_t Row::getColumnLength(size_t index) const {
	return strlen(columns[index].getText());
}

size_t Row::getColumnIndex(const char* columnName) const {
	for (size_t i = 0; i < columnsCount; i++)
		if (!strcmp(columns[i].getText(), columnName))
			return i;

	return -1;
}

bool Row::checkValue(size_t index, const char* value)
{
	return !strcmp(columns[index].getText(), value);
}

void Row::changeColumnName(const char* oldName, const char* newName) {
	for (size_t i = 0; i < columnsCount; i++)
	{
		if (!strcmp(this->columns[i].getText(), oldName)) {
			this->columns[i].setText(newName);
			return;
		}
	}
}

void Row::changeValue(size_t columnIndex, const char* newValue) {
	//validate index
	this->columns[columnIndex].setText(newValue);
}

void Row::writeToFile(std::ofstream& file) const {
	file << "|";

	for (size_t i = 0; i < columnsCount; i++)
		file << " " << this->columns[i].getText() << " |";

	file << "\n";
}