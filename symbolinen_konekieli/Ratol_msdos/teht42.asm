        ;RaTol Symbolinen konekieli: Harjoitus 4, tehtävä 2
        ;Tero Kukka IY96A

        ;Tiedosto: teht42.asm versio 1.1
        ;Luotu 13.4.1998

        include a:makrot.txt

        ;Ohjelman kuvaus:
        ;Luetaan päätteeltä N kpl oppilaiden nimiä
        ;ja tulostetaan ne.

        ;Ulkoiset aliohjelmat: 
        extrn _lue_nimet: proc
        extrn _tulosta_jonot: proc
        
        ;Vakiot
N equ   3    ;nimien lkm
MERKKEJA equ 15   ;nimen maksimipituus

Oppilastiedot struc
        nimi db MERKKEJA dup(0), '$'
Oppilastiedot ends
        
        .model small    ;muistimalli

        .stack 100h     ;pinon koko

        .data           ;muuttujalohko
;merkkipuskurin varaaminen
puskuri  db  MERKKEJA+1, 0, MERKKEJA+1 dup('X'), '$'
oppilas  Oppilastiedot N dup(?)

        ;Näytölle tulostuvat tekstit:
kehote1  db  0ah, 0dh, "Anna ", '$'  
kehote2  db  " nimeä:", 0ah, 0dh, '$'
tuloste  db  0ah, 0dh, "Syötetyt nimet:", 0ah, 0dh, '$'

        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax

        tulosta kehote1
        mov byte ptr al, N      ;ladataan vakio N AL:ään
        bin2ascii al            ;muunnos asciiksi
        tulosta_ascii al        ;tulostetaan luku ascii-muodossa
        tulosta kehote2

        ;parametrit pinoon:
        mov ax, offset oppilas
        push ax                 ;tietuetaulukon siirros pinoon
        push MERKKEJA +1        ;yhden tietueen koko
        mov ax, offset puskuri  
        push ax                 ;merkkipuskurin siirros
        push ds                 ;datasegm.
        push N                  ;nimien lkm
        call _lue_nimet         ;luetaan nimet päätteeltä
        add sp, 10              ;10 tavun vapautus pinosta

        ;nimien tulostus alkaa: 
        tulosta tuloste
        mov ax, offset oppilas  
        push ax                 ;siirros tietuetaulukkoon
        push MERKKEJA +1        ;tietueen koko pinoon
        push ds                 ;datasegm. pinoon
        push N                  ;jonojen lkm pinoon
        call _tulosta_jonot     ;tulostetaan nimet
        add sp, 8               ;8 tavun vapautus pinosta

        exit 0          ;lopetus

_main   endp
        end _main       ;ohjelman loppu
