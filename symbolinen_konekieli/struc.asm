        ;RaTol Symbolinen konekieli: Harjoitus 5, tehtävä 4
        ;Tero Kukka IY96A


        include a:makrot.txt

                
        ;Ulkoiset aliohjelmat:


        ;Vakiot:

KESKEYTYSNRO equ 1ch
KESK_PER_SEK equ 18
PAIVITYSVALI equ 1

Aika    struc
  riv_vaih db 0ah, 0dh
  tunti db "00:"
  minuutti db "00:"
  sekunti db "00$"
Aika    ends

        .model large    ;Huom. muistimalli

        .stack 100h     ;pinon koko

        .data           ;muuttujalohko

kello   Aika {}

        .code         

_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax

        tulosta kello
        
        exit 0

_main   endp
        end _main       ;pääohjelman loppu
