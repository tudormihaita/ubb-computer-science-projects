#pragma once
#include "Tractor.h"
#include "Repository.h"
#include "Service.h"
#include "Validator.h"
#include "Exceptions.h"
#include <cassert>

class Tests {
private:
	void runDomainTests();
	void runRepoTests();
	void runServiceTests();
public:
	void runAllTests();
};