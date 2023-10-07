#include "Repository.h"

void Repository::loadFromFile() {
	ifstream fin(fileCPU);

	if (!fin.is_open())
		throw RepoException("Nu s-a putut deschide fisierul!\n");

	if (fin.peek() == EOF)
		return;

	int generatedId = 0;
	string line;
	while (!fin.eof()) {
		getline(fin, line);

		string atribute;
		vector<string> atr;
		if (!line.empty()) {
			stringstream ss(line);

			while (getline(ss, atribute, ','))
				atr.push_back(atribute);

			generatedId++;
			int id = generatedId;
			string name = atr[0];
			int threads = stoi(atr[1]);
			string socket = atr[2];
			double price = stod(atr[3]);

			CPU cpu{ id, name, threads, socket, price };
			processors.push_back(cpu);
		}
	}

	fin.close();

	//ifstream fin(fileMOBO);
	fin.open(fileMOBO);

	if (!fin.is_open())
		throw RepoException("Nu s-a putut deschide fisierul!\n");

	if (fin.peek() == EOF)
		return;

	generatedId = 0;
	while (!fin.eof()) {
		getline(fin, line);

		string atribute;
		vector<string> atr;
		if (!line.empty()) {
			stringstream ss(line);

			while (getline(ss, atribute, ','))
				atr.push_back(atribute);

			generatedId++;
			int id = generatedId;
			string name = atr[0];
			string socket = atr[1];
			double price = stod(atr[2]);

			MOBO  mobo{ id, name, socket, price };
			motherboards.push_back(mobo);
		}
	}

	fin.close();
}

vector<CPU>& Repository::getAllCPUs() {
	return this->processors;
}

vector<MOBO>& Repository::getAllMOBOs() {
	return this->motherboards;
}

int Repository::getCPUSize() {
	return static_cast<int>(processors.size());
}

int Repository::getMOBOSize() {
	return static_cast<int>(motherboards.size());
}

void Repository::addMOBO(const MOBO& mobo) {
	auto it = find_if(motherboards.begin(), motherboards.end(), [&](const MOBO& m) {
		return m.getId() == mobo.getId();
	});

	if (it != motherboards.end()) {
		throw RepoException("Placa de baza deja exista in lista!\n");
	}

	motherboards.push_back(mobo);
}

const CPU& Repository::findCPU(int id) {
	auto it = find_if(processors.begin(), processors.end(), [&](const CPU& c) {
		return c.getID() == id;
	});

	if (it == processors.end()) {
		throw RepoException("Nu exista procesorul cu id-ul dat!\n");
	}

	return (*it);
}


const MOBO& Repository::findMOBO(int id){
	auto it = find_if(motherboards.begin(), motherboards.end(), [&](const MOBO& m) {
		return m.getId() == id;
		});

	if (it == motherboards.end()) {
		throw RepoException("Nu exita placa de baza cu id-ul dat!\n");
	}

	return (*it);
}