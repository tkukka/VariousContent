        ;RaTol Symbolinen konekieli: Harjoitus 4, tehtävä 1
        ;Tero Kukka IY96A

        ;Tiedosto: teht41.asm Versio 1.0
        ;Luotu 15.4.1998

        include a:makrot.txt

        ;*****    Kertolaskua taulukoilla   ********
        ;Pinoon tallennetaan datasegmentti (@data), kahden word-taulukon
        ;siirrokset, doubleword-taulukon siirros tuloksia varten ja
        ;alkioiden lkm. Kolmanteen taulukkoon sijoitetaan aliohjelmassa
        ;word-taulukot kerrottuna keskenään (etumerkillä). Aliohjelma
        ;palauttaa AX:ssä nollaa suurempien arvojen lukumäärän doubleword-
        ;taulukossa. Etumerkki otetaan huomioon tässä ratkaisussa.
                
        ;Ulkoinen aliohjelma _tulot

        extrn _tulot: proc

        ;Vakiot:

N       equ 5           ;taulukoiden alkioiden lkm
        
        .model small    ;muistimalli

        .stack 100h     ;pinon koko

        .data           ;muuttujalohko

taulu1  dw 8777h, 65, -1, 0, 1          ;alustus testausarvoilla
taulu2  dw N dup(10)
taulu3  dd N dup(0)

        .code           

_main   proc            ;pääohjelma 

        push @data      ;datasegm pinoon
        mov ax, offset taulu3
        push ax
        mov ax, offset taulu2
        push ax
        mov ax, offset taulu1
        push ax
        push N
        call _tulot
        add sp, 10      ;vapautetaan pinosta 10 tavua

        exit 0          

_main   endp
        end _main       ;loppu
