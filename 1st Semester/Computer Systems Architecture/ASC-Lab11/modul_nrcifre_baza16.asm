bits 32

global nr_cifre16

extern exit
import exit msvcrt.dll


segment data use32 class=data


segment code use32 class=public
        nr_cifre16:
            ;preia de pe stiva valoarea numarului, transmis prin referinta
            mov eax, [esp+4]
            mov ebx, [eax]
            mov eax, 0
            
            ;calculeaza numarul de cifre ale numarului in baza 16 si pune valoarea in eax
            numara_cifre:
                inc eax
                shr ebx, 4
                cmp ebx, 0
                jne numara_cifre
                
            ret 4
        
        
                push dword 0
                call [exit]