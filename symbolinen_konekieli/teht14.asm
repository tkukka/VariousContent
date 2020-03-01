        ;RaTol Symbolinen konekieli: Harjoitus 1, tehtävä 4
        ;Tero Kukka IY96A

        ;Tiedosto: teht14.asm
        ;Luotu 4.2.1998
        ;Hyväksytty []

        ;Pääohjelmassa nollataan 20 kpl word-tyyppisiä muistipaikkoja.

        ;Vakiot

MAXIND equ 20          ;taulukon koko
TAYTE  equ 00h         ;taulukon alkuasetusarvo

        ;Makrot

exit    MACRO           ;esimerkkimakro 'exit'
        mov ax, 4c00h
        int 21h
        ENDM

        .model small    ;muistimalli
        .stack 00h      ;pinon koko

        .data           ;muuttujalohko
taulu   dw MAXIND dup(?)    ;int taulu[20]; alustamaton

        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax      ;ds-rekisterin alustus

        mov cx, MAXIND  ;taulukon koko cx:ään
        mov bx, 0       ;indeksilaskurin nollaus

NOLLAUS:
        mov taulu[bx], TAYTE   ;cx:llä ei saa osoittaa
        add bx, 2       ;wordille 2 pykälää
        loop NOLLAUS

        exit            ;lopetusrutiini

_main   endp
        end _main       ;pääohjelman loppu

