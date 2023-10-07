bits 32

global start

extern exit,printf,scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll


;13.	Se citeste de la tastatura un cuvant (sir de caractere de maxim 20 de caractere) si un numar reprezentat pe un octet. Daca numarul este impar se cere criptarea cuvantului prin adunarea la fiecare caracter a numarului citit modulo 20. Daca numarul este par se cere criptarea cuvantului prin adaugarea dupa fiecare consoana a gruparii "p"+consoana. Se cere afisarea cuvantului criptat

segment data use32 class=data
    len_max equ 20
    cuvant times len_max+1 db 0
    cuvant_criptat times 2*len_max+1 db 0
    mesaj_cuvant db "Introduceti un cuvant: ", 0
    format_cuvant db "%s", 0
    mesaj_numar db "Introduceti un numar: ", 0
    mesaj_afisare db "Cuvantul criptat este: %s", 13, 10, 0
    vocale db 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U', 0
    format_numar db "%d", 0
    nr dd 0

segment code use32 class=code
        start:
                push dword mesaj_cuvant
                call [printf]
                add esp, 4
                
                push dword cuvant
                push dword format_cuvant
                call [scanf]
                add esp, 4*2
                
                push dword mesaj_numar
                call [printf]
                add esp, 4
                
                push dword nr
                push dword format_numar
                call [scanf]
                add esp, 4*2
                
                mov eax, [nr]
                test al, 1
                jz par
                
                ;impar
                mov esi, 0
                
                cripteaza:
                    mov cl, [cuvant+esi]
                    cmp cl, 0
                    je gata
                    mov eax, [nr]
                    mov bl, 20
                    div bl
                    add [cuvant+esi], ah
                    mov dl, [cuvant+esi]
                    mov [cuvant_criptat+esi], dl
                    inc esi
                    jmp cripteaza
                  

             par:
                mov esi, 0
                mov ecx, 0
                
                criptare:
                    mov bl, [cuvant+esi]
                    cmp bl, 0
                    je gata
                    mov edi, 0
                    cauta_vocala:
                        cmp bl, [vocale+edi]
                        je gasit
                        mov dl, [vocale+edi]
                        cmp dl, 0
                        je stop
                        inc edi
                        jmp cauta_vocala
                        
                stop:
                    mov [cuvant_criptat+ecx], bl
                    inc ecx
                    mov dl, 'p'
                    mov [cuvant_criptat+ecx], dl
                    inc ecx
                    mov [cuvant_criptat+ecx], bl
                    inc ecx
                    jmp mai_departe
              
              gasit:
                    mov [cuvant_criptat+ecx], bl
                    inc ecx
                    
              mai_departe:
                    inc esi
                    jmp criptare
                  
             gata:
                push dword cuvant_criptat
                push dword mesaj_afisare
                call [printf]
                add esp, 4*2
             
             push dword 0
             call [exit]