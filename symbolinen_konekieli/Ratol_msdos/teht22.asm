        ;RaTol Symbolinen konekieli: Harjoitus 2, tehtävä 2
        ;Tero Kukka IY96A

        ;Tiedosto: teht22.asm
        ;Luotu 19.2.1998

        ;Ohjelma kutsuu aliohjelmia _ali1 ja _ali2. Aliohjelma _ali1
        ;palauttaa arvon 1 ja _ali2 arvon 2 ax-rekisterissä. Ohjelma
        ;laskee palautusarvojen summan.

        ;Ulkoisten aliohjelmien esittely

        extrn _ali1: proc
        extrn _ali2: proc

        ;Makrot

exit    MACRO           ;makro 'exit'
        mov ax, 4c00h
        int 21h
        ENDM

        .model small    ;muistimalli small toimii!!
        .stack 100h     ;pinon koko 

        .data           ;muuttujalohko

luku1   dw ?            ;int luku1;
summa   dw ?            ;int summa;

        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax      ;ds-rekisterin alustus

        call _ali1      ;ax = _ali1(); 
        mov luku1, ax   

        call _ali2      ;luku2 ax:ään
        add ax, luku1   ;ax =+ luku1
        mov summa, ax

        exit            ;lopetusrutiini

_main   endp

        end _main       ;ohjelman loppu
