bits 32

global start

extern exit,printf,scanf,fopen,fclose,fread,perror
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import perror msvcrt.dll


;MODIFICA: FOLOSESTE XLAT CU O TABELA DE TRANSLATIE CORESPUNZATOARE CARACTERELOR CRIPTATE: CDEFGHI...ZABCD SI ASOCIAZA FIECARUI CARACTER CEL
;CORESPUNZATOR!!
segment data use32 class=data
        max_len equ 100
        fisier db "r2.txt", 0
        mod_fisier db "r", 0
        desc_fisier dd 0
        buffer db 0
        mesaj_eroare db "Continut fisier invalid!", 0
        format_afisare1 db "Numele fisierului dat este %s si fisierul contine: %s", 13, 10, 0
        format_afisare2 db "Mesajul original este: %s", 13, 10, 0
        mesaj_criptat times max_len+1 db 0
        mesaj_original times max_len+1 db 0
        len_mesaj db 0

segment code use32 class=code
        start:
            push dword mod_fisier
            push dword fisier
            call [fopen]
            add esp, 4*2
            
            cmp eax, 0
            je eroare
            
            mov [desc_fisier], eax
            mov esi, 0
            
            citire:
                push dword [desc_fisier]
                push dword 1
                push dword 1
                push dword buffer
                call [fread]
                add esp, 4*4
                
                cmp eax, 0
                je continua
                
                mov eax, 0
                mov al, [buffer]
                mov bl, [buffer]
                sub bl, 3
                
                mov [mesaj_criptat+esi], al
                
                cmp al, 'a'
                jae verificare_litera_mica
                jmp verifica_majuscula
                
                verificare_litera_mica:
                    cmp al, 'z'
                    jbe litera_mica
                    jmp verifica_majuscula
                    
                verifica_majuscula:
                      cmp al, 'A'
                      jae verificare_litera_mare
                      jmp alt_caracter
                      
               verificare_litera_mare:
                        cmp al, 'Z'
                        jbe litera_mare
                        jmp alt_caracter
                
                alt_caracter:
                     mov [mesaj_original+esi], al
                     inc esi
                     jmp next
                
                
                litera_mica:
                cmp bl, 'a'
                jb de_la_capat_mica
                
                jmp caracter_valid
                
                de_la_capat_mica:
                     mov cl, 'a'
                     sub cl, bl
                     mov bl, 'z'
                     sub bl, cl
                     add bl, 1
                     mov al, bl
                     jmp caracter_valid
                     
               litera_mare:
                    cmp bl, 'A'
                    jb de_la_capat_mare
                
                jmp caracter_valid
                
                de_la_capat_mare:
                     mov cl, 'A'
                     sub cl, bl
                     mov bl, 'Z'
                     sub bl, cl
                     add bl, 1
                     mov al, bl
                     jmp caracter_valid
                     
                caracter_valid:
                    mov al, bl
                    mov [mesaj_original+esi], al
                    inc esi
                    
                    
                    next:
                        jmp citire
                    
             continua:
                    push dword mesaj_criptat
                    push dword fisier
                    push dword format_afisare1
                    call [printf]
                    add esp, 4*3
                    
                    push dword mesaj_original
                    push dword format_afisare2
                    call [printf]
                    add esp, 4*2
                    
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