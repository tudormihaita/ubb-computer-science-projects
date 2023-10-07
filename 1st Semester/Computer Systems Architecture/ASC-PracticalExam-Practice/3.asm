bits 32

global start

extern exit,scanf,printf,gets
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import gets msvcrt.dll

;3.	Se citeste o propozitie de la tastatura. Sa se inverseze fiecare cuvant si sa se afiseze pe ecran.
segment data use32 class=data
        mesaj db "Introduceti propozitia de la tastatura:", 0
        format_citire db "%s", 0
        format_afisare db "%c", 0
        rand_nou db 13, 10, 0
        max_len equ 100
        propozitie times max_len+1 db 0
        cuvant times max_len+1 db 0
        propozitie1 db "ana are mere", 0
        caracter db 0
        len_propozitie db 0


segment code use32 class=code
        start:
            push dword mesaj
            call [printf]
            add esp, 4
            
            
            push dword propozitie
            ;push dword format_citire
            call [gets]
            add esp, 4
            
            
            ; push dword propozitie
            ; push dword format_citire
            ; call [printf]
            ; add esp, 4*2
            
            mov esi, propozitie
            cld
            ;mov edi, cuvant
            
            lungime:
                lodsb
                cmp al, 0
                je gata
                inc byte[len_propozitie]
                jmp lungime
                
            gata:
                
                mov esi, propozitie
                mov al, [len_propozitie]
                dec al
                movzx eax, al
                add esi, eax
                std
            
            repeta:
                ;mov al, [propozitie+esi]
                lodsb
                mov ebx, 0
                mov bl, al
                cmp bl, 0
                je final
                
                cmp bl, ' '
                je cuvant_nou
                
                ;stosb
                
                push dword ebx
                push dword format_afisare
                call [printf]
                add esp, 4*2
                jmp next
                
                cuvant_nou:
                    push dword rand_nou
                    push dword format_citire
                    call [printf]
                    add esp, 4*2
                    
                    ; afisare:
                        ; sub byte[len_curent], 1
                        ; mov eax, 0
                        ; lodsb
                        ; push eax
                        ; push dword format_citire
                        ; call [printf]
                        ; add esp, 4*2
                        
                        ; cmp byte[len_curent], 0
                        ; jne afisare
                        
                    
                 next:
                    ;inc esi
                    jmp repeta
                
            
            final:
            
        
        
            push dword 0
            call [exit]