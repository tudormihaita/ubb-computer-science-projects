bits 32 

global start        

extern exit               
import exit msvcrt.dll    

; 2 + 8                          
segment data use32 class=data
    ;a db 2
    ;b db 8
    x resb 1

segment code use32 class=code
    start:
        mov al, 2 ; al = 2
        add al, 8 ; al = al + 8 = 10
        mov [x], al ; x = al = 10
        ; exit(0)
        push    dword 0 
        call    [exit]       
