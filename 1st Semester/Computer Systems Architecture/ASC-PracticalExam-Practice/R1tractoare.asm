bits 32

global start

extern exit,printf,scanf,fopen,fread,fclose,perror
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import perror msvcrt.dll


segment data use32 class=data
        len_max equ 100
        len_max_cuvant equ 30
        fisier db "inputR1.txt", 0
        mod_fisier db "r", 0
        desc_fisier dd 0
        format_afisare db "Propozitia %d : %s Nr cuvinte: %d, Primul cuvant %s are %d litere", 13, 10, 0
        mesaj_eroare db "Continut fisier invalid!", 0
        cuvant times len_max_cuvant+1 db 0
        cuvant_inversat times len_max_cuvant+1 db 0
        propozitie times len_max+1 db 0
        buffer db 0
        nr_cuvinte dd 1
        nr_propozitii dd 0
        nr_caractere_propozitie dd 0
        nr_caractere_cuvant dd 0
        primul_cuvant_gasit db 0

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
            mov edi, 0
            
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
                
                mov [propozitie+edi], al
                inc edi
                inc dword [nr_caractere_propozitie]
                
                cmp al, ' '
                je cuvant_nou
                
                cmp byte[primul_cuvant_gasit], 0
                je adauga_caracter
                jmp mai_vedem
                
                
                adauga_caracter:
                     mov [cuvant+esi], al
                     inc esi
                     inc dword [nr_caractere_cuvant]
                
                mai_vedem:
                
                jmp mai_departe
                
                cuvant_nou:
                    mov byte[primul_cuvant_gasit], 1
                    inc dword[nr_cuvinte]
                    jmp mai_departe
                    
                     
                mai_departe:
                    cmp al, '.'
                    je propozitie_noua
                    
                    jmp inainte
                    
                propozitie_noua:
                       inc dword [nr_propozitii]
                       mov esi, cuvant
                       add esi, [nr_caractere_cuvant]
                       dec esi
                       
                       mov edi, cuvant_inversat
                       
                       mov ecx, [nr_caractere_cuvant]
                       std
                       inverseaza:
                            lodsb
                            cld
                            stosb
                            std
                       loop inverseaza
                       
                       push dword [nr_caractere_cuvant]
                       push dword cuvant_inversat
                       push dword [nr_cuvinte]
                       push dword propozitie
                       push dword [nr_propozitii]
                       push dword format_afisare
                       call [printf]
                       add esp, 4*6
                       
                       
                      mov esi, 0
                      mov ebx, [nr_caractere_cuvant]
                      
                      goleste_cuvant:
                            mov al, [cuvant+esi]
                            cmp al, 0
                            je gol
                            mov byte[cuvant+esi], 0
                            mov byte[cuvant_inversat+esi], 0
                            inc esi
                            dec ebx
                            cmp ebx, 0
                            je gol
                            jmp goleste_cuvant
                            
                            
                      gol:
                        mov esi, 0
                        mov ebx, [nr_caractere_propozitie]
                        
                        goleste_propozitie:
                            mov al, [propozitie+esi]
                            cmp al, 0
                            je prop_goala
                            mov byte[propozitie+esi], 0
                            inc esi
                            dec ebx
                            cmp ebx, 0
                            je prop_goala
                            jmp goleste_propozitie
                            
                       prop_goala:
                            mov esi, 0
                            mov edi, 0
                            mov dword[nr_cuvinte], 1
                            mov byte[primul_cuvant_gasit], 0
                            mov dword [nr_caractere_cuvant], 0
                            mov dword [nr_caractere_propozitie], 0
                       jmp go
                      inainte:
                          go:
                       jmp citire
                       
                            
             continua:
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