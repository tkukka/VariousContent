        ;RaTol Symbolinen konekieli: Harjoitus 4, tehtävä 3
        ;Tero Kukka IY96A

        ;Tiedosto: teht43.asm Versio 1.0
        ;Luotu 13.4.1998

        include a:makrot.txt

        ;Ohjelman kuvaus:
        ;Luetaan päätteeltä N kpl oppilaiden nimiä sekä arvosanat
        ;ja tulostetaan ne.

        ;Ulkoiset aliohjelmat: 
        extrn _lue_nimet: proc
        extrn _tulosta_jonot: proc
        
        ;Vakiot
N equ   3         ;nimien lkm
MERKKEJA equ 15   ;nimen maksimipituus
TIETUEKOKO equ MERKKEJA + 3

Oppilastiedot struc
        nimi db MERKKEJA dup(0), '$'
        arvosana dw ?
Oppilastiedot ends
        
        .model small    ;muistimalli

        .stack 100h     ;pinon koko

        .data           ;muuttujalohko

;merkkipuskurin varaaminen:
puskuri  db  MERKKEJA+1, 0, MERKKEJA+1 dup('X'), '$'
oppilas  Oppilastiedot N dup(?)

        ;Näytölle tulostuvat tekstit:
kehote1  db  0ah, 0dh, "Anna ", '$'  
kehote2  db  " nimeä:", 0ah, 0dh, '$'
kehote3  db  " arvosanaa:", 0ah, 0dh, '$'
tuloste  db  0ah, 0dh, "Syötetyt nimet ja arvosanat:", 0ah, 0dh, '$'

        .code           ;ohjelmakoodi alkaa

_main   proc                    ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax

;nimien syöttö:

        tulosta kehote1
        mov byte ptr al, N      ;ladataan vakio N AL:ään
        bin2ascii al            ;muunnos asciiksi
        tulosta_ascii al        ;tulostetaan luku ascii-muodossa
        tulosta kehote2
        
        ;parametrit pinoon:

        mov ax, offset oppilas
        push ax                 ;tietuetaulukon siirros pinoon
        push TIETUEKOKO         ;yhden tietueen koko
        mov ax, offset puskuri  
        push ax                 ;merkkipuskurin siirros
        push ds                 ;datasegm.
        push N                  ;nimien lkm
        call _lue_nimet         ;luetaan nimet päätteeltä
        add sp, 10              ;10 tavun vapautus pinosta

;arvosanojen syöttö:

        tulosta kehote1
        mov byte ptr al, N
        bin2ascii al
        tulosta_ascii al
        tulosta kehote3

        ;luetaan arvosanat:
        mov cx, N
        mov di, offset oppilas.arvosana
LUUPPI:
        lue_luku di             ;luetaan makrolla luku muistiin
        rivin_vaihto
        add di, TIETUEKOKO      ;seur. tietueen word-kenttä
        loop LUUPPI
        
;nimien tulostus alkaa:

        tulosta tuloste
        mov ax, offset oppilas  
        push ax                 ;siirros tietuetaulukkoon
        push TIETUEKOKO         ;tietueen koko pinoon
        push ds                 ;datasegm. pinoon
        push N                  ;pinoon jonojen lkm
        call _tulosta_jonot     ;tulostetaan nimet
        add sp, 8               ;8 tavun vapautus pinosta

;tulostetaan arvosanat:

        rivin_vaihto
        mov cx, N
        mov di, offset oppilas.arvosana
LUUPPI2:
        tulosta_luku di         ;makrolla tulostetaan luku muistista
        rivin_vaihto
        add di, TIETUEKOKO      ;seur. tietueen kenttä
        loop LUUPPI2
        
        exit 0                  ;lopetus

_main   endp
        end _main               ;pääohjelman loppu
