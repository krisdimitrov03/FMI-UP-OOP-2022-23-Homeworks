#pragma once

#include "TextFile.h"
#include "Operations.h"

class TextFilesManager
{
	TextFile* files = nullptr;
	size_t count = 0;
	size_t maxCount = 0;
public:
	TextFilesManager(size_t _maxCount);
	TextFilesManager(const TextFilesManager& other);
	TextFilesManager& operator=(const TextFilesManager& other);
	~TextFilesManager();

	void addFile(
		const char* name, 
		size_t hours, 
		size_t mins, 
		size_t seconds, 
		unsigned day, 
		unsigned month, 
		unsigned year, 
		const char* accessRights
	);

	void editFile(
		const char* name,
		const char* content,
		size_t hours,
		size_t mins,
		size_t seconds,
		unsigned day,
		unsigned month,
		unsigned year,
		Role role);

	void addInFile(
		const char* name,
		const char* content,
		size_t hours,
		size_t mins,
		size_t seconds,
		unsigned day,
		unsigned month,
		unsigned year,
		Role role);

	void deleteFile(const char* name);
	void printFile(const char* name, Role role);
	void printFileInfo(const char* name, Role role);
	void printAllFiles();
    void changeRights(const char* fileName, Role role, Operation operation);
private:
	void free();
	void copyFrom(const TextFilesManager& other);
};