bits 32

global start

extern exit,fopen,fscanf,printf,fclose,perror
import exit msvcrt.dll
import printf msvcrt.dll
import perror msvcrt.dll
import fopen msvcrt.dll
import fscanf msvcrt.dll
import fclose msvcrt.dll

;1.	Se dă un șir de 10 numere în baza 16 în fișierul input.txt.  Să se determine cifra minimă din fiecare număr. Să se afișeze acest șir al cifrelor minime, în baza 10, pe ecran.

segment data use32 class=data
        input db "input.txt", 0
        mod_input db "r", 0
        desc_input dd 0
        format db "%x", 0
        format_afisare db "%x", 13, 10, 0
        n dd 0
        cifmin dd 0Fh
        cifre times 10 dd 0

segment code use32 class=code
        start:
            ;fopen("input.txt", "r")
            push dword mod_input
            push dword input
            call [fopen]
            add esp, 4*2
            
            cmp eax, 0
            je final
            
            mov [desc_input], eax
            
            mov ebx, 10
            mov edi, 0
            
            repeta:
                
                push dword n
                push dword format
                push dword [desc_input]
                call [fscanf]
                add esp, 4*3
                
                ;push dword [n]
                ;push dword format_afisare
                ;call [printf]
                
                mov [cifmin], dword 0Fh
                mov eax, [n]
                mov edx, 0
                mov ecx, 16
                imparte:
                    div ecx
                    cmp edx, [cifmin]
                    jl actualizeaza 
                    jmp next
                    
                    actualizeaza:
                           mov [cifmin], dx
                    next:
                        mov edx, 0
                        cmp eax, 0
                        jne imparte
                    
                mov ecx, [cifmin]
                mov [cifre+edi], ecx
                add edi, 4
                
                push dword [cifmin]
                push dword format_afisare
                call [printf]
                add esp, 4*2
                
                dec ebx
                cmp ebx, 0
                jne repeta
                
            ; mov esi, 0
            ; afiseaza:
                  ; mov ebx, [cifre+esi]
                  ; push ebx
                  ; push dword format_afisare
                  ; call [printf]
                  ; add esp, 4*2
                  
                  ; add esi, 4
                  
               
            final:
            
                push dword [desc_input]
                call [fclose]
                add esp, 4
            push dword 0
            call [exit]