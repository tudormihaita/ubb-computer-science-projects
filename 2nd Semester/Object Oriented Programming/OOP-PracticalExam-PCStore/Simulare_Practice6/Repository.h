#pragma once
#include "CPU.h"
#include "MOBO.h"
#include "Exceptions.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::vector;
using std::ifstream;
using std::ofstream;
using std::find_if;
using std::stringstream;

class Repository {
private:
	vector<CPU> processors;
	vector<MOBO> motherboards;

	string fileCPU;
	string fileMOBO;

	void loadFromFile();

public:
	Repository() = default;

	Repository(string cpu, string mobo) : fileCPU{ cpu }, fileMOBO{ mobo } {
		loadFromFile();
	}

	Repository(const Repository&) = delete;

	~Repository() = default;

	vector<CPU>& getAllCPUs();

	vector<MOBO>& getAllMOBOs();

	int getCPUSize();

	int getMOBOSize();

	void addMOBO(const MOBO& mobo);

	const CPU& findCPU(int id);
	
	const MOBO& findMOBO(int id);
};