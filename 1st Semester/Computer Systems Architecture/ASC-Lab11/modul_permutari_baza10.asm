bits 32

global permutari_baza10

extern exit,printf,scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll


segment data use32 class=data
        nr dd 0
        nrcifre dd 0
        putere dd 1
        format1 db "%d", 0
        format_afisare db "%d", 13, 10, 0
        mesaj_citire db "Introduceti numarul dorit in baza 10: ", 0
        mesaj_afisare db "Permutarile cifrelor numarului dat sunt: :", 13, 10, 0
        mesaj_cifre db "Numarul dat are %d cifre", 13, 10, 0

segment code use32 class=public
        ;jmp permutari_baza10
        ; nr_cifre10:
            ;mov eax, [esp+4]
            ;mov ebx, [eax]
            
            ; mov eax, ebx
            ; .numar_cifre:
                ; mov edx, 0
                ; mov ebx, 10
                ; div ebx
                ; inc dword [esp+12]
                ; cmp eax, 0
                ; jne .numar_cifre
                
            ; mov eax, [esp+12]
            ; ret 4


        permutari_baza10:
            ;preluarea de pe stiva a parametrilor furnizati, valoarea numarului si numarul de cifre
            mov eax, [esp+8]
            mov ebx, [eax]
            
            mov [nr], ebx
            
            ;push dword nr
            ;call nr_cifre10
            ;add esp, 4*1
           
            
            mov eax, [esp+4]
            mov ebx, [eax]
            
            mov [nrcifre], ebx
            
                
                mov ecx, [nrcifre]
                dec ecx
                jecxz final
                
                ;calcularea puterii cu care va fi inmultita fiecare cifra pentru a forma o noua permutare prin mutarea pozitiei acesteia la inceputul numarului de fiecare data
                calculeaza_putere:
                    mov eax, [putere]
                    mov edx, 0
                    mov ebx, 10
                    mul ebx
                    mov [putere], eax
                    loop calculeaza_putere
                    
                ; push dword [putere]
                ; push dword format
                ; call [printf]
                ; add esp, 4*2
                
                ;mov ebx, [nr]
                mov eax, [nr]
                ;generarea permutarilor, pana cand se ajunge la valoarea initiala a numarului
                generare:
                    mov edx, 0
                    mov ecx, 10
                    
                    div ecx
                    mov ebx, eax
                    mov eax, [putere]
                    mov ecx, edx
                    mov edx, 0
                    mul ecx
                    add eax, ebx
                    
                    push eax
                    
                    push eax
                    push dword format_afisare
                    call [printf]
                    add esp, 4*2
                    
                    pop eax
                    cmp eax, [nr]
                    je gata
                    
                    jmp generare
                    
                    gata:
        
            final:
            ret 8
            push dword 0
            call [exit]