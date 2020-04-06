; Visual Studio koodisivu 1252
                            .386
                            .MODEL  FLAT, STDCALL               ;stdcall: 32-bit WinAPI kutsutapa oletukseksi

;Esittelyt vasta käskykannan ja mallin jälkeen
;funktio@N: vapauta N tavua automaattisesti funktiosta palatessa: ret N generoituu ( = stdcall)

                            EXTERN  STDCALL GetStdHandle@4:proc
                            EXTERN  STDCALL WriteConsoleA@20:proc   ;ANSI
                            EXTERN  STDCALL ExitProcess@4:proc

STD_OUTPUT_HANDLE           EQU     -11
INVALID_HANDLE_VALUE        EQU     -1

                            .STACK                              ;oletuspino 1K

                            .CONST

teksti                      DB      'Testitulostus.', 13, 10
tekstin_pituus              EQU     ($ - teksti)
teksti2                     DB      'Ääkköset åäöÅÄÖ. Müller. Straße.', 13, 10
teksti2_pituus              EQU     ($ - teksti2)

                            .DATA?

hConsole                    DWORD   ?

                            .CODE

start                       PROC    C                           ;C kutsutapa
                            push    STD_OUTPUT_HANDLE
                            call    GetStdHandle@4              ;stdcall: 32-bit WinAPI kutsutapa
                            cmp     eax, 0
                            je      lopeta
                            cmp     eax, INVALID_HANDLE_VALUE
                            je      lopeta
                            mov     [hConsole], eax             ;tallennetaan konsolin kahva
; Aloitetaan tulostukset
                            push    0                           ;reserved
                            push    0                           ;kirjoitettujen merkkien määrä ei kiinnosta
                            push    DWORD PTR tekstin_pituus
                            lea     eax, teksti
                            push    eax
                            push    [hConsole]
                            call    WriteConsoleA@20
                            cmp     eax, 0
                            je      lopeta                      ;tapahtui virhe
                            push    0                           ;reserved
                            push    0                           ;kirjoitettujen merkkien määrä ei kiinnosta
                            push    DWORD PTR teksti2_pituus
                            lea     eax, teksti2
                            push    eax
                            push    [hConsole]
                            call    WriteConsoleA@20
lopeta:                     push    0                           ;palauta nolla
                            call    ExitProcess@4
start                       ENDP
                            END     start
