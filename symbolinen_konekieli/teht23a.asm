        ;RaTol Symbolinen konekieli: Harjoitus 2, tehtävä 3
        ;Tero Kukka IY96A

        ;Tiedosto: teht23a.asm
        ;Luotu 19.2.1998

        ;Ohjelma kutsuu aliohjelmaa _summaa, joka 
        ;palauttaa kahden luvun summan muistipaikkaan ds:summa.
        ;Yhteenlaskettavat ovat rekistereissä BL ja DH.

        ;Aliohjelmien esittely: ei tarvita, koska ovat samassa käännös-
        ;yksikössä.

        ;Makrot

exit    MACRO           ;esimerkkimakro 'exit'
        mov ax, 4c00h
        int 21h
        ENDM

        .model small    ;muistimalli
        .stack 00h      ;pinon koko 0h

        .data           ;muuttujalohko
summa   db ?            ;unsigned char summa;

        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax      ;ds-rekisterin alustus

        mov bl, 5       ;pienet luvut, joiden summa <= 255
        mov dh, 2

        call _summaa    ;ax = _summaa();
        mov summa, al   

        exit            ;lopetusrutiini

_main   endp

_summaa proc            ;unsigned char summaa();            
        mov al, bl
        add al, dh
        ret
_summaa endp

        end _main       ;ohjelman loppu
