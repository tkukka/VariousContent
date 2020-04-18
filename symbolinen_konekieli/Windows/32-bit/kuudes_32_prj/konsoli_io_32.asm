;Visual Studio, koodisivu 1252
                            .686
                            .MODEL  FLAT, STDCALL               ;stdcall: 32-bit WinAPI kutsutapa oletukseksi
                            OPTION  CASEMAP:NONE                ;erottele ISOT ja pienet kirjaimet tunnuksissa

                            INCLUDE ..\makrot_w32.txt
                            INCLUDE ..\makrot_32.txt


KOODISIVU_1252              EQU     1252
N_APUPUSKURI                EQU     64


                            .CONST

koodisivu_virhe_tulostus    BYTE    'Tulostuksen koodisivun vaihto ep�onnistui.', CRLF
koodisivu_virhe_lukeminen   BYTE    'Lukemisen koodisivun vaihto ep�onnistui.', CRLF
luenta_virheteksti          BYTE    CRLF, 'Lukemisessa virhe.',CRLF

                            .DATA?

tulostuskahva               DWORD   ?
luentakahva                 DWORD   ?


                            .CODE

;----------------------------------------------------------------------------
;Haetaan konsolin stdin- ja stdout-kahvat. Tehd��n konsolin koodisivuston asetukset. 
;
_valmistele_konsoli         PROC    C
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
asetus_virhe_tulostus:      INVOKE  _tulosta_konsoliin, ADDR koodisivu_virhe_tulostus, SIZEOF koodisivu_virhe_tulostus
                            jmp     poistu
asetus_virhe_lukeminen:     INVOKE  _tulosta_konsoliin, ADDR koodisivu_virhe_lukeminen, SIZEOF koodisivu_virhe_lukeminen
poistu:                     xor     eax, eax
                            ret
_valmistele_konsoli         ENDP
;----------------------------------------------------------------------------
;Tulostaa teksti� n�yt�lle
;in  : merkkipuskurin osoite, tulostettavien merkkien lukum��r�.
;

_tulosta_konsoliin          PROC    C Buffer:PVOID, NumberOfChars:DWORD
                            INVOKE  WriteConsoleA, [tulostuskahva], [Buffer], [NumberOfChars], 0, 0
                            ret
_tulosta_konsoliin          ENDP
;----------------------------------------------------------------------------
;Lukee n�pp�imist�sy�tteen. Ylipitk� teksti hyl�t��n. Rivinvaihtomerkkej�
;ei lasketa mukaan merkkeihin.
;in  : merkkipuskurin osoite, puskurin koko
;out : osoite luettujen merkkien m��r��n
;out : EAX = 1, kaikki OK. EAX = 0, tapahtui virhe

_lue_konsolilta             PROC    C USES esi ecx, Buffer:PVOID, NumberOfCharsToRead:DWORD,
                                                    NumberOfCharsRead:PDWORD
                            LOCAL   apupuskuri[N_APUPUSKURI]:BYTE, n_merkit:DWORD
                            INVOKE  FlushConsoleInputBuffer, [luentakahva]
                            cmp     eax, 0
                            je      virhe
                            INVOKE  ReadConsoleA, [luentakahva], [Buffer], [NumberOfCharsToRead], [NumberOfCharsRead], 0
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
tyhjennys:                  INVOKE  ReadConsoleA, [luentakahva], ADDR apupuskuri, N_APUPUSKURI, ADDR n_merkit, 0
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
virhe:                      INVOKE  _tulosta_konsoliin, ADDR luenta_virheteksti, SIZEOF luenta_virheteksti
                            xor     eax, eax
                            ret
_lue_konsolilta             ENDP
;----------------------------------------------------------------------------
                            END
