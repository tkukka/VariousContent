;Visual Studio, koodisivu 1252
                            .686                                ;uudemmat x87-käskyt, CPUID
                            .MODEL  FLAT, STDCALL               ;stdcall: 32-bit WinAPI kutsutapa oletukseksi
                            OPTION  CASEMAP:NONE                ;erottele ISOT ja pienet kirjaimet tunnuksissa

                            INCLUDE ..\makrot_w32.txt
                            INCLUDE ..\makrot_32.txt

                            .NOLIST
modulo                      MACRO   a:REQ, b:REQ
                            push    edx
                            push    ebx
                            mov     ebx, b
                            mov     eax, a
                            xor     edx, edx
                            div     ebx
                            mov     eax, edx
                            pop     ebx
                            pop     edx
                            ENDM
                            .NOLISTMACRO
                            .LIST

_alusta_sallitut            PROTO   C sallitut:PBYTE, aakkoslista:PBYTE, N_lista:DWORD
_luo_aakkosindeksit         PROTO   C
_pienaakkosiksi             PROTO   C jono:PBYTE, N_jono:DWORD
_suuraakkosiksi             PROTO   C jono:PBYTE, N_jono:DWORD
_sekoita                    PROTO   C teksti:PBYTE, tekstin_pituus:DWORD, avain:PBYTE, avaimen_pituus:DWORD, salattu:PBYTE, salattu_pituus:DWORD
_pura                       PROTO   C teksti:PBYTE, tekstin_pituus:DWORD, avain:PBYTE, avaimen_pituus:DWORD, purettu:PBYTE, purettu_pituus:DWORD

                            .STACK  4096

                            .CONST

alkuteksti                  BYTE    '--- Ohjelma 8 ---', CRLF
lopputeksti                 BYTE    CRLF, 'Ohjelma suoritettu.', CRLF
aakkoset                    BYTE    'ABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ'
N_aakkoset                  EQU     SIZEOF aakkoset
alkusiirtyma                EQU     1                           ;1. rivin/sarakkeen siirros aakkosissa
salattu_puskuri_pieni       BYTE    CRLF, 'Salauksen tulos ei mahdu annettuun muistialueeseen.'
selko_puskuri_pieni         BYTE    CRLF, 'Salauksen purun tulos ei mahdu annettuun muistialueeseen.'
selkoteksti                 BYTE    'LÄHETÄMEILLEHYVÄLUOTSI'
purettava_teksti            BYTE    'ATWÅYRVWAÅEJÅEKTÅNTJÄÅ'
salausavain                 BYTE    'RUOVESI'

                            .DATA

sallitut_merkit             BYTE    1, 255 DUP(0)               ;0/1 ei sallittu, merkki kohdallaan = sallittu
aakkosindeksit              BYTE    256 DUP(N_aakkoset)         ;hakutaulu, A -> 0, B -> 1, ...
mjono                       BYTE    'ABCDEFGHIJKLMNOPQRSTUVWXYZÅÄÖ'
N_mjono                     EQU     SIZEOF mjono

merkkipuskuri               BYTE    64 DUP(32)

                            .CODE
;----------------------------------------------------------------------------
start                       PROC    C

                            INVOKE  _valmistele_konsoli
                            cmp     eax, 0
                            je      poistu

                            INVOKE  _tulosta_konsoliin, ADDR alkuteksti, SIZEOF alkuteksti
                            INVOKE  _alusta_sallitut, ADDR sallitut_merkit, ADDR aakkoset, N_aakkoset
                            INVOKE  _luo_aakkosindeksit
                            INVOKE  _pienaakkosiksi, ADDR mjono, N_mjono
                            INVOKE  _suuraakkosiksi, ADDR mjono, N_mjono
                            INVOKE  _sekoita, ADDR selkoteksti, SIZEOF selkoteksti, ADDR salausavain, SIZEOF salausavain, 
                                              ADDR merkkipuskuri, SIZEOF merkkipuskuri

                            INVOKE  _pura, ADDR purettava_teksti, SIZEOF purettava_teksti, ADDR salausavain, SIZEOF salausavain, 
                                              ADDR merkkipuskuri, SIZEOF merkkipuskuri


lopeta:                     INVOKE  _tulosta_konsoliin, ADDR lopputeksti, SIZEOF lopputeksti
poistu:                     INVOKE  ExitProcess, 0
start                       ENDP
;----------------------------------------------------------------------------
_alusta_sallitut            PROC    C USES eax ebx edx edi, sallitut:PBYTE, aakkoslista:PBYTE, N_lista:DWORD
                            mov     eax, [aakkoslista]
                            mov     ebx, N_lista
                            lea     ebx, [eax + ebx]
                            mov     edi, [sallitut]
silmukka:                   movzx   edx, BYTE PTR [eax]
                            inc     eax
                            mov     [edi + edx], dl
                            cmp     eax, ebx
                            jne     silmukka
                            ret
_alusta_sallitut            ENDP
;----------------------------------------------------------------------------
_luo_aakkosindeksit         PROC    C USES eax ebx ecx edx
                            mov     eax, OFFSET aakkosindeksit
                            mov     ebx, OFFSET aakkoset
                            xor     ecx, ecx
silmukka:                   movzx   edx, BYTE PTR [ebx]         ;'A', 'B',... -> EDX (indeksoi kirjaimella)
                            inc     ebx
                            mov     [eax + edx], cl             ;A:lle 0, B:lle 1, ... Ö:lle 28
                            inc     ecx                            
                            cmp     ecx, N_aakkoset
                            jne     silmukka
                            ret
_luo_aakkosindeksit         ENDP
;----------------------------------------------------------------------------
_pienaakkosiksi             PROC    C  USES eax ebx edx, jono:PBYTE, N_jono:DWORD
                            mov     eax, [jono]
                            mov     ebx, N_jono
                            lea     ebx, [eax + ebx]
silmukka:                   movzx   edx, BYTE PTR [eax]
                            cmp     edx, 'A'
                            jb      seuraava
                            cmp     edx, 'Z'
                            ja      skandit
                            or      edx, 20h                    ;muunna
                            mov     [eax], dl
                            jmp     seuraava
skandit:                    cmp     edx, 0c4h                   ;Ä
                            je      muunna
                            cmp     edx, 0c5h                   ;Å
                            je      muunna
                            cmp     edx, 0d6h                   ;Ö
                            jne     seuraava
muunna:                     or      edx, 20h
                            mov     [eax], dl
seuraava:                   inc     eax
                            cmp     eax, ebx
                            jne     silmukka
                            ret
_pienaakkosiksi             ENDP
;----------------------------------------------------------------------------
_suuraakkosiksi             PROC    C  USES eax ebx edx, jono:PBYTE, N_jono:DWORD
                            mov     eax, [jono]
                            mov     ebx, N_jono
                            lea     ebx, [eax + ebx]
silmukka:                   movzx   edx, BYTE PTR [eax]
                            cmp     edx, 'a'
                            jb      seuraava
                            cmp     edx, 'z'
                            ja      skandit
                            and     edx, 0dfh                   ;muunna
                            mov     [eax], dl
                            jmp     seuraava
skandit:                    cmp     edx, 0e4h                   ;ä
                            je      muunna
                            cmp     edx, 0e5h                   ;å
                            je      muunna
                            cmp     edx, 0f6h                   ;ö
                            jne     seuraava
muunna:                     and     edx, 0dfh
                            mov     [eax], dl
seuraava:                   inc     eax
                            cmp     eax, ebx
                            jne     silmukka
                            ret
_suuraakkosiksi             ENDP
;----------------------------------------------------------------------------
_sekoita                    PROC    C USES eax ebx ecx edx edi esi, teksti:PBYTE, 
                                    tekstin_pituus:DWORD, avain:PBYTE, avaimen_pituus:DWORD, 
                                    salattu:PBYTE, salattu_pituus:DWORD
                            LOCAL   avainrivi:DWORD, selkosarake:DWORD, salattu_lkm:DWORD
                            mov     [salattu_lkm], 0
                            mov     esi, [teksti]
                            mov     ecx, [tekstin_pituus]
                            mov     edi, [avain]
                            mov     edx, [avaimen_pituus]
                            lea     ecx, [esi + ecx]
                            lea     edx, [edi + edx]
silmukka:                   mov     ebx, OFFSET aakkosindeksit
                            movzx   eax, BYTE PTR [esi]
                            xlat                                ;lähdetekstin merkin indeksi
                            mov     [selkosarake], eax
                            movzx   eax, BYTE PTR [edi]
                            xlat                                ;avaimen merkin indeksi
                            mov     [avainrivi], eax
                            mov     eax, alkusiirtyma           ;1. rivin/sarakkeen siirros aakkosissa
                            add     eax, [avainrivi]
                            add     eax, [selkosarake]
                            modulo  eax, N_aakkoset
                            lea     eax, [aakkoset + eax]       ;merkin osoite
                            movzx   eax, BYTE PTR [eax]         ;merkki
                            mov     ebx, [salattu]
                            push    ecx
                            mov     ecx, [salattu_lkm]
                            cmp     ecx, [salattu_pituus]       ;mahtuuko koodattu merkki?
                            je      virhe
                            mov     [ebx + ecx], al
                            inc     ecx
                            mov     [salattu_lkm], ecx
                            jmp     normitilanne
virhe:                      mov     eax, -1                     ;ei voida edetä. merkitään.
normitilanne:               pop     ecx
                            cmp     eax, -1
                            je      virheilmoitus
                            inc     edi
                            cmp     edi, edx                    ;avain lopussa?
                            jne     ohi
                            mov     edi, [avain]
ohi:                        inc     esi
                            cmp     esi, ecx                    ;lähdeteksti lopussa?
                            jne     silmukka
                            mov     eax, [salattu_lkm]          ;palauta montako merkkiä salaustekstiin tuli
                            jmp     ulos
virheilmoitus:              INVOKE  _tulosta_konsoliin, ADDR salattu_puskuri_pieni, SIZEOF salattu_puskuri_pieni
                            xor     eax, eax
ulos:                       ret
_sekoita                    ENDP
;----------------------------------------------------------------------------
_pura                       PROC    C USES eax ebx ecx edx edi esi, teksti:PBYTE, 
                                    tekstin_pituus:DWORD, avain:PBYTE, avaimen_pituus:DWORD, 
                                    purettu:PBYTE, purettu_pituus:DWORD
                            LOCAL   salatun_indeksi:DWORD, avainrivi:DWORD, purettu_lkm:DWORD
                            mov     [purettu_lkm], 0
                            mov     esi, [teksti]
                            mov     ecx, [tekstin_pituus]
                            mov     edi, [avain]
                            mov     edx, [avaimen_pituus]
                            lea     ecx, [esi + ecx]            ;tekstin loppu
                            lea     edx, [edi + edx]            ;avaimen loppu
silmukka:                   mov     ebx, OFFSET aakkosindeksit
                            movzx   eax, BYTE PTR [esi]
                            xlat                                ;salatun tekstin merkin indeksi
                            mov     [salatun_indeksi], eax
                            movzx   eax, BYTE PTR [edi]
                            xlat                                ;avaimen merkin indeksi
                            mov     [avainrivi], eax
                            mov     eax, alkusiirtyma           ;1. rivin/sarakkeen siirros aakkosissa
                            add     eax, [avainrivi]
                            modulo  eax, N_aakkoset
                            mov     ebx, N_aakkoset
                            add     ebx, [salatun_indeksi]
                            sub     ebx, eax
                            mov     eax, ebx
                            modulo  eax, N_aakkoset
                            lea     eax, [aakkoset + eax]       ;merkin osoite
                            movzx   eax, BYTE PTR [eax]         ;merkki
                            mov     ebx, [purettu]
                            push    ecx
                            mov     ecx, [purettu_lkm]
                            cmp     ecx, [purettu_pituus]       ;mahtuuko purettu merkki?
                            je      virhe
                            mov     [ebx + ecx], al
                            inc     ecx
                            mov     [purettu_lkm], ecx
                            jmp     normitilanne
virhe:                      mov     eax, -1                     ;ei voida edetä. merkitään.
normitilanne:               pop     ecx
                            cmp     eax, -1
                            je      virheilmoitus
                            inc     edi
                            cmp     edi, edx                    ;avain lopussa?
                            jne     ohi
                            mov     edi, [avain]
ohi:                        inc     esi
                            cmp     esi, ecx                    ;lähdeteksti lopussa?
                            jne     silmukka
                            mov     eax, [purettu_lkm]          ;palauta montako merkkiä purettiin
                            jmp     ulos
virheilmoitus:              INVOKE  _tulosta_konsoliin, ADDR selko_puskuri_pieni, SIZEOF selko_puskuri_pieni
                            xor     eax, eax
ulos:                       ret
_pura                       ENDP
;----------------------------------------------------------------------------
                            END     start
