        ;RaTol Symbolinen konekieli: Harjoitus 5, tehtävä 4
        ;Tero Kukka IY96A

        ;Tiedosto: luekesk.asm Versio 1.0
        ;Luotu 22.4.1998

        ;Aliohjelma _lue_kesk
        ;Lukee keskeytysvektoritaulukosta annetun tyyppinumeron perusteella
        ;ko. käsittelijän CS:n ja IP:n.
        ;Parametrit: dummy1, dummy2 ja tyyppinro. 
       

        public _lue_kesk
        
        .model large        ;HUOM. muistimalli

        .stack  00h         ;pinon koko

        .data                   

        .code           

_lue_kesk   proc           
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
        mov ax, [bx]            ;IP:n arvo 
        mov dx, [bx + 2]        ;CS:n arvo
        mov [bp + 8], dx        ;kesk.palv. segm.
        mov [bp + 10], ax       ;kesk.palv. offset

        xor ax, ax              ;OK
        jmp LOPPU
VIRHE:
        mov word ptr ax, 0ffh
LOPPU:
        pop dx
        pop bx
        pop ds
        pop bp
        ret
_lue_kesk  endp

        end      
