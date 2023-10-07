bits 32

global nr_cifre10

extern exit
import exit msvcrt.dll


segment data use32 class=data
       nrcifre dd 0

segment code use32 class=public
        nr_cifre10:
            ;preluarea de pe stiva a valorii numarului
            mov eax, [esp+4]
            mov ebx, [eax]
            
            mov eax, ebx
            ;calcularea numarului de cifre si stocarea rezultatului in eax
            numar_cifre:
                mov edx, 0
                mov ebx, 10
                div ebx
                inc dword [nrcifre]
                cmp eax, 0
                jne numar_cifre
                
            mov eax, [nrcifre]
            ret 4
        
        
                push dword 0
                call [exit]