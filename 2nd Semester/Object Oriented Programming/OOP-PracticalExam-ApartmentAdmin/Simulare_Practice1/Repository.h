#pragma once
#include "Apartment.h"
#include "Exceptions.h"
#include <vector>
#include <sstream>

using std::vector;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::find_if;
using std::to_string;
using std::distance;

class Repository {
private:
	vector<Apartment> apartmentList;
	string fileName;

	void loadFromFile();
	void writeToFile();
public:
	Repository() = default;

	Repository(string filename) : fileName{ filename } {
		loadFromFile();
	}

	Repository(const Repository& other) = delete;

	const Apartment& findApartment(const int& id);

	void addApartment(const Apartment& apartment);

	void deleteApartment(const Apartment& apartment);

	vector<Apartment> getAllApartments();

	int getSize() const noexcept;

	void clearFile();

	~Repository() = default;
};
