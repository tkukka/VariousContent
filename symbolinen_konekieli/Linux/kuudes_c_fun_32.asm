                            BITS    32

                            SECTION .rodata

vakioteksti                 db      "12345", 0

                            SECTION .text

                            EXTERN  strtoul
                            EXTERN  reset_errno
                            EXTERN  get_errno
                            GLOBAL  muunna:function

;Vastaa: const char *muunna(unsigned long *)
;Kokeilufunktio, joka kutsuu C-funktioita. Varsinaisesti muuntaa merkkijonon numeeriseen muotoon.
;Palauttaa numeerisen tuloksen ja osoitteen lähdemerkkijonoon. Osoite on NULL, jos muunnos epäonnistui.

muunna:                     push    ebp                     ;ABI: rekisterin tila säilytettävä
                            mov     ebp, esp                ;funktion pinokehys
                            sub     esp, 4                  ;varataan pinosta tilaa osoittimelle (4 tavua)
                            call    reset_errno
                            mov     eax, -1                 ;jokin testiarvo != 0
                            call    get_errno
                            cmp     eax, 0                  ;errno nollattavissa?
                            je      .nolla
                            xor     eax, eax                ;virhetilanne. paluuarvoksi NULL
                            jmp     .loppu
.nolla:                     push    dword 10                ;kantaluku
                            lea     eax, [ebp - 4]          ;osoite merkkiin, johon muunnos pysähtyi
                            push    eax
                            push    dword vakioteksti
                            xor     eax, eax
                            call    strtoul                 ;standardi C funktio
                            mov     edx, eax                ;EDX = muunnoksen tulos
                            call    get_errno
                            cmp     eax, 0
                            je      .toinen_tarkistus
                            xor     eax, eax                ;virhetilanne. paluuarvoksi NULL
                            jmp     .loppu
.toinen_tarkistus:          mov     dword eax, vakioteksti
                            mov     ecx, [ebp - 4]
                            cmp     eax, ecx                ;tekstin pointterien vertailu
                            jne     .kolmas_tarkistus
                            xor     eax, eax                ;muunnos pysähtyi ekaan merkkin
                            jmp     .loppu
.kolmas_tarkistus:          cmp     byte [ecx], 0           ;muunnettu kokonaan?
                            je      .muunnos_ok
                            xor     eax, eax                ;muunnos pysähtyi välille
                            jmp     .loppu
.muunnos_ok:                mov     ecx, [ebp + 8]          ;ECX = osoite lukuarvomuuttujaan ('pointteri')
                            mov     dword [ecx], edx        ;unsigned long *pointteri = EDX
                            mov     dword eax, vakioteksti
.loppu:                     leave
                            ret

