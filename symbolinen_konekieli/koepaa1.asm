        ;RaTol Symbolinen konekieli: Koetehtävä 1d
        ;Tero Kukka IY96A

        ;Tiedosto: koe1d.asm Versio 1.0
        ;Luotu 27.4.1998

        ;

        include a:makrot.txt

        extrn _f: near        ;!

        ;Vakiot:

KOKO equ 5

        .model small            ;HUOM. malli

        .stack 100h

        .data

taulu   db 1,2,3,4,5

        .code
_main   proc
        mov ax, @data
        mov ds, ax

        push KOKO
        push @data
        mov ax, offset taulu
        push ax
        call _f
        add sp, 6 ;!

        exit 0
_main   endp
        end _main
