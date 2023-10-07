#pragma once
#include <cassert>
#include "TicTacToe.h"
#include "Repository.h"
#include "Service.h"

class Tests {
private:
	void runDomainTests();
	void runRepoTests();
	void runServiceTests();
public:
	void runAllTests();
};