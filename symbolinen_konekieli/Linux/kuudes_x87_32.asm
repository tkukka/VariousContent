                            BITS    32

metodi                      EQU     0

                            SECTION .text

                            EXTERN  set_method
                            GLOBAL  laske_ala:function

;vastaa: double laske_ala(double). ST0 = ympyrän pinta-ala
laske_ala:                  push    ebp                     ;ABI: rekisterin tila säilytettävä
                            mov     ebp, esp                ;funktion pinokehys
                            fld     qword [ebp + 8]         ;st0 = säde
                            fmul    st0, st0                ;st0 = säde ^ 2
                            fldpi                           ;st0 = pii, st1 = säde ^ 2
                            fmul    st0, st1                ;st0 = pii * säde ^ 2
                            push    metodi
                            call    set_method              ;kerrotaan main():iin laskentatapa
                            add     esp, 4
                            leave
                            ret

