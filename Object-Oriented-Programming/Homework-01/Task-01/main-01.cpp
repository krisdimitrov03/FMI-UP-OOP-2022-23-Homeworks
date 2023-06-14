#include <iostream>
#include "main-01.h"
#include "Table.h"

void runTableParser() {
	std::cout << "Enter file name(maximum of 100 symbols without spaces): ";
	char fileName[100];
	std::cin >> fileName;

	Table t;
	t.readFromFile(fileName);
	while (true)
	{
		std::cout << "Choose action:" << std::endl;
		std::cout << "1. print table" << std::endl;
		std::cout << "2. change column name" << std::endl;
		std::cout << "3. change value(1)" << std::endl;
		std::cout << "4. change value(2)" << std::endl;
		std::cout << "5. write table to file" << std::endl;

		int option;
		std::cin >> option;
		std::cin.ignore();
		switch (option) {
		case 1:
			t.print();
			break;
		case 2:
			std::cout << "Enter: <old-name> (enter) <new-name>:" << std::endl;
			char oldName[100];
			char newName[100];
			std::cin.getline(oldName, 100, '\n');
			std::cin.getline(newName, 100, '\n');
			t.changeColumnName(oldName, newName);
			break;
		case 3:
			std::cout << "Enter: <column-name> (enter) <value-to-change> (enter) <new-value>:" << std::endl;
			char columnName[100];
			char value[100];
			char newValue[100];
			std::cin.getline(columnName, 100, '\n');
			std::cin.getline(value, 100, '\n');
			std::cin.getline(newValue, 100, '\n');
			t.changeValue(columnName, value, newValue);
			break;
		case 4:
			std::cout << "Enter: <row-number> (enter) <column-name> (enter) <new-value>:" << std::endl;
			int rowNum;
			char valueToChange[100];
			char newValueToInsert[100];
			std::cin >> rowNum;
			std::cin.ignore();
			std::cin.getline(valueToChange, 100, '\n');
			std::cin.getline(newValueToInsert, 100, '\n');
			t.changeValue(rowNum, valueToChange, newValueToInsert);
			break;
		case 5:
			std::cout << "Enter file name: ";
			char writeFileName[100];
			std::cin >> writeFileName;
			t.writeToFile(writeFileName);
			break;
		default:
			std::cout << "Invalid option! Try again!" << std::endl;
			break;
		}
	}
}