        ;RaTol Symbolinen konekieli: Harjoitus 5, tehtävä 4
        ;Tero Kukka IY96A

        ;Tiedosto: lueaika.asm Versio 1.0
        ;Luotu 26.4.1998

        ;Aliohjelma _lue_aika: far
        ;Param. DS, offset tunnit, offset minuutit, offset sekunnit

        include a:makrot.txt

        ;Ulkoiset aliohjelmat:

        extrn _lue_ascii: far
        extrn _dec2hex: far

        ;Vakiot:

NUMEROITA equ 2
        
        public _lue_aika
        
        .model large        ;HUOM. muistimalli

        .stack  100h        ;HUOM. pinon koko

        .data                   

kehote1 db 0ah, 0dh, "Anna tunnit:$"
kehote2 db 0ah, 0dh, "Anna minuutit:$"
kehote3 db 0ah, 0dh, "Anna sekunnit:$"
des_luvut dw 2 dup(0)

        .code           

_lue_aika proc           
        push bp
        mov bp, sp              ;PINO: parametrit, CS, IP, BP
        push ds
        push es
        push bx
        push cx
        push di
        push si

        mov ax, @data
        mov ds, ax              ;tulostusta varten ladattava 
        mov es, [bp + 12]       ;ladataan pääohjelman ds
        mov word ptr si, 10     ;tuntien sijainti pinossa
ALKU:
        cmp si, 8
        jz KEH_2
        cmp si, 6
        jz KEH_3
        tulosta kehote1
        jmp OHI
KEH_2:
        tulosta kehote2
        jmp OHI
KEH_3:
        tulosta kehote3
OHI:
        xor di, di
        mov cx, NUMEROITA
LUE:
        call _lue_ascii
        mov byte ptr des_luvut[di], al
        add di, 2
        loop LUE

        push NUMEROITA
        push ds
        mov ax, offset des_luvut
        push ax
        call _dec2hex
        pop ax
        add sp, 4
        mov bx, [bp + si]       ;kirjataan h, min tai s
        mov es:[bx], ax
        sub si, 2
        cmp si, 4
        jz LOPETUS
        jmp ALKU
LOPETUS:
        xor ax, ax              ;AX = OK

        pop si
        pop di
        pop cx
        pop bx
        pop es
        pop ds
        pop bp
        ret
_lue_aika endp

        end      
