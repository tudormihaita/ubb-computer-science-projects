bits 32 


global start        

extern exit              
import exit msvcrt.dll    
                          

;a - byte, b - word, c - double word, d - qword - Interpretare cu semn
segment data use32 class=data
    a db 4
    b dw 3
    c dd 1
    d dq 12
    x resq 1

;(d-b)-a-(b-c) = (12-3) - 4 - (3-1) = 9 - 4 - 2 = 5 - 2 = 3  
segment code use32 class=code
    start:
        mov ax, [b]
        cwde
        cdq
        mov ecx, [d]
        mov ebx, [d+4] ; EBX:ECX = d
        sub ecx, eax
        sbb ebx, edx   ; EBX:ECX = EBX:ECX - EDX:EAX = d-b
        ;mov [x], ecx
        ;mov [x+4], ebx
        mov al, [a]
        cbw ; AX = a
        cwde ; EAX = a
        cdq ; EDX:EAX = a
        sub ecx, eax
        sbb ebx, edx ;EBX:ECX = EBX:ECX - EDX:EAX = (d-b) - a
        mov ax, [b]
        cwde ; EAX = b
        sub eax, [c] ; EAX = EAX - c = b - c
        cdq ; EDX:EAX = b - c 
        sub ecx, eax
        sbb ebx, edx ; EBX:ECX = EBX:ECX - EDX:EAX = (d-b) - a - (b-c)
        mov [x], ecx
        mov [x+4], ebx
        ;push ebx
        ;push ecx  - am vrut sa verific daca rezultatul este cel corect, asa ca am pus valoarea obtinuta in varful stivei sa o compar
        ;             cu cea pusa in adresa de memorie :)
    
        ; exit(0)
        push    dword 0     
        call    [exit]       
