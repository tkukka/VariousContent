        ; iy03.asm 22.1.98
        ; Symbolinen konekieliesimerkki
        ; Tero Kukka IY96A

        .model tiny ;muistikoko
        .stack 00h  ;pinon koko 0

        .data ;muuttujat
luku1   dw 1  ; int luku1=1;
luku2   dw 2  ; int luku2=2;
summa   dw ?  ; int summa; ? alustamatta

        .code  ;ohjelmalohko

main    proc   ;pääohjelma
        mov ax, @data
        mov ds, ax      ;ds-rekisterin alustus!!!

        mov ax, luku1
        add ax, luku2
        mov summa, ax

        ;luku al:stä (0...9) kuvaruudulle
        mov dl, al
        add dl, '0'    ; ascii-muunnos
        mov ah, 06h    ; 
        int 21h        ;

        mov ax, 4c00h   ;exit 0
        int 21h         ; dos-keskeytysfunktio
      

main    endp
        end main    ;loppu
        
