#pragma once
#include <string>

using std::string;

class CPU {
private:
	int id;

	string name;

	int threads;

	string socket;

	double price;

public:
	CPU() = default;

	CPU(int id, string name, int threads, string socket, double price) : id{ id }, name{ name }, threads{ threads }, socket{ socket }, price{ price } {};

	CPU(const CPU&) = default;
	CPU(CPU&&) = default;

	CPU& operator=(const CPU&) = default;
	CPU& operator=(CPU&&) = default;

	~CPU() = default;

	int getID() const noexcept {
		return this->id;
	}

	string getName() const {
		return this->name;
	}

	int getThreads() const noexcept {
		return this->threads;
	}

	string getSocket() const {
		return this->socket;
	}

	double getPrice() const noexcept {
		return this->price;
	}

};