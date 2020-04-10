                            BITS    32

metodi                      EQU     1

                            SECTION .rodata

vakio_pii                   dq      3.141592654             ;const double pii = 3.14...

                            SECTION .text

                            EXTERN  set_method
                            GLOBAL  laske_ala:function

;vastaa: double laske_ala(double). xmm0 = ympyrän pinta-ala. Siirretään lopuksi ala FPU:n st0-rekisteriin (Sys V 32-bit ABI)
laske_ala:                  push    ebp                     ;ABI: rekisterin tila säilytettävä
                            mov     ebp, esp                ;funktion pinokehys
                            sub     esp, 8                  ;pinomuistin varaus. double (8 tavua) välikaisesti pinoon.
                            movsd   xmm0, [ebp + 8]         ;säde pinosta
                            mulsd   xmm0, xmm0              ;xmm0 = säde²
                            mulsd   xmm0, [vakio_pii]       ;π otetaan muistivakioista, xmm0 = π * säde²
                            movsd   [ebp - 8], xmm0         ;pinoon
                            fld     qword [ebp - 8]         ;st0:aan
                            push    metodi
                            call    set_method              ;kerrotaan main():iin laskentatapa
                            add     esp, 4
                            leave                           ;funktion pinon kehyksen purku ja väliaikaisen muistin vapautus
                            ret

