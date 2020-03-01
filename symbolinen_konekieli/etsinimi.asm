
        ;RaTol Symbolinen konekieli: Harjoitus 4, tehtävä 4
        ;Tero Kukka IY96A

        ;Tiedosto: etsinimi.asm  Versio 1.0
        ;Luotu 13.4.1998

        include a:makrot.txt

        ;Ulkoinen aliohjelma _vrt_jono:

        extrn _vrt_jono: proc
        
        ;Aliohjelma _etsi_nimi:
        ;Parametrit: 1. merkkien lkm, 2. siirros tietuetaulukkoon,
        ;3. tietueen koko, 4. datasegmentti, 5. jonojen lkm ja
        ;6. siirros etsittävään m.jonoon

        public _etsi_nimi

        .model small    ;muistimalli

        .stack 100h      ;pinon koko

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_etsi_nimi proc 
        ;rekisterien tallennus
        push bp                 ;pinossa: param., ip, bp
        mov bp, sp              ;kopioidaan sp
        push cx
        push ds
        push si
        push bx

        xor bx, bx              ;BX = 0
        mov cx, [bp + 6]        ;jonojen lkm
        mov si, [bp + 12]       ;tietuetaulukon siirros
SILMUKKA:
        push si                 ;pinoon tutkittava jonon siirros
        push [bp + 4]           ;pinoon etsittävän jonon siirros
        push [bp + 8]           ;datasegm. pinoon
        push [bp + 14]          ;merkkien lkm pinoon
        call _vrt_jono          ;palautusarvo = 0, jos jonot ovat samat
        add sp, 8 
        add si, [bp + 10]       ;seur. tietue vertailtavaksi
        or ax, ax               ;onko AX != 0?
        jnz OHI
        inc bx
OHI:
        loop SILMUKKA
        mov ax, bx              ;palautetaan löytyneiden nimien lkm
        ;rekisterien palautus:
        pop bx
        pop si
        pop ds
        pop cx
        pop bp
        ret          
_etsi_nimi endp

        end      
