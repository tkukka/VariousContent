                            BITS    32

laitetulostus               EQU     4
stdout                      EQU     1
loppu_hyvin                 EQU     0
lopetus                     EQU     1

                            SECTION .rodata
sade                        dq      5.0                     ;const double sade = 5.0
viesti                      db      "Ohjelma suoritettu.",10 ;const char viesti[], '\0'-merkitön
viestin_pituus              EQU     $ - viesti
luvut                       dd      5, 6, 0, -1, 2, 1       ;const int luvut[]
luvut_kpl                   EQU     ($ - luvut) / 4         ;int: 4 tavua per luku

                            SECTION .text

                            EXTERN  pienin
                            GLOBAL  _start:function

_start:                     finit                           ;x87 alustus
                            push    dword [(sade + 4)]      ;ylempi 4 tavua doublesta
                            push    dword [sade]            ;alempi 4 tavua doublesta
                            call    laske_ala               ;ympyrän ala
                            add     esp, 8                  ;pinon tilan palautus
                            push    luvut_kpl
                            push    luvut
                            call    pienin                  ;pienimmän haku
                            add     esp, 8
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
;vastaa: double laske_ala(double). ST0 = ympyrän pinta-ala
laske_ala:                  push    ebp                     ;ABI: rekisterin tila säilytettävä
                            mov     ebp, esp                ;funktion pinokehys
                            fld     qword [ebp + 8]         ;st0 = säde
                            fmul    st0, st0                ;st0 = säde ^ 2
                            fldpi                           ;st0 = pii, st1 = säde ^ 2
                            fmul    st0, st1                ;st0 = pii * säde ^ 2
                            leave
                            ret

