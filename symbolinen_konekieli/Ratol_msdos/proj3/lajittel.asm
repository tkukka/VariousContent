        ;RaTol Symbolinen konekieli: Harjoitus 5, tehtävä 3
        ;Tero Kukka IY96A

        ;Tiedosto: lajittel.asm 
        ;Luotu 25.4.1998

        ;Aliohjelma _lajittele (near)
        ;parametrit: kok.lukutaulukon siirros ja lukujen kplmäärä.
        
        public _lajittele
        
        .model small        ;HUOM. muistimalli

        .stack  100h        ;pinon koko

        .data                   

        .code           

_lajittele proc           
        push bp
        mov bp, sp              ;PINO: parametrit, IP, BP
        push bx
        push cx
        push dx
        push si
        
        mov dx, [bp + 6]        ;lkm
        cmp dx, 1
        jbe PALUU               ;jos lkm <= 1, ei lajitella
        dec dx                  ;lkm - 1, koska osoitetaan [si+2]
ALKU:
        xor bx, bx              ;lippu vaihtotapahtumalle
        mov si, [bp + 4]        ;osoitin taulukon alkuun
        xor cx, cx              ;indeksi-laskuri
TOISTA:
        cmp cx, dx
        jae LOPPU               ;taulukko käyty läpi?
        mov ax, [si + 2]        ;ladataan alkio  
        cmp ax, [si]            ;verrataan
        jge YLI                 ;jos jälkimmäinen >= etumainen -> ohi
        xchg ax, [si]
        mov [si + 2], ax
        mov word ptr bx, 1      ;vaihdon merkiksi
YLI:
        add si, 2
        inc cx
        jmp TOISTA
LOPPU:
        or bx, bx               ;onko tehty vaihto?
        jnz ALKU
PALUU:
        xor ax, ax              ;AX = OK
        pop si
        pop di
        pop cx
        pop bx
        pop bp
        ret
_lajittele endp

        end      
