        ;RaTol Symbolinen konekieli: Harjoitus 2, tehtävä 3
        ;Tero Kukka IY96A

        ;Tiedosto: summaa3.asm
        ;Luotu 25.2.1998

        ;Aliohjelma _Summaa3
        ;Yhteenlaskettavat luvut ovat PINOSSA.

        ;Aliohjelmien esittely:

        public _Summaa3
               
        .model small    ;muistimalli
        .stack  00h     ;pinon koko 

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_Summaa3 proc           ;unsigned int _Summaa3();             
        push bp         ;Nyt pinossa: bx, dx, ip, bp
        mov bp, sp      ;Kopioidaan sp bp:hen. bp osoittaa "entistä" bp:tä

        ;Pino kasvaa alaspäin, wanhat arvot saa kiinni +:lla. Pinoon
        ;tallennetaan 2 tavua kerrallaan, siksi osoitus kahden välein.

        mov ax, [bp + 6] ;bx:n arvo on 6 pykälää "taaksepäin"
        mov bx, [bp + 4] ;Vastaavasti löytyy dx
        add ax, bx
        
        pop bp          ;palautetaan bp
        ret 4           ;return AX
        ; Huom. 4 (tavua) = 2 x 2 tavua vapautuu pinosta
_Summaa3 endp

        end      
