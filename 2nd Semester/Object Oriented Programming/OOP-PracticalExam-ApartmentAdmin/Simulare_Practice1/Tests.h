#pragma once


class Tests {
public:
	void runAllTests();

private:
	void runDomainTests();
	void runRepositoryTests();
	void runServiceTests();
};