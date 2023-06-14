#include "main-02.h"
#include "TextFilesManager.h"

void runTextFileManager() {
	TextFilesManager fs(5);
	fs.addFile("test.txt", 14, 0, 0, 20, 3, 2023, "rwxr--r--");
	fs.editFile("test.txt", "Hello, world!", 14, 10, 0, 20, 3, 2023, Role::user);
	fs.editFile("test.txt", "Hello, world!", 14, 15, 0, 20, 3, 2023, Role::group);
	fs.addInFile("test.txt", "Hello, my friend!", 14, 13, 0, 20, 3, 2023, Role::user);
	fs.addFile("attest.txt", 14, 0, 0, 20, 3, 2023, "rwxr--r--");
	fs.printFile("test.txt", Role::user);
    fs.changeRights("test.txt", Role::user, Operation::write);
	fs.printFileInfo("test.txt", Role::user);
	fs.printAllFiles();
}