bits 32

global start

extern exit,scanf,printf,fprintf,fopen,fclose
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll


;2.	Se citește de la tastatură un număr N și apoi N numere. Să se calculeze suma numerelor pare introduse, să se calculeze suma numerelor impare introduse, apoi diferența dintre cele două sume. Să se afișeze în fișierul output.txt cele 3 rezultate, în baza 16, pe linii separate.
segment data use32 class=data
        output db "output.txt", 0
        mod_output db "w", 0
        mesaj db "Introduceti numarul de valori citite de la tastatura:",13,10, 0
        format db "%d", 13,10, 0
        format_afisare db "%x", 13, 10, 0
        desc_output dd 0
        n dd 0
        nr dd 0
        suma_pare dd 0
        suma_impare dd 0

;??? mereu imi cere un input in plus
segment code use32 class=code
        start:
               push dword mesaj
               call [printf]
               add esp, 4
               
               push dword n
               push dword format
               call [scanf]
               add esp, 4*2
               
               ;mov dword [n], 4 
               
               ; push dword [n]
               ; push dword format
               ; call [printf]
               ; add esp, 4*2
               
               mov ebx, 0
               mov ebx, [n]
               cmp ebx, 0
               je final
               
               repeta:
                    push dword nr
                    push dword format
                    call [scanf]
                    add esp, 4*2
                    
                    mov eax, [nr]
                    test eax, 1
                    jz par
                    
                    ;impar
                    add [suma_impare], eax
                    jmp next
                    
                    par:
                        add [suma_pare], eax
                    
                    next:
                    dec ebx
                    cmp ebx, 0
                    jne repeta
                    
                push dword mod_output
                push dword output
                call [fopen]
                add esp, 4*2
                
                cmp eax, 0
                je final
                
                mov [desc_output], eax
                
                push dword [suma_pare]
                push dword format
                push dword [desc_output]
                call [fprintf]
                add esp, 4*3
                
                push dword [suma_impare]
                push dword format
                push dword [desc_output]
                call [fprintf]
                add esp, 4*3
            
                mov eax, [suma_pare]
                sub eax, [suma_impare]
                
                push eax
                push dword format
                push dword [desc_output]
                call [fprintf]
                add esp, 4*3
                
                
            final:
            
                push dword [desc_output]
                call [fclose]
                add esp, 4
                
            push dword 0
            call [exit]