
        ;RaTol Symbolinen konekieli: Harjoitus 3, tehtävä 3
        ;Tero Kukka IY96A

        ;Tiedosto: print.asm Versio 1.1
        ;Luotu 18.4.1998

        include a:makrot.txt

        ;Ulkoinen aliohjelma _print_ascii

        extrn _print_ascii: proc

        ;Vakiot:
HEKSALUKUJA  equ 4

        ;Aliohjelma _print; Tulostaa heksalukuja PINOSTA
        ;Parametrina 4 heksalukua (word).

        public _print
                
        .model small    ;muistimalli

        .stack  100h    ;pinon koko

        .data           ;muuttujalohko
teksti  db 0ah, 0dh, "16-bittinen hex-luku: 0x", '$'

        .code           ;ohjelmakoodi alkaa

_print  proc 
        ;rekisterit talteen:
        push bp        ;pinossa param., ip, bp
        mov bp, sp     ;kopioidaan sp
        push di
        push ds
        mov ax, @data
        mov ds, ax

;******   a-kohta:  Makrolla tulostus  *********************
        tulosta teksti

        ;tulostetaan kaikki luvut ensimmäisestä alkaen. DI on indeksinä.
        mov word ptr di, 2*HEKSALUKUJA+2  ;1. luvun paikka pinossa
ALKU:
        tulosta_pinosta1 di  ;tulostetaan yksi luku pinosta makrolla
        sub di, 2       
        cmp di, 2       ;jos DI <= 2, lopetetaan
        jle LOPPU
        jmp ALKU
LOPPU:

;******    b-kohta: Aliohjelmalla tulostus  *****************
        tulosta teksti

        ;tulostetaan kaikki luvut ensimmäisestä alkaen. DI on indeksinä.
        mov word ptr di, 2*HEKSALUKUJA+2  ;1. luvun paikka pinossa
ALKU2:        
        push [bp + di]     ;aliohjelman parametriksi pinossa ollut luku
        call _print_ascii    ;tulostetaan pinossa ollut luku aliohjelmalla
        sub di, 2
        cmp di, 2       ;jos DI <= 2, lopetetaan
        jle LOPPU2
        jmp ALKU2
LOPPU2:
        mov ax, 0       ;OK-arvo
        pop ds
        pop di
        pop bp
        ret 2*HEKSALUKUJA ;8 tavun (4 word) vapautus paluun jälkeen
_print  endp

        end   
