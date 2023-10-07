#pragma once
#include <cassert>
#include "CPU.h"
#include "MOBO.h"
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