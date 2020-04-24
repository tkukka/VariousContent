                            BITS    64
                            DEFAULT REL

                            SECTION .rodata

vakioteksti                 db      "12345", 0

                            SECTION .text

                            EXTERN  strtoul
                            EXTERN  reset_errno
                            EXTERN  get_errno
                            GLOBAL  muunna:function

;Vastaa: const char *muunna(unsigned long *)
;Kokeilufunktio, joka kutsuu C-funktioita. Varsinaisesti muuntaa merkkijonon numeeriseen muotoon.
;Palauttaa numeerisen tuloksen ja osoitteen lähdemerkkijonoon. Merkkijonon osoite on NULL, jos muunnos epäonnistui.

muunna:                     push    rbp
                            mov     rbp, rsp
                            sub     rsp, 2*8                ;varataan muistia pinosta 16 tavua
                            mov     [rsp + 8], rdi          ;kopioidaan lukuarvon osoite talteen
                            call    reset_errno
                            mov     rax, -1                 ;jokin testiarvo != 0
                            call    get_errno
                            cmp     eax, 0                  ;errno nollattavissa?
                            je      .nolla
                            xor     eax, eax                ;virhetilanne. paluuarvoksi NULL
                            jmp     .loppu
.nolla:                     mov     rdi, vakioteksti
                            mov     rsi, rsp                ;RSI = char *end
                            mov     edx, 10
                            xor     eax, eax
                            call    strtoul wrt ..plt       ;standardi C funktio
                            mov     rdx, rax                ;RDX = muunnoksen tulos. ulong 8 tavua x64:ssa
                            call    get_errno
                            cmp     eax, 0
                            je      .toinen_tarkistus
                            xor     eax, eax                ;virhetilanne. paluuarvoksi NULL
                            jmp     .loppu
.toinen_tarkistus:          mov     rax, vakioteksti
                            mov     rcx, [rsp]
                            cmp     rax, rcx                ;tekstin pointterien vertailu
                            jne     .kolmas_tarkistus
                            xor     eax, eax                ;muunnos pysähtyi ekaan merkkin
                            jmp     .loppu
.kolmas_tarkistus:          cmp     byte [rcx], 0           ;muunnettu kokonaan?
                            je      .muunnos_ok
                            xor     eax, eax                ;muunnos pysähtyi välille
                            jmp     .loppu
.muunnos_ok:                mov     r11, [rsp + 8]
                            mov     [r11], rdx              ;muunnoksen tulos muistiin
                            mov     rax, vakioteksti
.loppu:                     leave                           ;vapautetaan pinosta varattu muisti
                            ret

