#pragma once
#include <string>

using std::string;

class MOBO {
private:
	int id;

	string name;

	string socket;

	double price;
public:
	MOBO() = default;

	MOBO(int id, string name, string socket, double price) : id{ id }, name{ name }, socket{ socket }, price{ price } {};

	MOBO(const MOBO&) = default;
	MOBO(MOBO&&) = default;

	MOBO& operator=(const MOBO&) = default;
	MOBO& operator=(MOBO&&) = default;

	~MOBO() = default;

	int getId() const noexcept {
		return this->id;
	}

	string getName() const {
		return this->name;
	}

	string getSocket() const {
		return this->socket;
	}

	double getPrice() const noexcept {
		return this->price;
	}
};