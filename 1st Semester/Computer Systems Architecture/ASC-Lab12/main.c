#include <stdio.h>

int asmPermutari16(int n, int nrcifre);
int asmPermutari10(int n, int nrcifre);

int nrCifre_baza16(int n){
    int nr=0;
    while(n){
        n/=16;
        nr++;
    }
    return nr;
}

int nrCifre_baza10(int n){
    int nr=0;
    while(n){
        n/=10;
        nr++;
    }
    return nr;
}

int n,cifre10,cifre16;


//Se da un numar a reprezentat pe 32 biti fara semn. Se cere sa se afiseze reprezentarea in baza 16 a lui a, precum si rezultatul permutarilor circulare ale cifrelor sale.
int main()
{
    printf("Introduceti numarul dorit in baza 10:");
    scanf("%d", &n);
    
    printf("Valoarea numarului dat in baza 10 este: %d\n", n);
    printf("Valoarea numarului dat in baza 16 este: %x\n", n);

    //Calcularea numarului de cifre ale numarului dat in baza 10 si in baza 16
    cifre10=nrCifre_baza10(n);
    cifre16=nrCifre_baza16(n);
    
    //apelul modulelor asm in care se calculeaza si afiseaza permutarile circulare ale cifrelor numarului in baza 16 si in baza 10
    asmPermutari16(n,cifre16);
    printf("\n");
    asmPermutari10(n,cifre10);
    
    return 0;
}

//functie de afisare a unei permutari in baza 10 ce va fi apelata in modulul asm
void afisarePermutare10_C(int x){
    printf("%d ", x);
}

//functie de afisare a unei permutari in baza 16 ce va fi apelata in modulul asm
void afisarePermutare16_C(int x){
    printf("%x ", x);
}