        ;RaTol Symbolinen konekieli: Harjoitus 2, tehtävä 3
        ;Tero Kukka IY96A

        ;Tiedosto: summaa2.asm
        ;Luotu 25.2.1998

        ;Aliohjelma _Summaa2
        ;Yhteenlaskettavat luvut ovat osoitteissa luku1 ja luku2.

        ;Aliohjelmien esittely:

        public _Summaa2

        ;Globaalit muuttujat

        extrn luku1, luku2

        .model small    ;muistimalli
        .stack  00h     ;pinon koko 

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_Summaa2 proc           ;unsigned int _Summaa2();             
        mov ax, luku1
        mov bx, luku2
        add ax, bx
        jnc PALUU       ;Normaali paluu, jos ei itseisarvon ylivuotoa
        mov dx, 0001h   ;Itseisarvon ylivuoto
PALUU:
        ret             ;return AX;
_Summaa2 endp

        end      
