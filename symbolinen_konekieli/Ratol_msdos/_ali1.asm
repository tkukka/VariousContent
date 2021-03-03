        ;RaTol Symbolinen konekieli: Harjoitus 2, tehtävä 2
        ;Tero Kukka IY96A

        ;Tiedosto: _ali1.asm
        ;Luotu 19.2.1998

        ;Aliohjelma _ali1

        public _ali1

        .model small    ;muistimalli
        .stack 0h       ;pinon koko

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_ali1   proc            ;int _ali1();
        mov ax, 1
        ret
_ali1   endp
        end

