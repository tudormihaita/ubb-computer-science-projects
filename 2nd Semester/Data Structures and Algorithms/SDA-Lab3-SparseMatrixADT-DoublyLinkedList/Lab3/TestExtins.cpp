#include <assert.h>
#include "Matrice.h"
#include "TestExtins.h"
#include <iostream>
#include <exception>

using namespace std;


void testCreeaza() {
	Matrice m(10,10);
	assert(m.nrLinii() == 10);
	assert(m.nrColoane() == 10);
	for(int i=0; i<m.nrLinii(); i++)
	  for(int j=0; j<m.nrColoane(); j++)
		assert(m.element(i,j) == NULL_TELEMENT);
}

void testAdauga() {
	Matrice m(10,10);
	for(int j=0; j<m.nrColoane(); j++)
		m.modifica(4,j,3);
	for(int i=0; i<m.nrLinii(); i++)
           for(int j=0; j<m.nrColoane(); j++)
		if (i==4)
		  assert(m.element(i,j) == 3);
		else
		  assert(m.element(i,j) == NULL_TELEMENT);
}

void testQuantity() {//scopul e sa adaugam multe date
	Matrice m(300,300);
	for(int i=m.nrLinii()/2; i<m.nrLinii(); i++){
           for(int j=0; j<m.nrColoane()/2; j++)
	   {	
		int v1=j;
		int v2=m.nrColoane()-v1-1;
		if (i%2==0 && v1%2==0)
		     m.modifica(i, v1, i*v1);
		else
	            if (v1%3==0)
			m.modifica(i, v1, i+v1);
		if (i%2==0 && v2%2==0)
		     m.modifica(i, v2, i*v2);
		else
	            if (v2%3==0)
			m.modifica(i, v2, i+v2);
	   }
	}
	for(int i=0; i<=m.nrLinii()/2; i++){
           for(int j=0; j<m.nrColoane()/2; j++)
	   {	
		int v1=j;
		int v2=m.nrColoane()-v1-1;
		if (i%2==0 && v1%2==0)
		     m.modifica(i, v1, i*v1);
		else
	            if (v1%3==0)
			m.modifica(i, v1, i+v1);
		if (i%2==0 && v2%2==0)
		     m.modifica(i, v2, i*v2);
		else
	            if (v2%3==0)
			m.modifica(i, v2, i+v2);
	   }
	}		
	for(int i=0; i<m.nrLinii(); i++)
           for(int j=0; j<m.nrColoane(); j++)
		if (i%2==0 && j%2==0)
		     assert(m.element(i,j) == i*j);
		else
	            if (j%3==0)
			 assert(m.element(i,j) == i+j);
				else assert(m.element(i,j) == 0);
}

void testExceptii() {
	Matrice m(10,10);
	try {
		m.element(-1,-1);
	}
	catch (exception&) {
		assert(true); //ar trebui sa arunce exceptie
	}
    try {
		m.modifica(12,0,1);
	}
	catch (exception&) {
		assert(true); //ar trebui sa arunce exceptie
	}
	try {
		assert(m.nrLinii());
	}
	catch (exception&) {
		assert(false); //nu ar trebui sa arunce exceptie
	}
}


void testRedimensioneaza() {
	Matrice m(5, 5);
	try{
		m.redimensioneaza(-2, 3);
	}
	catch (exception&) {
		assert(true);
	}

	m.modifica(0, 3, 12);
	m.modifica(4, 2, 1);
	m.modifica(4, 3, 1);
	m.redimensioneaza(4, 4);
	assert(m.nrLinii() == 4);
	assert(m.nrColoane() == 4);

	try {
		m.element(4, 2);
	}
	catch (exception&) {
		assert(true);
	}

	m.redimensioneaza(6, 8);
	assert(m.nrLinii() == 6);
	assert(m.nrColoane() == 8);
	assert(m.element(4, 2) == NULL_TELEMENT);
	try {
		m.element(6, 1);
	}
	catch (exception&) {
		assert(true);
	}

	assert(m.element(2, 2) == NULL_TELEMENT);
	assert(m.element(0, 3) == 12);
}

void testMemoryLeaks() {
	Matrice m(5, 5);
	m.modifica(1, 2, 3);
	m.modifica(3, 4, 5);
	m.modifica(2, 2, 7);
	m.modifica(2, 2, NULL_TELEMENT);
	m.modifica(1, 2, NULL_TELEMENT);
	m.modifica(3, 4, NULL_TELEMENT);
}

void testAllExtins() {
	testCreeaza();
	testAdauga();
	testQuantity();
	testExceptii();
	testRedimensioneaza();
	testMemoryLeaks();
}
