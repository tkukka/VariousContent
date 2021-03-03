        ;RaTol Symbolinen konekieli: Harjoitus 4, tehtävä 1
        ;Tero Kukka IY96A

        ;Tiedosto: tulot.asm Versio 1.0
        ;Luotu 15.4.1998

        ;Aliohjelma _tulot: kertoo (IMUL:illa) kahden word-taulukon luvut
        ;keskenään ja sijoittaa tulokset doubleword-taulukkoon.
        ;Parametrit: datasegm., 1. word-taulukon siirros, 2. word-taulukon
        ;siirros, doubleword-taulukon siirros ja alkioiden lkm.

        public _tulot
        
        .model small    ;muistimalli

        .stack  00h     ;pinon koko

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_tulot   proc           
        push bp
        mov bp, sp      ;PINO: parametrit, IP, BP
        push bx
        push cx
        push dx
        push ds
        push si
        push di

;rekisterien alustukset:
        xor si, si
        xor di, di
        mov cx, [bp + 4]        ;alkioiden lkm
        mov ds, [bp + 12]       ;datasegmentin kiinnitys
KERRO:
        mov bx, [bp + 6]        ;BX = offset taulu1
        mov ax, [bx + si]
        mov bx, [bp + 8]        ;BX = offset taulu2
        mov dx, [bx + si]
        imul dx                 ;DX.AX = AX * DX
        mov bx, [bp + 10]       ;BX = offset taulu3
        mov word ptr [bx + di], ax      ;alempi sana talteen
        mov word ptr [bx + di + 2], dx  ;ylempi sana talteen

        add si, 2               ;SI word ptr
        add di, 4               ;DI doubleword ptr
        loop KERRO

;tuloksien tutkiminen:
        mov cx, [bp + 4]        ;CX, AX ja SI taas alustettava
        xor ax, ax              
        xor si, si
TUTKI:
        cmp word ptr [bx + si + 2], 0   ;ylemmän sanan vertailu
        jl OHI
        cmp word ptr [bx + si + 2], 0
        jnz KASVATA
        cmp word ptr [bx + si], 0       ;alemman sanan vertailu
        jle OHI
KASVATA:
        inc ax              ;löytyi ehdot täyttävä luku -> AX++;
OHI:
        add si, 4
        loop TUTKI

        pop di
        pop si
        pop ds
        pop dx
        pop cx
        pop bx
        pop bp
        ret
_tulot  endp

        end      
