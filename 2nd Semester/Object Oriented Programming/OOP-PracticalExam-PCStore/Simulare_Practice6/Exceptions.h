#pragma once
#include <string>

using std::string;

class RepoException {
private:
	string errorMsg;
public:
	RepoException(string error) : errorMsg{ error } {};

	~RepoException() = default;

	string getErrorMsg() {
		return this->errorMsg;
	}
};