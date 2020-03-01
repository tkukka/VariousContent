        ;RaTol Symbolinen konekieli: Harjoitus 4, tehtävä 4
        ;Tero Kukka IY96A

        ;Tiedosto: teht44.asm versio 1.0
        ;Luotu 13.4.1998

        include a:makrot.txt

        ;Ohjelman kuvaus:
        ;Luetaan päätteeltä N kpl oppilaiden nimiä sekä arvosanat
        ;ja tulostetaan ne. Lisäksi etsitään haluttua nimeä tietueista.

        ;Ulkoiset aliohjelmat: 
        extrn _lue_nimet: proc
        extrn _tulosta_jonot: proc
        extrn _strcpy: proc
        extrn _etsi_nimi: proc
        
        ;Vakiot ja tietueet
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
etsittava db MERKKEJA+1 dup(?)

        ;Näytölle tulostuvat tekstit:
kehote1  db  0ah, 0dh, "Anna ", '$'  
kehote2  db  " nimeä:", 0ah, 0dh, '$'
kehote3  db  " arvosanaa:", 0ah, 0dh, '$'
tuloste  db  0ah, 0dh, "Syötetyt nimet ja arvosanat:", 0ah, 0dh, '$'
kehote4  db  "etsittävä nimi:", 0ah, 0dh, '$'
tuloste2 db  0ah, 0dh, "Nimi löytyi.", 0ah, 0dh, '$'
tuloste3 db  0ah, 0dh, "Nimeä ei löytynyt.", 0ah, 0dh, '$'

        .code                   ;ohjelmakoodi alkaa

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

;nimen etsintä:

        tulosta kehote1
        tulosta kehote4

        ;syötetään merkkijono:
        mov bx, offset puskuri
        lue_puskuriin ds, bx    ;luetaan jono kesk.palvelulla INT 21h AH=0Ah
        mov ax, [bx + 1]        
        xor ah, ah
        push ax                 ;pinoon luettujen merkkien lkm
        push ds
        mov ax, offset puskuri
        add ax, 2
        push ax                 ;siirros kopioitavan jonon alkuun
        push ds
        mov ax, offset etsittava    ;siirros kohdejonoon
        push ax
        call _strcpy            ;suoritetaan jonon kopiointi

        mov di, offset etsittava
        add di, ax                ;AX:ssä on kopioitujen merkkien lkm
        mov byte ptr [di], '$'    ;lisätään loppumerkki 

        ;parametreja pinoon:
        push ax                   ;tutkittavien merkkien lkm pinoon
        mov ax, offset oppilas
        push ax                   ;siirros tietueeseen
        push TIETUEKOKO           ;tietueen koko pinoon
        push ds                   ;datasegm.
        push N                    ;nimien lkm
        mov ax, offset etsittava
        push ax                   ;etsittavan jonon siirros pinoon
        call _etsi_nimi           ;etsitään m.jonoa
        add sp, 12                ;vapautetaan 12 tavua pinosta

        or ax, ax                 ;AX = 0, jos nimeä ei löytynyt
        jnz LOYTYI
        tulosta tuloste3          ;nimeä ei löytynyt
        jmp LOPPU
LOYTYI:
        tulosta tuloste2
LOPPU:  
        exit 0                    ;lopetus

_main   endp
        end _main                 ;pääohjelman loppu
