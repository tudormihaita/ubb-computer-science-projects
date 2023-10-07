#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "tests.h"
#include <string.h>
#include "cheltuiala.h"
#include "repository.h"
#include "validator.h"
#include "service.h"


void run_tests_domain_cheltuieli();
void run_tests_repo_cheltuieli();
void run_tests_validare_cheltuieli();
void run_tests_service_cheltuieli();
void run_tests_undo_cheltuieli();


void run_all_tests() {
	printf("**************************************\n");
	run_tests_domain_cheltuieli();
	printf("Teste domain trecute cu succes!\n");
	run_tests_repo_cheltuieli();
	printf("Teste repo trecute cu succes!\n");
	run_tests_validare_cheltuieli();
	printf("Teste validare trecute cu succes!\n");
	run_tests_service_cheltuieli();
	printf("Teste service trecute cu succes!\n");
	run_tests_undo_cheltuieli();
	printf("Teste undo trecute cu succes!\n");
	printf("**************************************\n");
}



void run_tests_domain_cheltuieli() {
	int zi1 = 12;
	double suma1 = 467.89;
	Cheltuiala* cheltuiala1 = create_cheltuiala(zi1, suma1, "Mancare");
	assert(strcmp(get_tip(cheltuiala1), "Mancare") == 0);
	assert(get_zi(cheltuiala1) == zi1);
	assert(get_suma(cheltuiala1) == suma1);

	Cheltuiala* copie_cheltuiala1 = create_cheltuiala(zi1, suma1, "Mancare");
	assert(compare_cheltuieli(cheltuiala1, copie_cheltuiala1) == 1);

	int zi2 = 27;
	double suma2 = 987.35;
	Cheltuiala* cheltuiala2 = create_cheltuiala(zi2, suma2, "Transport");
	assert(strcmp(get_tip(cheltuiala2), "Transport") == 0);
	assert(get_zi(cheltuiala2) == zi2);
	assert(get_suma(cheltuiala2) == suma2);
	assert(compare_cheltuieli(cheltuiala1, cheltuiala2) == 0);

	replace_cheltuiala(cheltuiala2, copie_cheltuiala1);
	assert(compare_cheltuieli(cheltuiala1, cheltuiala2) == 1);

	destroy_cheltuiala(cheltuiala1);
	destroy_cheltuiala(cheltuiala2);
	destroy_cheltuiala(copie_cheltuiala1);
	
}

void run_tests_repo_cheltuieli() {
	Vector* vector = create_empty(destroy_cheltuiala);
	assert(get_size(vector) == 0);

	set_size(vector, 2);
	assert(get_size(vector) == 2);
	set_size(vector, 0);

	Cheltuiala* c1 = create_cheltuiala(15, 560.3, "Imbracaminte");
	Cheltuiala* c2 = create_cheltuiala(26, 289.435, "Mancare");

	add_element(vector, c1);
	add_element(vector, c2);

	assert(get_size(vector) == 2);
	assert(compare_cheltuieli(get_element(vector, 0), c1) == 1);
	assert(compare_cheltuieli(get_element(vector, 1), c2) == 1);

	Cheltuiala* c3 = create_cheltuiala(4, 110.15, "Telefon&Internet");
	set_element(vector, 0, c3);

	assert(compare_cheltuieli(get_element(vector, 0), c3) == 1);


	set_element(vector, 1, c3);
	assert(compare_cheltuieli(get_element(vector, 1), c3) == 1);


	delete_element(vector, 1);
	assert(get_size(vector) == 1);
	assert(compare_cheltuieli(get_element(vector, 0), c3) == 1);

	assert(exchange_elements(vector, 0, 1) == -1);

	Cheltuiala* c4 = create_cheltuiala(11, 25364.435, "Altele");
	add_element(vector, c4);

	delete_element(vector, 0);

	assert(get_size(vector) == 1);

	destroy_cheltuiala(c1);
	destroy_cheltuiala(c2);
	destroy_cheltuiala(c3);
	destroy_vector(vector);

}

void run_tests_validare_cheltuieli() {
	int zi_valida = 12;
	double suma_valida = 670.34;
	char tip_valid[30] = "Altele";
	Cheltuiala* cheltuiala_valida = create_cheltuiala(zi_valida, suma_valida, tip_valid);
	char validare_cheltuiala1[90];
	strcpy(validare_cheltuiala1, "");

	valideaza_cheltuiala(cheltuiala_valida, validare_cheltuiala1);

	assert(strlen(validare_cheltuiala1) == 0);

	int zi_invalida = -8;
	double suma_invalida = 0;
	char tip_invalid[30] = "Factura";
	Cheltuiala* cheltuiala_invalida = create_cheltuiala(zi_invalida, suma_invalida, tip_invalid);
	char validare_cheltuiala2[90];
	strcpy(validare_cheltuiala2, "");
;
	valideaza_cheltuiala(cheltuiala_invalida, validare_cheltuiala2);

	assert(strcmp(validare_cheltuiala2, "Zi invalida!\nSuma invalida!\nTip invalid!\n")== 0);

	assert(valideaza_zi(zi_invalida) == -1);
	assert(valideaza_suma(suma_invalida) == -2);
	assert(valideaza_tip(tip_invalid) == -3);

	assert(valideaza_zi(zi_valida) == 0);
	assert(valideaza_suma(suma_valida) == 0);
	assert(valideaza_tip(tip_valid) == 0);

	destroy_cheltuiala(cheltuiala_valida);
	destroy_cheltuiala(cheltuiala_invalida);
}


void run_tests_service_cheltuieli() {
	char erori[90];
	Buget buget = create_buget();


	int zi1 = 22;
	double suma1 = 765.982;
	char tip1[30] = "Telefon&Internet";

	int cod_eroare1 = add_cheltuiala(&buget, zi1, suma1, tip1, erori);
	assert(cod_eroare1 == 0);
	assert(strlen(erori) == 0);

	assert(get_lungime(buget.cheltuieli) == 1);

	int zi2_invalid = 89;
	double suma2_invalid = 2085.982;
	char tip2_invalid[30] = "Intretinere";

	int cod_eroare = add_cheltuiala(&buget, zi2_invalid, suma2_invalid, tip2_invalid, erori);
	assert(cod_eroare == -1);
	assert(strcmp(erori, "Zi invalida!\nTip invalid!\n") == 0);

	int zi2 = 17;
	double suma2 = 2085.982;
	char tip2[30] = "Mancare";

	int cod_eroare2 = add_cheltuiala(&buget, zi2, suma2, tip2, erori);
	assert(cod_eroare2 == 0);

	Vector* lista = get_all_cheltuieli(&buget);
	assert(get_size(lista) == 2);

	int eroare_stergere = delete_cheltuiala(&buget, 9);
	assert(eroare_stergere == -1);

	assert(get_lungime(buget.cheltuieli) == 2);

	delete_cheltuiala(&buget, 1);
	assert(get_lungime(buget.cheltuieli) == 1);

	int eroare_modificare = modify_cheltuiala(&buget, 2, 14, 675.98, "Imbracaminte", erori);
	assert(eroare_modificare == -2);
	assert(strcmp(erori, "Pozitie/Id cheltuiala invalid!\n") == 0);

	int eroare_modificare_valida = modify_cheltuiala(&buget, 0, 14, 675.98, "Imbracaminte", erori);
	assert(eroare_modificare_valida == 0);
	assert(get_zi(get_element(buget.cheltuieli, 0))== 14);

	int eroare_modificare_invalida = modify_cheltuiala(&buget, 0, -45, 0, "Intretinere", erori);
	assert(eroare_modificare_invalida == -1);
	assert(strcmp("erori", "Zi invalida!\nSuma invalida!\nTip invalid!\n"));


	add_cheltuiala(&buget, 17, 897.2, "Transport", erori);
	assert(get_lungime(buget.cheltuieli) == 2);

	
	int zi_filtru = 17;

	Vector* lista_filtrata_zi = filter_cheltuieli_proprietate(&buget, &zi_filtru, filtru_zi);
	assert(get_size(lista_filtrata_zi) == 1);

	
	char* tip_filtru = "Imbracaminte";

	add_cheltuiala(&buget, 4, 342.2, "Imbracaminte", erori);
	assert(get_lungime(buget.cheltuieli) == 3);

	
	int id_cautat = 0;
	Cheltuiala* cheltuiala_cautata = find_cheltuiala(&buget, id_cautat);
	assert(get_zi(cheltuiala_cautata) == get_zi(get_element(buget.cheltuieli, id_cautat)));

	int id_inexistent = 7;
	Cheltuiala* cheltuiala_inexistenta = find_cheltuiala(&buget, id_inexistent);
	assert(cheltuiala_inexistenta == NULL);


	Vector* lista_filtrata_tip = filter_cheltuieli_proprietate(&buget, tip_filtru, filtru_tip);
	assert(get_size(lista_filtrata_tip) == 1);

	double suma_filtru = 342.2;

	Vector* lista_filtrata_suma_minima = filter_cheltuieli_proprietate(&buget, &suma_filtru, filtru_suma_minima);
	assert(get_size(lista_filtrata_suma_minima) == 2);

	Vector* lista_filtrata_suma_maxima = filter_cheltuieli_proprietate(&buget, &suma_filtru, filtru_suma_maxima);
	assert(get_size(lista_filtrata_suma_maxima) == 1);
	

	/*
	vector_cheltuieli lista_nesortata = get_all_cheltuieli(vector);
	for (int i = 1; i <= get_size(lista_nesortata); i++)
		printf("%lf ", get_suma(get_element(lista_nesortata, i)));

	printf("\n");
	*/
	

	double suma_cautata = get_suma(get_element(buget.cheltuieli, 2));


	bool reversed_suma1 = false;
	Vector* lista_sortata1 = sort_cheltuieli(buget.cheltuieli, reversed_suma1, compare_suma);
	assert(get_suma(get_element(lista_sortata1, 0)) == suma_cautata);

	bool reversed_suma2 = true;
	Vector* lista_sortata2 = sort_cheltuieli(buget.cheltuieli, reversed_suma2, compare_suma);
	

	char* tip_cautat = "Transport";


	bool reversed_tip1 = true;
	Vector* lista_sortata3 = sort_cheltuieli(buget.cheltuieli, reversed_tip1, compare_tip);
	assert(strcmp(get_tip(get_element(lista_sortata3,0)), tip_cautat) == 0);

	bool reversed_tip2 = false;
	Vector* lista_sortata4 = sort_cheltuieli(buget.cheltuieli, reversed_tip2, compare_tip);
	

	destroy_buget(&buget);
	
	destroy_vector(lista);
	destroy_vector(lista_filtrata_zi);
	destroy_vector(lista_filtrata_tip);
	destroy_vector(lista_filtrata_suma_minima);
	destroy_vector(lista_filtrata_suma_maxima);
	destroy_vector(lista_sortata1);
	destroy_vector(lista_sortata2);
	destroy_vector(lista_sortata3);
	destroy_vector(lista_sortata4);

	/*
	vector_cheltuieli lista_sortata = get_all_cheltuieli(vector);
	for (int i = 1; i <= get_size(lista_sortata); i++)
		printf("%f ", get_suma(get_element(lista_sortata, i)));
	printf("\n");
	*/
}


void run_tests_undo_cheltuieli() {
	char* erori = (char*)malloc(90 * sizeof(char));
	Buget buget = create_buget();

	assert(undo(&buget) == 0);
	assert(add_cheltuiala(&buget, 12, 324.23, "Mancare", erori) == 0);
	assert(add_cheltuiala(&buget, 30, 7832.124, "Telefon&Internet", erori) == 0);

	assert(get_lungime(buget.cheltuieli) == 2);
	undo(&buget);
	assert(get_lungime(buget.cheltuieli) == 1);

	assert(delete_cheltuiala(&buget, 0) == 0);
	assert(get_lungime(buget.cheltuieli) == 0);
	undo(&buget);
	assert(get_lungime(buget.cheltuieli) == 1);

	assert(modify_cheltuiala(&buget, 0, 12, 452.23, "Altele", erori) == 0);
	Cheltuiala* cheltuiala_modified = find_cheltuiala(&buget, 0);
	assert(strcmp(get_tip(cheltuiala_modified), "Altele") == 0);

	undo(&buget);
	Cheltuiala* cheltuiala_restored = find_cheltuiala(&buget, 0);
	assert(strcmp(get_tip(cheltuiala_restored), "Mancare") == 0);
	
	undo(&buget);
	assert(get_lungime(buget.cheltuieli) == 0);
	destroy_buget(&buget);
	free(erori);

}