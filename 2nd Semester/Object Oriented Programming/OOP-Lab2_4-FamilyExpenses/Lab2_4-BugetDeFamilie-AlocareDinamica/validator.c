#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "validator.h"
#include "cheltuiala.h"

void valideaza_cheltuiala(Cheltuiala* cheltuiala, char* string_erori) {
	int zi_cheltuiala = get_zi(cheltuiala);
	double suma_cheltuiala = get_suma(cheltuiala);

	char string_validari[90];
	strcpy(string_validari, "");

	if (zi_cheltuiala <= 0 || zi_cheltuiala > 31)
		strcat(string_validari, "Zi invalida!\n");

	if (suma_cheltuiala <= 0)
		strcat(string_validari, "Suma invalida!\n");

	int valid = 0;
	char tipuri_valide[6][30] = { "Mancare", "Transport", "Telefon&Internet", "Imbracaminte", "Altele" };
	for (int i = 0; i < 5 && valid == 0; i++)
		if (strcmp(get_tip(cheltuiala), tipuri_valide[i]) == 0)
			valid = 1;
	if (valid == 0)
		strcat(string_validari, "Tip invalid!\n");

	strcpy(string_erori, string_validari);

}

int valideaza_zi(int zi) {
	if (zi <= 0 || zi > 31)
		return -1;
	else
		return 0;
}

int valideaza_suma(double suma) {
	if (suma <= 0)
		return -2;
	else
		return 0;
		
}

int valideaza_tip(char* tip) {
	char tipuri_valide[6][30] = { "Mancare", "Transport", "Telefon&Internet", "Imbracaminte", "Altele" };
	for (int i = 0; i < 5; i++)
		if (strcmp(tip, tipuri_valide[i]) == 0)
			return 0;
	return -3;
			
}	
