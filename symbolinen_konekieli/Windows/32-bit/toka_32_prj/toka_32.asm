;Visual Studio, koodisivu 1252
                            .386
                            .MODEL  FLAT, STDCALL               ;stdcall: 32-bit WinAPI kutsutapa oletukseksi
                            OPTION  CASEMAP:NONE                ;erottele ISOT ja pienet kirjaimet tunnuksissa
;M‰‰ritell‰‰n tyyppej‰
PBYTE                       TYPEDEF PTR BYTE
PDWORD                      TYPEDEF PTR DWORD
PVOID                       TYPEDEF PTR

;Esittelyt vasta k‰skykannan ja mallin j‰lkeen
;PROTO, INVOKE  vain 32-bit MASM
;EXTERN ei tarvita
GetStdHandle                PROTO   STDCALL StdHandle:DWORD
ExitProcess                 PROTO   STDCALL ExitCode:DWORD
WriteConsoleA               PROTO   STDCALL handle:DWORD, buffer:PBYTE, NumberOfCharsToWrite:DWORD,
                                            NumberOfCharsWritten:PDWORD, Reserved:PVOID

STD_OUTPUT_HANDLE           EQU     -11
INVALID_HANDLE_VALUE        EQU     -1

                            .STACK                              ;oletuspino 1K

                            .CONST

teksti                      DB      'Testitulostus, ohjelma 2.', 13, 10
;ei toimi INVOKEssa: tekstin_pituus  EQU     ($ - teksti)

teksti2                     DB      'ƒ‰kkˆset Â‰ˆ≈ƒ÷. M¸ller. Straﬂe.', 13, 10
;ei toimi INVOKEssa: teksti2_pituus  EQU     ($ - teksti2)

                            .DATA?

hConsole                    DWORD   ?

                            .CODE

_start                      PROC    C                           ;C kutsutapa
                            INVOKE  GetStdHandle, STD_OUTPUT_HANDLE
                            cmp     eax, 0
                            je      lopeta
                            cmp     eax, INVALID_HANDLE_VALUE
                            je      lopeta
                            mov     [hConsole], eax             ;tallennetaan konsolin kahva
; Aloitetaan tulostukset
; kirjoitettujen merkkien m‰‰r‰ ei kiinnosta = 0, reserved = 0
; INVOKE k‰ytt‰‰ EAX, ja mahd. EDX rekistereit‰

                            INVOKE  WriteConsoleA, [hConsole], ADDR teksti, SIZEOF teksti, 0, 0
                            cmp     eax, 0
                            je      lopeta                      ;tapahtui virhe
                            INVOKE  WriteConsoleA, [hConsole], ADDR teksti2, SIZEOF teksti2, 0, 0
lopeta:                     INVOKE  ExitProcess, 0
_start                      ENDP
                            END     _start
