#pragma once
#include "Repository.h"

void Repository::loadFromFile() {
	ifstream fin(this->fileName);

	if (!fin.is_open()) {
		throw RepoException("Nu s-a putut deschide fisierul!\n");
	}
	
	string line;
	int generatedId = 0;

	if (fin.peek() == EOF) {
		return;
	}

	while (!fin.eof()) {
		string atribute;
		vector<string> atr;

		getline(fin, line);
		if (!line.empty()) {
			stringstream ss(line);

			while (getline(ss, atribute, ',')) {
				atr.push_back(atribute);
			}

			generatedId++;
			const int id = generatedId;
			const string street = atr[0];
			const int surface = stoi(atr[1]);
			const double price = stod(atr[2]);

			const Apartment ap{ id, street, surface, price };
			this->apartmentList.push_back(ap);

		}
	}

	fin.close();
}

void Repository::writeToFile() {
	ofstream fout(this->fileName);

	if (!fout.is_open()) {
		throw RepoException("Nu s-a putut deschide fisierul!\n");
	}

	for (const Apartment& ap : getAllApartments()) {
		fout << ap.getStreet() << "," << ap.getSurface() << "," << ap.getPrice() << "\n";
	}

	fout.close();
}

void Repository::clearFile() {
	ofstream fout;

	fout.open(this->fileName, ofstream::out | ofstream::trunc);

	if (!fout.is_open()) {
		throw RepoException("Nu s-a putut deschide fisierul!\n");
	}

	fout.close();
}

const Apartment& Repository::findApartment(const int& id) {
	auto it = find_if(apartmentList.begin(), apartmentList.end(), [=](const Apartment& ap) {
		return ap.getId() == id;
	});

	if (it == apartmentList.end()) {
		throw RepoException("Apartamentul cu id-ul " + to_string(id) + " nu exista in lista!\n");
	}

	return(*it);
}

void Repository::addApartment(const Apartment& apartment) {
	auto it = find_if(apartmentList.begin(), apartmentList.end(), [=](const Apartment& ap) {
		return ap.getId() == apartment.getId();
	});

	if (it != apartmentList.end()) {
		throw RepoException("Apartamentul exista deja in lista!\n");
	}

	apartmentList.push_back(apartment);
	writeToFile();
}


void Repository::deleteApartment(const Apartment& apartment) {
	auto it = find_if(apartmentList.begin(), apartmentList.end(), [=](const Apartment& ap) {
		return ap.getId() == apartment.getId(); 
	});

	if (it == apartmentList.end()) {
		throw RepoException("Apartamentul cu id-ul " + to_string(apartment.getId()) + " nu exista in lista!\n");
	}

	const int pos = static_cast<int>(distance(apartmentList.begin(), it));
	apartmentList.erase(apartmentList.begin() + pos);
	writeToFile();
}

vector<Apartment> Repository::getAllApartments() {
	return this->apartmentList;
}

int Repository::getSize() const noexcept{
	return static_cast<int>(this->apartmentList.size());
}