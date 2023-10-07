#pragma once
#include "TicTacToe.h"

int TicTacToe::getId() const noexcept {
	return this->id;
}

int TicTacToe::getDim() const noexcept {
	return this->dim;

}

string TicTacToe::getTable() const {
	return this->table;

}

string TicTacToe::getNextPlayer() const {
	return this->nextPlayer;
}

string TicTacToe::getState() const {
	return this->state;
}