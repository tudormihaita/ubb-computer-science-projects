#include "Tests.h"

void Tests::runAllTests() {
	runDomainTests();
	runRepoTests();
	runServiceTests();
}

void Tests::runDomainTests() {
	CPU c{ 12, "I7", 8, "PLCC", 4500 };
	assert(c.getID() == 12);
	assert(c.getName() == "I7");
	assert(c.getThreads() == 8);
	assert(c.getSocket() == "PLCC");
	assert(c.getPrice() == 4500);

	MOBO m{ 14,"GIGABYTE H130M", "PLCC", 2700 };
	assert(m.getId() == 14);
	assert(m.getName() == "GIGABYTE H130M");
	assert(m.getSocket() == "PLCC");
	assert(m.getPrice() == 2700);

	CPU otherC{ 16, "I5", 8, "PLCC", 4500 };
	MOBO otherM{ 21,"GIGABYTE Z120", "PLCC", 2700 };

	c = otherC;
	m = otherM;
}

void Tests::runRepoTests() {
	try {
		Repository repo{ "", "" };
	}
	catch (RepoException) {
		assert(true);
	}

	Repository repo{ "test_cpu.txt", "test_mobo.txt" };
	assert(repo.getCPUSize() == 2);
	assert(repo.getMOBOSize() == 2);

	assert(repo.getAllCPUs().size() == 2);
	assert(repo.getAllMOBOs().size() == 2);

	assert(repo.findCPU(1).getThreads() == 8);
	assert(repo.findMOBO(1).getSocket() == "PLCC");
}

void Tests::runServiceTests() {
	Repository repo{ "test_cpu.txt", "test_mobo.txt" };
	Service serv{ repo };

	assert(serv.getCPUSize() == 2);
	assert(serv.getMOBOSize() == 2);

	assert(serv.getAllCPUs().size() == 2);
	assert(serv.getAllMOBOs().size() == 2);

	assert(serv.findCPU(1).getSocket() == "PLCC");
	assert(serv.findMOBO(1).getPrice() == 1700);

	assert(serv.filterBySocket("PLCC").size() == 1);

	serv.addMOBO("ASUS H180", "DIP", 2100);
	assert(serv.getMOBOSize() == 3);
}