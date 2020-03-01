        ;RaTol Symbolinen konekieli: 
        ;Tero Kukka IY96A

        ;Tiedosto: koekesk3.asm 
        ;Luotu 27.4.1998 

        include a:makrot.txt

        ;
                
        ;Ulkoiset aliohjelmat:

        extrn _lue_kesk: far
        extrn _aseta_kesk: far
        extrn _kp: far             ;kesk.palv.

        extrn laskuri: word
        extrn taulu: word

        ;Vakiot:

KESKEYTYSNRO equ 90h

        .model large    ;Huom. muistimalli

        .stack 100h     ;pinon koko

        .data           ;muuttujalohko

wanha_seg dw 0
wanha_off dw 0

        .code         

_main   proc                    ;pääohjelma alkaa
        ;mov ax, @data
        ;mov ds, ax

        ;olemassaolevan palvelun lukeminen:

        push ax                 ;kaksi "tyhjää" pushia:
        push ax                 ;varataan tilaa paluuarvoille
        push KESKEYTYSNRO
        call _lue_kesk
        pop ax                  ;"tyhjä" pop
        pop wanha_seg           ;poimitaan data pinosta
        pop wanha_off

        ;keskeytyspalvelijan asetus:

        mov ax, offset _kp
        push ax
        mov ax, seg _kp
        push ax
        push KESKEYTYSNRO
        call _aseta_kesk
        add sp, 6

        ;testaus
        mov cx, 12
T:
        int KESKEYTYSNRO
        loop T

        push wanha_off
        push wanha_seg
        push KESKEYTYSNRO
        call _aseta_kesk
        add sp, 6

        exit 0

_main   endp
        end _main               ;pääohjelman loppu
