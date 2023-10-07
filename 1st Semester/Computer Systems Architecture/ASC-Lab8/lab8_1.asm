bits 32 


global start        
; Sa se citeasca de la tastatura doua numere a si b (in baza 10) si sa se calculeze: (a+b) * (a-b). Rezultatul inmultirii se va salva in memorie in variabila "rezultat" (definita in segmentul de date).

extern exit, printf, scanf
import exit msvcrt.dll 
import printf msvcrt.dll 
import scanf msvcrt.dll   


segment data use32 class=data
    a dd 0
    b dd 0
    format db "%d %d", 0
    message db "rezultat = %lld", 0
    rezultat dq 0
    


segment code use32 class=code
    start:
        ;scanf(format,a,b)
        push dword b
        push dword a
        push dword format
        call [scanf]
        add esp, 4*3
        ;eax = a+b
        mov eax, [a]
        add eax, [b]
        ;ebx = a-b
        mov ebx, [a]
        sub ebx, [b]
        ;edx:eax = eax * ebx = (a+b) * (a-b)
        imul ebx
        ;rezultat = edx:eax
        mov [rezultat], eax
        mov [rezultat+4], edx
        ;printf(message,rezultat)
        push dword [rezultat+4]
        push dword [rezultat]
        push dword message
        call [printf]
        add esp, 4*3
        
    
        ; exit(0)
        push    dword 0    
        call    [exit]       
