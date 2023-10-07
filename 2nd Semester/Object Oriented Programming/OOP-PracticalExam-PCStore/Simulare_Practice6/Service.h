#pragma once
#include "Repository.h"

using std::copy_if;
using std::back_inserter;

class Service {
private:
	Repository& repoPC;
public:
	Service() = default;

	Service(Repository& repo) : repoPC{ repo } {};

	Service(const Service& srv) = delete;

	~Service() = default;

	vector<CPU>& getAllCPUs();

	vector<MOBO>& getAllMOBOs();

	int getCPUSize();

	int getMOBOSize();

	void addMOBO(string name, string socket, double price);

	vector<MOBO> filterBySocket(string socket);

	const CPU& findCPU(int id);

	const MOBO& findMOBO(int id);

};