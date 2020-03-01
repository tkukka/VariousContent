        ;RaTol Symbolinen konekieli: Harjoitus 3, tehtävä 2
        ;Tero Kukka IY96A

        ;Tiedosto: teht32.asm Versio 1.1
        ;Luotu 5.4.1998

        include a:makrot.txt

        ;Ohjelman kuvaus:
        ;Luetaan kaksi ascii-merkkiä (esim. '2' ja '9') ja muutetaan
        ;ne binääriksi AL:ään (esim. AL = 29).
        
        .model small    ;muistimalli
        .stack 100h     ;pinon koko 

        .data           ;muuttujalohko
kehote  db 0ah, 0dh, "Anna kaksi ascii-merkkiä: ", '$'
tuloste db 0ah, 0dh, "Syötit luvun ", '$'

        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax

        tulosta kehote
        lue_ascii_AL    ;luetaan 1. merkki
        ascii2bin al    ;merkki binääriseksi
        siirra_vas al, 4  ;bittien siirto vasemmalle
        mov dl, al      ;kopioidaan AL DL:ään talteen
        lue_ascii_AL    ;luetaan 2. merkki
        ascii2bin al    ;merkki binääriluvuksi
        add al, dl      ;nyt AL:ssä kaksi BCD-lukua

        tulosta tuloste
        xor dh, dh       ;varmistetaan etunollat bittien siirrossa
        siirra_oik dx, 4 ;DL:ssä on 1. merkki, jonka bittejä siirretään.
        bin2ascii dl     ;muunnos ascii-merkiksi
        tulosta_ascii dl ;tulostetaan 1. luku
        and al, 0Fh      ;nollataan AL:n neljä ylimmäistä bittiä
        mov dl, al       ;kopioidaan AL DL:ään
        bin2ascii dl     ;muunnos ascii-merkiksi
        tulosta_ascii dl  ;tulostetaan 2. luku

        exit 0  

_main   endp
        end _main       ;ohjelman loppu
