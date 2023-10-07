#pragma once
#include <string>

using std::string;

class TicTacToe {
private:
	int id;
	int dim;
	string table;
	string nextPlayer;
	string state;
public:
	TicTacToe() = default;

	TicTacToe(int id, int dim, string table, string nextPlayer, string state) : id{ id }, dim{ dim }, table{ table }, nextPlayer{ nextPlayer }, state{ state } {};

	~TicTacToe() = default;

	TicTacToe(const TicTacToe& other) = default;
	TicTacToe(TicTacToe&& other) = default;

	TicTacToe& operator=(const TicTacToe& other) = default;
	TicTacToe& operator=(TicTacToe&& other) = default;

	bool operator==(const TicTacToe& other) {
		return this->id == other.id;
	}

	bool operator!=(const TicTacToe& other) {
		return this->id != other.id;
	}

	int getId() const noexcept;

	int getDim() const noexcept;

	string getTable() const;

	string getNextPlayer() const;

	string getState() const;
};