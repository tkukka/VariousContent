
        ;RaTol Symbolinen konekieli: Harjoitus 4, tehtävä 2
        ;Tero Kukka IY96A

        ;Tiedosto: luenimet.asm Versio 1.1
        ;Luotu 13.4.1998

        include a:makrot.txt

        ;Ulkoiset aliohjelmat

        extrn _strcpy: proc

        ;Aliohjelma _lue_nimet
        ;Lukee nimiä puskurialueelle DOS-kesketyksellä 21h AH=0Ah.
        ;Kopioi sitten nimet niille varatulle muistialueelle,
        ;ja palauttaa luettujen nimien lukumäärän.

        public _lue_nimet

        .model small    ;muistimalli
        .stack 100h     ;pinon koko 

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_lue_nimet  proc 
        ;rekisterit talteen
        push bp        ;pinossa: param., ip, bp
        mov bp, sp     ;kopioidaan sp
        push cx
        push ds
        push bx
        push dx
        push di
        
        mov cx, [bp + 4]  ;nimien lkm
        mov ds, [bp + 6]  ;datasegm.
        mov bx, [bp + 8]  ;puskurin siirros
        mov dx, [bp + 10] ;yhden tietueen koko
        mov di, [bp + 12] ;siirros taulukon alkuun
LUUPPI:
        lue_puskuriin ds, bx  ;luetaan merkkijono
        rivin_vaihto
        mov ax, [bx + 1]    ;luettujen merkkien lkm AX-rekisteriin
        xor ah, ah      ;nollaus AH:lle
        push ax         ;pinoon puskurissa olevien merkkien lkm
        push ds
        mov ax, bx
        add ax, 2       ;2 tavua puskurin alusta ovat lukuja
        push ax         ;siirros kopioitavan m.jonon alkuun 
        push ds         ;datasegm. pinoon
        push di         ;siirros kohdejonon alkuun
        call _strcpy    ;kopioidaan syötetty m.jono 

        push di        ;tallennetaan DI:n wanha arvo pinoon
        add di, ax    ;_strcpy palautti luettujen merkkien lkm:n AX:ssä
        mov byte ptr [di], '$' ;lisätään loppumerkki
        pop di
        add di, dx      ;seuraava tietue
        loop LUUPPI

        mov ax, [bp + 4]  ;ladataan nimien/jonojen lkm pinosta
        sub ax, cx      ;palautetaan luettujen nimien lkm
   ;rekisterien palautus:
        pop di
        pop dx
        pop bx
        pop ds
        pop cx
        pop bp
        ret       
_lue_nimet endp

        end      
