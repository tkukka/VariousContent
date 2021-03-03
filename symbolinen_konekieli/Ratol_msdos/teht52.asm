        ;RaTol Symbolinen konekieli: Harjoitus 5, tehtävä 2
        ;Tero Kukka IY96A

        ;Tiedosto: teht52.asm 
        ;Luotu 19.4.1998

        include a:makrot.txt

        ;Ohjelman kuvaus:
        ;Ohjelma asettaa keskeytyspalvelun, joka tulostaa
        ;oman nimeni. Keskeytystä kutsutaan pääohjelmasta,
        ;kun vastataan 'n' erääseen kehotteeseen.
                
        ;Ulkoiset aliohjelmat: 

        extrn _aseta_kesk: far
        extrn _tulosta_nimi: far        ;kesk.palv.

        ;Vakiot:

KESKEYTYSNRO equ 0a0h

        .model large    ;Huom. muistimalli

        .stack 100h     ;pinon koko

        .data           ;muuttujalohko

teksti  db 0ah, 0dh, "Paina n tai m tai q: ", '$'
        
        .code         

_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax

;keskeytyspalvelijan asetus:

        mov ax, offset _tulosta_nimi
        push ax
        mov ax, seg _tulosta_nimi
        push ax
        push KESKEYTYSNRO
        call _aseta_kesk
        add sp, 6

        ;Testaus:
        mov cx, 4
TOISTA:
        tulosta teksti
        lue_ascii_AL
        cmp al, 'n'
        jz KESKEYTYS
        cmp al, 'N'
        jz KESKEYTYS
        cmp al, 'm'
        jz OHI
        cmp al, 'M'
        jz OHI
        exit 0
KESKEYTYS:
        int KESKEYTYSNRO
OHI:
        loop TOISTA

        exit 0

_main   endp
        end _main       ;pääohjelman loppu
