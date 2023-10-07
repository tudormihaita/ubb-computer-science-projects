#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <signal.h>
#include <iostream>
#include "Tests.h"
#include "UI.h"

using std::cout;


void run() {
	Tests tests;
	tests.runAllTests();

	//MemoryBookRepository bookRepository;
	//LabRepository bookRepository{ 0.5 }
	FileBookRepository bookRepository("books.txt");
	Validator bookValidator;
	Library bookLibrary{ bookRepository, bookValidator };
	ConsoleUI ui{ bookLibrary };


	ui.run();
}


int main() {
	run();

	_CrtDumpMemoryLeaks();
	return 0;
}