#pragma once
#include "Tests.h"

void Tests::runAllTests() {
	runDomainTests();
	runRepoTests();
	runServiceTests();
}

void Tests::runDomainTests() {
	Tractor t1{ 12,"John Deere","6150r",10 };
	assert(t1.getId() == 12);
	assert(t1.getModel() == "John Deere");
	assert(t1.getType() == "6150r");
	assert(t1.getNrWheels() == 10);

	Tractor t2{ 14,"New Holland","165",8 };
	assert(t1 != t2);

	t1 = t2;
	assert(t1 == t2);
}

void Tests::runRepoTests() {
	try {
		Repository tractorRepo{ "" };
	}
	catch (RepoException&) {
		assert(true);
	}

	Repository tractorRepo{ "test_tractors.txt" };
	assert(tractorRepo.getSize() == 6);
	assert(tractorRepo.getAllTractors().size() == 6);

	Tractor t1{ 100,"John Deere","6150r",10 };
	Tractor t2{ 101,"New Holland","165",8 };
	Tractor t3{ 12,"John Deere","6150r",10 };

	try {
		tractorRepo.addTractor(t3);
	}
	catch (RepoException&) {
		assert(true);
	}

	tractorRepo.addTractor(t1);
	assert(tractorRepo.getSize() == 7);

	try {
		tractorRepo.updateTractor(t2);
	}
	catch (RepoException&) {
		assert(true);
	}

	Tractor t4{ 100,"John Deere","165",16 };
	tractorRepo.updateTractor(t4);
	assert(tractorRepo.findTractor(100).getNrWheels() == 16);

	try {
		tractorRepo.findTractor(-20);
	}
	catch (RepoException&) {
		assert(true);
	}

	tractorRepo.deleteTractor(t4);
	assert(tractorRepo.getSize() == 6);
	try {
		tractorRepo.deleteTractor(t4);
	}
	catch (RepoException&) {
		assert(true);
	}
	
}

void Tests::runServiceTests() {
	Repository tractorRepo{ "test_tractors.txt" };
	Validator validator;
	Service tractorServ{ tractorRepo, validator };

	assert(tractorServ.getSize() == 6);
	assert(tractorServ.getAllTractors().size() == 6);
	assert(tractorServ.sortTractors().at(0).getId() == 23);
	assert(tractorServ.filterByType("165").size() == 2);

	try {
		tractorServ.addTractor(100, "", "", 7);
	}
	catch (ValidationException&) {
		assert(true);
	}

	tractorServ.addTractor(100, "a", "b", 10);
	assert(tractorServ.getSize() == 7);

	assert(tractorServ.findTractor(100).getId() == 100);
	tractorServ.updateTractor(100, 16);
	assert(tractorServ.findTractor(100).getNrWheels() == 16);

	try {
		tractorServ.updateTractor(100, 7);
	}
	catch (ValidationException&) {
		assert(true);
	}

	tractorServ.deleteTractor(100);
	assert(tractorServ.getSize() == 6);
}