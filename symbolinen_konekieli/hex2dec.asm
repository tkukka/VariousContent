        ;RaTol Symbolinen konekieli: 
        ;Tero Kukka IY96A

        ;Tiedosto: hex2dec.asm
        ;Luotu 25.4.1998

        include a:makrot.txt

        ;Muuntaa hex-luvun 10-järjestelmään. Suurin hex-luku 0009 fff6h.
        ;eli 655 350 (dec). Parametrit: word-taulukon (1 nro = 2 tavua;
        ;max 6 alkioinen) segm. ja siirros sekä hex-luku kahtena wordinä.

        public _hex2dec

        .model large    ;muistimalli

        .stack 00h      ;pinon koko

        .data           

        .code          

_hex2dec proc            
        push bp
        mov bp, sp              ;pinossa param., CS, IP ja BP
        push ds
        push bx
        push dx
        push cx
        push di

        xor di, di              ;laskurin nollaus
        mov ax, [bp + 6]        ;alempi sana
        mov dx, [bp + 8]        ;ylempi sana
        cmp dx, 9               ;muunnettava luku ei saa ylittää
        jb OHI2                 ;arvoa 9fff6h
        jz OHI1
        mov byte ptr ax, -1     ;virhe
        jmp LOPPU
OHI1:
        cmp ax, 0fff6h
        jbe OHI2
        mov byte ptr ax, -1     ;virhe
        jmp LOPPU
OHI2:
        mov bx, [bp + 10]       ;taulukon siirros
        mov ds, [bp + 12]       ;datasegm.
        mov cx, 10              ;jaetaan 10:llä
JAA:
        div cx
        ;dx:stä luku talteen
        mov [bx], dx
        add bx, 2               ;word ptr
        inc di
        or ax, ax
        jz LOPPU
        xor dx, dx
        jmp JAA
LOPPU:
        mov [bp + 6], di
        pop di
        pop cx
        pop dx
        pop bx
        pop ds
        pop bp
        ret
_hex2dec endp
        end 

