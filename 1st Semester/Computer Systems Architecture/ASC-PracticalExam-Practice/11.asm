bits 32

global start

extern exit,printf,scanf,fopen,fclose,perror,fprintf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import perror msvcrt.dll

;11. Se citesc cuvinte de la tastatura, sa se creeze un fisier cu numele primului .txt si restul sa se afiseze in acest fisier cu literele inversate
segment data use32 class=data
    max_len_cuvant equ 30
    mesaj db "Introduceti numele fisierului, urmat de o serie de cuvinte: ", 0
    mesaj_eroare db "Fisierul nu exista sau continutul este invalid!", 0
    format_citire db "%s", 0
    format_invers db "%c", 0
    spatiu db " ", 0
    fisier times max_len_cuvant+1 db 0
    cuvant times max_len_cuvant+1 db 0
    mod_fisier db "w", 0
    desc_fisier dd 0
    len_cuvant dd 0
    

segment code use32 class=code
        start:
               push dword mesaj
               call [printf]
               add esp, 4
               
               push dword fisier
               push dword format_citire
               call [scanf]
               add esp, 4*2
               
               push dword mod_fisier
               push dword fisier
               call [fopen]
               add esp, 4*2
               
               cmp eax, 0
               je eroare
               
               mov [desc_fisier], eax
               
               citeste:
                    push dword cuvant
                    push dword format_citire
                    call [scanf]
                    add esp, 4*2
                    
                    mov al, [cuvant]
                    cmp al, '#'
                    je gata
                    
                mov dword [len_cuvant], 0
                mov esi, cuvant
                cld
                parcurge:
                   lodsb
                   cmp al, 0
                   je next
                   inc dword[len_cuvant]
                   jmp parcurge
                   
                next:
                    ; mov esi, cuvant
                    ; add esi, [len_cuvant]
                    ; sub esi, 1
                    ; std
                    
                    mov esi, [len_cuvant]
                    dec esi
                    mov ebx, [len_cuvant]
                    invers:
                        mov eax, 0
                        ;lodsb
                        mov al, [cuvant+esi]
                        
                        push eax
                        push dword format_invers
                        push dword [desc_fisier]
                        call [fprintf]
                        add esp, 4*3
                        
                        ; push dword spatiu
                        ; push dword format_citire
                        ; push dword [desc_fisier]
                        ; call [fprintf]
                        ; add esp, 4*3
                        
                        dec esi
                        dec ebx
                        cmp ebx, 0
                        jne invers
                        
                     mov ebx, [len_cuvant]
                     mov esi, 0
                     cld
                     golire:
                        mov al, [cuvant+esi]
                        cmp al, 0
                        je gol
                        mov [cuvant+esi], byte 0
                        inc esi
                        jmp golire
                        
                     
                gol:
                    push dword spatiu
                    push dword format_citire
                    push dword [desc_fisier]
                    call [fprintf]
                    add esp, 4*3
                    
                    jmp citeste
                gata:       
               
               jmp final
        
            eroare:
                push dword mesaj_eroare
                call [perror]
                add esp, 4
        
            final:
            push dword 0
            call [exit]