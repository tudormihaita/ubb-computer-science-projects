bits 32

global start

extern exit,printf,scanf
;extern permutari
extern nr_cifre16
extern nr_cifre10
extern permutari_baza10
extern permutari_baza16

import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

;Se da un numar a reprezentat pe 32 biti fara semn. Se cere sa se afiseze reprezentarea in baza 16 a lui a, precum si rezultatul permutarilor circulare ale cifrelor sale.
segment data use32 class=public
        a dd 1A2B3C4Dh
        n dd 0
        numar_cifre16 dd 0
        numar_cifre10 dd 0
        mesaj_citire db "Introduceti numarul dorit in baza 10:", 0
        mesaj db "Numarul dat are in baza 10 valoarea: %d", 13, 10, 0
        mesaj_cifre db "Numarul dat are %d cifre in baza 16", 13 , 10, 0
        format db "%d", 0
        afisare db "Numarul reprezentat in baza 16 este= %x ", 13, 10, 0
        mesaj_baza10 db "Permutarile circulare ale cifrelor numarului in baza 10 sunt:", 13, 10, 0
        mesaj_baza16 db "Permutarile circulare ale cifrelor numarului in baza 16 sunt:", 13, 10, 0
        format_afisare db "%x", 13, 10, 0

segment code use32 class=public
        start:
            ;afisarea mesajului pentru citirea unui numar de la tastatura in baza 10
            ;printf(mesaj_citire)
            push dword mesaj_citire
            call [printf]
            add esp, 4
        
            ;citirea cuvantului in format decimal
            ;scanf(format,&n)
            push dword n
            push dword format
            call [scanf]
            add esp, 4*2
            
            ;afisarea numarului citit in baza 10
            ;printf(mesaj, n)
            push dword [n]
            push dword mesaj
            call [printf]
            add esp, 4*2
            
            
            ;afisarea numarului citit in baza 16
            ;printf(afisare,n)
            push dword [n]
            push dword afisare
            call [printf]
            add esp, 4*2
            
            ;apelarea modulului asm in care se va calcula numarul de cifre ale numarului reprezentat in baza 16
            ;nr_cifre16(&n)
            push dword n
            call nr_cifre16
            
            mov [numar_cifre16], eax
            
            ;apelarea modulului asm in care se va calcula numarul de cifre ale numarului reprezentat in baza 10
            ;nr_cifre10(&n)
            push dword n
            call nr_cifre10
            
            mov [numar_cifre10], eax
            
            ; test afisare numar cifre in baza 16
            ; push dword [numar_cifre16]
            ; push dword mesaj_cifre
            ; call [printf]
            ; add esp, 4*2
            
            ;afisarea unui mesaj pentru permutarile circulare ale cifrelor numarului dat in baza 16
            ;printf(mesaj_baza16)
            push dword mesaj_baza16
            call [printf]
            add esp, 4
            
            ;apelul modulului asm in care se calculeaza si afiseaza permutarile numarului dat in baza 16
            ;permutari_baza16(&numar_cifre16, &n)
            push dword n
            push dword numar_cifre16
            call permutari_baza16
            
            ;afisarea unui mesaj pentru permutarile circulare ale cifrelor numarului dat in baza16
            ;printf(mesaj_baza10)
            push dword mesaj_baza10
            call [printf]
            add esp, 4
            
            ;apelul modulului asm in care se calculeaza si afiseaza permutarile numarului dat in baza 10
            ;permutari_baza10(&numar_cifre10, &n)
            push dword n
            push dword numar_cifre10
            call permutari_baza10
            
            push dword 0
            call [exit]