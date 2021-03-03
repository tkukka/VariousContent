        ;RaTol Symbolinen konekieli: Harjoitus 2, tehtävä 3
        ;Tero Kukka IY96A

        ;Tiedosto: summaa1.asm
        ;Luotu 25.2.1998

        ;Aliohjelma _Summaa1
        ;Yhteenlaskettavat luvut ovat rekistereissä BL ja DH.

        ;Aliohjelmien esittely:

        public _Summaa1

        .model small    ;muistimalli
        .stack  00h     ;pinon koko 

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_Summaa1 proc           ;unsigned char _Summaa1();             
        mov ah, 0       ;varmistetaan summan (word) oikea tulos
        mov al, bl
        add al, dh
        ret             ;return AX;
_Summaa1 endp

        end      
