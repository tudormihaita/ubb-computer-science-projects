#pragma once
#include "Service.h"

int Service::getSize() {
	return tractorRepo.getSize();
}

vector<Tractor>& Service::getAllTractors() {
	return tractorRepo.getAllTractors();
}

Tractor& Service::findTractor(int id) {
	return tractorRepo.findTractor(id);
}

void Service::addTractor(int id, string model, string type, int nrWheels) {
	Tractor tractor{ id,model,type,nrWheels };

	tractorValidator.validateTractor(tractor);
	tractorRepo.addTractor(tractor);
}

void Service::deleteTractor(int id) {
	auto foundTractor = tractorRepo.findTractor(id);

	tractorRepo.deleteTractor(foundTractor);
}

void Service::updateTractor(int id, int newNrWheels) {
	auto foundTractor = tractorRepo.findTractor(id);

	Tractor newTractor{ foundTractor.getId(), foundTractor.getModel(), foundTractor.getType(), newNrWheels };
	tractorValidator.validateTractor(newTractor);

	tractorRepo.updateTractor(newTractor);
}

vector<Tractor> Service::sortTractors() {
	vector<Tractor> sortedTractors{ tractorRepo.getAllTractors() };

	sort(sortedTractors.begin(), sortedTractors.end(), [&](const Tractor& t1, const Tractor& t2) {
		return t1.getModel() < t2.getModel();
		});

	return sortedTractors;
}

vector<Tractor> Service::filterByType(string type) {
	vector<Tractor> allTractors{ tractorRepo.getAllTractors() };
	vector<Tractor> filteredTractors;

	copy_if(allTractors.begin(), allTractors.end(), back_inserter(filteredTractors), [&](const Tractor& t) {
		return t.getType() == type;
		});

	return filteredTractors;
}

map<string, int> Service::groupByType() {
	vector<Tractor> tractors = tractorRepo.getAllTractors();
	map<string, int> types;
	for (auto& tractor : tractors) {
		types[tractor.getType()]++;
	}

	return types;
}