;Visual Studio, koodisivu 1252
                            .686                                ;uudemmat x87-k‰skyt, CPUID
                            .MODEL  FLAT, STDCALL               ;stdcall: 32-bit WinAPI kutsutapa oletukseksi
                            OPTION  CASEMAP:NONE                ;erottele ISOT ja pienet kirjaimet tunnuksissa

                            INCLUDE ..\makrot_w32.txt
                            INCLUDE ..\makrot_32.txt

N_VAKIOKOHTEET              EQU     13
N_VAKIOMERKIT               EQU     3                           ; 1, X tai 2 (yht. 3)
N_LOTTONUMEROT              EQU     40
N_LOTTORASTIT               EQU     7


                            .STACK  4096

                            .CONST

alkuteksti                  BYTE    '--- Ohjelma 7 ---', CRLF
lopputeksti                 BYTE    CRLF, 'Ohjelma suoritettu.', CRLF
DLL_teksti                  BYTE    'Sai DLL-kahvan', CRLF
funktioteksti               BYTE    'Funktio linkitetty', CRLF
DLL_tiedostomimi            BYTE    'Advapi32.dll', 0
funktion_nimi               BYTE    'SystemFunction036', 0
vakioteksti                 BYTE    'Vakiorivi:', CRLF
vakiomerkit                 BYTE    '1  ',  CRLF, ' X ',  CRLF, '  2', CRLF     ; 5 ascii-merkki‰ kukin
lottoteksti                 BYTE    'Lottorivi: '
lottomerkit                 BYTE    ' 1 ', ' 2 ', ' 3 ', ' 4 ', ' 5 ', ' 6 '    ; 3 ascii-merkki‰ kukin
                            BYTE    ' 7 ', ' 8 ', ' 9 ', '10 ', '11 ', '12 '
                            BYTE    '13 ', '14 ', '15 ', '16 ', '17 ', '18 '
                            BYTE    '19 ', '20 ', '21 ', '22 ', '23 ', '24 '
                            BYTE    '25 ', '26 ', '27 ', '28 ', '29 ', '30 '
                            BYTE    '31 ', '32 ', '33 ', '34 ', '35 ', '36 '
                            BYTE    '37 ', '38 ', '39 ', '40 '

                            .DATA

kahva                       DWORD           ?
pfunc                       RANDFUNCPTR     ?
vakio_satunnaisdata         BYTE            (N_VAKIOKOHTEET * 4) DUP(0)     ;riitt‰‰ vakiolle
lotto_satunnaisdata         BYTE            (N_LOTTORASTIT * 4)  DUP(0)     ;ladataan lis‰‰ arvonnassa
lottorivi                   BYTE            N_LOTTONUMEROT       DUP(0)     ;riviin kuuluvat numerot merkit‰‰n 1:ll‰

                            .CODE
;----------------------------------------------------------------------------
start                       PROC    C

                            INVOKE  _valmistele_konsoli
                            cmp     eax, 0
                            je      poistu

                            INVOKE  _tulosta_konsoliin, ADDR alkuteksti, SIZEOF alkuteksti
                            INVOKE  LoadLibraryA, ADDR DLL_tiedostomimi
                            cmp     eax, 0
                            je      lopeta
                            mov     [kahva], eax
                            INVOKE  _tulosta_konsoliin, ADDR DLL_teksti, SIZEOF DLL_teksti
                            INVOKE  GetProcAddress, [kahva], ADDR funktion_nimi
                            cmp     eax, 0
                            je      lopeta
                            mov     [pfunc], eax
                            INVOKE  _tulosta_konsoliin, ADDR funktioteksti, SIZEOF funktioteksti

                            INVOKE RANDFUNCPTR PTR [pfunc], ADDR vakio_satunnaisdata, SIZEOF vakio_satunnaisdata
                            cmp     eax, 0
                            je      vapauta_dll

                            INVOKE  _tulosta_konsoliin, ADDR vakioteksti, SIZEOF vakioteksti
                            xor     ecx, ecx                    ;arvottujen kohteiden lukum‰‰r‰
                            mov     esi, OFFSET vakio_satunnaisdata     ;satunnaisluvut
                            mov     ebx, N_VAKIOMERKIT          ;jakaja
toista:                     mov     eax, [esi]                  ;otetaan satunnaisluku
                            xor     edx, edx
                            div     ebx                         ;0...2 -> EDX
                            lea     eax, [vakiomerkit + 4 * edx + edx]  ;siirros 5*edx
                            push    ecx                         ;tuhoutuva rekisteri
                            INVOKE  _tulosta_konsoliin, eax, 5  ; 5 merkki‰
                            pop     ecx
                            add     esi, SIZEOF DWORD           ;seuraava satunnaisluku
                            inc     ecx                         ;yksi kohde tehty lis‰‰
                            cmp     ecx, N_VAKIOKOHTEET         ;kaikki tehty?
                            je      vakiovalmis
                            jmp     toista
vakiovalmis:                INVOKE RANDFUNCPTR PTR [pfunc], ADDR lotto_satunnaisdata, SIZEOF lotto_satunnaisdata
                            cmp     eax, 0
                            je      vapauta_dll

                            xor     ecx, ecx                    ;arvottujen numeroiden lukum‰‰r‰
                            xor     edi, edi                    ;loton satunnaisdatan laskuri
                            mov     esi, OFFSET lotto_satunnaisdata     ;satunnaisluvut
                            mov     ebx, N_LOTTONUMEROT         ;jakaja
arvonta:                    cmp     edi, N_LOTTORASTIT          ;onko kaikki satunnaisdata k‰ytetty?
                            jne     jatko
                            push    ecx                         ;tuhoutuva rekisteri
                            INVOKE RANDFUNCPTR PTR [pfunc], ADDR lotto_satunnaisdata, SIZEOF lotto_satunnaisdata
                            pop     ecx
                            cmp     eax, 0                      ;virhetarkistus
                            je      vapauta_dll
                            xor     edi, edi                    ;satunn.datan k‰yttˆ = 0
                            mov     esi, OFFSET lotto_satunnaisdata
jatko:                      mov     eax, [esi]                  ;otetaan satunnaisluku
                            xor     edx, edx
                            div     ebx                         ;0...39 -> EDX
                            lea     eax, [lottorivi + edx]      ;kohdistetaan numeron kohdalle
                            inc     edi
                            add     esi, SIZEOF DWORD           ;seuraava satunnaisluku
                            cmp     BYTE PTR [eax], 0           ;onko jo arvottu?
                            jne     arvonta
                            inc     BYTE PTR [eax]              ;merkit‰‰n k‰ytetyksi
                            inc     ecx                         ;yksi nro lis‰‰ riviin
                            cmp     ecx, N_LOTTORASTIT          ;rivi t‰ysi?
                            je      tulosta
                            jmp     arvonta
tulosta:                    INVOKE  _tulosta_konsoliin, ADDR lottoteksti, SIZEOF lottoteksti
                            xor     ebx, ebx                    ;tulostettujen numeroiden m‰‰r‰
                            mov     edi, OFFSET lottomerkit     ;tulostettavat merkit
                            mov     esi, OFFSET lottorivi       ;arvotut numerot
tarkista_nro:               cmp     BYTE PTR [esi], 0
                            je      ohi
                            INVOKE  _tulosta_konsoliin, edi, 3  ; 3 merkki‰
                            inc     ebx                         ;tulosttu yksi lis‰‰
ohi:                        add     edi, 3                      ;kolme ascii-merkki‰
                            inc     esi                         ;seuraava mahdollinen numero
                            cmp     ebx, N_LOTTORASTIT          ;kaikki tulostettu?
                            je      vapauta_dll
                            jmp     tarkista_nro

vapauta_dll:                INVOKE FreeLibrary, [kahva]

lopeta:                     INVOKE  _tulosta_konsoliin, ADDR lopputeksti, SIZEOF lopputeksti
poistu:                     INVOKE  ExitProcess, 0
start                       ENDP
;----------------------------------------------------------------------------
                            END     start
