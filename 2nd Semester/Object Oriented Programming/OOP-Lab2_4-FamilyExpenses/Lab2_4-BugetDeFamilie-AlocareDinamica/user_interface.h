#pragma once
#include "service.h"

typedef void (*PointerCmd)(Buget*);

typedef struct {
	char nume_comanda[30];
	//void (*pointer_comanda)(Buget*);
	PointerCmd pointer_comanda;
}dictionar_comenzi;

/*
* Ruleaza meniul aplicatiei prin care se ofera posibilitatea utilizatorului de introducere de comenzi astfel incat sa ruleze functionalitatile programului
* Se introduc comenzile corespunzatoare fiecarei functionalitati asa cum se afiseaza in meniul printat pe ecran la deschiderea aplicatiei
* Se ofera posibilitatea de realizare a mai multor operatii consecutive, cat timp datele introduse sunt corecte
*/
void run();