        ;RaTol Symbolinen konekieli: Harjoitus 5, tehtävä 2
        ;Tero Kukka IY96A

        ;Tiedosto: asekesk.asm Versio 1.0
        ;Luotu 19.4.1998

        ;Aliohjelma _aseta_kesk
        ;Asettaa keskeytysvektoritaulukkoon annetun keskeytyspalveluohjelman
        ;Parametrit: palveluohjelman segm. ja siirros sekä keskeytystyyppinro.
        
        public _aseta_kesk
        
        .model large        ;HUOM. muistimalli

        .stack  200h        ;HUOM. pinon koko

        .data                   

        .code           

_aseta_kesk   proc           
        push bp
        mov bp, sp              ;PINO: parametrit, CS, IP, BP
        push ds
        push bx
        push dx
        
        mov ax, 0
        mov ds, ax              ;vektoritaulukon alku 0000H:0000H
        mov bx, [bp + 6]        ;tyyppinro pinosta
        cmp bx, 255
        ja VIRHE
        sal bx, 2               ;siirros = 4 x tyyppinro
        mov dx, [bp + 8]        ;kesk.palv. segm.
        mov ax, [bp + 10]       ;kesk.palv. offset
        cli
        mov [bx], ax            ;IP:n arvo 
        mov [bx + 2], dx        ;CS:n arvo
        sti
        xor ax, ax              ;OK
        jmp LOPPU
VIRHE:
        mov word ptr ax, -1
LOPPU:
        pop dx
        pop bx
        pop ds
        pop bp
        ret
_aseta_kesk  endp

        end      
