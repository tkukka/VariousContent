        ;RaTol Symbolinen konekieli: koetehtävä 2
        ;Tero Kukka IY96A

        ;Tiedosto: koe2.asm
        ;Luotu 26.2.1998

        ;Ohjelma tallentaa 3 kokonaisluvun taulukon siirroksen pinoon
        ;ja kutsuu aliohjelmaa _laske. Aliohjelma tutkii pinoon tallennettua
        ;ensimmäistä lukua:
        ;* arvolla 1 palautetaan kahden muun luvun summa
        ;* arvolla 2 niiden erotus
        ;* muilla arvoilla palautetaan 0
        
        ;Aliohjelmien esittely:
        extrn _laske: proc

        ;Makrot

exit    MACRO           ;lopetusmakro 'exit'
        mov ax, 4c00h
        int 21h
        ENDM

        .model small    ;muistimalli
        .stack 100h     ;pinon koko 

        .data           ;muuttujalohko
taulu   dw 1, 2, 3      ;laskee summan, koska 1. on 1

        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax      ;ds-rekisterin alustus

        mov ax, offset taulu
        push ax         ;siirros pinoon
        call _laske     ;AX =_laske(taulu);

        exit            ;lopetusrutiini
_main   endp
        end _main       ;ohjelman loppu
