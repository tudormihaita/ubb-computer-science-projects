bits 32


global start        


extern exit          
import exit msvcrt.dll 
                          

;a,b-byte; c-word; e-doubleword; x-qword - interpretare FARA semn
segment data use32 class=data
    a db 1
    b db 4
    c dw 2
    e dd 6
    x dq 2
    y resq 1
   
;(a+b*c+2/c)/(2+a)+e+x 
; a+b*c+2/c = 1 + 4*2 + 2/2 = 1 + 8 + 1 = 10
; 10 / (2+a) = 10 / 3 = 3 rest 1
segment code use32 class=code
    start:
        mov ax, 2
        mov dx, 0          ; DX:AX = 2
        div word[c] ; AX = DX:AX / c = 2/c
        mov bx, ax   ; BX = AX = 2/c
        mov al, [b]
        mov ah, 0 ; AX = b
        mul word[c] ; DX:AX = AX * c = b*c
        push dx
        push ax
        pop ecx      ; ECX = b*c
        mov al, [a]
        mov ah, 0    ; AX = a
        mov dx, 0
        push dx
        push ax
        pop eax  ; EAX = a
        add ecx, eax ; ECX = ECX + EAX = b*c + a
        mov ax, bx
        mov dx, 0
        push dx
        push ax
        pop eax  ; EAX = 2/c
        add ecx, eax ; ECX = ECX + EAX = b*c + a + 2/c
        mov eax, ecx
        mov edx, 0          ; EDX:EAX = b*c + a + 2/c
        mov ecx, eax
        mov ebx, edx ; EBX:ECX = EDX:EAX
        mov al, 2
        add al, [a]
        mov ah, 0
        mov dx, 0
        push dx
        push ax
        pop eax  ; EAX = 2+a
        push eax
        mov eax, ecx
        mov edx, ebx ; EDX:EAX = EBX:ECX
        pop ebx ; EBX = 2+a
        div ebx ; EAX = EDX:EAX / EBX = (a+b*c+2/c)/(2+a)
        ;+e+x 
        add eax, [e]
        mov edx, 0
        add eax, [x]
        adc edx, [x+4]
        mov [y], eax
        mov [y+4], edx
        ; exit(0)
        push    dword 0      
        call    [exit]       
