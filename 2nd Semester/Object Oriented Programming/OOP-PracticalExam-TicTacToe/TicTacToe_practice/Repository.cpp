#pragma once
#include "Repository.h"

void Repository::loadFromFile() {
	ifstream fin(fileName);

	if (!fin.is_open()) {
		throw RepoException("Nu s-a putut deschide fisierul!\n");
	}

	if (fin.peek() == EOF)
		return;

	string line;
	while (!fin.eof()) {
		string atribute;
		vector<string> atr;

		getline(fin, line);
		if (!line.empty()) {
			stringstream ss(line);

			while (getline(ss, atribute, ',')) {
				atr.push_back(atribute);
			}

			int id = stoi(atr[0]);
			int dim = stoi(atr[1]);
			string table = atr[2];
			string nextPlayer = atr[3];
			string state = atr[4];

			TicTacToe game{ id, dim,table, nextPlayer, state };
			games.push_back(game);

			atr.clear();
		}
	}

	fin.close();
}

void Repository::writeToFile() {
	ofstream fout(fileName);

	if (!fout.is_open()) {
		throw RepoException("Nu s-a putut deschide fisierul!\n");
	}

	for (auto& game : games) {
		fout << game.getId() << "," << game.getDim() << "," << game.getTable() << "," << game.getNextPlayer() << "," << game.getState() << "\n";
	}

	fout.close();
}

int Repository::getSize() {
	return static_cast<int>(games.size());
}

vector<TicTacToe> Repository::getAllGames() {
	return games;
}

TicTacToe& Repository::findGame(int id) {
	auto it = find_if(games.begin(), games.end(), [&](const TicTacToe& g) {
		return g.getId() == id;
	});

	if (it == games.end()) {
		throw RepoException("Nu exista jocul cautat!\n");
	}

	return *it;
}

void Repository::addGame(const TicTacToe& game) {
	auto it = find_if(games.begin(), games.end(), [&](const TicTacToe& g) {
		return g.getId() == game.getId();
	});

	if (it != games.end()) {
		throw RepoException("Jocul dat exista deja!\n");
	}

	games.push_back(game);
	writeToFile();
}

void Repository::updateGame(const TicTacToe& game) {
	auto it = find_if(games.begin(), games.end(), [&](const TicTacToe& g) {
		return g.getId() == game.getId();
		});

	if (it == games.end()) {
		throw RepoException("Jocul dat nu exista!\n");
	}

	const int pos = static_cast<int>(distance(games.begin(), it));
	games.at(pos) = game;
	writeToFile();
}

void Repository::deleteGame(const TicTacToe& game) {
	auto it = find_if(games.begin(), games.end(), [&](const TicTacToe& g) {
		return g.getId() == game.getId();
		});

	if (it == games.end()) {
		throw RepoException("Jocul dat nu exista!\n");
	}

	const int pos = static_cast<int>(distance(games.begin(), it));
	games.erase(games.begin() + pos);
	writeToFile();
}