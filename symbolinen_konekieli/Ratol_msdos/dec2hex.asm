        ;RaTol Symbolinen konekieli: 
        ;Tero Kukka IY96A

        ;Tiedosto: dec2hex.asm
        ;Luotu 26.4.1998

        include a:makrot.txt

        ;Muuntaa 10-järjestelmän luvun hex-luvuksi.
        ;Suurin luku 65535 (ffffh). Parametrit: numeroiden lkm, datasegm. ja
        ;siirros nro-taulukkoon (word). 

        public _dec2hex

        .model large    ;muistimalli

        .stack 00h      ;pinon koko

        .data           

        .code          

_dec2hex proc            
        push bp
        mov bp, sp              ;pinossa param., CS, IP ja BP
        push ds
        push bx
        push dx
        push cx
        push di

        mov word ptr di, 10     ;kertojan alustus
        mov ds, [bp + 8]        ;taulukon datasegm.
        mov bx, [bp + 6]        ;siirros dec-lukuihin (word-taulu)
        mov cx, [bp + 10]       ;numeroiden lkm
        dec cx
        mov ax, [bx]            ;ladataan nro (eniten merkitsevästä päästä)
        or cx, cx
        jz YLI
KERRO:
        mul di                  ;AX = AX * DI
        add bx, 2               ;seur. nro (word ptr)
        add ax, [bx]
        loop KERRO
YLI:
        mov [bp + 6], ax        ;tulos pinoon
        xor ax, ax              ;AX = OK

        pop di
        pop cx
        pop dx
        pop bx
        pop ds
        pop bp
        ret
_dec2hex endp
        end 

