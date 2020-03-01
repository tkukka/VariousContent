        ;RaTol Symbolinen konekieli: Harjoitus 3, tehtävä 3
        ;Tero Kukka IY96A

        ;Tiedosto: teht33.asm Versio 1.1
        ;Luotu 18.4.1998

        include a:makrot.txt

        ;Ohjelman kuvaus:
        ;Pinoon tallennetaan AX-rekisterin sisältö heksalukuina (4 kpl)
        ;ja tulostetaan ne _print-aliohjelmassa.

        ;Ulkoinen aliohjelma _print
        extrn _print: proc

        ;Vakiot:

HEKSALUKUJA  equ 4
        
        .model small    ;muistimalli

        .stack 100h     ;pinon koko

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa

_main   proc            ;pääohjelma 

        mov ax, 9ed7h      ;kokeiluarvo AX:ään
        mov cx, (HEKSALUKUJA-1) * 4  ;ladataan siirrettävien bittien alkuarvo
LUUPPI:
        erota_hex_DX ax, cx  ;makro erottaa hex-luvun DX:ään
        push dx         ;luku pinoon esim. 000Eh
        sub cx, 4
        jge LUUPPI
                        ;nyt pinossa on 4 heksalukua parametreina
        call _print     ;tulostetaan kahdella eri tavalla
                        ;AX ei säily
 
        exit 0          ;lopetus

_main   endp
        end _main       ;ohjelman loppu
