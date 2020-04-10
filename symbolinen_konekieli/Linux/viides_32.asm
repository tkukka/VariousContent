                            BITS    32

laitetulostus               EQU     4
stdout                      EQU     1
loppu_hyvin                 EQU     0
lopetus                     EQU     1
AT_SYSINFO                  EQU     32

                            SECTION .rodata

ei_ole_teksti               db      "** AT_SYSINFO ei ole ***",10
ei_ole_pituus               EQU     $ - ei_ole_teksti
on_teksti                   db      "AT_SYSINFO löytyi.",10
on_pituus                   EQU     $ - on_teksti
osoitteet_samat             db      "Osoitteet ovat samat.",10
osoitteet_samat_pituus      EQU     $ - osoitteet_samat
osoitteet_erit              db      "** Osoitteet eivät ole samat. ***",10
osoitteet_erit_pituus       EQU     $ - osoitteet_erit
viesti                      db      "Ohjelma suoritettu.",10
viestin_pituus              EQU     $ - viesti

                            SECTION .data

funktio                     dd      0                       ;__kernel_vsyscall:n osoite

                            SECTION .text

                            GLOBAL  _start:function

_start:                     mov     eax, esp
                            ;mov     dword [funktio], hae_vsyscall
                            ;call    [funktio]               ;epäsuora funktiokutsu
                            call    hae_vsyscall            ;normi funktiokutsu
                            cmp     eax, 0                  ;ei löytynyt?
                            je      .ohi
                            mov     eax, [eax]              ;osoittimen sisältämä funktion osoite
                            mov     [funktio], eax          ;tallennetaan funktion osoite
                            cmp     eax, [gs:10h]           ;glibc: säikeen TCB:stä __kernel_vsyscall:n osoite.
                            jne     .ei_samat
                            mov     ecx, osoitteet_samat
                            mov     edx, osoitteet_samat_pituus
                            mov     ebx, stdout
                            mov     eax, laitetulostus
                            call    [funktio]               ;call [gs:10h] sama asia
                            jmp     .ohi
.ei_samat:                  mov     ecx, osoitteet_erit     ;erikoinen tilanne
                            mov     edx, osoitteet_erit_pituus
                            mov     ebx, stdout
                            mov     eax, laitetulostus
                            call    [funktio]
.ohi:                       push    viesti
                            push    viestin_pituus
                            call    tulosta
                            add     esp, 8                  ;pinon tilan palautus
                            mov     ebx, loppu_hyvin
                            mov     eax, lopetus
                            int     80h
;----------------------------------------------------------------------------
;vastaa: void tulosta(size_t, const char *)
tulosta:                    push    ebp                     ;ABI: rekisterin tila säilytettävä
                            mov     ebp, esp                ;funktion pinokehys
                            push    ebx                     ;ABI: rekisterin tila säilytettävä
                            mov     edx, [ebp + 8]          ;pituus
                            mov     ecx, [ebp + 12]         ;tekstin osoite
                            mov     ebx, stdout
                            mov     eax, laitetulostus
                            int     80h
                            pop     ebx
                            leave                           ;funktion pinon kehyksen purku
                            ret
;----------------------------------------------------------------------------
; ei ABIn mukainen rekisteri - rekisteri kutsutapa
; in: EAX = ESP (pinon pinta)
; out: EAX = 0   ei löytynyt,
;      EAX != 0  osoitin funktioon
hae_vsyscall:               push    esi
                            push    edi
                            push    ebx
                            mov     esi, 0                      ;silmukan laskuri (0...1)
                            mov     edi, 0                      ;siirtymä pinossa. 1. alkio: argumenttien määrä
.komentorivi_ymparisto_ohitus:
                            cmp     dword [eax + edi], 0        ;taulukon loppu?
                            je      .null_loppumerkki
                            add     edi, 4                      ;4-tavuiset alkiot taulukossa
                            jmp     .komentorivi_ymparisto_ohitus
.null_loppumerkki:          cmp     esi, 1                      ;kahdet taulukot käyty läpi?
                            je      .kaikki_hypitty
                            inc     esi
                            add     edi, 4                      ;siirrytään ympäristömuuttujien alkuun
                            jmp     .komentorivi_ymparisto_ohitus
.kaikki_hypitty:            add     edi, 4                      ;siirrytään ELF AUX-vektoreihin 
.sys_haku:                  cmp     dword [eax + edi], AT_SYSINFO ;etsitty vektorin tyyppi?
                            je      .sys_on
                            cmp     dword [eax + edi], 0        ;tuliko loppumerkki vastaan?
                            je      .sys_ei_ole
                            add     edi, 8                      ;vektorit ovat 8-tavuisia
                            jmp     .sys_haku
.sys_ei_ole:                mov     edx, ei_ole_pituus
                            mov     ecx, ei_ole_teksti
                            mov     ebx, stdout
                            mov     eax, laitetulostus
                            int     80h                         ;vanhempi keino
                            mov     eax, 0                      ;EAX = NULL
                            jmp     .loppu
.sys_on:                    add     edi, 4                      ;siirrytään funktio-osoittimen kohdalle
                            lea     eax, [eax + edi]            ;lasketaan suhteellinen osoite siihen
                            mov     esi, eax                    ;kopioidaan. ESI:ttömät systeemikutsut käy.
                            mov     edx, on_pituus
                            mov     ecx, on_teksti
                            mov     ebx, stdout
                            mov     eax, laitetulostus
                            call    [esi]                       ;käytämme __kernel_vsyscall()
                            mov     eax, esi
.loppu:                     pop     ebx
                            pop     edi
                            pop     esi
                            ret

