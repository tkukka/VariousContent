        ;RaTol Symbolinen konekieli: Harjoitus 3, tehtävä 0
        ;Tero Kukka IY96A

        ;Tiedosto: teht30.asm
        ;Luotu 25.2.1998

;a-kohta
        ;Tallennetaan M kappaletta lukua 3 taulukkoon indeksoitua
        ;osoitusmuotoa käyttäen.

;b-kohta
        ;Edellisen kohdan taulukon arvoja kasvatetaan yhdellä. Rekisteri
        ;di osoittaa alkion.

;c-kohta
        ;Aliohjelmalle annetaan pinossa taulukon osoite ja alkioiden
        ;lukumäärä. Aliohjelma kertoo taulukon luvut kahdella.

        ;Ulkoiset funktiot
        extrn _Tuplaa: proc

        ;Vakiot ja osoitteet
M       equ 4

        ;Makrot

exit    MACRO           ;lopetusmakro 'exit'
        mov ax, 4c00h
        int 21h
        ENDM

        .model small    ;muistimalli
        .stack 100h     ;pinon koko

        .data           ;muuttujalohko
taulu   dw M dup(?)     ;int taulu[M];

        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax      ;datasegmentin kiinnitys

;*********  a-kohta  *****************************
        xor si, si      ;nollataan si
        mov cx, M       ;cx = M
SILMUKKA:
        mov word ptr [taulu + si], 3
        ;sama kuin 'mov word ptr taulu[si], 3'

        add si, 2       ;kahden tavun lisäys
        loop SILMUKKA
;*********  b-kohta  ******************************
        mov di, offset taulu
        mov cx, M
SILMUKKA2:
        inc word ptr [di]  ;word tyyppisen tiedon inkrementointi
        add di, 2       ;kahden tavun lisäys 
        loop SILMUKKA2
;********  c-kohta  *******************************
        push M          ;tallennetaan M ja &taulu pinoon
        push offset taulu
        call _Tuplaa    ;_Tuplaa(taulu, M);

        exit            ;lopetusrutiini

_main   endp
        end _main       ;pääohjelman loppu

