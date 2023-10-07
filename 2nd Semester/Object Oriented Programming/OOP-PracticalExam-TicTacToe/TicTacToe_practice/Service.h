#pragma once
#include "Repository.h"
#include "Validator.h"

using std::sort;
using std::copy_if;

class Service {
private:
	Repository& gameRepo;
	Validator& gameValidator;
public:
	Service(Repository& repo, Validator& validator) : gameRepo{ repo }, gameValidator{ validator } {};

	Service(const Service& other) = delete;

	~Service() = default;

	int getSize();

	vector<TicTacToe> getAllGames();

	TicTacToe& findGame(int id);

	void addGame(int id, int dim, string table, string next, string state);

	void updateGame(int id, int newDim, string newTable, string newNext, string newState);

	void deleteGame(int id);

	bool checkGameState(int dim, string table, char currentPlayer);

};