#pragma once
#include <string>

using std::string;

class RepoException {
private:
	string errorMsg;
public:
	RepoException(const string& error) : errorMsg{ error } {};
	
	string getErrorMsg() {
		return this->errorMsg;
	}
};


