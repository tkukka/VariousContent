        ;RaTol Symbolinen konekieli: Harjoitus 1, tehtävä 1
        ;Tero Kukka IY96A

        ;Tiedosto: malli.asm
        ;Luotu 25.1.1998
        ;Hyväksytty []

        ;[Kuvaus] Tämä malli toimii tulevien koodien pohjana.

        ;Ulkoiset muuttujat ja funktiot

        ;Vakiot ja osoitteet

        ;Makrot

exit    MACRO           ;esimerkkimakro 'exit'
        mov ax, 4c00h
        int 21h
        ENDM

        .model small    ;muistimalli
        .stack 100h     ;pinon koko

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax      ;ds-rekisterin alustus, jos on muuttujia

        nop             ;koodia tähän...

        exit            ;lopetusrutiini, esimerkiksi makrolla

_main   endp
        end _main       ;pääohjelman loppu

