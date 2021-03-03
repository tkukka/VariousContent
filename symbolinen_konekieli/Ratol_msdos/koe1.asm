        ;RaTol Symbolinen konekieli: koetehtävä 1
        ;Tero Kukka IY96A

        ;Tiedosto: koe1.asm
        ;Luotu 26.2.1998

;b-kohta
        ;Ohjelma lukee päätteeltä N kpl ascii merkkejä
        ;taulukkoon taulu.

        ;Vakiot

N       equ 3        ;pieni kokeiluarvo

        ;Makrot

lue_N_ascii MACRO param1
        mov di, offset param1
        mov cx, N       ;laskuri cx = N
SILMUKKA:
        mov ah, 1h
        int 21h
        mov byte ptr [di], al
        inc di   ;byten verran kasvatus
        loop SILMUKKA
        ENDM

exit    MACRO           ;lopetusmakro 'exit'
        mov ax, 4c00h
        int 21h
        ENDM

        .model small    ;muistimalli
        .stack 100h     ;pinon koko

        .data           ;muuttujalohko
taulu   db N dup(?)     ;int taulu[N];

        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax      ;datasegmentin kiinnitys

        lue_N_ascii taulu

        exit            ;lopetusrutiini

_main   endp
        end _main       ;pääohjelman loppu

