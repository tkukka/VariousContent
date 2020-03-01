        ;RaTol Symbolinen konekieli: Harjoitus 5, tehtävä 4
        ;Tero Kukka IY96A

        ;Tiedosto: lueasc.asm Versio 1.0
        ;Luotu 26.4.1998

        include a:makrot.txt

        ;Luetaan kaksi ascii-merkkiä (esim. '2' ja '9') ja muutetaan
        ;ne binääriksi AX:ään (esim. AH = 2 ja AL = 9).

        public _lue_ascii

        .model large    ;muistimalli

        .stack  00h     ;pinon koko 

        .data           ;muuttujalohko

        .code  

_lue_ascii proc
        push dx

        lue_ascii_AL    ;luetaan 1. merkki
        ascii2bin al    ;merkki binääriseksi
        ;AL:ssä luku

        pop dx
        ret
_lue_ascii endp
        end 
