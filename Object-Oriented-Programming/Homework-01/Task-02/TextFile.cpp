#include "TextFile.h"
#include <cstring>
#pragma warning(disable : 4996)

TextFile::TextFile() :
	name(),
	content(),
	size(),
	created(0, 0, 0, 0, 0, 0),
	lastModified(0, 0, 0, 0, 0, 0),
	accessRights() {}

const char* TextFile::getName() {
	return name;
}

const char* TextFile::getContent() {
	return content;
}

unsigned TextFile::getSize() {
	return size;
}

const DateTime& TextFile::getCreated() {
	return created;
}

const DateTime& TextFile::getLastModified() {
	return lastModified;
}

const char* TextFile::getAccessRights() {
	return accessRights;
}

void TextFile::setName(const char* _name) {
	if (_name == nullptr) // print message
		return;

	strcpy_s(name, _name);
}

void TextFile::setContent(const char* _content) {
	if (_content == nullptr) // print message
		return;

	strcpy(content, _content);
}

void TextFile::setSize(unsigned _size) {
	size = _size;
}

void TextFile::setCreated(unsigned day, unsigned month, unsigned year, size_t hours, size_t mins, size_t seconds) {
	created.setDate(day, month, year);
	created.setTime(hours, mins, seconds);
}

void TextFile::setLastModified(unsigned day, unsigned month, unsigned year, size_t hours, size_t mins, size_t seconds) {
	lastModified.setDate(day, month, year);
	lastModified.setTime(hours, mins, seconds);
}

void TextFile::setAccessRights(const char* _accessRights) {
	if (_accessRights == nullptr) // print message
		return;

	strcpy(accessRights, _accessRights);
}

void TextFile::empty() {
	setName("");
	setContent("");
	setSize(0);
	setCreated(0, 0, 0, 0, 0, 0);
	setLastModified(0, 0, 0, 0, 0, 0);
	setAccessRights("");
}

const char* TextFile::getAccessRightsForRole(Role role) {
	char* result = new char[4]{ '\0' };

	switch (role)
	{
	case Role::user:
		result[0] = accessRights[0];
		result[1] = accessRights[1];
		result[2] = accessRights[2];
		break;
	case Role::group:
		result[0] = accessRights[3];
		result[1] = accessRights[4];
		result[2] = accessRights[5];
		break;
	case Role::other:
		result[0] = accessRights[6];
		result[1] = accessRights[7];
		result[2] = accessRights[8];
		break;
	}

	return result;
}

TextFile::~TextFile() {
    setName("");
    setContent("");
    setCreated(0,0,0,0,0,0);
    setLastModified(0,0,0,0,0,0);
    setAccessRights("");
}
