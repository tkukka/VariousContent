        ;RaTol Symbolinen konekieli: Koetehtävä 
        ;Tero Kukka IY96A

        ;Tiedosto: palvelu.asm 
        ;Luotu 27.4.1998

        ;Keskeytyspalvelu _kp

        public _kp   ;!

        public laskuri
        public taulu
        
        .model large        ;! Huom. muistimalli

        .stack  0h          ;! pinon koko

        .data                   

laskuri dw 0
taulu   dw 10 dup(0)

        .code           

_kp proc
        push ds
        push ax
        push bx
        push di

        mov ax, @data
        mov ds, ax

        mov bx, offset taulu
        mov di, laskuri
        sal di, 1       ;word ptr!
        inc word ptr [bx + di]

        inc laskuri
        cmp laskuri, 10
        jnz OHI
        mov laskuri, 0
OHI:
        pop di
        pop bx
        pop ax
        pop ds       
        iret                    ;!
_kp endp

        end      
