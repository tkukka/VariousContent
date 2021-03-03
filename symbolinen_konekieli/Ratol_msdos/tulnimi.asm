        ;RaTol Symbolinen konekieli: Harjoitus 5, tehtävä 2
        ;Tero Kukka IY96A

        ;Tiedosto: tulnimi.asm 
        ;Luotu 19.4.1998

        include a:makrot.txt

        ;Aliohjelma _tulosta_nimi

        public _tulosta_nimi
        
        .model large        ;huom. muistimalli

        .stack  0h          ;pinon koko

        .data                   

nimi    db 0ah, 0dh, "Tero Kukka", 0ah, 0dh, '$'

        .code           

_tulosta_nimi   proc
        push ds
        push ax

        mov ax, @data
        mov ds, ax
        tulosta nimi

        pop ax
        pop ds
        iret
_tulosta_nimi  endp

        end      
