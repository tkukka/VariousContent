        ;RaTol Symbolinen konekieli: Koetehtävä 1d
        ;Tero Kukka IY96A

        ;Tiedosto: koeali1.asm Versio 1.0
        ;Luotu 27.4.1998

        ;Aliohjelma _f: near
        ;Parametrit: KOKO, DS, Offset

        include a:makrot.txt

        ;Ulkoiset aliohjelmat:

        ;extrn _: far/near
        ;extrn _: far/near

        ;Vakiot:
        
        public _f     ;
        
        .model small        ;HUOM!! muistimalli

        .stack  100h        ;HUOM. pinon koko

        .data                   

x       dw 0
        .code           

_f proc           
        push bp
        mov bp, sp              ;PINO: parametrit,  IP, BP
        push ds
        push es
        push bx
        push cx
        push dx
        push si

        mov ax, @data
        mov es, ax              ;aliohjelman DS

        mov cx, [bp + 8]        ;koko
        mov ds, [bp + 6]        ;pääohjelman DS
        mov bx, [bp + 4]        ;offset taulu

        mov al, [bx]            ;1. luku
        mov ah, 0

        inc bx                  ;osoittaa nyt 2. lukuun
        mov dh, 0               ;varmistetaan
        mov dl, [bx]            ;
        mov si, dx              ;si on kertoja
        mov word ptr dx, 0      ;

        dec cx                  ;kertolaskuja KOKO -1
KERRO:
        imul si
        inc bx
        push dx
        mov dh, 0
        mov dl, [bx]            ;byte-arvo
        mov si, dx              ;seur. kertoja SI:hin
        pop dx
        loop KERRO

        mov es: x, ax
        mov word ptr ax, offset x  

        pop si
        pop dx
        pop cx
        pop bx
        pop es
        pop ds
        pop bp
        ret
_f endp

        end      
