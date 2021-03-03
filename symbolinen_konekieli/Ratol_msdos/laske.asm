
        ;RaTol Symbolinen konekieli: koetehtävä 2
        ;Tero Kukka IY96A

        ;Tiedosto: laske.asm
        ;Luotu 26.2.1998

        ;Aliohjelma _laske
        ;Hakee taulukon osoitteen PINOSTA

        ;Aliohjelmien esittely:

        public _laske

        .model small    ;muistimalli
        .stack  00h     ;pinon koko 

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_laske  proc           ;int _laske(int *taulu);             
        ;rekisterit talteen
        push bp        ;pinossa &taulu, ip, bp
        push di        ;pinossa &taulu, ip, bp, di
        push ax
        push bx
        push cx         ;pino: &taulu, ip, bp, di, ax, bx, cx

        mov bp, sp     ;Kopioidaan sp
        mov di, [bp + 12] ;siirros di-rekisteriin
        mov ax, [di]      ;1. luku
        mov bx, [di + 2]  ;2. luku
        mov cx, [di + 4]  ;3. luku

        cmp ax, 1
        jz SUMMA

        cmp ax, 2
        jz EROTUS

        cmp ax, 3
        jz PIENIN

        ;MUU
        mov ax, 0
        jmp LOPPU
SUMMA:
        add bx, cx
        mov ax, bx
        jmp LOPPU

EROTUS:
        sub bx, cx
        mov ax, bx
        jmp LOPPU

PIENIN:
        cmp bx, cx
        jnc PALAUTA_CX  ;hyppy, jos CF=0
        mov ax, bx      ;bx < cx
        jmp LOPPU

PALAUTA_CX:
        mov ax, cx


LOPPU:
        pop cx         ;rekisterien palautus
        pop bx
        pop ax
        pop di
        pop bp         
        ret 2          ;2 tavun vapautus paluun jälkeen
_laske endp

        end      
