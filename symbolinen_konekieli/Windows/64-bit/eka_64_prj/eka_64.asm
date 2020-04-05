; Visual Studio koodisivu 1252
                            EXTERN  GetStdHandle:proc
                            EXTERN  WriteConsoleA:proc          ;ANSI
                            EXTERN  ExitProcess:proc

STD_OUTPUT_HANDLE           EQU     -11
INVALID_HANDLE_VALUE        EQU     -1

                            .CONST

teksti                      DB      'Testitulostus.', 13, 10
tekstin_pituus              EQU     ($ - teksti)
teksti2                     DB      'Ääkköset åäöÅÄÖ. Müller. Straße.', 13, 10
teksti2_pituus              EQU     ($ - teksti2)

                            .DATA

hConsole                    QWORD   ?

                            .CODE

start                       PROC
                            sub     rsp, 5*8                    ;varataan pinosta muistia (tavuina) kutsuttavia funktioita varten.
                            mov     rcx, STD_OUTPUT_HANDLE      ;Windows x64: 4 ensimmäistä rekisteriin RCX, RDX, R8, R9
                            call    GetStdHandle
                            cmp     rax, 0
                            je      lopeta
                            cmp     rax, INVALID_HANDLE_VALUE
                            je      lopeta
                            mov     [hConsole], rax             ;tallennetaan konsolin kahva
; Aloitetaan tulostukset
                            mov     rcx, [hConsole]
                            lea     rdx, teksti
                            mov     r8, tekstin_pituus
                            mov     r9, 0                       ;kirjoitettujen merkkien määrä ei kiinnosta
                            mov     QWORD PTR [rsp + 32], 0
                            call    WriteConsoleA
                            cmp     rax, 0
                            je      lopeta                      ;tapahtui virhe
                            mov     rcx, [hConsole]
                            lea     rdx, teksti2
                            mov     r8, teksti2_pituus
                            mov     r9, 0
                            mov     QWORD PTR [rsp + 32], 0
                            call    WriteConsoleA
lopeta:                     sub     rcx, rcx
                            call    ExitProcess
start                       ENDP
                            END
