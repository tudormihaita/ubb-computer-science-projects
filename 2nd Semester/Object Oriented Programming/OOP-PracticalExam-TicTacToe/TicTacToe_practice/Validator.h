#pragma once
#include "Exceptions.h"
#include <string>

class Validator {
public:
	Validator() = default;

	void validateGame(const TicTacToe& game) {
		string errors = "";
		if (game.getDim() != 3 && game.getDim() != 4 && game.getDim() != 5) {
			errors += "Dimensiunea poate fi 3,4,5!\n";
		}

		if (game.getTable().size() != game.getDim() * game.getDim()) {
			errors += "Tabla trebuie sa fie un string de dim x dim caractere!\n";
		}

		auto table = game.getTable();
		bool valid = true;
		for (int i = 0; i < table.size() && valid; i++) {
			if (table[i] != 'X' && table[i] != 'O' && table[i] != '-')
				valid = false;
		}

		if (valid == false) {
			errors += "Tabla trebuie sa contine doar caractere X,O,- !\n";
		}

		auto next = game.getNextPlayer();
		if (next != "X" && next != "O") {
			errors += "Urmatorul jucator poate fi X sau O!\n";
		}

		auto state = game.getState();
		if (state != "Neinceput" && state != "Terminat" && state != "In derulare") {
			errors += "Stare invalida!\n";
		}

		if (errors.size() > 0) {
			throw ValidationException(errors);
		}
	}

	~Validator() = default;
};