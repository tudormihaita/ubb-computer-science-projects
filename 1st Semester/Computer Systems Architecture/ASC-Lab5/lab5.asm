bits 32


global start        


extern exit             
import exit msvcrt.dll                  

;Se da un sir de octeti S. Sa se construiasca sirul D ale carui elemente reprezinta suma fiecaror 
;doi octeti consecutivi din sirul S
segment data use32 class=data
    S db 1, 2, 3, 4, 5, 6
    len equ $-S-1
    D times len db 0


segment code use32 class=code
    start:
        mov ecx, len;
        jecxz final
        mov esi, 0  ; i = 0
        mov edi, 0  ; j = 0
    repeta:
        mov al, [S+esi]
        inc esi
        add al, [S+esi]
        mov [D+edi], al
        inc edi
    loop repeta
    
    final:
        ; exit(0)
        push    dword 0
        call    [exit]       
