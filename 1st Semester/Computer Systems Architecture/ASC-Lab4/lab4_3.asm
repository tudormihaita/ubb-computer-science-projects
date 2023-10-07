bits 32


global start        


extern exit          
import exit msvcrt.dll 
                          

;a,b-byte; c-word; e-doubleword; x-qword - interpretare CU semn
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
        cwd          ; DX:AX = 2
        idiv word[c] ; AX = DX:AX / c = 2/c
        mov bx, ax   ; BX = AX = 2/c
        mov al, [b]
        cbw ; AX = b
        imul word[c] ; DX:AX = AX * c = b*c
        push dx
        push ax
        pop ecx      ; ECX = b*c
        mov al, [a]
        cbw          ; AX = a
        cwde         ; EAX = a
        add ecx, eax ; ECX = ECX + EAX = b*c + a
        mov ax, bx
        cwde         ; EAX = 2/c
        add ecx, eax ; ECX = ECX + EAX = b*c + a + 2/c
        mov eax, ecx
        cdq          ; EDX:EAX = b*c + a + 2/c
        mov ecx, eax
        mov ebx, edx ; EBX:ECX = EDX:EAX
        mov al, 2
        add al, [a]
        cbw
        cwde ; EAX = 2+a
        push eax
        mov eax, ecx
        mov edx, ebx ; EDX:EAX = EBX:ECX
        pop EBX ; EBX = 2+a
        idiv EBX ; EAX = EDX:EAX / EBX = (a+b*c+2/c)/(2+a)
        ;+e+x 
        add eax, [e]
        cdq
        add eax, [x]
        adc edx, [x+4]
        mov [y], eax
        mov [y+4], edx
        ; exit(0)
        push    dword 0      
        call    [exit]       
