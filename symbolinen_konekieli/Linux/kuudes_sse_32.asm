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
                            sub     esp, 16                 ;double välikaisesti pinoon tähän. 16 tavua pitäisi riittää.
                            movsd   xmm0, [ebp + 8]         ;säde pinosta
                            mulsd   xmm0, xmm0              ;xmm0 = säde²
                            mulsd   xmm0, [vakio_pii]       ;π otetaan muistivakioista, xmm0 = π * säde²
                            movsd   [esp], xmm0             ;pinoon
                            fld     qword [esp]             ;st0:aan
                            add     esp, 16                 ;väliaikaisen muistin vapautus
                            push    metodi
                            call    set_method              ;kerrotaan main():iin laskentatapa
                            add     esp, 4
                            leave                           ;funktion pinon kehyksen purku
                            ret

