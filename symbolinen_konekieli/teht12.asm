        ;RaTol Symbolinen konekieli: Harjoitus 1, tehtävä 2
        ;Tero Kukka IY96A

        ;Tiedosto: teht12.asm
        ;Luotu 29.1.1998
        ;Hyväksytty []

        ;Ohjelma siirtää 8-bittisiin rekistereihin erilaisia
        ;vakioarvoja.
        
        ;Makrot

exit    MACRO           ;lopetusmakro 
         mov ax, 4c00h
         int 21h
        ENDM

        .model small    ;muistimalli
        .stack 00h     ;pinon koko

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma alkaa

        mov al, 'a'     ;ax = 0061h (ascii-koodi)
        mov bl, 10      ;bx = 000Ah  (muuntui heksaksi)
        mov cl, 0110011b ;cx = 0033h (muuntui heksaksi)
        mov ah, 0fah    ;ax = fa61h '61' on jo asetettu al:ään
        
        exit            ;lopetusrutiini, esimerkiksi makrolla

_main   endp
        end _main       ;pääohjelman loppu

