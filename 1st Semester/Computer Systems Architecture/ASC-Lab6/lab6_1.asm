bits 32 


global start        


extern exit              
import exit msvcrt.dll    
                         
;Se da un sir de dublucuvinte. Sa se ordoneze crescator sirul cuvintelor superioare ale acestor dublucuvinte. Cuvintele inferioare raman neschimbate.
segment data use32 class=data
    sir dd 12ab5678h, 1256abcdh, 12344344h
    len equ ($-sir)/4 ; lungimea sirului in dublucuvinte
    d times len dd 0
    ok db 1  ; variabila contor folosita pentru BubbleSort


segment code use32 class=code
    start:
        mov ecx, len
        jecxz final
        cld
        mov esi, sir
        mov edi, d
        repeta:
            movsd    ; mutarea intr-un sir destinatie a dublucuvintelor din sirul sursa dat
        loop repeta
        
        while:
            cmp byte[ok], 1
            jne final_sortare  ; in momentul in care ok ramane la 0 dupa o parcurgere a sirului,
            mov byte[ok], 0    ; inseamna ca toate cuvintele superioare au fost sortate, deci loop-ul se opreste
            mov ecx, len-1
            jecxz final_sortare
            mov esi, d+2       ; esi va fi setat la pozitia cuvantului superior din primul dublucuvant
            cld
            for:
                lodsw ; in AX va fi incarcat primul cuvant superior
                mov bx, ax  ; cuvantul preluat va fi pus in BX, pentru a elibera AX
                add esi, 2  ; sar peste cuvantul inferior din urmatorul dublucuvant
                lodsw       ; incarc in AX urmatorul cuvant superior
                sub esi, 6  ; ma intorc la pozitia primului cuvant superior 
                cmp ax, bx  ; compar cele 2 cuvinte superioare pentru a decide daca trebuie facuta interschimbarea
                jge next    ; daca AX > BX, atunci cuvintele sunt ordonate crescator si se sare peste interschimbare
                mov [esi], ax
                mov ax, bx
                mov [esi+4], ax
                mov byte[ok], 1
                next:
                add esi, 4  ; sar la adresa urmatorului cuvant superior
           loop for
           jmp while
        final_sortare:
            final:
        ; exit(0)
        push    dword 0  
        call    [exit] 
        
