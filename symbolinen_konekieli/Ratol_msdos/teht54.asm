        ;RaTol Symbolinen konekieli: Harjoitus 5, tehtävä 4
        ;Tero Kukka IY96A

        ;Tiedosto: teht54.asm 
        ;Luotu 25.4.1998 Versio 1.2

        include a:makrot.txt

        ;Kello-ohjelma
                
        ;Ulkoiset aliohjelmat:

        extrn _lue_kesk: far
        extrn _lue_aika: far
        extrn _aseta_kesk: far
        extrn _palvelu: far             ;kesk.palv.
        extrn _paivita: far

        extrn laskuri: word
        extrn laskuri91: word           ;5 sekunnin laskuri

        ;Vakiot:

KESKEYTYSNRO equ 1ch    ;timer-keskeytys
KESK_PER_SEK equ 18     ;keskeytyksiä sekunnissa
KESK_5_SEK   equ 91     ;keskeytyksiä 5 sekunnissa
VERSIO equ "1.2"

Aika    struc           ;määritellään tietue 'Aika'
        riv_vaih db 0ah, 0dh
        tunti    db "00:"
        minuutti db "00:"
        sekunti  db "00$"
Aika    ends

        .model large    ;Huom. muistimalli

        .stack 100h     ;pinon koko

        .data           ;muuttujalohko

wanha_seg dw 0          ;entisen kesk.palv. segmentti
wanha_off dw 0          ;entisen kesk.palv. siirros
tunnit    dw 0
minuutit  dw 0
sekunnit  dw 0
dec_luvut dw 2 dup(0)   ;taulukko 10-järjestelmän numeroille
kello   Aika {}         ;kello-tietue alustetaan oletusarvoilla 
alkutuloste db 0ah, 0dh, "Kello (Versio "
        db VERSIO
        db ")$"
aloitus dw 1            ;varmistaa kellon oikean näyttämän alussa

        .code         

_main   proc                    ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax

        tulosta alkutuloste

        ;olemassaolevan palvelun lukeminen:

        push ax                 ;kaksi "tyhjää" pushia:
        push ax                 ;varataan tilaa paluuarvoille
        push KESKEYTYSNRO
        call _lue_kesk
        pop ax                  ;"tyhjä" pop
        pop wanha_seg           ;poimitaan data pinosta
        pop wanha_off
        
        ;kysytään kellonaika:

        push @data
        mov ax, offset tunnit
        push ax
        mov ax, offset minuutit
        push ax
        mov ax, offset sekunnit
        push ax
        call _lue_aika
        add sp, 8

        ;keskeytyspalvelijan asetus:

        mov ax, offset _palvelu
        push ax
        mov ax, seg _palvelu
        push ax
        push KESKEYTYSNRO
        call _aseta_kesk
        add sp, 6

        ;toiminta:

ALKU: 
        mov ax, laskuri91
        cmp ax, KESK_5_SEK      ;onko 5 sekuntia kulunut?
        jz POIS
        mov ax, laskuri
        cmp ax, KESK_PER_SEK    ;onko 1 sekunti kulunut?
        jnz ALKU
        jmp YLI                 ;ei nollata 5 sekunnin laskuria
POIS:
        mov laskuri91, 0        ;tasan 5 sekuntia kulunut
YLI:
        mov laskuri, 0
        inc sekunnit
        cmp sekunnit, 60        ;onko minuutti tullut täyteen?
        jb OHI
        mov sekunnit, 0         ;minuutti täynnä
        inc minuutit
        cmp minuutit, 60        ;onko tunti tullut täyteen?
        jnz ohi
        mov minuutit, 0         ;tunti on kulunut
        inc tunnit
        cmp tunnit, 24          ;vaihtuuko vuorokausi?
        jnz ohi
        mov tunnit, 0           ;uusi vuorokausi alkaa
OHI:    
 ;*********    sekuntiluvun muunto   ******************

        push ds
        mov ax, offset dec_luvut
        push ax
        push sekunnit
        mov ax, offset kello.sekunti
        push ax
        call _paivita
        add sp, 8

 ;++++++++++  minuuttiluvun muunto  ++++++++++++++++
        cmp aloitus, 0          ;ihka ensimmäinen tulostus?
        jnz PAIV1

        cmp sekunnit, 0         ;optimoidaan muunto ja paivitys vain minuutin
        jnz TULOSTUS            ;vaihtumishetkelle
PAIV1:
        push ds
        mov ax, offset dec_luvut
        push ax
        push minuutit
        mov ax, offset kello.minuutti
        push ax
        call _paivita
        add sp, 8

 ;-------  tuntiluvun muunto   -----------------------
        cmp aloitus, 0          ;ihka ensimm. tulostus?
        jnz PAIV2

        cmp sekunnit, 0         ;optimoidaan muunto ja paivitys vain tunnin
        jnz TULOSTUS            ;vaihtumishetkelle
        cmp minuutit, 0
        jnz TULOSTUS
PAIV2:
        push ds
        mov ax, offset dec_luvut
        push ax
        push tunnit
        mov ax, offset kello.tunti
        push ax
        call _paivita
        add sp, 8

TULOSTUS:
        tulosta kello
        mov aloitus, 0          ;1. tulostus ohi
        mov ah, 1               ;tutkitaan, onko jotain näppäintä
        int 16h                 ;painettu
        jnz LOPPU               ;näppäimen painalluksella lopetus
        jmp ALKU
LOPPU:
        ;entisen keskeytyspalvelijan palautus:
        
        push wanha_off
        push wanha_seg
        push KESKEYTYSNRO
        call _aseta_kesk
        add sp, 6

        exit 0

_main   endp
        end _main               ;pääohjelman loppu
