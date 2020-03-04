                            BITS    32

laitetulostus               EQU     4
stdout                      EQU     1
loppu_hyvin                 EQU     0
lopetus                     EQU     1

                            SECTION .data

viesti                      db      "Ääkköset äöåÄÖÅ. Хорошо Müller Straße",10,0
viestin_pituus              EQU     $ - viesti

toinen_viesti               db      "Toinenkin tuloste.",10,0
toisen_viestin_pituus       EQU     $ - toinen_viesti

                            SECTION .text

                            GLOBAL _start

_start:                     mov     edx, viestin_pituus
                            mov     ecx, viesti
                            mov     ebx, stdout
                            mov     eax, laitetulostus
                            int     80h                         ;vanhempi keino

                            mov     edx, toisen_viestin_pituus
                            mov     ecx, toinen_viesti
                            mov     ebx, stdout
                            mov     eax, laitetulostus
                            int     80h

                            mov     ebx, loppu_hyvin
                            mov     eax, lopetus
                            int     80h

