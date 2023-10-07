bits 32

extern _n
extern _printf
extern _afisarePermutare10_C

global _asmPermutari10

segment data public data use32
        a dd 0
        nrcif dd 0
        putere10 dd 1
        mesaj db "Permutarile numarului dat in baza 10 sunt:",13,10,0
        format db "%d", 13, 10, 0

segment code public code use32
       _asmPermutari10:
            ;cod de intrare
            push ebp
            mov ebp, esp
            
            mov eax, [ebp+12]
            mov [nrcif], eax
            
            mov eax, [ebp+8]
            mov ebx, eax
            mov [a], ebx
            
            push dword mesaj
            call _printf
            add esp, 4*1
            
            
            mov ecx, [nrcif]
            dec ecx
            jecxz final
             calculeaza_putere:
                    mov eax, [putere10]
                    mov ebx, 10
                    mul ebx
                    mov [putere10], eax
                    loop calculeaza_putere
                    
                mov eax, [a]
                generare:
                    mov edx, 0
                    mov ecx, 10
                    div ecx
                    mov ebx, eax
                    mov eax, [putere10]
                    mov ecx, edx
                    mov edx, 0
                    mul ecx
                    add eax, ebx
                    
                    push eax
                    
                    ;push eax
                    ;push dword format
                    ;call _printf
                    ;add esp, 4*2
                    
                    push eax
                    call _afisarePermutare10_C
                    add esp, 4*1
                    
                    pop eax
                    cmp eax, [a]
                    je gata
                    
                    jmp generare
                    
                    gata:
                
                final:
                    ;add esp, 4
                    mov esp, ebp
                    pop ebp
                    ret
