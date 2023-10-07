#pragma once
#include "Tractor.h"
#include "Exceptions.h"

class Validator {
public:
	Validator() = default;

	void validateTractor(const Tractor& tractor) {
		string error = "";
		if (tractor.getModel().length() == 0)
			error += "Denumire nu poate fi vid!\n";
		if (tractor.getType().length() == 0)
			error += "Tip nu poate fi vid!\n";
		if (tractor.getNrWheels() % 2 != 0 || tractor.getNrWheels() < 2 || tractor.getNrWheels() > 16)
			error += "Numar roti trebuie sa fie par si intre 2 si 16!\n";

		if (error.length() > 0)
			throw ValidationException(error);
	}

	~Validator() = default;
};