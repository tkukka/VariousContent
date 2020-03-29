                            BITS    64

laitetulostus               EQU     1
stdout                      EQU     1
loppu_hyvin                 EQU     0
lopetus                     EQU     60

                            SECTION .rodata

viesti                      db      "Ääkköset äöåÄÖÅ. Хорошо Müller Straße",10,0
viestin_pituus              EQU     $ - viesti

toinen_viesti               db      "Toinenkin tuloste.",10,0
toisen_viestin_pituus       EQU     $ - toinen_viesti

                            SECTION .text

                            GLOBAL _start

_start:                     mov     rdx, viestin_pituus
                            mov     rsi, viesti
                            mov     rdi, stdout
                            mov     rax, laitetulostus
                            syscall

                            mov     rdx, toisen_viestin_pituus
                            mov     rsi, toinen_viesti
                            mov     rdi, stdout
                            mov     rax, laitetulostus
                            syscall

                            mov     rdi, loppu_hyvin
                            mov     rax, lopetus
                            syscall

