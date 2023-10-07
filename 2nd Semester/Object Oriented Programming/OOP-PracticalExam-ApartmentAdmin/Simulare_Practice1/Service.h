#pragma once
#include "Repository.h"
#include <algorithm>

using std::copy_if;
using std::back_inserter;

class Service {
private:
	Repository& apartmentRepository;

public:
	Service() = default;

	Service(Repository& repo) noexcept : apartmentRepository{ repo } {};

	Service(const Service& other) = delete;

	~Service() = default;

	void addApartment(const int& id, const string& street, const int& surface, const double& price);

	void removeApartment(const int& id);

	const vector<Apartment> getAllApartments() const;

	int getSize() const noexcept;

	vector<Apartment> filterBySurface(const int& minSurface, const int& maxSurface) noexcept;

	vector<Apartment> filterByPrice(const double& minPrice, const double& maxPrice) noexcept;
};