;Visual Studio, koodisivu 1252
                            .386
                            .MODEL  FLAT, STDCALL               ;stdcall: 32-bit WinAPI kutsutapa oletukseksi
                            OPTION  CASEMAP:NONE                ;erottele ISOT ja pienet kirjaimet tunnuksissa
;M‰‰ritell‰‰n tyyppej‰
PBYTE                       TYPEDEF PTR BYTE
PDWORD                      TYPEDEF PTR DWORD
PVOID                       TYPEDEF PTR

;Esittelyt vasta k‰skykannan ja mallin j‰lkeen
;PROTO, INVOKE vain 32-bit MASM
;EXTERN ei tarvita 

GetConsoleOutputCP          PROTO   STDCALL
GetStdHandle                PROTO   STDCALL StdHandle:DWORD
ExitProcess                 PROTO   STDCALL ExitCode:DWORD
SetConsoleOutputCP          PROTO   STDCALL CodePageID:DWORD
WriteConsoleA               PROTO   STDCALL handle:DWORD, buffer:PBYTE, NumberOfCharsToWrite:DWORD,
                                            NumberOfCharsWritten:PDWORD, Reserved:PVOID



STD_OUTPUT_HANDLE           EQU     -11
INVALID_HANDLE_VALUE        EQU     -1
OLETUSKOODISIVU             EQU     850                         ;Suomessa myˆs t‰m‰
KOODISIVU_1252              EQU     1252


                            .STACK  4096

                            .CONST

alkuteksti                  DB      'Ohjelma 3.', 13, 10
oletuskoodisivu             DB      'Koodisivu on 850, OEM Multilingual Latin 1; Western European (DOS).', 13, 10
toimintakoodisivu           DB      'Koodisivu on 1252, ANSI Latin 1; Western European (Windows).', 13, 10
koodisivu                   DB      'Koodisivu on jokin muu.', 13, 10
koodisivu_vaihto_virhe      DB      'Koodisivun vaihto ep‰onnistui.', 13, 10
koodisivu_vaihto_ok         DB      'Koodisivun vaihto onnistui.', 13, 10
testiteksti                 DB      'Testiteksti: Â‰ˆ ≈ƒ÷ M¸ller Straﬂe.', 13, 10
lopputeksti                 DB      'Ohjelma suoritettu.', 13, 10

                            .DATA?

hConsole                    DWORD   ?

                            .CODE

start                       PROC    C                           ;C kutsutapa
                            INVOKE  GetStdHandle, STD_OUTPUT_HANDLE
                            cmp     eax, 0
                            je      poistu
                            cmp     eax, INVALID_HANDLE_VALUE
                            je      poistu
                            mov     [hConsole], eax             ;tallennetaan konsolin kahva

; WriteConsoleA: kirjoitettujen merkkien m‰‰r‰ ei kiinnosta = 0, reserved = 0
; INVOKE k‰ytt‰‰ EAX, ja mahd. EDX rekistereit‰

                            INVOKE  WriteConsoleA, [hConsole], ADDR alkuteksti, SIZEOF alkuteksti, 0, 0
                            cmp     eax, 0
                            je      lopeta                      ;tapahtui virhe
                            INVOKE  GetConsoleOutputCP
                            cmp     eax, 0
                            je      lopeta
                            cmp     eax, KOODISIVU_1252
                            jne     vertaa_850
                            INVOKE  WriteConsoleA, [hConsole], ADDR toimintakoodisivu, SIZEOF toimintakoodisivu, 0, 0
                            INVOKE  WriteConsoleA, [hConsole], ADDR testiteksti, SIZEOF testiteksti, 0, 0
                            jmp     sivun_vaihto
vertaa_850:                 cmp     eax, OLETUSKOODISIVU
                            jne     muu_sivu
                            INVOKE  WriteConsoleA, [hConsole], ADDR oletuskoodisivu, SIZEOF oletuskoodisivu, 0, 0
                            INVOKE  WriteConsoleA, [hConsole], ADDR testiteksti, SIZEOF testiteksti, 0, 0
                            jmp     sivun_vaihto
muu_sivu:                   INVOKE  WriteConsoleA, [hConsole], ADDR koodisivu, SIZEOF koodisivu, 0, 0
                            INVOKE  WriteConsoleA, [hConsole], ADDR testiteksti, SIZEOF testiteksti, 0, 0
sivun_vaihto:               INVOKE  SetConsoleOutputCP, KOODISIVU_1252
                            cmp     eax, 0
                            je      vaihto_epaonnistunut
                            INVOKE  WriteConsoleA, [hConsole], ADDR koodisivu_vaihto_ok, SIZEOF koodisivu_vaihto_ok, 0, 0
;tarkistus
                            INVOKE  GetConsoleOutputCP
                            cmp     eax, 0
                            je      lopeta
                            cmp     eax, KOODISIVU_1252
                            jne     lopeta                      ;ei pit‰isi suorittaa t‰t‰ hyppy‰ koskaan
                            INVOKE  WriteConsoleA, [hConsole], ADDR toimintakoodisivu, SIZEOF toimintakoodisivu, 0, 0
                            INVOKE  WriteConsoleA, [hConsole], ADDR testiteksti, SIZEOF testiteksti, 0, 0
                            jmp     lopeta
vaihto_epaonnistunut:       INVOKE  WriteConsoleA, [hConsole], ADDR koodisivu_vaihto_virhe, SIZEOF koodisivu_vaihto_virhe, 0, 0
lopeta:                     INVOKE  WriteConsoleA, [hConsole], ADDR lopputeksti, SIZEOF lopputeksti, 0, 0
poistu:                     INVOKE  ExitProcess, 0
start                       ENDP
                            END     start
