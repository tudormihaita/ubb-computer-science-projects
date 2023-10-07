#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>  
#include <crtdbg.h>
#include "tests.h"
#include "user_interface.h"

int main() {
	run_all_tests();
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}