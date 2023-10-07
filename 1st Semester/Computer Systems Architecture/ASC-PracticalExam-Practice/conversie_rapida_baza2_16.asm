bits 32

global start

extern exit,printf,scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll


segment data use32 class=data
        numar dd 1001_1101_1111_1010_1011_0001_0101_1100b
        format_afisare db "%x", 0
        ; 9DFAB15Ch

segment code use32 class=code
        start:
               mov ebx, 8
               mov eax, [numar]
               rol eax, 4
               shifteaza:
                    mov ecx, 0000_0000_0000_0000_0000_0000_0000_1111b
                    mov edx, eax
                    and edx, ecx
                    push eax
                    push edx
                    push dword format_afisare
                    call [printf]
                    add esp, 4*2
                    pop eax
                    
                    rol eax, 4
                    dec ebx
                    cmp ebx, 0
                    je gata
                    jmp shifteaza
                    
                 gata:
               
             push dword 0
             call [exit]