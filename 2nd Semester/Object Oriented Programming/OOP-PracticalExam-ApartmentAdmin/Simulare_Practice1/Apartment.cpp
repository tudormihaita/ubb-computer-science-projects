#pragma once
#include "Apartment.h"

int Apartment::getId() const noexcept {
	return this->id;
}

string Apartment::getStreet() const{
	return this->street;
}

int Apartment::getSurface() const noexcept {
	return this->surface;
}

double Apartment::getPrice() const noexcept {
	return this->price;
}