#pragma once

#include "constants.h"
#include "DateTime.h"
#include "Role.h"

class TextFile {
	char name[sizes::MAX_NAME_SIZE + 1];
	char content[sizes::MAX_CONTENT_SIZE + 1];
	unsigned size;
	DateTime created;
	DateTime lastModified;
	char accessRights[sizes::ACCESS_RIGHTS_SIZE + 1];
public:
	TextFile();
    ~TextFile();

	const char* getName();
	const char* getContent();
	unsigned getSize();
	const DateTime& getCreated();
	const DateTime& getLastModified();
	const char* getAccessRights();

	void setName(const char* _name);
	void setContent(const char* _content);
	void setSize(unsigned _size);
	void setCreated(unsigned day, unsigned month, unsigned year, size_t hours, size_t mins, size_t seconds);
	void setLastModified(unsigned day, unsigned month, unsigned year, size_t hours, size_t mins, size_t seconds);
	void setAccessRights(const char* _accessRights);

	const char* getAccessRightsForRole(Role role);
	void empty();
};