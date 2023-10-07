#include <iostream>

#include "TestExtins.h"
#include "TestScurt.h"
#include "IteratorColectie.h"
#include "Colectie.h"

using namespace std;


int main() {
	testAllExtins();
	testAll();
	testUniq();

	/*
	Colectie col;
	IteratorColectie iterator = col.iterator();
	//col.adauga(0);
	try {
		iterator.urmator();
	}
	catch (out_of_range& e) {
		cerr << e.what();
	}
	*/
}
