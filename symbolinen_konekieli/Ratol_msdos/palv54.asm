        ;RaTol Symbolinen konekieli: Harjoitus 5, tehtävä 4
        ;Tero Kukka IY96A

        ;Tiedosto: palv54.asm Versio 1.01
        ;Luotu 25.4.1998

        include a:makrot.txt

        ;Keskeytyspalvelu _palvelu

        public _palvelu

        public laskuri          ;sekunnin laskuri
        public laskuri91        ;5 sekunnin laskuri
        
        .model large            ;huom. muistimalli

        .stack  50h             ;pinon koko

        .data                   
                                
laskuri dw 0                    ;sekunnin laskuri
laskuri91 dw 0                  ;5 sekunnin laskuri

        .code           

_palvelu proc
        sti                     ;sallitaan muut keskeytykset
        push ds
        push ax

        mov ax, @data
        mov ds, ax
        inc laskuri
        inc laskuri91

        pop ax
        pop ds       
        iret
_palvelu endp

        end      
