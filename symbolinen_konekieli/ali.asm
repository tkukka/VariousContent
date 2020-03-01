        ;RaTol Symbolinen konekieli: Koetehtävä
        ;Tero Kukka IY96A

        ;Tiedosto: ali.asm Versio 1.0
        ;Luotu 27.4.1998

        ;Aliohjelma _: far/near
        ;Parametrit: ?

        include a:makrot.txt

        ;Ulkoiset aliohjelmat:

        ;extrn _: far/near
        ;extrn _: far/near

        ;Vakiot:
        
        public _ali     ;
        
        .model small        ;HUOM!! muistimalli

        .stack  100h        ;HUOM. pinon koko

        .data                   

kehote db 0ah, 0dh, "Toimii$"

        .code           

_ali proc           
        push bp
        mov bp, sp              ;PINO: parametrit, (CS,) IP, BP
        push ds

        mov ax, @data
        mov ds, ax   
        tulosta kehote

LOPETUS:
        xor ax, ax              ;AX = OK

        pop ds
        pop bp
        ret
_ali endp

        end      
