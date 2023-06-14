#include "Table.h"
#include "helper.h"

void Table::writeAlignments(std::ofstream& file) const {
	file << "|";
	for (size_t i = 0; i < this->alignmentsCount; i++)
	{
		switch (alignments[i]) {
		case Alignment::left:
			file << " :--- |";
			break;
		case Alignment::center:
			file << " :---: |";
			break;
		case Alignment::right:
			file << " ---: |";
			break;
		}
	}

	file << "\n";
}

void Table::readAlignments(std::ifstream& file) {
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
			char currentAlignmentStr[sizes::MAX_VALUE_LEN + 1]{ '\0' };
			for (size_t i = 0; i < sizes::MAX_VALUE_LEN; i++)
			{
				if (current == ' ' || current == '|')
					break;

				currentAlignmentStr[i] = current;
				file.get(current);
			}

			if (str::contains(currentAlignmentStr, ":---:")) {
				alignments[alignmentsCount++] = Alignment::center;
			}
			else if (str::contains(currentAlignmentStr, "---:")) {
				alignments[alignmentsCount++] = Alignment::right;
			}
			else {
				alignments[alignmentsCount++] = Alignment::left;
			}
		}
	}
}

void Table::readFromFile(const char* fileName) {
	std::ifstream file(fileName, std::ios::in);

	if (!file.is_open()) {
		std::cout << message::FILE_ERR << std::endl;
		return;
	}

	if (fileName == nullptr) {
		std::cout << message::VALIDATION_ERR << std::endl;
		return;
	}

	this->heading.readFromFile(file);
	readAlignments(file);
	while (!file.eof())
		this->rows[rowsCount++].readFromFile(file);

	file.close();
}

void Table::print() {
	size_t* columnsLengths = new size_t[alignmentsCount]{ 0 };

	for (size_t i = 0; i < alignmentsCount; i++)
	{
		size_t currentLength = heading.getColumnLength(i);
		if (currentLength > columnsLengths[i])
			columnsLengths[i] = currentLength;

		for (size_t j = 0; j < rowsCount; j++)
		{
			currentLength = rows[j].getColumnLength(i);
			if (currentLength > columnsLengths[i])
				columnsLengths[i] = currentLength;
		}
	}

	this->heading.print(this->alignments, columnsLengths);

	std::cout << "|";

	for (size_t i = 0; i < this->alignmentsCount; i++)
	{
		std::cout << " ";
		for (size_t j = 0; j < columnsLengths[i]; j++)
			std::cout << "-";
		std::cout << " |";
	}
	std::cout << std::endl;

	for (size_t i = 0; i < rowsCount; i++)
		this->rows[i].print(this->alignments, columnsLengths);
}

void Table::changeColumnName(const char* oldName, const char* newName) {
	this->heading.changeColumnName(oldName, newName);
}

void Table::addRow(const Row& row) {
	if (!this->rows[sizes::MAX_ROWS - 1].isEmpty()) {
		std::cout << message::NO_SPACE << std::endl;
		return;
	}

	size_t firstEmptyPosition = 0;
	for (size_t i = 0; i < sizes::MAX_ROWS; i++)
	{
		if (this->rows[i].isEmpty()) {
			firstEmptyPosition = i;
			break;
		}
	}

	this->rows[firstEmptyPosition] = row;
}

void Table::changeValue(size_t row, const char* column, const char* newValue) {
	if (row == 0 || row > sizes::MAX_ROWS - 1) {
		std::cout << message::VALIDATION_ERR << std::endl;
		return;
	}

	if (column == nullptr || newValue == nullptr) {
		std::cout << message::VALIDATION_ERR << std::endl;
		return;
	}

	size_t index = heading.getColumnIndex(column);
	this->rows[row - 1].changeValue(index, newValue);
}

void Table::changeValue(const char* column, const char* value, const char* newValue) {
	size_t columnIndex = heading.getColumnIndex(column);

	for (size_t i = 0; i < rowsCount; i++)
	{
		if (rows[i].checkValue(columnIndex, value))
			rows[i].changeValue(columnIndex, newValue);
	}
}

void Table::printSelectedRows(const char* value, const char* column) {
	size_t* columnsLengths = new size_t[alignmentsCount]{ 0 };

	for (size_t i = 0; i < alignmentsCount; i++)
	{
		size_t currentLength = heading.getColumnLength(i);
		if (currentLength > columnsLengths[i])
			columnsLengths[i] = currentLength;

		for (size_t j = 0; j < rowsCount; j++)
		{
			currentLength = rows[j].getColumnLength(i);
			if (currentLength > columnsLengths[i])
				columnsLengths[i] = currentLength;
		}
	}

	heading.print(alignments, columnsLengths);

	std::cout << "|";

	for (size_t i = 0; i < this->alignmentsCount; i++)
	{
		std::cout << " ";
		for (size_t j = 0; j < columnsLengths[i]; j++)
			std::cout << "-";
		std::cout << " |";
	}
	std::cout << std::endl;

	size_t columnIndex = heading.getColumnIndex(column);
	for (size_t i = 0; i < rowsCount; i++)
		if (rows[i].checkValue(columnIndex, value))
			rows[i].print(alignments, columnsLengths);
}

void Table::writeToFile(const char* fileName) const {
	std::ofstream file(fileName, std::ios::out);

	if (!file.is_open()) {
		std::cout << message::FILE_ERR << std::endl;
		return;
	}

	if (fileName == nullptr) {
		std::cout << message::VALIDATION_ERR << std::endl;
		return;
	}

	this->heading.writeToFile(file);
	writeAlignments(file);
	for (size_t i = 0; i < rowsCount; i++)
		this->rows[i].writeToFile(file);

	file.close();
}