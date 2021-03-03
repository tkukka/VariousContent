
        ;RaTol Symbolinen konekieli: Harjoitus 4, tehtävä 4
        ;Tero Kukka IY96A

        ;Tiedosto: vrtjono.asm  
        ;Luotu 13.4.1998

        include a:makrot.txt
                
        ;Aliohjelma _vrt_jono:
        ;Parametrit: 1. siirros tutkittavaan jonoon,
        ;2. siirros etsittävään jonoon,  3. datasegmentti
        ;ja 4. merkkien lkm

        public _vrt_jono

        .model small    ;muistimalli
        .stack 00h      ;pinon koko 

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_vrt_jono proc 
        ;rekisterien tallennus
        push bp                 ;pinossa: param., ip, bp
        mov bp, sp              ;kopioidaan sp
        push cx
        push ds
        push es
        push si
        push di

        cld                     ;kasvavat osoitteet
        mov cx, [bp + 4]        ;verrattavien merkkien lkm
        mov ds, [bp + 6]
        mov es, [bp + 6]        ;ES = DS
        mov di, [bp + 8]        ;vertailujonon siirros
        mov si, [bp + 10]       ;tutkittavan jonon siirros

        repe cmpsb
        cmpsb           ;varmistetaan eripituisten jonojen erilaisuus
        jz LOYTYI
        mov word ptr ax, 1      ;jonot ovat erilaiset
        jmp LOPPU
LOYTYI:
        xor ax, ax
LOPPU:
        ;rekisterien palautus:
        pop di
        pop si
        pop es
        pop ds
        pop cx
        pop bp
        ret 
_vrt_jono endp

        end      
