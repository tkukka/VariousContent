        ;RaTol Symbolinen konekieli: Koetehtävä
        ;Tero Kukka IY96A

        ;Tiedosto: testmain.asm Versio 1.0
        ;Luotu 27.4.1998

        ;

        include a:makrot.txt

        extrn _ali: near        ;!

        ;Vakiot:

        .model small            ;HUOM. malli

        .stack 100h

        .data

        .code
_main   proc
        ;mov ax, @data
        ;mov ds, ax

        call _ali
        ;add sp, 

        exit 0
_main   endp
        end
