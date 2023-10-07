#pragma once
#include "Repository.h"
#include "Validator.h"
#include <map>

using std::map;
using std::sort;
using std::copy_if;
using std::back_inserter;

class Service {
private:
	Repository& tractorRepo;
	Validator& tractorValidator;
public:
	Service(Repository& repo, Validator& validator) : tractorRepo{ repo }, tractorValidator{ validator } {};

	Service(const Service& other) = delete;

	~Service() = default;

	int getSize();

	vector<Tractor>& getAllTractors();

	Tractor& findTractor(int id);

	void addTractor(int id, string model, string type, int nrWheels);

	void updateTractor(int id, int newNrWheels);

	void deleteTractor(int id);

	vector<Tractor> sortTractors();

	vector<Tractor> filterByType(string type);

	map<string, int> groupByType();
};