        ;RaTol Symbolinen konekieli: Harjoitus 2, tehtävä 1
        ;Tero Kukka IY96A

        ;Tiedosto: teht21b.asm
        ;Luotu 12.2.1998
        ;Hyväksytty []

        ;Sanojen siirtelyä paikasta toiseen

        ;Vakiot

N       equ  1100

        ;Makrot

exit    MACRO           ;esimerkkimakro 'exit'
        mov ax, 4c00h
        int 21h
        ENDM

        .model small    ;muistimalli
        .stack 100h     ;pinon koko

        .data           ;muuttujalohko

luvut1  dw  N dup(10)   ;10 näkyy muistissa 000A:na (hex)
luvut2  dw  N dup(?)


        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma alkaa
        mov ax, @data
        mov ds, ax      ;ds-rekisterin alustus

        mov cx, N       ;laskuri alkaa N:stä
        mov si, offset luvut1   ;data-alueen siirros si-rekisteriin
        mov di, offset luvut2   ;data-alueen siirros di-rekisteriin

SILMUKKA:
        mov ax, [si]    ; mov [di],[si] ei käy
        mov [di], ax    

        add si, 2       ;sanan kokoinen lisäys
        add di, 2
        loop SILMUKKA
        
        exit            ;exit 0

_main   endp
        end _main       ;pääohjelman loppu

