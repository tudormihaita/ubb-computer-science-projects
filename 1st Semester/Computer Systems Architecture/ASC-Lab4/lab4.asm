bits 32

global start        


extern exit              
import exit msvcrt.dll  
;    exemplul folosit de mine:
;    a dw 0010110110110110b
;    b dw 0100111010110001b
;    c dd 0

segment data use32 class=data
    a dw 8a9fh
    b dw 0af9ah
    c dd 0
    
;Se dau cuvintele A si B. Sa se obtina dublucuvantul C:
;bitii 0-4 ai lui C coincid cu bitii 11-15 ai lui A
;bitii 5-11 ai lui C au valoarea 1
;bitii 12-15 ai lui C coincid cu bitii 8-11 ai lui B
;bitii 16-31 ai lui C coincid cu bitii lui A

segment code use32 class=code
    start:
    mov bx, 0
    mov ax, [a]
    and ax, 1111100000000000b ; izolez bitii 11-15 ai lui A
    mov cl, 11
    ror ax, cl ; rotim 11 pozitii spre dreapta pt ca bitii 0-4 ai lui C sa coincida cu 11-15 din A
    or bx, ax
    or bx, 0000111111100000b ; facem bitii 5-11 ai lui C sa aiba valoarea 1
    mov ax, [b]
    and ax, 0000111100000000b ; izolez bitii 8-11 ai lui B
    mov cl, 4
    rol ax, cl ; rotim 4 pozitii spre stanga pt ca bitii 12-15 ai lui C sa coincida cu 8-11 ai lui B
    or bx, ax
    mov dx, [a] ; bitii 16-31 ai lui C vor coincide cu bitii lui A
    mov ax, bx
    push dx
    push ax
    pop ebx      ; valoarea exemplului folosit de mine:
    mov [c], ebx ;  0010 1101 1011 0110 1110 1111 1110 0101
                 ;   2    D   B     6    E    F    E    5
        ; exit(0)
        push    dword 0    
        call    [exit] 
