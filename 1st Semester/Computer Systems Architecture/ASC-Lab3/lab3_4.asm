bits 32 

global start        

; declare external functions needed by our program
extern exit            
import exit msvcrt.dll  

; a,b,c - byte , d - word
segment data use32 class=data
    ; ...
    a db 4
    b db 3
    c db 2
    d dw 2
    x resb 1

 ; [(a*b)-d]/(b+c) = (4*3-2) / 5 = (12-2) / 5 = 10 / 5 = 2
segment code use32 class=code
    start:
        ; ...
        mov al, [a] ; al = a = 4
        mul byte[b] ; ax = al * b = 4 * 3 = 12
        sub ax, [d] ; ax = ax - d = 12 - 2 = 10
        mov dl, [b] ; dl = b = 3
        add dl, [c] ; dl = dl + c = 3 + 2 = 5
        div dl      ; al = ax / dl = 10 / 5 = 2 , ah = ax % dl = 10 % 5 =0
        mov [x], al ; x = al = 2
        
        ; exit(0)
        push    dword 0      
        call    [exit]       
