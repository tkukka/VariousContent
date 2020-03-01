        ;RaTol Symbolinen konekieli: Harjoitus 1, tehtävä 3
        ;Tero Kukka IY96A

        ;Tiedosto: teht13.asm
        ;Luotu 4.2.1998
        ;Hyväksytty []

        ;Ohjelmalla testataan, mihin rekistereihin voidaan sijoittaa
        ;välittömällä osoituksella vakio N. Rekisterit AX - DX eivät
        ;tuota ongelmia. Segmenttirekistereihin CS - ES ei voi käyttää
        ;suoraa osoitusta. CS-rekisteri on koodin kannalta tärkeä, sitä
        ;ei kannata muuttaa. Samoin pinon SS-rekisteriä.
        ;DS asetus on sallittu muulla tavalla.
        ;SI, DI ja BP-rekisterien arvot ovat ohjelmoijan asetettavissa.
        ;SP:n väärä arvo sekoittaa koneen hyvin todennäköisesti.
        ;IP:hen ei voi vaikuttaa suoraan, eikä kannatakaan.
        
        ;Vakiot 
N  EQU  0003h

        ;Makrot

exit    MACRO           ;esimerkkimakro 'exit'
         mov ax, 4c00h
         int 21h
        ENDM

        .model small    ;muistimalli
        .stack 00h      ;pinon koko

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma alkaa

        mov ax, N       ;ok
        mov bx, N       ;ok
        mov cx, N       ;ok
        mov dx, N       ;ok

        ;mov cs, N      ;"laiton segmenttirekisterin käyttö"
        ;mov ds, N      ;    - " -
        ;mov ss, N      ;    - " -   
        ;mov es, N      ;    - " -   

        mov si, N       ;meni läpi
        mov di, N       ;meni läpi
        mov bp, N       ;meni läpi       
        ;mov sp, N      ;"laiton toiminto" Windowsissa
        ;mov ip, N      ;ei käännä, kun ei tunne ip:tä
        
        exit            ;lopetusmakro

_main   endp
        end _main       ;pääohjelman loppu

