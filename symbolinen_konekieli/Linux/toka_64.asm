                            BITS    64
                            DEFAULT REL

laitetulostus               EQU     1
stdout                      EQU     1
loppu_hyvin                 EQU     0
lopetus                     EQU     60

                            SECTION .rodata

vakio_pii                   dq      3.141592654                 ;const double pii = 3.14...
sade                        dq      5.0                         ;const double sade = 5.0
viesti                      db      "Ohjelma suoritettu.", 10   ;const char viesti[], '\0'-merkitön
viestin_pituus              EQU     $ - viesti
luvut                       dq      5, 6, 0, -1, 2, 1           ;const long luvut[]
luvut_kpl                   EQU     ($ - luvut) / 8             ;long: 8 tavua per luku

                            SECTION .text

                            EXTERN  pienin
                            GLOBAL  _start:function

_start:                     movsd   xmm0, [sade]
                            call    laske_ala                   ;ympyrän ala
                            mov     rdi, luvut
                            mov     rsi, luvut_kpl
                            call    pienin                      ;pienimmän haku
                            mov     rdi, viesti
                            mov     esi, viestin_pituus         ;RSI yläosa = 0
                            call    tulosta
                            mov     edi, loppu_hyvin            ;RDI yläosa = 0
                            mov     eax, lopetus                ;RAX yläosa = 0
                            syscall
;vastaa: void tulosta(const char *, size_t)
;in: RDI: tekstin osoite
;in: RSI: tekstin pituus
tulosta:                    mov     edx, esi                    ;RDX yläosa nolla?
                            mov     rsi, rdi
                            mov     edi, stdout                 ;RDI yläosa = 0
                            mov     eax, laitetulostus          ;RAX yläosa = 0
                            syscall
                            ret
;vastaa: double laske_ala(double).
;in: XMM0 = säde
;out: XMM0 = ympyrän pinta-ala
laske_ala:                  mulsd   xmm0, xmm0                  ;XMM0 = säde²
                            mulsd   xmm0, [vakio_pii]           ;π otetaan muistivakioista, XMM0 = π * säde²
                            ret

