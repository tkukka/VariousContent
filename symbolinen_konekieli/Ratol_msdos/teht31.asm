        ;RaTol Symbolinen konekieli: Harjoitus 3, tehtävä 1
        ;Tero Kukka IY96A

        ;Tiedosto: teht31.asm
        ;Luotu 15.3.1998

        ;Ohjelma etsii pienimmän tavun 2000H tavun (8192 kpl) joukosta.
;a-kohta:
        ;Tavut unsigned tyyppiä

;b-kohta:
        ;Tavut etumerkillä (signed).
        
        ;Aliohjelmien esittely:
        
        extrn _Etsi: proc 
        ;Palauttaa pienimmän tavun ax-rekisterissä
        ;Taulukon osoite saadaan pinosta

        ;Vakiot
TAVUJA  equ  2000h
UNSIGNED equ 0000h
SIGNED  equ  0001h

        ;Makrot

exit    MACRO arg        ;lopetusmakro 'exit'

        mov al, arg
        mov ah, 4ch
        int 21h
        ENDM

        .model small    ;muistimalli
        .stack 100h     ;pinon koko 

        .data           ;muuttujalohko
luvut   db TAVUJA dup(?)  ;ei alustusta            
pienin  db ?

        .code           ;ohjelmakoodi alkaa
        
_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax      ;ds-rekisterin alustus

;**********   a-kohta  ************************************
        push UNSIGNED
        push TAVUJA
        push ds
        mov ax, offset luvut
        push ax
        call _Etsi
        mov pienin, al

;***********  b-kohta  ************************************
        push SIGNED
        push TAVUJA
        push ds
        mov ax, offset luvut
        push ax
        call _Etsi
        mov pienin, al

        exit 0          ;lopetusrutiini
_main   endp
        
        end _main       ;ohjelman loppu
