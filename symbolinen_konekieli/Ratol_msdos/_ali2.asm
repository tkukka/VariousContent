        ;RaTol Symbolinen konekieli: Harjoitus 2, tehtävä 2
        ;Tero Kukka IY96A

        ;Tiedosto: _ali2.asm
        ;Luotu 19.2.1998

        ;Aliohjelma _ali2

        public _ali2

        .model small    ;muistimalli
        .stack 0h       ;pinon koko

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_ali2   proc            ;int _ali2();
        mov ax, 2
        ret
_ali2   endp
        end

