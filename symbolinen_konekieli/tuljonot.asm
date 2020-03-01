
        ;RaTol Symbolinen konekieli: Harjoitus 4, tehtävä 2
        ;Tero Kukka IY96A

        ;Tiedosto: tuljonot.asm  Versio 1.1
        ;Luotu 13.4.1998

        include a:makrot.txt
        
        ;Aliohjelma _tulosta_jonot
        ;Parametrit: 1. siirros tietuetaulukkoon,
        ;2. tietueen koko, 3. datasegmentti ja 4. jonojen lkm

        public _tulosta_jonot

        .model small    ;muistimalli
        .stack 00h      ;pinon koko 

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_tulosta_jonot  proc 
        ;rekisterit talteen
        push bp        ;pinossa: param., ip, bp
        mov bp, sp     ;kopioidaan sp
        push cx
        push ds
        push si

        mov cx, [bp + 4]        ;jonojen lkm
        mov ds, [bp + 6]        ;datasegm.
        mov si, [bp + 10]       ;taulukon siirros
SILMUKKA:
        tulosta si              ;tulostetaan merkkijono
        rivin_vaihto
        add si, [bp + 8]        ;seuraavan jonon siirros
        loop SILMUKKA
        mov ax, 0               ;AX = "OK"        
   ;rekisterien palautus:
        pop si
        pop ds
        pop cx
        pop bp
        ret           
_tulosta_jonot endp

        end      
