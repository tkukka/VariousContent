        ;RaTol Symbolinen konekieli: Harjoitus 3, tehtävä 0
        ;Tero Kukka IY96A

        ;Tiedosto: tuplaa.asm
        ;Luotu 25.2.1998

        ;Aliohjelma _Tuplaa
        ;Hakee taulukon osoitteen ja alkioiden lukumäärän PINOSTA

        ;Aliohjelmien esittely:

        public _Tuplaa

        .model small    ;muistimalli
        .stack  00h     ;pinon koko 

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_Tuplaa proc           ;void _Tuplaa(int *taulu, int M);             
        push bp        ;pinossa M, &taulu, ip, bp
        push cx
        push di        ;pinossa M, &taulu, ip, bp, cx, di
        mov bp, sp     ;Kopioidaan sp
        mov word ptr cx, [bp + 10]
        mov word ptr di, [bp + 8]
TOISTO:
        sal word ptr [di], 1    ;kerrotaan kahdella siirtämällä bittejä
                                ;vasemmalle, 16-bittinen muistipaikka

        add di, 2      ;osoitin kasvaa kahdella (word)
        loop TOISTO
        
        pop di         ;palautetaan rekisterit
        pop cx
        pop bp         ;bp takaisin
        ret 4          ;4 tavun vapautus paluun jälkeen
_Tuplaa endp

        end      
