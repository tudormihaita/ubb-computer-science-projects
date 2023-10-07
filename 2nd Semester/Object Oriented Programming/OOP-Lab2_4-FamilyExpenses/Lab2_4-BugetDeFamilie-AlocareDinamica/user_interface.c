#pragma once
#pragma warning (disable: 4996)
#pragma warning (disable: 4113)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_interface.h"
#include "service.h"
#include "validator.h"
#include "repository.h"
#include "cheltuiala.h"


void afiseaza_cheltuieliUI(Buget*);
void adauga_cheltuialaUI(Buget*);
void sterge_cheltuialaUI(Buget*);
void modifica_cheltuialaUI(Buget*);
void filtreaza_cheltuieliUI(Buget*);
void sorteaza_cheltuieliUI(Buget*);
void undoUI(Buget*);
void populate_bugetUI(Buget*);


dictionar_comenzi* construieste_dictionar_comenzi(int* dim) {
	dictionar_comenzi* dict = (dictionar_comenzi*)malloc(30 * sizeof(dictionar_comenzi));
	*dim = 0;
	if (dict) {
		strcpy(dict[*dim].nume_comanda, "afiseaza_cheltuieli");
		dict[*dim].pointer_comanda = afiseaza_cheltuieliUI;
		(*dim)++;

		strcpy(dict[*dim].nume_comanda, "adauga_cheltuiala");
		dict[*dim].pointer_comanda = adauga_cheltuialaUI;
		(*dim)++;

		strcpy(dict[*dim].nume_comanda, "sterge_cheltuiala");
		dict[*dim].pointer_comanda = sterge_cheltuialaUI;
		(*dim)++;

		strcpy(dict[*dim].nume_comanda, "modifica_cheltuiala");
		dict[*dim].pointer_comanda = modifica_cheltuialaUI;
		(*dim)++;

		strcpy(dict[*dim].nume_comanda, "filtreaza_cheltuieli");
		dict[*dim].pointer_comanda = filtreaza_cheltuieliUI;
		(*dim)++;

		strcpy(dict[*dim].nume_comanda, "sorteaza_cheltuieli");
		dict[*dim].pointer_comanda = sorteaza_cheltuieliUI;
		(*dim)++;

		strcpy(dict[*dim].nume_comanda, "undo");
		dict[*dim].pointer_comanda = undoUI;
		(*dim)++;

		strcpy(dict[*dim].nume_comanda, "populeaza_buget");
		dict[*dim].pointer_comanda = populate_bugetUI;
		(*dim)++;

	}
	return dict;
}


int cauta_comanda_dictionar(dictionar_comenzi* dict, int dim, char* cmd) {
	int ind;
	for (ind = 0; ind < dim; ind++)
		if (strcmp(dict[ind].nume_comanda, cmd) == 0)
			return ind;
	return -1;
}


void menuUI() {
	printf("--------------------------------------------------------------------------------------------------------\n");
	printf("Aplicatia permite efectuarea urmatoarelor operatii:\n");
	printf("[afiseaza_cheltuieli] - afisarea tuturor cheltuielilor introduse in lista pana la momentul actual\n");
	printf("[adauga_cheltuiala] - adauga o noua cheltuiala la bugetul familiei, specificand ziua, suma si tipul pentru aceasta\n");
	printf("[sterge_cheltuiala] - sterge din lista curenta o cheltuiala specificata prin id/pozitia sa in lista de cheltuieli\n");
	printf("[modifica_cheltuiala] - modifica o cheltuiala deja existenta in lista, specificand id-ul acesteia si noile valori pentru zi, suma si tip\n");
	printf("[filtreaza_cheltuieli] - filtreaza cheltuielile existente in lista la momentul actual prin eliminarea celor care au ziua/suma/tipul specificat, optiune aleasa de utilizator\n");
	printf("[sorteaza_cheltuieli] - sorteaza cheltuielile de lista crescator sau descrescator, in functie de suma sau de tip, utilizatorul specificand atat criteriul cat si proprietatea dupa care se va face sortarea\n");
	printf("---------------------------------------------------------------------------------------------------------\n");
}

void print_lista(Vector* lista) {
	for (int id = 0; id < get_size(lista); id++) {
		Cheltuiala* cheltuiala_curenta = get_element(lista, id);
		printf("[%d] %d - %s : %lf\n", id+1, get_zi(cheltuiala_curenta), get_tip(cheltuiala_curenta), get_suma(cheltuiala_curenta));
	}
}


void afiseaza_cheltuieliUI(Buget* buget) {
	Vector* lista_cheltuieli = get_all_cheltuieli(buget);
	if (get_lungime(buget->cheltuieli) == 0) {
		printf("Nu exista cheltuieli adaugate in buget!\n");
	}
	else {
		printf("Cheltuielile actuale bugetului de familie:\n");
		for (int id = 0; id < get_size(lista_cheltuieli); id++) {
			Cheltuiala* cheltuiala_curenta = find_cheltuiala(buget, id);
			printf("[%d] %d - %s : %lf\n", id + 1, get_zi(cheltuiala_curenta), get_tip(cheltuiala_curenta), get_suma(cheltuiala_curenta));
		}
	}
	destroy_vector(lista_cheltuieli);
}


void adauga_cheltuialaUI(Buget* buget) {
	bool input_invalid = false;
	int zi;
	double suma;
	char* tip = (char*)malloc(30 * sizeof(char));
	char* erori = (char*)malloc(90 * sizeof(char));

	printf("Introduceti ziua in care a fost efectuata cheltuiala: ");
	if (scanf("%d", &zi) != 1 && input_invalid==false) {
		printf("Input invalid pentru zi, nu se poate efectua adaugarea!\n");
		input_invalid = true;
		
	}
	if(input_invalid == false)
		printf("Introduceti suma achitata: ");
	if (scanf("%lf", &suma) != 1 && input_invalid == false) {
		printf("Input invalid pentru suma, nu se poate efectua adaugarea!\n");
		input_invalid = true;
	}

	if(input_invalid == false)
		printf("Introduceti tipul cheltuielii: ");
	if (scanf("%s", tip) != 1 && input_invalid == false) {
		printf("Input invalid pentru tip, nu se poate efectua adaugarea!\n");
		input_invalid = true;
	}

	if (input_invalid == false) {
		int cod_eroare = add_cheltuiala(buget, zi, suma, tip, erori);
		if (cod_eroare == -1) {
			printf("Cheltuiala nu a putut fi adaugata:\n");
			printf("%s", erori);
		}
		else
			printf("Cheltuiala adaugata cu succes!\n");
	}

	free(erori);
	free(tip);

}


void sterge_cheltuialaUI(Buget* buget) {
	int id;
	printf("Introduceti id-ul/pozitia cheltuielii pe care doriti sa o stergeti din buget:");
	scanf("%d", &id);

	int cod_eroare = delete_cheltuiala(buget, id-1);
	if (cod_eroare == -1) {
		printf("Pozitie invalida, nu exista o cheltuiala cu id-ul dat!\n");
	}
	else {
		printf("Cheltuiala stearsa cu succes!\n");
	}
}


void modifica_cheltuialaUI(Buget* buget) {
	bool input_invalid = false;
	int id;
	char* erori = (char*)malloc(90 * sizeof(char));
	printf("Introduceti id-ul/pozitia cheltuielii pe care doriti sa o modificati:");
	scanf("%d", &id);

	int zi_noua;
	double suma_noua;
	char* tip_nou = (char*)malloc(30 * sizeof(char));
	printf("Introduceti ziua noua: ");
	if (scanf("%d", &zi_noua) != 1 && input_invalid == false) {
		printf("Input invalid pentru zi, nu s-a putut efectua modificarea!\n");
		input_invalid = true;
	}
	if(input_invalid == false)
		printf("Introduceti suma noua: ");
	if (scanf("%lf", &suma_noua) != 1 && input_invalid == false) {
		printf("Input invalid pentru suma, nu s-a putut efectua modificarea!\n");
		input_invalid = true;
	}
	if(input_invalid == false)
		printf("Introduceti tipul nou: ");
	if (scanf("%s", tip_nou) != 1 && input_invalid == false) {
		printf("Input invalid pentru tip, nu s-a putut efectua modificarea!\n");
		input_invalid = true;
	}

	if (input_invalid == false) {
		int cod_eroare = modify_cheltuiala(buget, id - 1, zi_noua, suma_noua, tip_nou, erori);
		if (cod_eroare != 0) {
			printf("Modificare invalida:\n");
			printf("%s", erori);

		}
		else {
			printf("Cheltuiala modificata cu succes!\n");
		}
	}
	free(tip_nou);
	free(erori);
}


void filtreaza_cheltuieliUI(Buget* buget) {
	bool proprietate_valida = false;
	bool valoare_valida = false;
	char* proprietate_filtru = (char*)malloc(30 * sizeof(char));

	printf("Introduceti proprietatea dupa care doriti sa se efectueze filtrarea(zi / suma / tip): ");
	scanf("%s", proprietate_filtru);


	if (strcmp(proprietate_filtru, "zi") == 0 || strcmp(proprietate_filtru, "suma") == 0 || strcmp(proprietate_filtru, "tip") == 0)
		proprietate_valida = true;
	else {
		printf("Proprietatea introdusa este invalida, nu se poate efectua filtrarea!\n");
	}

	if (strcmp(proprietate_filtru, "zi") == 0 && proprietate_valida == true) {
		printf("Introduceti valoarea zilei pentru care se vor filtra cheltuielile: ");

		int zi_filtru;
		scanf("%d", &zi_filtru);

		if (valideaza_zi(zi_filtru) == 0) {
			valoare_valida = true;
			Vector* lista_filtrata = filter_cheltuieli_proprietate(buget, &zi_filtru, filtru_zi);
			if (get_lungime(lista_filtrata) > 0) {
				printf("Lista de cheltuieli filtrata astfel incat cheltuielile sa respecta filtrul de %s setat este:\n", proprietate_filtru);
				print_lista(lista_filtrata);
			}
			else {
				printf("Au fost filtrate toate cheltuielile introduse, nu exista cheltuieli de afisat!\n");
			}
			destroy_vector(lista_filtrata);
		}
		else {
			printf("Valoarea introdusa pentru filtru este invalida!\n");
		}
	}

	if (strcmp(proprietate_filtru, "suma") == 0 && proprietate_valida == true) {
		int optiune;
		printf("1 - Filtrare cheltuieli cu suma mai mica sau egala cu suma data\n");
		printf("2 - Filtrare cheltuieli cu suma mai mare decat suma data\n");
		printf("Introduceti optiunea de filtru suma pe care doriti sa-l aplicati:\n");

		if (scanf("%d", &optiune) != 1) {
			printf("Optiunea introdusa pentru filtrare este invalida!\n");
		}
		else if (optiune != 1 && optiune != 2) {
			printf("Optiunea introdusa pentru filtrare este invalida!\n");
		}
		else {
			printf("Introduceti valoarea sumei pentru care se vor filtra cheltuielile: ");

			double suma_filtru;
			scanf("%lf", &suma_filtru);

			if (valideaza_suma(suma_filtru) == 0) {
				valoare_valida = true;

				if (optiune == 1) {
					Vector* lista_filtrata = filter_cheltuieli_proprietate(buget, &suma_filtru, filtru_suma_minima);
					if (get_lungime(lista_filtrata) > 0) {
						printf("Lista de cheltuieli filtrata astfel incat cheltuielile sa respecta filtrul de %s setat este:\n", proprietate_filtru);
						print_lista(lista_filtrata);
					}
					else {
						printf("Au fost filtrate toate cheltuielile introduse, nu exista cheltuieli de afisat!\n");
					}
					destroy_vector(lista_filtrata);
				}
				else {
					Vector* lista_filtrata = filter_cheltuieli_proprietate(buget, &suma_filtru, filtru_suma_maxima);
					if (get_lungime(lista_filtrata) > 0) {
						printf("Lista de cheltuieli filtrata astfel incat cheltuielile sa respecta filtrul de %s setat este:\n", proprietate_filtru);
						print_lista(lista_filtrata);
					}
					else {
						printf("Au fost filtrate toate cheltuielile introduse, nu exista cheltuieli de afisat!\n");
					}
					destroy_vector(lista_filtrata);
				}
			}
			else {
				printf("Valoarea introdusa pentru filtru este invalida!\n");
			}
		}
	}

	if (strcmp(proprietate_filtru, "tip") == 0 && proprietate_valida == true) {
		printf("Introduceti tipul pentru care se vor filtra cheltuielile(unul din: Mancare, Transport, Telefon&Internet, Imbracaminte, Altele): ");

		char* tip_filtru=(char*)malloc(30*sizeof(char));
		scanf("%s", tip_filtru);

		if (valideaza_tip(tip_filtru) == 0) {
			valoare_valida = true;
			Vector* lista_filtrata = filter_cheltuieli_proprietate(buget, tip_filtru, filtru_tip);
			if (get_lungime(lista_filtrata) > 0) {
				printf("Lista de cheltuieli filtrata astfel incat cheltuielile sa respecta filtrul de %s setat este:\n", proprietate_filtru);
				print_lista(lista_filtrata);
			}
			else {
				printf("Au fost filtrate toate cheltuielile introduse, nu exista cheltuieli de afisat!\n");
			}
			destroy_vector(lista_filtrata);
		}
		else {
			printf("Valoarea introdusa pentru filtru este invalida!\n");
		}
		free(tip_filtru);
	}
	free(proprietate_filtru);
}


void sorteaza_cheltuieliUI(Buget* buget) {
	char* proprietate_sortare = (char*)malloc(30 * sizeof(char));
	printf("Introduceti proprietatea dupa care doriti sa se efectueze sortarea(suma / tip): ");
	scanf("%s", proprietate_sortare);


	if (proprietate_sortare) {
		char* criteriu = (char*)malloc(30 * sizeof(char));
		bool reversed = false;
		printf("Introduceti criteriul pentru sortare: (crescator/descrescator)");
		if (criteriu) {
			scanf("%s", criteriu);
			if (strcmp(criteriu, "crescator") == 0)
				reversed = false;
			else if (strcmp(criteriu, "descrescator") == 0)
				reversed = true;
			else {
				printf("Criteriu sortare invalid, nu s-a putut efectua sortarea!\n");
				free(proprietate_sortare);
				free(criteriu);
				return;
			}
		}

		if (strcmp(proprietate_sortare, "suma") == 0) {
			Vector* lista_sortata = sort_cheltuieli(buget->cheltuieli, reversed, compare_suma);
			printf("Sortare efectuata cu succes!\n");

			printf("Lista de cheltuieli sortata dupa criteriile date este:\n");
			print_lista(lista_sortata);

			destroy_vector(lista_sortata);
		}
		else if (strcmp(proprietate_sortare, "tip") == 0) {
			Vector* lista_sortata = sort_cheltuieli(buget->cheltuieli, reversed, compare_tip);
			printf("Sortare efectuata cu succes!\n");

			printf("Lista de cheltuieli sortata dupa criteriile date este:\n");
			print_lista(lista_sortata);

			destroy_vector(lista_sortata);
		}
		else {
			printf("Proprietate invalida, nu s-a putut efectua sortarea!\n");
			free(criteriu);
			free(proprietate_sortare);
			return;
		}

		free(criteriu);
	}
	free(proprietate_sortare);

}


void undoUI(Buget* buget) {
	if (undo(buget) == 1)
		printf("Undo realizat cu succes!\n");
	else
		printf("Nu se mai poate efectua undo!\n");
}


void goodbyeUI() {
	printf("88        db        88%c%cYb 888888 Yb    dP 888888 8888b.  888888 88%c%cYb 888888   d8b\n", 0x22, 0x22, 0x22, 0x22);
	printf("88       dPYb       88__dP 88__    Yb  dP  88__    8I  Yb 88__   88__dP 88__     Y8P\n");
	printf("88.o    dP__Yb      88%cYb  88%c%c     YbdP   88%c%c    8I  dY 88%c%c   88%cYb  88%c%c     `%c'\n", 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22);
	printf("88ood8 dP%c%c%c%cYb     88  Yb 888888    YP    888888 8888Y%c  888888 88  Yb 888888   (8)\n", 0x22, 0x22, 0x22, 0x22, 0x22);
}



void populate_bugetUI(Buget* buget) {
	char* erori = (char*)malloc(90*sizeof(char));
	add_cheltuiala(buget, 12, 142.32, "Mancare", erori);
	add_cheltuiala(buget, 30, 2489.225, "Altele", erori);
	add_cheltuiala(buget, 12, 8932.2, "Telefon&Internet", erori);
	add_cheltuiala(buget, 15, 345.98, "Imbracaminte", erori);
	add_cheltuiala(buget, 27, 142.32, "Altele", erori);
	add_cheltuiala(buget, 30, 876.44, "Imbracaminte", erori);
	add_cheltuiala(buget, 10, 1024.68, "Mancare", erori);
	add_cheltuiala(buget, 8, 98.23, "Telefon&Internet", erori);
	add_cheltuiala(buget, 21, 7623.322, "Altele", erori);
	printf("Cheltuieli generate cu succes!\n");
	free(erori);
}


void run() {
	int dim = 0;
	dictionar_comenzi* dict = construieste_dictionar_comenzi(&dim);

	menuUI();

	//char* cmd = (char*)malloc(30 * sizeof(char*));
	char cmd[30];
	Buget buget_familie = create_buget();

	while (1) {
		printf("Introduceti optiunea: ");
		scanf(" %s", cmd);
		if (cmd) {
			int ind = cauta_comanda_dictionar(dict, dim, cmd);
			if (ind != -1)
				dict[ind].pointer_comanda(&buget_familie);
			else if (strcmp(cmd, "exit") == 0) {
				//goodbyeUI();
				printf("Goodbye!\n");
				free(dict);
				destroy_buget(&buget_familie);
				return;
			}
			else
				printf("Comanda invalida!\n");
		}

	}
}