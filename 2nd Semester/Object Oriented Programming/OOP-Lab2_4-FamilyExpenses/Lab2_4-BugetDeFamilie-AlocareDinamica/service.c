#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include "service.h"
#include "repository.h"
#include "validator.h"

Buget create_buget() {
	Buget buget;
	buget.cheltuieli = create_empty(destroy_cheltuiala);
	buget.undo_list = create_empty(destroy_vector);
	return buget;
}


int add_cheltuiala(Buget* buget, int zi, double suma, char* tip, char* erori) {
	Cheltuiala* cheltuiala = create_cheltuiala(zi, suma, tip);
	strcpy(erori, "");

	valideaza_cheltuiala(cheltuiala, erori);
	if (strlen(erori) == 0) {
		Vector* lista_to_undo = copy_vector(buget->cheltuieli, copy_cheltuiala);
		add_element(buget->cheltuieli , cheltuiala);
		add_element(buget->undo_list, lista_to_undo);
		return 0;}
	else {
		destroy_cheltuiala(cheltuiala);
		return -1;
	}
}

Cheltuiala* find_cheltuiala(Buget* buget, int id) {
	if (id < 0 || id >= get_size(buget->cheltuieli))
		return NULL;
	else
		return (Cheltuiala*)get_element(buget->cheltuieli, id);
}


int delete_cheltuiala(Buget* buget, int id) {
	if (find_cheltuiala(buget, id) == NULL) {
		return -1;}
	else {
		Vector* lista_to_undo = copy_vector(buget->cheltuieli, copy_cheltuiala);
		add_element(buget->undo_list, lista_to_undo);

		Cheltuiala* cheltuiala_deleted = delete_element(buget->cheltuieli, id);
		destroy_cheltuiala(cheltuiala_deleted);
		return 0;
	}
}


int modify_cheltuiala(Buget* buget, int id, int zi, double suma, char* tip, char* erori) {
	strcpy(erori, "");

	if (find_cheltuiala(buget, id) == NULL) {
		strcpy(erori, "Pozitie/Id cheltuiala invalid!\n");
		return -2;
	}

	Cheltuiala* cheltuiala_new = create_cheltuiala(zi, suma, tip);
	valideaza_cheltuiala(cheltuiala_new, erori);

	if (strlen(erori) == 0) {
		Vector* lista_to_undo = copy_vector(buget->cheltuieli, copy_cheltuiala);
		add_element(buget->undo_list, lista_to_undo);

		Cheltuiala* cheltuiala_modified = set_element(buget->cheltuieli, id, cheltuiala_new);
		destroy_cheltuiala(cheltuiala_modified);
		return 0;}
	else {
		destroy_cheltuiala(cheltuiala_new);
		return -1;
	}
}


int get_lungime(Vector* vector) {
	return get_size(vector);
}


Vector* get_all_cheltuieli(Buget* buget) {
	return copy_vector(buget->cheltuieli, copy_cheltuiala);
}


int filtru_zi(Cheltuiala* cheltuiala_verificata, void* zi) {
	int zi_filtru = *((int*)zi);
	if (get_zi(cheltuiala_verificata) == zi_filtru)
		return 1;
	else
		return 0;
}


int filtru_suma_minima(Cheltuiala* cheltuiala_verificata, void* suma) {
	double suma_minima_filtru = *((double*)suma);
	if (get_suma(cheltuiala_verificata) <= suma_minima_filtru)
		return 1;
	else
		return 0;
}


int filtru_suma_maxima(Cheltuiala* cheltuiala_verificata, void* suma) {
	double suma_maxima_filtru = *((double*)suma);
	if (get_suma(cheltuiala_verificata) > suma_maxima_filtru)
		return 1;
	else
		return 0;
}


int filtru_tip(Cheltuiala* cheltuiala_verificata, void* tip) {
	char* tip_filtru = (char*)tip;
	if (strcmp(get_tip(cheltuiala_verificata), tip_filtru) == 0)
		return 1;
	else
		return 0;
}


//Vector* filter_cheltuieli_proprietate(Buget* buget, char* proprietate_filtru, int (*proprietate)(Cheltuiala* , char*));

Vector* filter_cheltuieli_proprietate(Buget* buget, void* proprietate_filtru, FilterFct filtru) {
	Vector* lista_filtrata = create_empty(destroy_cheltuiala);
	for (int i = 0; i < get_size(buget->cheltuieli); i++)
		if (filtru(get_element(buget->cheltuieli, i), proprietate_filtru) == 0) {
			Cheltuiala* c = get_element(buget->cheltuieli, i);
			add_element(lista_filtrata, create_cheltuiala(c->zi, c->suma, c->tip));
		}
	return lista_filtrata;

}


int compare_suma(Cheltuiala* c1, Cheltuiala* c2, bool reversed) {
	if(reversed==false)
		return (get_suma(c1) > get_suma(c2));
	else
		return (get_suma(c1) < get_suma(c2));
}


int compare_tip(Cheltuiala* c1, Cheltuiala* c2, bool reversed) {
	if(reversed==false)
		return (strcmp(get_tip(c1), get_tip(c2)) > 0);
	else
		return (strcmp(get_tip(c1), get_tip(c2)) < 0);
}

//void sort_cheltuieli(Buget* buget, bool reversed, int (*compare)(Cheltuiala*, Cheltuiala*, bool));

Vector* sort_cheltuieli(Vector* lista, bool reversed, CompareFct cmp) {
	//qsort(vector, get_size(*vector), sizeof(Cheltuiala), compare);
	Vector* lista_sortata = copy_vector(lista, copy_cheltuiala);
	int sorted = 0;
	int i;
	while (!sorted) {
		sorted = 1;
		for (i = 0; i < get_size(lista_sortata)-1; i++) {
			if (cmp(get_element(lista_sortata, i), get_element(lista_sortata, i + 1), reversed)) {
				sorted = 0;
				exchange_elements(lista_sortata, i, i + 1);
			}
		}

	}
	return lista_sortata;
}


int undo(Buget* buget) {
	if (get_size(buget->undo_list) == 0)
		return 0;
	Vector* lista_cheltuieli_restored = delete_element(buget->undo_list, buget->undo_list->size - 1);
	destroy_vector(buget->cheltuieli);
	buget->cheltuieli = lista_cheltuieli_restored;
	return 1;
}


void destroy_buget(Buget* buget) {
	destroy_vector(buget->cheltuieli);
	destroy_vector(buget->undo_list);
}
