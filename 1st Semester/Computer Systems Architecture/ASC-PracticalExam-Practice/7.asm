bits 32

global start

extern exit,fopen,printf,scanf,fscanf,fprintf,perror,fclose
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
import fopen msvcrt.dll
import fscanf msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll
import perror msvcrt.dll

;7.	Se da un sir de qword definit in data segment. elementele sirului sunt in baza 16
;a)	sa se printeze bytes care compun qword urile din sir
;b)    sa se identifice words care au ultima cifra egala cu constanta k definita in segmentul de date. sa se salveze aceste words in sirul d
;c)	sa se identifice dwords care sunt cuprinse in intervalul AAA - FFFF. sa se determine numarul dwords din acest interval. sa se afiseze acest numar in baza 10 in fisierul 'iesire.txt'

segment data use32 class=data
       s dq 1a2b3c4d5e6f899dh, 4a3b2c1dh, 21abh, 0abcdh
       len_s_bytes equ $-s
       len_s_words equ ($-s)/2
       len_s_dwords equ ($-s)/4
       k equ 0bh
       d times len_s_words dw 0
       mesaj db "Octetii din componenta sirului sunt: ", 0
       format db "%x ", 0
       newline db 13, 10, 0
       afisare_words db "Word-urile cu ultima cifra egala cu %x sunt: ", 0
       nr_dwords_interval db "Numarul de dwords cuprinse in intervalul [%x;%x] este: ", 0
       fisier db "iesire.txt", 0
       mod_fisier db "w", 0
       desc_fisier dd 0
       a dd 0aaah
       b dd 0ffffh
       nr_dwords dd 0
       
       

segment code use32 class=code
        start:
            mov ebx, len_s_bytes
            cmp ebx, 0
            je final
            
            mov esi, s
            cld
            
            push dword mesaj
            call [printf]
            add esp, 4
            
            repeta:
              lodsb
              movzx ax, al
              movzx eax, ax
              
              cmp eax, 0
              je next
              
              push eax
              push dword format
              call [printf]
              add esp, 4*2
              
              next:
              dec ebx
              cmp ebx, 0
              jne repeta
              
              
              mov ebx, len_s_words
              cmp ebx, 0
              je final
              
              push dword newline
              call [printf]
              add esp, 4
              
              push dword k
              push dword afisare_words
              call [printf]
              add esp, 4*2
              
              mov esi, s
              cld
              
              cauta:
                 lodsw
                 movzx eax, ax
                 push eax
                 mov dx, 0
                 mov ecx, 0
                 mov cx, 16
                 div cx
                 mov cx, k
                 cmp dx, cx
                 je afiseaza
                 jmp urmatorul
                 
                 afiseaza:
                    pop eax
                    ;movzx eax, ax
                    push eax
                    push dword format
                    call [printf]
                    add esp, 4*2
                    
                urmatorul:
                      dec ebx
                      cmp ebx, 0
                      jne cauta
                    
              
              mov ebx, len_s_dwords
              cmp ebx, 0
              je final
              
              push dword mod_fisier
              push dword fisier
              call [fopen]
              add esp, 4*2
              
              cmp eax, 0
              je final
              
              mov [desc_fisier], eax
              
              push dword [b]
              push dword [a]
              push dword nr_dwords_interval
              push dword [desc_fisier]
              call [fprintf]
              add esp, 4*4
              
              
              mov esi, s
              cld
              
              interval:
                  lodsd
                  cmp eax, [a]
                  jb mai_departe
                  
                  cmp eax, [b]
                  ja mai_departe
                  
                  inc dword[nr_dwords]
                  
                  mai_departe:
                    dec ebx
                    cmp ebx, 0
                    jne interval
                  
                  
              push dword [nr_dwords]
              push dword format
              push dword [desc_fisier]
              call [fprintf]
              add esp, 4*3
              
              push dword [desc_fisier]
              call [fclose]
              add esp, 4
                  
        
            final:
            
            push dword 0
            call [exit]