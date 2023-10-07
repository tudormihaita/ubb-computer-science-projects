bits 32 

global start        

; declare external functions needed by our program
extern exit             
import exit msvcrt.dll    
                          
; a,b,c,d - byte
; e,f,g,h - word
segment data use32 class=data
    a db 3
    d db 5
    g dw 25
    x resw 1

; (g+5)-a*d = ( 25 + 5 ) - 3 * 5 = 30 - 15 = 15
segment code use32 class=code
    start:
        mov ax, [g] ; ax = g = 25
        add ax, 5   ; ax = ax + 5 = g + 5 = 30
        push ax     ; valoarea lui ax este pusa pe stiva pt a elibera registrul pt operatia de inmultire care urmeaza  
        mov al, [a] ; al = a = 3
        mul byte[d] ; ax = al * d = 3 * 5 = 15
        pop dx      ; valoarea de pe stiva este pusa in registrul dx
        sub dx, ax  ; dx = dx - ax = 30 - 15 = 15
        mov [x], dx ; x = dx = 15
        
    
        ; exit(0)
        push    dword 0      
        call    [exit]       
