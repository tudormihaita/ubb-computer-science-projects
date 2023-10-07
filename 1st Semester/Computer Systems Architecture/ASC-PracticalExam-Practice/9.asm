bits 32

global start

extern exit,printf,scanf,fopen,fclose,fprintf,fscanf,fread,perror
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import fscanf msvcrt.dll
import fread msvcrt.dll
import perror msvcrt.dll

;9.	De la tastatura se citeste un nume de fisier input. Se creaza un alt fisier de output in care se pune continutul fisierului de input su toate caracterele mici schimbate cu codul lor ascii.
segment data use32 class=data
        len_max_fisier equ 30
        len_max equ 100
        input times len_max_fisier db 0
        mod_input db "r", 0
        desc_input dd 0
        output db "output9.txt", 0
        mod_output db "w", 0
        desc_output dd 0
        buffer db 0
        mesaj db "Introduceti numele fisierului de input: ", 0
        mesaj_eroare db "Fisierul nu exista!", 0
        mesaj_succes db "Fisierul a fost accesat cu succes!", 0
        format_citire db "%s", 0
        format_afisare db "%c", 0
        format_conversie db "%d", 0

segment code use32 class=code
        start:
             push dword mesaj
             call [printf]
             add esp, 4
             
             push dword input
             push dword format_citire
             call [scanf]
             add esp, 4*2
             
             push dword mod_input
             push dword input
             call [fopen]
             add esp, 4*2
             
             cmp eax, 0
             je eroare
             
             mov [desc_input], eax
             
             push dword mesaj_succes
             call [printf]
             add esp, 4
             
             
             push dword mod_output
             push dword output
             call [fopen]
             add esp, 4*2
             
             cmp eax, 0
             je eroare
             
             mov [desc_output], eax
             
             repeta:
                push dword [desc_input]
                push dword 1
                push dword 1
                push dword buffer
                call [fread]
                add esp, 4*4
                
                cmp eax, 0
                je continua
                
                mov eax, 0
                mov al, [buffer]
                cmp al, 'a'
                jb next
                
                cmp al, 'z'
                ja next
                
                ;inlocuieste cu cod ascii
                
                ;push dword [buffer]
                push eax
                push dword format_conversie
                push dword [desc_output]
                call [fprintf]
                add esp, 4*3
                jmp mai_departe
                
                next:
                    ;push dword [buffer]
                    push eax
                    push dword format_afisare
                    push dword [desc_output]
                    call [fprintf]
                    add esp, 4*3
                    
                    
                mai_departe:
                jmp repeta
                
                
              continua:
              push dword [desc_input]
              call [fclose]
              add esp, 4
              
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