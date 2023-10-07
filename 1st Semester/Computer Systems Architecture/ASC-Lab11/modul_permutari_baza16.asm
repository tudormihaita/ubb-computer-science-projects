bits 32

global permutari_baza16

extern exit,printf,scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll


segment data use32 class=data
        nr16 dd 0
        nr_cifre16 dd 0
        putere16 dd 1
        format db "%x", 0
        format_afisare db "%x", 13, 10, 0
        mesaj_citire db "Introduceti numarul dorit in baza 16: ", 0
        mesaj_afisare db "Permutarile cifrelor numarului dat sunt: :", 13, 10, 0

segment code use32 class=code
        permutari_baza16:
            mov eax, [esp+8]
            mov ebx, [eax]
            
            mov [nr16], ebx
            
            mov eax, [esp+4]
            mov ebx, [eax]
            
            mov [nr_cifre16], ebx
            
                mov ecx, [nr_cifre16]
                dec ecx
                jecxz final
                calculeaza_putere:
                    mov eax, [putere16]
                    mov ebx, 16
                    mul ebx
                    mov [putere16], eax
                    loop calculeaza_putere
                    
                mov eax, [nr16]
                generare:
                    mov edx, 0
                    mov ecx, 16
                    div ecx
                    mov ebx, eax
                    mov eax, [putere16]
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
                    cmp eax, [nr16]
                    je gata
                    
                    jmp generare
                    
                    gata:
        
            final:
            ret 8
            push dword 0
            call [exit]