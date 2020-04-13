;Visual Studio, koodisivu 1252
                            .386
                            .MODEL  FLAT, STDCALL               ;stdcall: 32-bit WinAPI kutsutapa oletukseksi
                            OPTION  CASEMAP:NONE                ;erottele ISOT ja pienet kirjaimet tunnuksissa

STD_OUTPUT_HANDLE           EQU     -11
INVALID_HANDLE_VALUE        EQU     -1
KOODISIVU_1252              EQU     1252

;M‰‰ritell‰‰n tyyppej‰
PBYTE                       TYPEDEF PTR BYTE
PDWORD                      TYPEDEF PTR DWORD
PVOID                       TYPEDEF PTR

;Esittelyt vasta k‰skykannan ja mallin j‰lkeen
;PROTO, INVOKE vain 32-bit MASM
;EXTERN ei tarvita

GetStdHandle                PROTO   STDCALL StdHandle:DWORD
ExitProcess                 PROTO   STDCALL ExitCode:DWORD
SetConsoleOutputCP          PROTO   STDCALL CodePageID:DWORD
WriteConsoleA               PROTO   STDCALL handle:DWORD, buffer:PBYTE, NumberOfCharsToWrite:DWORD,
                                            NumberOfCharsWritten:PDWORD, Reserved:PVOID

;omat funktiot
_kerro                      PROTO   C kerrottava:DWORD, kertoja:DWORD
;_jaa                        PROTO   C jaettava:DWORD, jakaja:DWORD


                            .STACK  4096

                            .CONST

alkuteksti                  DB      'Ohjelma 4.', 13, 10
koodisivu_vaihto_virhe      DB      'Koodisivun vaihto ep‰onnistui.', 13, 10
lopputeksti                 DB      'Ohjelma suoritettu.', 13, 10
funktio_1_teksti            DB      'Kertolasku-funktio tehty.', 13, 10
funktio_1_teksti_2          DB      'Kertolasku-funktio tehty. [K‰sintehty kutsu].', 13, 10
funktio_2_teksti            DB      'summa 5-funktio tehty.', 13, 10
funktio_3_teksti            DB      'Jakolasku-funktio tehty. [K‰sintehty kutsu].', 13, 10
funktio_4_teksti            DB      'Pariton-funktio tehty. [K‰sintehty kutsu].', 13, 10

                            .DATA?

hConsole                    DWORD   ?

;----------------------------------------------------------------------------
                            .CODE

_start                      PROC    C                           ;C kutsutapa
                            INVOKE  GetStdHandle, STD_OUTPUT_HANDLE
                            cmp     eax, 0
                            je      poistu
                            cmp     eax, INVALID_HANDLE_VALUE
                            je      poistu
                            mov     [hConsole], eax             ;tallennetaan konsolin kahva
;vaihdetaan koodisivuksi 1252
                            INVOKE  SetConsoleOutputCP, KOODISIVU_1252
                            cmp     eax, 0
                            je      vaihto_epaonnistunut
                            INVOKE  WriteConsoleA, [hConsole], ADDR alkuteksti, SIZEOF alkuteksti, 0, 0
;--- Funktiokokeilut alku ---
                            INVOKE  _kerro, 8, 4                ;vastaava PROTO tarvitaan
                            INVOKE  WriteConsoleA, [hConsole], ADDR funktio_1_teksti, SIZEOF funktio_1_teksti, 0, 0
;kutsutaan _kerro() ilman INVOKE:a
;--- alku --
                            push    10
                            push    3
                            call    _kerro
                            add     esp, 8
;--- loppu --
                            INVOKE  WriteConsoleA, [hConsole], ADDR funktio_1_teksti_2, SIZEOF funktio_1_teksti_2, 0, 0
                            call    _summa_viisi
                            INVOKE  WriteConsoleA, [hConsole], ADDR funktio_2_teksti, SIZEOF funktio_2_teksti, 0, 0

                            call    _testi_funktio              ;v‰liss‰ kokeilufunktio

                            ;INVOKE  _jaa, 30, 10                ;vastaava PROTO tarvitaan
;kutsutaan _jaa() ilman INVOKE:a
;--- alku --
                            push    10
                            push    30
                            call    _jaa
                            add     esp, 8
;--- loppu --
                            INVOKE  WriteConsoleA, [hConsole], ADDR funktio_3_teksti, SIZEOF funktio_3_teksti, 0, 0
;parittomuuden tutkinta
                            push    1234
                            call    _pariton
                            add     esp, 4
                            INVOKE  WriteConsoleA, [hConsole], ADDR funktio_4_teksti, SIZEOF funktio_4_teksti, 0, 0
;--- Funktiokokeilut loppu ---
                            jmp     lopeta
vaihto_epaonnistunut:       INVOKE  WriteConsoleA, [hConsole], ADDR koodisivu_vaihto_virhe, SIZEOF koodisivu_vaihto_virhe, 0, 0
lopeta:                     INVOKE  WriteConsoleA, [hConsole], ADDR lopputeksti, SIZEOF lopputeksti, 0, 0
poistu:                     INVOKE  ExitProcess, 0
_start                      ENDP
;----------------------------------------------------------------------------
;Etumerkitˆn kertolasku. Parametrit pinosta.
;vastaa: int kerro(int kerrottava, int kertoja)
;K‰ytt‰‰ EDX rekisteri‰ EAX:n lis‰ksi. USES ilmoittaa s‰ilytett‰v‰t rekisterit
;MASM:lle.
;out : EAX = kerrottava * kertoja   (EDX huomiotta)

_kerro                      PROC    C USES edx, kerrottava:DWORD, kertoja:DWORD
                            mov     eax, [kerrottava]
                            mul     [kertoja]
                            ret
_kerro                      ENDP
;----------------------------------------------------------------------------
;Palauttaa 5. Ei parametreja.
;vastaa: int summa_viisi(void)
;Varaa pinosta kaksi muuttujaa LOCAL-direktiivill‰. 
;Muuttujien alkuarvot k‰sipelill‰.
;out : EAX = 5

_summa_viisi                PROC    C
                            LOCAL   lukuA:DWORD, lukuB:DWORD
                            mov     [lukuA], 2
                            mov     [lukuB], 3
                            mov     eax, [lukuA]
                            add     eax, [lukuB]
                            ret
_summa_viisi                ENDP
;----------------------------------------------------------------------------
;Jokin funktio. Generoiko MASM mit‰‰n?
;vastaa: int testi_funktio(void)
;out : EAX = 7

_testi_funktio              PROC    C
                            xor     eax, eax
                            add     eax, 7
                            ret
_testi_funktio              ENDP
;----------------------------------------------------------------------------
;Etumerkitˆn jakolasku. Parametrit pinosta.
;vastaa: int jaa(int jaettava, int jakaja)
;K‰ytt‰‰ EDX rekisteri‰ EAX:n lis‰ksi. EDX vanha arvo ylikirjoitetaan.
;Generoiko MASM mit‰‰n?
;out: EAX = jaettava/jakaja (jakoj‰‰nnˆs hyl‰t‰‰n)

_jaa                        PROC    C jaettava:DWORD, jakaja:DWORD
                            xor     edx, edx
                            mov     eax, [jaettava]
                            div     [jakaja]
                            ret
_jaa                        ENDP
;----------------------------------------------------------------------------
;Pariton vai parillinen luku. Parametri luku (DWORD) pinosta.
;vastaa: int pariton(int luku)
;out: EAX = 1 (pariton), 0 (parillinen)

_pariton                    PROC    C
                            push    ebp
                            mov     ebp, esp
                            mov     eax, [ebp + 8]
                            and     eax, 1            ;tutkitaan vain alin bitti
                            leave
                            ret
_pariton                    ENDP
;----------------------------------------------------------------------------
                            END     _start
