bits 32 

global start        

extern exit       
import exit msvcrt.dll  

; a,b,c,d - byte                         
segment data use32 class=data
    ; ...
    a db 5
    b db 4
    c db 3
    d db 2
    x resb 1

; a + b - c + d - ( a - d )
segment code use32 class=code
    start:
        ; ...
        mov al, [a] ; al = a = 5
        add al, [b] ; al = al + b = a + b = 5 + 4 = 9
        sub al, [c] ; al = al - c = a + b - c = 9 - 3 = 6
        add al, [d] ; al = al + d = a + b - c + d = 6 + 2 = 8
        mov ah, [a] ; ah = a = 5
        sub ah, [d] ; ah = ah - d = a - d = 5 - 2 = 3
        sub al, ah  ; al = al - ah = a + b - c + d - (a - d) = 8 - 3 = 5
        mov [x], al ; x = al = 5
        
    
        ; exit(0)
        push    dword 0 
        call    [exit]       
