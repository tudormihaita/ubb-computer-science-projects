#pragma once
#include "TicTacToe.h"
#include "Exceptions.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

using std::vector;
using std::find_if;
using std::getline;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::distance;

class Repository {
private:
	vector<TicTacToe> games;
	string fileName;

	void loadFromFile();
	void writeToFile();

public:
	Repository(string file) : fileName{ file } {
		loadFromFile();
	}

	Repository(const Repository& other) = delete;

	~Repository() = default;

	int getSize();

	vector<TicTacToe> getAllGames();

	TicTacToe& findGame(int it);

	void addGame(const TicTacToe& game);

	void updateGame(const TicTacToe& game);

	void deleteGame(const TicTacToe& game);
};