#pragma once
#include "Tractor.h"

int Tractor::getId() const noexcept {
	return this->id;
}

string Tractor::getModel() const {
	return this->model;
}

string Tractor::getType() const {
	return this->type;
}

int Tractor::getNrWheels() const noexcept {
	return this->nrWheels;
}