#pragma once
#include <iostream>
#include <string>
#include <fstream>

using std::string;

class Apartment {
private:
	int id;

	string street;

	int surface;

	double price;

public:
	Apartment() = default;

	Apartment(int id, string street, int surface, double price) : id{ id }, street { street }, surface{ surface }, price{ price } {};

	Apartment(const Apartment& ap) :
		id{ ap.id },
		street{ ap.street },
		surface{ ap.surface },
		price{ ap.price }{};

	Apartment(Apartment&& other) = default;

	Apartment& operator=(const Apartment&) = default;

	Apartment& operator=(Apartment&& other) = default;

	~Apartment() = default;

	bool operator==(const Apartment& other) const noexcept {
		return this->id == other.id && this->street == other.street && this->surface == other.surface && abs(this->price - other.price) < 0.0001;
	}

	bool operator!=(const Apartment& other) const noexcept {
		return this->id != other.id || this->street != other.street || this->surface != other.surface || abs(this->price - other.price) > 0.0001;
	}

	int getId() const noexcept;

	string getStreet() const;

	int getSurface() const noexcept;

	double getPrice() const noexcept;

};
