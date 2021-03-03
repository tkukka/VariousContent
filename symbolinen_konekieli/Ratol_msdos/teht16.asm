        ;RaTol Symbolinen konekieli: Harjoitus 1, tehtävä 6
        ;Tero Kukka IY96A

        ;Tiedosto: teht16.asm
        ;Luotu 12.2.1998
        ;Hyväksytty []

        ;Ohjelma tallentaa luvut N, N - 1, ... , 2, 1 taulukkoon
        ;indeksin kasvaessa 0...N-1 

        ;Vakiot

N       equ  4

        ;Makrot

exit    MACRO           ;esimerkkimakro 'exit'
        mov ax, 4c00h
        int 21h
        ENDM

        .model small    ;muistimalli
        .stack 100h     ;pinon koko

        .data           ;muuttujalohko

taulu   dw  N dup(?)    ;int taulu[N]

        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax      ;ds-rekisterin alustus

        mov cx, N       ;laskuri alkaa N:stä
        mov bx, 0       ;indeksi = 0

SILMUKKA:
        mov taulu[bx], cx  ;taulu[bx] = cx
        add bx, 2       ;lisätään wordin verran
        loop SILMUKKA
        
        exit            ;exit 0

_main   endp
        end _main       ;pääohjelman loppu

