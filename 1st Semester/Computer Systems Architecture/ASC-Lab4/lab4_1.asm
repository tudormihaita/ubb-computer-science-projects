bits 32


global start        


extern exit              
import exit msvcrt.dll    
                          

;a - byte, b - word, c - double word, d - qword - Interpretare fara semn
segment data use32 class=data
    a db 5
    b dw 3
    c dd 2
    d dq 6
    x resq 1

;(d+d)-a-b-c = 12 - 5 - 3 - 2 = 7 - 3 - 2 = 4 - 2 = 2
segment code use32 class=code
    start:
    mov eax, 0
    mov edx, 0
    add eax, [d]
    adc edx, [d+4] ; EDX:EAX = d
    add eax, [d]
    adc edx, [d+4] ; EDX:EAX = d+d
    mov ebx, edx
    mov ecx, eax   ; EBX:ECX = EDX:EAX = d+d
    mov al, [a]
    mov ah, 0      ; AX = a
    mov dx, 0      ; DX:AX = a (dword)
    push dx
    push ax
    pop eax        ; EAX = DX:AX = a
    mov edx, 0     ; EDX:EAX = a (qword)
    sub ecx, eax
    sbb ebx, edx   ; EBX:ECX = EBX:ECX - EDX:EAX = (d+d) - a
    mov ax, [b]
    mov dx, 0 ; DX:AX = b
    push dx
    push ax
    pop eax   ; EAX = b
    mov edx, 0 ; EDX:EAX = b (qword)
    sub ecx, eax
    sbb ebx, edx ; EBX:ECX = (d+d) - a - b
    mov eax, [c]
    mov edx, 0   ; EDX:EAX = c
    sub ecx, eax
    sbb ebx, edx
    
    mov [x], ecx
    mov [x+4], ebx
    
    
        ; exit(0)
        push    dword 0      
        call    [exit]       
