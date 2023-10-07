#pragma once
#include "Tests.h"

void Tests::runAllTests() {
	runDomainTests();
	runRepoTests();
	runServiceTests();
}

void Tests::runDomainTests() {
	TicTacToe game1{ 1,3,"--XO-X-O-","X","Neinceput" };
	assert(game1.getId() == 1);
	assert(game1.getDim() == 3);
	assert(game1.getTable() == "--XO-X-O-");
	assert(game1.getNextPlayer() == "X");
	assert(game1.getState() == "Neinceput");

	TicTacToe game2{ 2,3,"---X-----","O","In derulare" };
	assert(game2 != game1);

	game1 = game2;
	assert(game1 == game2);
}

void Tests::runRepoTests() {
	try {
		Repository gameRepo{ "" };
	}
	catch (RepoException&) {
		assert(true);
	}

	Repository gameRepo{ "test_games.txt" };
	assert(gameRepo.getSize() == 3);
	assert(gameRepo.getAllGames().size() == 3);

	assert(gameRepo.findGame(1).getDim() == 3);
	
	TicTacToe game1{ 8,3,"--XO-X-O-","X","Neinceput" };
	gameRepo.addGame(game1);
	assert(gameRepo.getSize() == 4);

	try {
		gameRepo.addGame(game1);
	}
	catch (RepoException&) {
		assert(true);
	}

	TicTacToe game2{ 8,3,"---X-----","O","In derulare" };
	gameRepo.updateGame(game2);

	TicTacToe game3{ 12,3,"---X-----","O","In derulare" };
	try {
		gameRepo.updateGame(game3);
	}
	catch (RepoException&) {
		assert(true);
	}

	assert(gameRepo.findGame(8).getState() == "In derulare");
	gameRepo.deleteGame(game2);

	try {
		gameRepo.deleteGame(game3);
	}
	catch (RepoException&) {
		assert(true);
	}

	assert(gameRepo.getSize() == 3);
}

void Tests::runServiceTests() {
	Repository gameRepo{ "test_games.txt" };
	Validator validator;
	Service gameServ{ gameRepo, validator };

	assert(gameServ.getSize() == 3);
	assert(gameServ.getAllGames().size() == 3);

	gameServ.addGame(12, 3, "---------", "X", "Neinceput");
	assert(gameServ.getSize() == 4);

	gameServ.updateGame(12, 3, "XX-O-XO-X", "O", "In derulare");
	assert(gameServ.findGame(12).getState() == "In derulare");

	gameServ.deleteGame(12);
	assert(gameServ.getSize() == 3);

	assert(gameServ.checkGameState(3, "---------", 'X') == false);
}