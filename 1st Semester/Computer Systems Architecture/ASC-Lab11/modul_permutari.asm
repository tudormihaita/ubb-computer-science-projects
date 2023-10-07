bits 32 
       
global permutari

extern exit,printf  

import exit msvcrt.dll
import printf msvcrt.dll 


segment data use32 class=data
    numar dd 0
    format db "%x", 13,10,0


segment code use32 class=public
    permutari:
        mov eax, [esp+4]
        mov ebx, [eax]
        mov [numar], ebx
        
        
        generare:
            ror ebx, 4
            
            push ebx
            push format
            call [printf]
            add esp, 4*2
            
            cmp ebx, dword [numar]
            je final
            
            jmp generare
            
            final:
                ret 4
                push dword 0     
                call [exit]      