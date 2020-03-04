                            BITS    32

laitetulostus               EQU     4
stdout                      EQU     1
loppu_hyvin                 EQU     0
lopetus                     EQU     1
AT_SYSINFO                  EQU     32
AT_SYSINFO_EHDR             EQU     33

                            SECTION .data

viesti                      db      "Ääkköset äöåÄÖÅ toimii. Ohjelma suoritettu.",10
viestin_pituus              EQU     $ - viesti

ei_ole_teksti               db      "** SYSINFO ei ole ***",10
ei_ole_pituus               EQU     $ - ei_ole_teksti

on_teksti                   db      "AT_SYSINFO löytyi.",10
on_pituus                   EQU     $ - on_teksti


                            SECTION .text

                            GLOBAL  _start

_start:                     mov     esi, 0                      ;silmukan laskuri (0...1)
                            mov     edi, 0                      ;siirtymä pinossa. 1. alkio: argumenttien määrä
komentorivi_ymparisto_ohitus:
                            cmp     dword [esp + edi], 0        ;taulukon loppu?
                            je      null_loppumerkki
                            add     edi, 4                      ;4-tavuiset alkiot taulukossa
                            jmp     komentorivi_ymparisto_ohitus
null_loppumerkki:           cmp     esi, 1                      ;kahdet taulukot käyty läpi?
                            je      kaikki_hypitty
                            inc     esi
                            add     edi, 4                      ;siirrytään ympäristömuuttujien alkuun
                            jmp     komentorivi_ymparisto_ohitus
kaikki_hypitty:             add     edi, 4                      ;siirrytään ELF AUX-vektoreihin 
sys_haku:                   cmp     dword [esp + edi], AT_SYSINFO ;etsitty vektorin tyyppi?
                            je      sys_on
                            cmp     dword [esp + edi], 0        ;tuliko loppumerkki vastaan?
                            je      sys_ei_ole
                            add     edi, 8                      ;vektorit ovat 8-tavuisia
                            jmp     sys_haku

sys_ei_ole:                 mov     edx, ei_ole_pituus
                            mov     ecx, ei_ole_teksti
                            mov     ebx, stdout
                            mov     eax, laitetulostus
                            int     80h                         ;vanhempi keino
                            jmp     loppu

sys_on:                     add     edi, 4                      ;siirrytään funktion osoitteen kohdalle
                            lea     eax, [esp + edi]            ;lasketaan suhteellinen osoite siihen
                            mov     esi, eax                    ;kopioidaan testikäyttöön. ESI:ttömät systeemikutsut käy.
                            mov     edx, on_pituus
                            mov     ecx, on_teksti
                            mov     ebx, stdout
                            mov     eax, laitetulostus
                            call    [esi]                       ;käytämme __kernel_vsyscall()
                            mov     edx, viestin_pituus
                            mov     ecx, viesti
                            mov     ebx, stdout
                            mov     eax, laitetulostus
                            call    [esi]                       ;uusi tapa
                            mov     ebx, loppu_hyvin
                            mov     eax, lopetus
                            call    [esi]                       ;uusi tapa. lopetus exit:illä

loppu:                      mov     edx, viestin_pituus
                            mov     ecx, viesti
                            mov     ebx, stdout
                            mov     eax, laitetulostus
                            int     80h                         ;vanhempi keino
                            mov     ebx, loppu_hyvin
                            mov     eax, lopetus
                            int     80h                         ;vanhempi keino

