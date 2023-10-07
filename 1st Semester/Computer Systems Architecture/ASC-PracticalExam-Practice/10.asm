bits 32

global start

extern exit, printf, scanf, fopen, fclose, perror, fprintf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import perror msvcrt.dll

;10. Se citeste de la tastatura m,n apoi m numere zecimale, pe linii diferite. Sa se afiseze nr cu cel putin n cifre pare in output.txt.
segment data use32 class=data
        output db "output10.txt", 0
        mod_output db "w", 0
        desc_output dd 0
        mesaj_citire db "Introduceti valorile lui  m si n:", 0
        mesaj_eroare db "Fisierul nu are continut sau nu exista!", 0
        format_citire db "%d %d", 0
        format_nr db "%d", 0
        rand_nou db 13, 10, 0
        m dd 0
        n dd 0
        nr dd 0
        cifre_pare dd 0
        

segment code use32 class=code
        start:
            
            push dword mesaj_citire
            call [printf]
            add esp, 4
            
            push dword n
            push dword m
            push dword format_citire
            call [scanf]
            add esp, 4*3
            
            push dword mod_output
            push dword output
            call [fopen]
            add esp, 4*2
            
            cmp eax, 0
            je eroare
            
            mov [desc_output], eax
            
            mov ebx, [m]
            citire:
            
                push dword nr
                push dword format_nr
                call [scanf]
                add esp, 4*2
                
                mov dword[cifre_pare], 0
                mov eax, [nr]
                parcurgere:
                    mov edx, 0
                    mov ecx, 10
                    div ecx
                    test edx, 1
                    jz par
                    jmp mai_departe
                    
                    par:
                        inc dword [cifre_pare]
                        
                    mai_departe:
                        cmp eax, 0
                        jne parcurgere
                        
                 mov ecx, [cifre_pare]
                 cmp ecx, [n]
                 jae afiseaza
                 
                 jmp next
                 
                 afiseaza:
                    push dword [nr]
                    push dword format_nr
                    push dword [desc_output]
                    call [fprintf]
                    add esp, 4*3
                    
                    push dword rand_nou
                    push dword [desc_output]
                    call [fprintf]
                    add esp, 4*2
                    
                 next:
                    dec ebx
                    cmp ebx, 0
                    je continua
                
                    jmp citire
                 
            continua:
            
            push dword [desc_output]
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