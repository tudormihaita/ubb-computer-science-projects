bits 32

global start

extern exit,printf,scanf,fopen,fclose,fprintf,fscanf,perror
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import fscanf msvcrt.dll
import perror msvcrt.dll

;citirea numelui unui fisier de la tastatura, citirea din fisier a unor cifre in baza 16 si numararea bitilor de 1 din reprezentarea binara a fiecarei cifre hexa citite.
segment data use32 class=data
    len_max_nume equ 30
    fisier times len_max_nume+1 db 0
    mod_fisier db "r", 0
    desc_fisier dd 0
    mesaj db "Introduceti numele fisierului de intrare:", 0
    mesaj_eroare db "Nume fisier invalid!", 0
    rand_nou db 13, 10, 0
    format_citire_fisier db "%s", 0
    format_cifre db "%x", 0
    format_biti db "%d", 0
    format_afisare db "%x - %d", 0
    cifra dd 0
    nr_biti dd 0
    


segment code use32 class=code
        start:
            push dword mesaj
            call [printf]
            add esp, 4
            
            push dword fisier
            push dword format_citire_fisier
            call [scanf]
            add esp, 4*2
            
            push dword mod_fisier
            push dword fisier
            call [fopen]
            add esp, 4*2
            
            cmp eax, 0
            je eroare
            
            mov [desc_fisier], eax
            
            citire:
                push dword cifra
                push dword format_cifre
                push dword [desc_fisier]
                call [fscanf]
                add esp, 4*3
                
                ;cmp byte[cifra], 0
                cmp eax, -1
                je gata
                
                ; push dword [cifra]
                ; push dword format_cifre
                ; call [printf]
                ; add esp, 4*2
                
                mov ebx, [cifra]
                mov ecx, 0
                
                numara_biti:
                    test bl, 1
                    jnz adauga
                    jmp next
                    
                    adauga:
                        inc ecx
                    next:
                        shr bl, 1
                        cmp bl, 0
                        je mai_departe
                        jmp numara_biti
                        
                    mai_departe:
                        push ecx
                        push dword [cifra]
                        push dword format_afisare
                        call [printf]
                        add esp, 4*3
                        
                        push dword rand_nou
                        call [printf]
                        add esp, 4
                        
                  jmp citire
                
            
            gata:
            push dword [desc_fisier]
            call [fclose]
            add esp, 4
            jmp final
            eroare:
                push dword mesaj_eroare
                call [perror]
                add esp, 4
               
        
            final:
            push dword 0
            call [exit]
            