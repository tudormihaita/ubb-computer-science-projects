#pragma once
#include "Service.h"

int Service::getSize() {
	return gameRepo.getSize();
}

vector<TicTacToe> Service::getAllGames() {
	auto games{ gameRepo.getAllGames() };

	sort(games.begin(), games.end(), [&](const TicTacToe& g1, const TicTacToe g2) {
		return g1.getState() < g2.getState();
	});

	return games;
}

TicTacToe& Service::findGame(int id) {
	return gameRepo.findGame(id);
}

void Service::addGame(int id, int dim, string table, string next, string state) {
	TicTacToe game{ id, dim, table, next, state };
	gameValidator.validateGame(game);

	gameRepo.addGame(game);
}

void Service::updateGame(int id, int dim, string table, string next, string state) {
	auto foundGame = gameRepo.findGame(id);

	TicTacToe newGame{ foundGame.getId(), dim, table, next, state };
	gameValidator.validateGame(newGame);

	gameRepo.updateGame(newGame);
}


void Service::deleteGame(int id) {
	auto foundGame = gameRepo.findGame(id);

	gameRepo.deleteGame(foundGame);
}

bool Service::checkGameState(int dim, string table, char currentPlayer) {
	auto currentTable = table;
	char** currentGame = new char* [dim];
	for (int i = 0; i < dim; i++)
		currentGame[i] = new char[dim];

	int i = 0, j = 0;
	int r = 0, c = 0;
	for (i = 0; i < currentTable.size(); i++) {
		currentGame[r][c] = currentTable.at(i);

		if ((c + 1) % dim == 0) {
			c = 0;
			r++;
		}
		else
			c++;
	}

	bool finished = false;
	bool diagonal = true;
	for (i = 0; i < dim && diagonal==true; i++) {
		if (currentGame[i][i] != currentPlayer) {
			diagonal = false;
		}
	}
	if (diagonal == true)
		finished = true;

	diagonal = true;
	for (i = 0; i < dim && diagonal == true; i++) {
		if (currentGame[i][dim-i-1] != currentPlayer) {
			diagonal = false;
		}
	}
	if (diagonal == true)
		finished = true;


	bool line;
	for (i = 0; i < dim; i++) {
		line = true;
		for (j = 0; j < dim && line == true; j++) {
			if (currentGame[i][j] != currentPlayer) {
				line = false;
			}
		}

		if (line == true)
			finished = true;
	}

	bool column;
	for (j = 0; j < dim; j++) {
		column = true;
		for (i = 0; i < dim && column == true; i++) {
			if (currentGame[i][j] != currentPlayer) {
				column = false;
			}
		}

		if (column == true)
			finished = true;
	}

	for (i = 0; i < dim; i++)
		delete currentGame[i];
	delete currentGame;

	return finished;
}