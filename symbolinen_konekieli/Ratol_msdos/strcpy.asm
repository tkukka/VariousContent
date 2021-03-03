
        ;RaTol Symbolinen konekieli: Harjoitus 4, tehtävä 0
        ;Tero Kukka IY96A

        ;Tiedosto: strcpy.asm
        ;Luotu 4.4.1998

        include a:makrot.txt

        ;Aliohjelma _strcpy
        ;Kopioi halutun määrän merkkejä jonosta toiseen
        ;Parametrit pinossa: lkm, segmentti1, offset1, segmentti2, offset2
        ;Palauttaa kopioitujen merkkien lukumäärän AX:ssä

        public _strcpy

        .model small    ;muistimalli
        .stack  00h     ;pinon koko 

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_strcpy  proc 
        ;rekisterit talteen
        push bp        ;pinossa: parametrit + ip, bp
        mov bp, sp     ;kopioidaan sp
        push ds
        push es
        push si
        push di
        push cx

        cld     ;suuntalipun nollaus -> kasvavat osoitteet
        mov cx, [bp + 12]  ;cx = siirrettävien tavujen lkm
        mov ds, [bp + 10]  ;lähdesegmentti
        mov si, [bp + 8]   ;lähdesiirros indeksirekisteriin
        mov es, [bp + 6]   ;kohdesegmentti
        mov di, [bp + 4]   ;kohdesiirros indeksirekisteriin
        rep movsb          ;suoritetaan kopiointi
        mov ax, [bp + 12]  
        sub ax, cx         ;paluuarvo AX:ään
   ;rekisterien palautus:
        pop cx
        pop di
        pop si
        pop es
        pop ds
        pop bp
        ret 10   ;10 tavun vapautus pinosta
_strcpy endp

        end      
