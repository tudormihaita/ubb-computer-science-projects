#pragma once
#include "Tractor.h"
#include "Exceptions.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using std::vector;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::getline;
using std::to_string;
using std::find_if;
using std::distance;

class Repository {
private:
	vector<Tractor> tractors;
	string fileName;

	void loadFromFile();
	void writeToFile();

public:
	Repository(string file) : fileName{ file } {
		loadFromFile();
	}

	Repository(const Repository& other) = delete;

	~Repository() = default;

	int getSize();

	vector<Tractor>& getAllTractors();

	void addTractor(const Tractor& tractor);

	Tractor& findTractor(int id);

	void deleteTractor(const Tractor& tractor);

	void updateTractor(const Tractor& tractor);
};