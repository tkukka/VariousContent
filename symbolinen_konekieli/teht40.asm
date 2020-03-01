        ;RaTol Symbolinen konekieli: Harjoitus 4, tehtävä 0
        ;Tero Kukka IY96A

        ;Tiedosto: teht40.asm 
        ;Luotu 4.4.1998

        include a:makrot.txt

        ;Ohjelman kuvaus:
        ;Tallennetaan pinoon kahden merkkijonon sijainti
        ;(segmentti ja offset). Pinossa on myös kopioitavien
        ;merkkien lukumäärä. Aliohjelma _strcpy palauttaa
        ;kopioitujen merkkien lukumäärän.
                
        ;Ulkoinen aliohjelma _strcpy

        extrn _strcpy: proc

        .model small    ;muistimalli

        .stack 100h     ;pinon koko

        .data           ;muuttujalohko
lahdejono   db "0123456789abc", '$'
kohdejono   db 10 dup('X'), '$'
jono1   db 0ah, 0dh, "Jono1 sisältö:", '$'
jono2   db 0ah, 0dh, "Jono2 sisältö:", '$'
kehote  db 0ah, 0dh,"Anna kopioitavien merkkien lukumäärä (max=9): ", '$'
tulos   db 0ah, 0dh,"Merkkejä kopioitui ", '$'

        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax
        tulosta jono1
        tulosta lahdejono
        tulosta jono2
        tulosta kohdejono
        tulosta kehote
        lue_ascii_al    ;luetaan yksi ascii-merkki
        ascii2bin al    ;ja muunnetaan se binääriluvuksi
        xor ah, ah      ;AH nollattava koodin toimimiseksi
        push ax         ;kopioitavien merkkien lkm pinoon
        push ds         ;datasegmentti pinoon
        mov ax, offset lahdejono
        push ax         ;1. jonon siirros pinoon
        push ds
        mov ax, offset kohdejono
        push ax         ;2. jonon siirros pinoon
        call _strcpy    ;kopioidaan jonosta toiseen
        tulosta tulos
        bin2ascii al    ;muunnos binäärimuotoon
        tulosta_ascii al ;kopioitujen merkkien lkm näkyville
        tulosta jono2
        tulosta kohdejono
        exit 0          ;lopetus

_main   endp
        end _main       ;ohjelman loppu
