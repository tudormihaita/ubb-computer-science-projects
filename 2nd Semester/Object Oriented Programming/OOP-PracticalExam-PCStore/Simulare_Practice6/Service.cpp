#include "Service.h"

vector<CPU>& Service::getAllCPUs() {
	return repoPC.getAllCPUs();
}

vector<MOBO>& Service::getAllMOBOs() {
	return repoPC.getAllMOBOs();
}

int Service::getCPUSize() {
	return repoPC.getCPUSize();
}

int Service::getMOBOSize() {
	return repoPC.getMOBOSize();
}

void Service::addMOBO(string name, string socket, double price) {
	int id = repoPC.getMOBOSize() + 1;
	MOBO mobo{ id, name, socket, price };

	repoPC.addMOBO(mobo);
}

vector<MOBO> Service::filterBySocket(string socket) {
	vector<MOBO> filteredMOBOs;

	vector<MOBO> allMOBOs = repoPC.getAllMOBOs();

	copy_if(allMOBOs.begin(), allMOBOs.end(), back_inserter(filteredMOBOs), [&](const MOBO& mobo) {
		return mobo.getSocket() == socket;
	});

	return filteredMOBOs;
}

const CPU& Service::findCPU(int id) {
	return repoPC.findCPU(id);
}

const MOBO& Service::findMOBO(int id) {
	return repoPC.findMOBO(id);
}