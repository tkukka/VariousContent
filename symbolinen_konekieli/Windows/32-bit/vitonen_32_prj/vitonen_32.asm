;Visual Studio, koodisivu 1252
                            .386
                            .MODEL  FLAT, STDCALL               ;stdcall: 32-bit WinAPI kutsutapa oletukseksi
                            OPTION  CASEMAP:NONE                ;erottele ISOT ja pienet kirjaimet tunnuksissa

STD_INPUT_HANDLE            EQU     -10
STD_OUTPUT_HANDLE           EQU     -11
INVALID_HANDLE_VALUE        EQU     -1
KOODISIVU_1252              EQU     1252
N_APUPUSKURI                EQU     64
CRLF                        EQU     <13, 10>

;M��ritell��n tyyppej�
PBYTE                       TYPEDEF PTR BYTE
PDWORD                      TYPEDEF PTR DWORD
PVOID                       TYPEDEF PTR


GetStdHandle                PROTO   STDCALL StdHandle:DWORD
ExitProcess                 PROTO   STDCALL ExitCode:DWORD
FlushConsoleInputBuffer     PROTO   STDCALL handle:DWORD
;GetLastError                PROTO   STDCALL
ReadConsoleA                PROTO   STDCALL handle:DWORD, Buffer:PVOID, NumberOfCharsToRead:DWORD,
                                            NumberOfCharsRead:PDWORD, InputControl:PVOID

SetConsoleCP                PROTO   STDCALL CodePageID:DWORD
SetConsoleOutputCP          PROTO   STDCALL CodePageID:DWORD
WriteConsoleA               PROTO   STDCALL handle:DWORD, buffer:PBYTE, NumberOfCharsToWrite:DWORD,
                                            NumberOfCharsWritten:PDWORD, Reserved:PVOID

;omat funktiot
_lue_konsolilta             PROTO   C       handle:DWORD, Buffer:PVOID, NumberOfCharsToRead:DWORD,
                                            NumberOfCharsRead:PDWORD

_tulosta_konsoliin          PROTO   C       handle:DWORD, Buffer:PVOID, NumberOfChars:DWORD

                            .STACK  4096

                            .CONST

alkuteksti                  BYTE    'Ohjelma 5.', CRLF
koodisivu_virhe_tulostus    BYTE    'Tulostuksen koodisivun vaihto ep�onnistui.', CRLF
koodisivu_virhe_lukeminen   BYTE    'Lukemisen koodisivun vaihto ep�onnistui.', CRLF
lopputeksti                 BYTE    CRLF, 'Ohjelma suoritettu.', CRLF
luenta_virheteksti          BYTE    CRLF, 'Lukemisessa virhe.',CRLF
kehote                      BYTE    CRLF, 'Sy�t� teksti�:'
kehote2                     BYTE    CRLF, 'Sy�t� lis��:'
palaute                     BYTE    CRLF, 'Annoit:'

                            .DATA?

tulostuskahva               DWORD   ?
luentakahva                 DWORD   ?
merkit                      BYTE    10 DUP(?)
merkki_lkm                  DWORD   ?

;----------------------------------------------------------------------------
                            .CODE

start                       PROC    C

                            call    _alkutoimet
                            cmp     eax, 0
                            je      poistu
;alkuvalmistelut ohi
                            INVOKE  _tulosta_konsoliin, [tulostuskahva], ADDR alkuteksti, SIZEOF alkuteksti
                            INVOKE  _tulosta_konsoliin, [tulostuskahva], ADDR kehote, SIZEOF kehote
                            INVOKE  _lue_konsolilta, [luentakahva], ADDR merkit, SIZEOF merkit, ADDR merkki_lkm
                            cmp     eax, 0
                            je      lopeta
                            INVOKE  _tulosta_konsoliin, [tulostuskahva], ADDR palaute, SIZEOF palaute
                            INVOKE  _tulosta_konsoliin, [tulostuskahva], ADDR merkit, [merkki_lkm]

                            INVOKE  _tulosta_konsoliin, [tulostuskahva], ADDR kehote2, SIZEOF kehote2
                            INVOKE  _lue_konsolilta, [luentakahva], ADDR merkit, SIZEOF merkit, ADDR merkki_lkm
                            cmp     eax, 0
                            je      lopeta
                            INVOKE  _tulosta_konsoliin, [tulostuskahva], ADDR palaute, SIZEOF palaute
                            INVOKE  _tulosta_konsoliin, [tulostuskahva], ADDR merkit, [merkki_lkm]
lopeta:                     INVOKE  _tulosta_konsoliin, [tulostuskahva], ADDR lopputeksti, SIZEOF lopputeksti
poistu:                     INVOKE  ExitProcess, 0
start                       ENDP
;----------------------------------------------------------------------------
;Haetaan konsolin stdin- ja stdout-kahvat. Tehd��n konsolin koodisivuston asetukset. 
;
_alkutoimet                 PROC    C PRIVATE
                            INVOKE  GetStdHandle, STD_OUTPUT_HANDLE
                            cmp     eax, 0
                            je      poistu
                            cmp     eax, INVALID_HANDLE_VALUE
                            je      poistu
                            mov     [tulostuskahva], eax        ;tallennetaan konsolin output-kahva

                            INVOKE  GetStdHandle, STD_INPUT_HANDLE
                            cmp     eax, 0
                            je      poistu
                            cmp     eax, INVALID_HANDLE_VALUE
                            je      poistu
                            mov     [luentakahva], eax          ;tallennetaan konsolin input-kahva
;vaihdetaan koodisivuksi 1252
                            INVOKE  SetConsoleOutputCP, KOODISIVU_1252
                            cmp     eax, 0
                            je      asetus_virhe_tulostus
                            INVOKE  SetConsoleCP, KOODISIVU_1252
                            cmp     eax, 0
                            je      asetus_virhe_lukeminen
                            mov     eax,1
                            ret
asetus_virhe_tulostus:      INVOKE  WriteConsoleA, [tulostuskahva], ADDR koodisivu_virhe_tulostus, SIZEOF koodisivu_virhe_tulostus, 0, 0
                            jmp     poistu
asetus_virhe_lukeminen:     INVOKE  WriteConsoleA, [tulostuskahva], ADDR koodisivu_virhe_lukeminen, SIZEOF koodisivu_virhe_lukeminen, 0, 0
poistu:                     xor     eax, eax
                            ret
_alkutoimet                 ENDP
;----------------------------------------------------------------------------
;Tulostaa teksti� n�yt�lle
;in  : konsolin stdout-kahva, merkkipuskurin osoite, tulostettavien merkkien
;      lukum��r�.
;

_tulosta_konsoliin          PROC    C handle:DWORD, Buffer:PVOID, 
                                      NumberOfChars:DWORD
                            INVOKE  WriteConsoleA, [handle], [Buffer], [NumberOfChars], 0, 0
                            ret
_tulosta_konsoliin          ENDP
;----------------------------------------------------------------------------
;Lukee n�pp�imist�sy�tteen. Ylipitk� teksti hyl�t��n. Rivinvaihtomerkkej�
;ei lasketa mukaan merkkeihin.
;in  : konsolin stdin-kahva, merkkipuskurin osoite, puskurin koko
;out : osoite luettujen merkkien m��r��n
;out : EAX = 1, kaikki OK. EAX = 0, tapahtui virhe

_lue_konsolilta             PROC    C USES esi ecx, handle:DWORD, Buffer:PVOID, 
                                                    NumberOfCharsToRead:DWORD,
                                                    NumberOfCharsRead:PDWORD
                            LOCAL   apupuskuri[N_APUPUSKURI]:BYTE, n_merkit:DWORD
                            INVOKE  FlushConsoleInputBuffer, [handle]
                            cmp     eax, 0
                            je      virhe
                            INVOKE  ReadConsoleA, [handle], [Buffer], [NumberOfCharsToRead], [NumberOfCharsRead], 0
                            cmp     eax, 0
                            je      virhe
                            mov     esi, [NumberOfCharsRead]    ;osoitin merkkien lukum��r��n
                            mov     ecx, [esi]                  ;luettujen merkkien lukum��r�
                            cmp     ecx, 0
                            je      virhe
                            mov     eax, [Buffer]               ;merkkipuskurin osoitin
                            cmp     BYTE PTR [eax + ecx - 1 ], 13   ;p��ttyv�tk� luetut merkit CR-merkkiin?
                            je      poista_cr                   ;LF ei siis ole luetuissa merkeiss�
                            cmp     ecx, 2
                            jb      virhe
                            cmp     BYTE PTR [eax + ecx - 1 ], 10   ;p��ttyv�tk� luetut merkit LF-merkkiin?
                            je      poista_crlf                 ;CFLF on luettu, paras tilanne
;CR,LF ei l�ytynyt.Tyhjennet��n merkkej� puskurista, kunnes LF l�ytyy
tyhjennys:                  INVOKE  ReadConsoleA, [handle], ADDR apupuskuri, N_APUPUSKURI, ADDR n_merkit, 0
                            cmp     eax, 0
                            je      virhe
                            lea     eax, [apupuskuri]
                            mov     ecx, [n_merkit]
                            cmp     BYTE PTR [eax + ecx - 1 ], 13   ;lopussa CR?
                            je      tyhjennys                   ;LF ei ole luetuissa merkeiss�. uusi luenta n�pp�imist�lt�
                            cmp     BYTE PTR [eax + ecx - 1 ], 10   ;lopussa LF?
                            je      pois
                            jmp     tyhjennys
pois:                       mov     eax, 1                      ;onnistui ja poistutaan
                            ret
poista_cr:                  dec     ecx
                            cmp     ecx, 0
                            je      virhe
                            mov     [esi], ecx                  ;p�ivitet��n uusi merkkim��r�
                            jmp     tyhjennys                   ;jatketaan LF:n etsimisell�.
poista_crlf:                sub     ecx, 2
                            cmp     ecx, 0
                            je      virhe
                            mov     [esi], ecx                  ;p�ivitet��n uusi merkkim��r�
                            mov     eax, 1                      ;onnistui ja poistutaan
                            ret
virhe:                      INVOKE  _tulosta_konsoliin, [tulostuskahva], ADDR luenta_virheteksti, SIZEOF luenta_virheteksti
                            xor     eax, eax
                            ret
_lue_konsolilta             ENDP
;----------------------------------------------------------------------------
                            END     start
