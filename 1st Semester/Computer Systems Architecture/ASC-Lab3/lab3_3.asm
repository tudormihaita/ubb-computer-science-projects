bits 32 

global start        

extern exit            
import exit msvcrt.dll    

; a,b,c,d - word                        
segment data use32 class=data
    ; ...
    a dw 5
    b dw 2
    c dw 3
    d dw 1
    x resw 1
 
; (a+a-c)-(b+b+d) = (5+5-3) - (2+2+1) = 7 - 5 = 2
segment code use32 class=code
    start:
        ; ...
        mov ax, [a] ; ax = a = 5
        add ax, [a] ; ax = ax + a = 5 + 5 = 10
        sub ax, [c] ; ax = ax - c = 10 - 3 = 7
        mov dx, [b] ; dx = b = 2
        add dx, [b] ; dx = dx + b = 2 + 2 = 4
        add dx, [d] ; dx = dx + d = 4 + 1 = 5
        sub ax, dx  ; ax = ax - dx = 7 - 5 = 2
        mov [x], ax ; x = ax = 2 
        ; exit(0)
        push    dword 0 
        call    [exit]       
