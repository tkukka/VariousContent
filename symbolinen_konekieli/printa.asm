
        ;RaTol Symbolinen konekieli: Harjoitus 3, tehtävä 3
        ;Tero Kukka IY96A

        ;Tiedosto: printa.asm
        ;Luotu 4.4.1998

        include a:makrot.txt

        ;Aliohjelma _print_ascii
        ;Tulostaa ascii-merkin PINOSTA

        public _print_ascii

        .model small    ;muistimalli
        .stack  00h     ;pinon koko 

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_print_ascii  proc 
        ;rekisterit talteen
        push bp        ;pinossa: hex-luku, ip, bp
        mov bp, sp     ;kopioidaan sp
        push dx

        mov byte ptr dl, [bp + 4]
        bin2ascii dl   ;DL binääriesityksestä asciiksi
        mov ah, 06h
        int 21h        ;tulostetaan ascii-merkki DL:stä
        xor ax, ax     ;AX = "OK"
   ;rekisterien palautus:
        pop dx
        pop bp
        ret 2   ;2 tavun vapautus pinosta
_print_ascii endp

        end      
