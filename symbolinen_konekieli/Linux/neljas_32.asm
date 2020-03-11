                            BITS    32

laitetulostus               EQU     4
stdout                      EQU     1
loppu_hyvin                 EQU     0
lopetus                     EQU     1

                            SECTION .rodata
vakio_pii                   dq      3.141592654             ;const double pii = 3.14...
sade                        dq      5.0                     ;const double sade = 5.0
viesti                      db      "Ohjelma suoritettu.",10 ;const char viesti[], '\0'-merkitön
viestin_pituus              EQU     $ - viesti

                            SECTION .text

                            GLOBAL  _start:function

_start:                     push    dword [(sade + 4)]      ;ylempi 4 tavua doublesta
                            push    dword [sade]            ;alempi 4 tavua doublesta
                            call    laske_ala               ;ympyrän ala
                            add     esp, 8                  ;pinon tilan palautus
                            push    viesti
                            push    viestin_pituus
                            call    tulosta
                            add     esp, 8                  ;pinon tilan palautus
                            mov     ebx, loppu_hyvin
                            mov     eax, lopetus
                            int     80h
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
;vastaa: double laske_ala(double). xmm0 = ympyrän pinta-ala
laske_ala:                  push    ebp                     ;ABI: rekisterin tila säilytettävä
                            mov     ebp, esp                ;funktion pinokehys
                            movsd   xmm0, [esp + 8]         ;säde pinosta
                            mulsd   xmm0, xmm0              ;xmm0 = säde²
                            mulsd   xmm0, [vakio_pii]       ;π otetaan muistivakioista, xmm0 = π * säde²
                            leave                           ;funktion pinon kehyksen purku
                            ret

