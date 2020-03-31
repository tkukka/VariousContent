                            BITS    64
                            DEFAULT REL

                            SECTION .rodata

vakio_pii                   dq      3.141592654             ;const double pii = 3.14...

                            SECTION .text

                            GLOBAL  laske_ala:function

;vastaa: double laske_ala(double).
;in: XMM0 = säde
;out: XMM0 = ympyrän pinta-ala
laske_ala:                  mulsd   xmm0, xmm0              ;XMM0 = säde²
                            mulsd   xmm0, [vakio_pii]       ;π otetaan muistivakioista, XMM0 = π * säde²
                            ret

