#pragma once
#include "Repository.h"

void Repository::loadFromFile() {
	ifstream fin(fileName);

	if (!fin.is_open()) {
		throw RepoException("Nu s-a putut deschide fisierul!\n");
	}

	if (fin.peek() == EOF) {
		return;
	}

	string line;
	while (!fin.eof()) {
		string atribute;
		vector<string> atr;

		getline(fin, line);
		if (!line.empty()) {
			stringstream ss(line);

			while (getline(ss, atribute, ',')) {
				atr.push_back(atribute);
			}

			int id = stoi(atr[0]);
			string model = atr[1];
			string type = atr[2];
			int nrWheels = stoi(atr[3]);

			Tractor tractor{ id,model,type,nrWheels };
			tractors.push_back(tractor);

			atr.clear();
		}
	}

	fin.close();
}

void Repository::writeToFile() {
	ofstream fout(fileName);

	if (!fout.is_open()) {
		throw RepoException("Nu s-a putut deschide fisierul!\n");
	}

	for (auto& tractor : tractors) {
		fout << tractor.getId() << "," << tractor.getModel() << "," << tractor.getType() << "," << tractor.getNrWheels() << "\n";
	}

	fout.close();
}

int Repository::getSize() {
	return static_cast<int>(tractors.size());
}

vector<Tractor>& Repository::getAllTractors() {
	return tractors;
}

Tractor& Repository::findTractor(int id) {
	auto it = find_if(tractors.begin(), tractors.end(), [&](const Tractor& t) {
		return t.getId() == id;
		});

	if (it == tractors.end()) {
		throw RepoException("Nu exista tractorul dat!\n");
	}

	return *it;
}

void Repository::deleteTractor(const Tractor& tractor) {
	auto it = find_if(tractors.begin(), tractors.end(), [&](const Tractor& t) {
		return t.getId() == tractor.getId();
	});

	if (it == tractors.end()) {
		throw RepoException("Nu exista tractorul dat!\n");
	}

	const int pos = static_cast<int>(distance(tractors.begin(), it));
	tractors.erase(tractors.begin() + pos);
	writeToFile();

}

void Repository::addTractor(const Tractor& tractor) {
	auto it = find_if(tractors.begin(), tractors.end(), [&](const Tractor& t) {
		return t.getId() == tractor.getId();
		});

	if (it != tractors.end()) {
		throw RepoException("Tractorul dat exista deja!\n");
	}

	tractors.push_back(tractor);
	writeToFile();
}

void Repository::updateTractor(const Tractor& tractor) {
	auto it = find_if(tractors.begin(), tractors.end(), [&](const Tractor& t) {
		return t.getId() == tractor.getId();
		});

	if (it == tractors.end()) {
		throw RepoException("Tractorul dat nu exista!\n");
	}

	const int pos = static_cast<int>(distance(tractors.begin(), it));

	tractors.at(pos) = tractor;
	writeToFile();
}