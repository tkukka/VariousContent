        ;RaTol Symbolinen konekieli: koeteht 2
        ;Tero Kukka IY96A

        ;Tiedosto: alik2.asm
        ;Luotu 27.4.1998

        ;Aliohjelma _etsi:

        public _etsi  ;near

        .model small    ;huom! muistimalli
        .stack  00h     ;pinon koko

        .data           ;muuttujalohko

        .code

_etsi  proc
        push bp
        mov bp, sp
        push dx
        push di

        mov word ptr ax, 0

        mov dx, [bp + 6]	;etsittävä tavu
        mov di, [bp + 4]   ;jonon offset

ALKU:
        cmp byte ptr [di], 0		;onko loppumerkki?
        jz LOPPU
        cmp [di], dl
        jnz OHI
        inc ax
OHI:
        inc di
		  jmp ALKU
LOPPU:

        pop di
        pop dx
        pop bp
        ret
_etsi endp

        end
