#pragma once
#include <string>

using std::string;

class RepoException {
private:
	string errorMsg;
public:
	RepoException(string error) : errorMsg{ error } {};

	string getErrorMsg() {
		return this->errorMsg;
	}

	~RepoException() = default;
};

class ValidationException {
private:
	string errorMsg;
public:
	ValidationException(string error) : errorMsg{ error } {};

	string getErrorMsg() {
		return this->errorMsg;
	}

	~ValidationException() = default;
};