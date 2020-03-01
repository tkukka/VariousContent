        ;RaTol Symbolinen konekieli: Harjoitus 2, tehtävä 3
        ;Tero Kukka IY96A

        ;Tiedosto: teht23.asm
        ;Luotu 25.2.1998

;a-kohta
        ;Ohjelma kutsuu aliohjelmaa _Summaa1, joka 
        ;palauttaa kahden luvun summan muistipaikkaan DS:summa.
        ;Yhteenlaskettavat luvut ovat rekistereissä BL ja DH.

;b-kohta
        ;Ohjelma kutsuu toista aliohjelmaa _Summaa2, joka saa
        ;yhteenlaskettavat luvut osoitteista luku1 ja luku2.
        ;luku1 ja luku2 ovat 16-bittisiä. Ylivuoto huomioidaan.
        ;Lukujen summa tallennetaan DS:summa:aan.

;c-kohta
        ;Summattavat luvut ovat rekistereissä BX ja DX, jotka tallen-
        ;netaan pinoon ennen aliohjelman _Summaa3 kutsua.
        ;Summa (ilman ylivuototestausta) DS:summa:aan.

        ;Globaalit muuttujat:

        public luku1, luku2

        ;Aliohjelmien esittely:

        extrn _Summaa1: proc
        extrn _Summaa2: proc
        extrn _Summaa3: proc

        ;Makrot

exit    MACRO           ;lopetusmakro 'exit'
        mov ax, 4c00h
        int 21h
        ENDM

        .model small    ;muistimalli
        .stack 100h     ;pinon koko 

        .data           ;muuttujalohko
summa   dw 0            ;unsigned int summa;
luku1   dw ?            ;unsigned int luku1; globaali
luku2   dw ?            ;unsigned int luku2; globaali

        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax      ;ds-rekisterin alustus

;**********   a-kohta  ************************************

        mov bl, 5       ;pienet luvut, joiden summa <= 255
        mov dh, 2

        call _Summaa1   ;AX = _Summaa1();
        mov summa, ax   

;***********  b-kohta  ************************************

        mov luku1, 0ffffh
        mov luku2, 0001h   ;ylivuoto odotettavissa
        xor dx, dx      ;DX = 0, DX != 0 ilmaisee ylivuodon
        call _Summaa2   ;AX = _Summaa2();

        cmp dx, 0000h   ;Ylivuodon tutkiminen
        jz TULOS_OK     ;Hyppy, jos zero-flag = 0

        nop             ;Ylivuodon käsittely alkaa..

        jmp KOHTA_C

TULOS_OK:
        mov summa, ax

;***********  c-kohta  *************************************

KOHTA_C:
        mov bx, 3
        mov dx, 6
        push bx         ;parametrit pinoon
        push dx
        call _Summaa3   ;AX = _Summaa3();
        mov summa, ax   ;ylivuotoa ei tutkita

        exit            ;lopetusrutiini
_main   endp
        
        end _main       ;ohjelman loppu
