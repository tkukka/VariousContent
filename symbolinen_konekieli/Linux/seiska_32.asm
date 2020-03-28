                            BITS    32

laitetulostus               EQU     4
stdout                      EQU     1

                            SECTION .rodata

viesti                      db      "asm kirjoittaa...", 10 ;const char viesti[], '\0'-merkitön
viestin_pituus              EQU     $ - viesti
vakioteksti                 db      "yli", 0

                            SECTION .text

                            GLOBAL  sotke:function

;Vastaa: void sotke(const char *)
sotke:                      push    ebp                     ;ABI: rekisterin tila säilytettävä
                            mov     ebp, esp                ;funktion pinokehys
                            push    viesti
                            push    viestin_pituus
                            call    tulosta
                            add     esp, 8                  ;pinon tilan palautus
                            mov     ecx, [ebp + 8]          ;parametri: ECX = tekstin osoite
                            xor     edx, edx
                            mov     dword eax, vakioteksti
.silmukka:                  mov     dl, [eax]
                            mov     [ecx], dl
                            cmp     byte [eax], 0           ;kopioitava teksti loppui?
                            je      .loppu
                            inc     eax
                            inc     ecx
                            jmp     .silmukka
.loppu:                     leave
                            ret
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

