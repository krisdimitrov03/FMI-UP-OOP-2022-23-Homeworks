#include "TextFilesManager.h"
#include <cstring>

#pragma warning(disable : 4996)

TextFilesManager::TextFilesManager(size_t _maxCount) {
    files = new TextFile[maxCount];
    maxCount = _maxCount;
}

TextFilesManager::TextFilesManager(const TextFilesManager &other) {
    free();
    copyFrom(other);
}

TextFilesManager &TextFilesManager::operator=(const TextFilesManager &other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

TextFilesManager::~TextFilesManager() {
    free();
}

void TextFilesManager::free() {
    delete[] files;
    files = nullptr;
}

void TextFilesManager::copyFrom(const TextFilesManager &other) {
    free();
    files = new TextFile[other.count];
    for (size_t i = 0; i < other.count; i++)
        files[i] = other.files[i];
}

void TextFilesManager::addFile(
        const char *name,
        size_t hours,
        size_t mins,
        size_t seconds,
        unsigned day,
        unsigned month,
        unsigned year,
        const char *accessRights) {
    if (count == maxCount) //print message
        return;

    files[count].setName(name);
    files[count].setCreated(day, month, year, hours, mins, seconds);
    files[count].setAccessRights(accessRights);

    count++;
}

void TextFilesManager::editFile(
        const char *name,
        const char *content,
        size_t hours,
        size_t mins,
        size_t seconds,
        unsigned day,
        unsigned month,
        unsigned year,
        Role role) {
    size_t fileIndex = -1;
    for (size_t i = 0; i < count; i++) {
        if (!strcmp(files[i].getName(), name)) {
            fileIndex = i;
            break;
        }
    }

    if (fileIndex == -1) {
        //print message
        return;
    }

    const char *rights = files[fileIndex].getAccessRightsForRole(role);

    if (rights[1] == '-') {
        std::cout << messages::RIGHTS_ERR << std::endl;
        return;
    }

    delete[] rights;

    files[fileIndex].setLastModified(day, month, year, hours, mins, seconds);
    files[fileIndex].setContent(content);
    files[fileIndex].setSize(strlen(content));

}

void TextFilesManager::addInFile(
        const char *name,
        const char *content,
        size_t hours,
        size_t mins,
        size_t seconds,
        unsigned day,
        unsigned month,
        unsigned year,
        Role role) {
    size_t fileIndex = -1;
    for (size_t i = 0; i < count; i++) {
        if (!strcmp(files[i].getName(), name)) {
            fileIndex = i;
            break;
        }
    }

    if (fileIndex == -1) {
        //print message
        return;
    }

    const char *rights = files[fileIndex].getAccessRightsForRole(role);

    if (rights[1] == '-') {
        std::cout << messages::RIGHTS_ERR << std::endl;
        return;
    }

    delete[] rights;

    size_t contentLength = strlen(files[fileIndex].getContent());
    size_t argContentLength = strlen(content);

    char buffer[513];
    strcpy(buffer, files[fileIndex].getContent());

    strcat(buffer, content);

    files[fileIndex].setContent(buffer);
    files[fileIndex].setSize(strlen(buffer));

}

void TextFilesManager::deleteFile(const char *name) {
    size_t fileIndex = -1;
    for (size_t i = 0; i < count; i++) {
        if (!strcmp(files[i].getName(), name)) {
            fileIndex = i;
            break;
        }
    }

    if (fileIndex == -1) {
        // print message
        return;
    }

    for (size_t i = 1; i < count; i++)
        files[i - 1] = files[i];

    files[count - 1].empty();
    count--;
}

void TextFilesManager::printFile(const char *name, Role role) {
    size_t fileIndex = -1;
    for (size_t i = 0; i < count; i++) {
        if (!strcmp(files[i].getName(), name)) {
            fileIndex = i;
            break;
        }
    }

    if (fileIndex == -1) {
        //print message
        return;
    }

    const char *rights = files[fileIndex].getAccessRightsForRole(role);

    if (rights[0] == '-') {
        std::cout << messages::RIGHTS_ERR << std::endl;
        return;
    }

    delete[] rights;

    std::cout << files[fileIndex].getContent() << std::endl;
}

void TextFilesManager::printFileInfo(const char *name, Role role) {
    size_t fileIndex = -1;
    for (size_t i = 0; i < count; i++) {
        if (!strcmp(files[i].getName(), name)) {
            fileIndex = i;
            break;
        }
    }

    if (fileIndex == -1) {
        std::cout << messages::
        return;
    }

    const char *rights = files[fileIndex].getAccessRightsForRole(role);

    if (rights[0] == '-') {
        std::cout << messages::RIGHTS_ERR << std::endl;
        return;
    }

    delete[] rights;

    std::cout << "Name: " << files[fileIndex].getName() << std::endl;
    std::cout << "Size: " << (size_t) files[fileIndex].getSize() << std::endl; // sizeErr
    std::cout << "Created on: ";
    files[fileIndex].getCreated().print();
    std::cout << "Last modified on: ";
    files[fileIndex].getCreated().print();
    std::cout << "Rights: " << files[fileIndex].getAccessRights() << std::endl;
}

void TextFilesManager::printAllFiles() {
    for (size_t i = 0; i < count; i++)
        std::cout << files[i].getName() << std::endl;
}

void TextFilesManager::changeRights(const char *fileName, Role role, Operation operation) {
    size_t fileIndex = -1;
    for (size_t i = 0; i < count; i++) {
        if (!strcmp(files[i].getName(), fileName)) {
            fileIndex = i;
            break;
        }
    }

    const char* rights = files[fileIndex].getAccessRights();
    char newRights[sizes::ACCESS_RIGHTS_SIZE + 1];
    strcpy(newRights, rights);
//    delete[] rights;

    size_t indexToChange = 0;
    char operationChar = '\0';
    switch(role) {
        case Role::user:
            switch(operation) {
                case Operation::read:
                    indexToChange = 0;
                    operationChar = 'r';
                    break;
                case Operation::write:
                    indexToChange = 1;
                    operationChar = 'w';
                    break;
                case Operation::execute:
                    indexToChange = 2;
                    operationChar = 'x';
                    break;
            }
            break;
        case Role::group:
            switch(operation) {
                case Operation::read:
                    indexToChange = 3;
                    operationChar = 'r';
                    break;
                case Operation::write:
                    indexToChange = 4;
                    operationChar = 'w';
                    break;
                case Operation::execute:
                    indexToChange = 5;
                    operationChar = 'x';
                    break;
            }
            break;
        case Role::other:
            switch(operation) {
                case Operation::read:
                    indexToChange = 6;
                    operationChar = 'r';
                    break;
                case Operation::write:
                    indexToChange = 7;
                    operationChar = 'w';
                    break;
                case Operation::execute:
                    indexToChange = 8;
                    operationChar = 'x';
                    break;
            }
            break;
    }

    if(newRights[indexToChange] == '-') {
        newRights[indexToChange] = operationChar;
    } else {
        newRights[indexToChange] = '-';
    }

    files[fileIndex].setAccessRights(newRights);
}
