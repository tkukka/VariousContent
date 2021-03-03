
        ;RaTol Symbolinen konekieli: Harjoitus 5, tehtävä 0
        ;Tero Kukka IY96A

        ;Tiedosto: h50a.asm
        ;Luotu 19.4.1998

        ;Aliohjelma _funktio:

        public _funktio

        .model large    ;huom! muistimalli
        .stack  00h     ;pinon koko 

        .data           ;muuttujalohko

        .code           

_funktio  proc           
        push bp
        mov bp, sp
        push ds
        push bx
        push ax

        mov ax, [bp + 8]
        mov ds, ax              ;datasegm. kuntoon
        mov bx, [bp + 6]        ;siirros luku1:een
        mov ax, [bp + 10]       ;luku2
        add [bx], ax
        
        xor ax, ax
        pop ax
        pop bx
        pop ds
        pop bp
        ret
_funktio endp

        end      
