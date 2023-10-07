#pragma warning (disable:4996)
#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "cheltuiala.h"


Cheltuiala* create_cheltuiala(int zi, double suma, char* tip) {
	Cheltuiala* cheltuiala = (Cheltuiala*)malloc(sizeof(Cheltuiala));
	if (cheltuiala) {
		int nrC = (int)strlen(tip) + 1;
		cheltuiala->tip = (char*)malloc(nrC * sizeof(char));

		if(cheltuiala->tip)
			strcpy(cheltuiala->tip, tip);
		cheltuiala->zi = zi;
		cheltuiala->suma = suma;
	}

	return cheltuiala;

}


Cheltuiala* copy_cheltuiala(Cheltuiala* cheltuiala) {
	return create_cheltuiala(cheltuiala->zi, cheltuiala->suma, cheltuiala->tip);
}


char* get_tip(Cheltuiala* cheltuiala) {
	return cheltuiala->tip;
}

int get_zi(Cheltuiala* cheltuiala) {
	return cheltuiala->zi;
}

double get_suma(Cheltuiala* cheltuiala) {
	return cheltuiala->suma;
}

void set_tip(Cheltuiala* cheltuiala, char* tip) {
	free(cheltuiala->tip);

	int nrC = (int)strlen(tip) + 1;
	cheltuiala->tip = malloc(nrC * sizeof(char));
	if(cheltuiala->tip)
		strcpy(cheltuiala->tip, tip);
}

void set_zi(Cheltuiala* cheltuiala, int zi) {
	cheltuiala->zi = zi;
}

void set_suma(Cheltuiala* cheltuiala,double suma) {
	cheltuiala->suma = suma;
}

void replace_cheltuiala(Cheltuiala* cheltuiala1, Cheltuiala* cheltuiala2) {
	set_tip(cheltuiala1, get_tip(cheltuiala2));
	set_zi(cheltuiala1, get_zi(cheltuiala2));
	set_suma(cheltuiala1, get_suma(cheltuiala2));
}

int compare_cheltuieli(Cheltuiala* cheltuiala1, Cheltuiala* cheltuiala2) {
	return(strcmp(get_tip(cheltuiala1), get_tip(cheltuiala2)) == 0 && get_zi(cheltuiala1) == get_zi(cheltuiala2) && fabs(get_suma(cheltuiala1) - get_suma(cheltuiala2)) < 0.0001);

}

void destroy_cheltuiala(Cheltuiala* cheltuiala) {
	cheltuiala->zi = -1;
	cheltuiala->suma = -1;
	free(cheltuiala->tip);
	free(cheltuiala);
}