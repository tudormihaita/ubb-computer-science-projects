#pragma once
#include <cassert>
#include "Tests.h"
#include "Apartment.h"
#include "Repository.h"
#include "Service.h"

using std::ifstream;
using std::cout;

void Tests::runAllTests() {
	cout << "Ruleaza teste domain...\n";
	runDomainTests();
	cout << "Teste domain trecute cu succes!\n";
	cout << "Ruleaza teste repository...\n";
	runRepositoryTests();
	cout << "Teste repository trecute cu succes!\n";
	cout << "Ruleaza teste service...\n";
	runServiceTests();
	cout << "Teste service trecute cu succes!\n";

}

void Tests::runDomainTests() {
	Apartment ap{ 11, "Hasdeu", 50, 1745.2 };

	assert(ap.getId() == 11);
	assert(ap.getStreet() == "Hasdeu");
	assert(ap.getSurface() == 50);
	assert(ap.getPrice() == 1745.2);

	Apartment identicalAp = ap;
	assert(identicalAp == ap);

	Apartment otherAp{ 9, "Vaida Voievod", 38, 2342.5 };

	assert(otherAp != ap);
}

void Tests::runRepositoryTests() {
	try {
		Repository repository("");
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.getErrorMsg() == "Nu s-a putut deschide fisierul!\n");
	}

	Repository repository("test_apartments.txt");

	assert(repository.getSize() == 0);
	Apartment ap1{ 11, "Hasdeu", 50, 1745.2 };
	repository.addApartment(ap1);

	Apartment identicalAp1{ 11, "Hasdeu", 50, 1745.2 };
	try {
		repository.addApartment(identicalAp1);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.getErrorMsg() == "Apartamentul exista deja in lista!\n");
	}

	assert(repository.getSize() == 1);
	assert(repository.getAllApartments().size() == 1);


	Apartment inexistentAp{ 22, "Teodor Mihali", 44, 1856.2 };
	try {
		repository.deleteApartment(inexistentAp);
		assert(false);
	}
	catch (RepoException& re) {
		assert(re.getErrorMsg() == "Apartamentul cu id-ul 22 nu exista in lista!\n");
	}

	assert(repository.findApartment(11) == ap1);

	try {
		auto foundAp = repository.findApartment(56);
		assert(false);
	}
	catch(RepoException& re) {
		assert(re.getErrorMsg() == "Apartamentul cu id-ul 56 nu exista in lista!\n");
	}

	repository.deleteApartment(ap1);
	assert(repository.getSize() == 0);

	repository.clearFile();
}

void Tests::runServiceTests() {
	Repository apartmentRepository("test_apartments.txt");
	Service apartmentService(apartmentRepository);

	assert(apartmentService.getSize() == 0);

	apartmentService.addApartment(11, "Hasdeu", 48, 1890.23);

	assert(apartmentService.getSize() == 1);
	assert(apartmentService.getAllApartments().size() == 1);

	try {
		apartmentService.addApartment(11, "Hasdeu", 48, 1890.23);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}

	apartmentService.addApartment(19, "Vaida Voievod", 26, 982.2);

	assert(apartmentService.filterByPrice(500, 1000).size() == 1);
	assert(apartmentService.filterBySurface(10, 50).size() == 2);

	apartmentService.removeApartment(11);
	assert(apartmentService.getSize() == 1);

	apartmentRepository.clearFile();
}