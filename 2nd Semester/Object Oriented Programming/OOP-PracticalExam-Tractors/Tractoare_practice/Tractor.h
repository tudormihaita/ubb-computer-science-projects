#pragma once
#include <string>

using std::string;

class Tractor {
private:
	int id;
	string model;
	string type;
	int nrWheels;

public:
	Tractor() = default;

	Tractor(int id, string model, string type, int nr) : id{ id }, model{ model }, type{ type }, nrWheels{ nr } {};

	Tractor(const Tractor& other) = default;
	Tractor(Tractor&& other) = default;

	~Tractor() = default;

	Tractor& operator=(const Tractor& other) = default;
	Tractor& operator=(Tractor&& other) = default;

	bool operator==(const Tractor& other) const noexcept {
		return this->id == other.id;
	}

	bool operator!=(const Tractor& other) const noexcept {
		return this->id != other.id;
	}

	int getId() const noexcept;

	string getModel() const;

	string getType() const;

	int getNrWheels() const noexcept;

};