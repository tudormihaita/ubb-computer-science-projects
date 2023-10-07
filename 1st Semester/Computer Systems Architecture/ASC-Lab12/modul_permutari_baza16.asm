bits 32

extern _n
extern _printf
extern _afisarePermutare16_C

global _asmPermutari16

segment data public data use32
        a dd 0
        nrcif dd 0
        putere16 dd 1
        mesaj db "Permutarile numarului dat in baza 16 sunt:",13,10,0
        format db "%x", 13, 10, 0

segment code public code use32
       _asmPermutari16:
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
                    mov eax, [putere16]
                    mov ebx, 16
                    mul ebx
                    mov [putere16], eax
                    loop calculeaza_putere
                    
                mov eax, [a]
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
                    
                    ;push eax
                    ;push dword format
                    ;call _printf
                    ;add esp, 4*2
                    
                    push eax
                    call _afisarePermutare16_C
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
