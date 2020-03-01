        ;RaTol Symbolinen konekieli: Harjoitus 5, tehtävä 4
        ;Tero Kukka IY96A

        ;Tiedosto: paivita.asm Versio 1.0
        ;Luotu 25.4.1998

        include a:makrot.txt

        ;Päivittää kello-tietueen tunti-, minuutti- ja sekuntikentät

        ;Ulkoinen aliohjelma _hex2dec

        extrn _hex2dec: far

        ;Aliohjelma _paivita: far
        
        public _paivita
        
        .model large        ;HUOM. muistimalli

        .stack  100h        ;pinon koko

        .data                   

        .code           

_paivita proc           
        push bp
        mov bp, sp              ;PINO: parametrit, CS, IP, BP
        push ds
        push bx
        push di

        mov ds, [bp + 12]       ;tarvitaan datasegm.
        mov bx, [bp + 10]       ;dec-lukujen taulukon siirros
        mov word ptr [bx], 0    ;nollataan ne (2 kpl)
        mov word ptr [bx + 2], 0

        ;hex-luvun muunto dec-luvuksi:

        push ds                 ;datasegm. pinoon
        push bx                 ;dec-lukujen taulukko
        xor bx, bx
        push bx                 ;ylempi sana = 0
        push [bp + 8]           ;aikamuuttuja (h, min tai s) pinoon
        call _hex2dec           ;muunnetaan 10-järjestelmään
        add sp, 8

        ;kirjataan kelloon uusi aika:

        mov bx, [bp + 10]       ;dec-lukujen siirros
        mov byte ptr al, [bx + 2]  ;1. nro
        bin2ascii al
        mov di, [bp + 6]        ;kellosta muutettava h, min tai s
        mov [di], al            ;1. nro kelloon
        mov byte ptr al, [bx]   ;2. nro
        bin2ascii al
        mov [di + 1], al        ;2. nro kelloon
        xor ax, ax              ;AX = OK

        pop di
        pop bx
        pop ds
        pop bp
        ret
_paivita endp

        end      
