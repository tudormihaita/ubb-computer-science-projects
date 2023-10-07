bits 32


global start        
; Se da un fisier text care contine litere, spatii si puncte. Sa se citeasca continutul fisierului, sa se determine numarul de cuvinte si sa se afiseze pe ecran aceasta valoare. (Se considera cuvant orice secventa de litere separate prin spatiu sau punct)

extern exit,fopen,fscanf,fread,fclose,printf,perror            
import exit msvcrt.dll
import fopen msvcrt.dll
import fscanf msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import perror msvcrt.dll
import fread msvcrt.dll
                         


segment data use32 class=data
   a db "a.txt", 0
   mod_a db "r", 0
   desc_a dd 0
   buffer db 0
   format db "%c", 0
   mesaj db "eroare", 0
   afisare db "nr cuvinte = %d", 0
   nr_cuv db 0


segment code use32 class=code
    start:
        ;fopen("a.txt","r")
        push dword mod_a
        push dword a
        call [fopen]
        add esp, 4*2
        
        cmp eax, 0
        je eroare
        
        mov [desc_a], eax
        repeta:
            ;fread(buffer,1,1,desc_a)
            push dword [desc_a]
            push dword 1
            push dword 1
            push dword buffer
            call [fread]
            add esp, 4*4
            
            cmp eax, 0
            je continua
            mov eax, 0
            mov al, [buffer]
            ;inc byte[buffer]
            ;mov eax,0
            ;mov al, [buffer]
            cmp al, ' '
            ;cmp al, 95
            jne test_punct
            ;add [nr_cuv], byte 1
            inc byte[nr_cuv]
            test_punct:
            cmp al, '.'
            ;cmp al, 46
            jne next
            ;add [nr_cuv], byte 1
            inc byte[nr_cuv]
            
            next:
            jmp repeta
            
            continua:
            ;fclose(desc_a)
            push dword [desc_a]
            call [fclose]
            add esp, 4
            
            ;printf(afisare,nr_cuv)
            push dword [nr_cuv]
            push dword afisare
            call [printf]
            add esp, 4*2
            
            jmp final
                eroare:
                ;perror(mesaj)
                push dword mesaj
                call [perror]
                add esp, 4
           final:
            
        ; exit(0)
        push    dword 0      
        call    [exit]       ; call exit to terminate the program
