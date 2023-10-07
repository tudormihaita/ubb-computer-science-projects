#pragma once
#include "Service.h"

void Service::addApartment(const int& id, const string& street, const int& surface, const double& price) {
	Apartment ap{ id, street, surface, price };
	this->apartmentRepository.addApartment(ap);
}


void Service::removeApartment(const int& id) {
	auto apartmentToRemove = this->apartmentRepository.findApartment(id);

	this->apartmentRepository.deleteApartment(apartmentToRemove);
}

const vector<Apartment> Service::getAllApartments() const{
	return this->apartmentRepository.getAllApartments();
}

int Service::getSize() const noexcept{
	return this->apartmentRepository.getSize();
}

vector<Apartment> Service::filterBySurface(const int& minSurface, const int& maxSurface) noexcept {
	const vector<Apartment>& allApartments = apartmentRepository.getAllApartments();
	vector<Apartment> filteredApartments;
	copy_if(allApartments.begin(), allApartments.end(), back_inserter(filteredApartments), [&](const Apartment& ap) {
		return ap.getSurface() >= minSurface && ap.getSurface() <= maxSurface;
	});

	return filteredApartments;
}

vector<Apartment> Service::filterByPrice(const double& minPrice, const double& maxPrice) noexcept {
	const vector<Apartment>& allApartments = apartmentRepository.getAllApartments();
	vector<Apartment> filteredApartments;
	copy_if(allApartments.begin(), allApartments.end(), back_inserter(filteredApartments), [&](const Apartment& ap) {
		return ap.getPrice() >= minPrice && ap.getPrice() <= maxPrice;
	});

	return filteredApartments;
}