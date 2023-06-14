#pragma once

namespace sizes {
	const int MAX_NAME_SIZE = 64;
	const int MAX_CONTENT_SIZE = 512;
	const int ACCESS_RIGHTS_SIZE = 9;
}

namespace messages {
	const char RIGHTS_ERR[] = "::ERROR:: You do not have the rights to edit!";
	const char VALIDATION_ERR[] = "::ERROR:: Validation error occurred!";
}