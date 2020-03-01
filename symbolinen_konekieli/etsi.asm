        ;RaTol Symbolinen konekieli: Harjoitus 3, tehtävä 1
        ;Tero Kukka IY96A

        ;Tiedosto: etsi.asm
        ;Luotu 15.3.1998

        ;Aliohjelma _Etsi
        ;Hakee taulukon osoitteen ja alkioiden lukumäärän PINOSTA
        ;Etsii pienimmän tavun ja palauttaa sen al:ssä.

        ;Aliohjelmien esittely:

        public _Etsi

        .model small    ;muistimalli
        .stack  00h     ;pinon koko 

        .data           ;muuttujalohko

        .code           ;ohjelmakoodi alkaa
                        
_Etsi   proc            ;int _Etsi(int *luvut, const int TAVUJA);             
        push bp         ;pinossa: etum., tavujen lkm, ds, &luvut, ip, bp
        mov bp, sp 
        push si
        push ds
        push cx        
        push dx

        mov si, [bp + 4] ;offset
        mov ds, [bp + 6] ;ds
        mov cx, [bp + 8] ;tavujen lkm
        mov dx, [bp + 10] ;unsigned/signed
        mov al, [si]    ;1. alkio valmiiksi al:ään
        inc si
        dec cx
        or dx, dx       ;onko dx != 0?
        jnz TOISTA2     ;jos on, niin signed vertailuun

;unsigned-vertailu
TOISTA1:
        test al, al     ;jos löytyy 0, lopetetaan
        jz LOPPU
        cmp al, [si]
        jbe SEURAAVA1    ;al <= [si] -> hyppy
        mov al, [si]     ;al > [si] -> al=[si]
SEURAAVA1:
        inc si
        loop TOISTA1
        jmp LOPPU

;signed-vertailu:
TOISTA2:
        cmp al, 80h     ;jos löytyy -128, lopetetaan
        jz LOPPU
        cmp al, [si]    
        jle SEURAAVA2   ;al <= [si] -> hyppy
        mov al, [si]    ;al > [si] -> al=[si]
SEURAAVA2:
        inc si
        loop TOISTA2
;loppu, pinon palautus
LOPPU:
        pop dx
        pop cx
        pop ds
        pop si
        pop bp         ;bp takaisin
        ret 8          ;8 tavun vapautus paluussa
_Etsi   endp

        end      
