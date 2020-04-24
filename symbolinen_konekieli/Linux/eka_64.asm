                            BITS    64
                            DEFAULT REL

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

                            GLOBAL _start:function

_start:                     mov     edx, viestin_pituus         ;RDX yläosa = 0
                            mov     rsi, viesti
                            mov     edi, stdout                 ;RDI yläosa = 0
                            mov     eax, laitetulostus          ;RAX yläosa = 0
                            syscall

                            mov     edx, toisen_viestin_pituus  ;RDX yläosa = 0
                            mov     rsi, toinen_viesti
                            mov     edi, stdout                 ;RDI yläosa = 0
                            mov     eax, laitetulostus          ;RAX yläosa = 0
                            syscall

                            mov     edi, loppu_hyvin            ;RDI yläosa = 0
                            mov     eax, lopetus                ;RAX yläosa = 0
                            syscall

