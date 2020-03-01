        ;RaTol Symbolinen konekieli: Harjoitus 1, tehtävä 5
        ;Tero Kukka IY96A

        ;Tiedosto: teht15.asm
        ;Luotu 12.2.1998
        ;Hyväksytty []

        ;Ohjelma laskee yhteen; luku1 = luku1 + luku2

        ;Makrot

exit    MACRO           ;esimerkkimakro 'exit'
        mov ax, 4c00h
        int 21h
        ENDM

        .model small    ;muistimalli
        .stack 100h     ;pinon koko

        .data           ;muuttujalohko

luku1   dw  5           ;int luku1 = 5
luku2   dw  3           ;int luku2 = 3

        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax      ;ds-rekisterin alustus

        mov ax, luku1   ;ax = luku1
        add ax, luku2   ;luku1 = luku1 + luku2 => ax = 8
        mov luku1, ax   ;luku1 = ax

        exit            ;exit 0

_main   endp
        end _main       ;pääohjelman loppu

