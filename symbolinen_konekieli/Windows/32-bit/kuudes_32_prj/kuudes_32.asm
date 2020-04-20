;Visual Studio, koodisivu 1252
                            .686                                ;uudemmat x87-käskyt, CPUID
                            .MODEL  FLAT, STDCALL               ;stdcall: 32-bit WinAPI kutsutapa oletukseksi
                            OPTION  CASEMAP:NONE                ;erottele ISOT ja pienet kirjaimet tunnuksissa

                            INCLUDE ..\makrot_w32.txt
                            INCLUDE ..\makrot_32.txt

_tutki_karkausvuosi         PROTO    C  vuosi:DWORD

                            .STACK  4096

                            .CONST

alkuteksti                  BYTE    'Ohjelma 6.', CRLF
lopputeksti                 BYTE    CRLF, 'Ohjelma suoritettu.', CRLF
vuosi_1984                  BYTE    CRLF, 'Vuosi 1984 '
vuosi_1985                  BYTE    CRLF, 'Vuosi 1985 '
vuosi_1900                  BYTE    CRLF, 'Vuosi 1900 '

on_karkausvuosi             BYTE    'on karkausvuosi', CRLF
ei_ole_karkausvuosi         BYTE    'ei ole karkausvuosi', CRLF

palaute_ok                  BYTE    CRLF, 'LOG laskettu.'
palaute_virhe               BYTE    CRLF, 'LOG virhe.'

palaute_lnz_ok              BYTE    CRLF, 'LN(z) laskettu.'
palaute_lnz_virhe           BYTE    CRLF, 'LN(z) virhe.'
palaute_exp_tehty           BYTE    CRLF, 'exp(x) laskettu.'
palaute_expz_tehty          BYTE    CRLF, 'expz(z) laskettu.'

                            .DATA?

merkit                      BYTE    10 DUP(?)
merkki_lkm                  DWORD   ?
logstatus                   DWORD   ?

                            .DATA

testiluku                   REAL8         101.0
reaali_log_tulos            REAL8         ?
testilukuz                  KOMPLEKSILUKU {5.0, 7.0}
tuloslnz                    KOMPLEKSILUKU {}
tulosexpz                   KOMPLEKSILUKU {}
exp_p                       REAL8         -0.4
exp_p2                      REAL8         -0.1
exp_p3                      REAL8         0.5
exp_tulos                   REAL8           ?

                            .CODE
;----------------------------------------------------------------------------
start                       PROC    C

                            INVOKE  _valmistele_konsoli
                            cmp     eax, 0
                            je      poistu

                            INVOKE  _tulosta_konsoliin, ADDR alkuteksti, SIZEOF alkuteksti

                            INVOKE  _tulosta_konsoliin, ADDR vuosi_1900, SIZEOF vuosi_1900
                            INVOKE  _tutki_karkausvuosi, 1900
                            cmp     eax, 1
                            jne     ei_kv_1900
                            INVOKE  _tulosta_konsoliin, ADDR on_karkausvuosi, SIZEOF on_karkausvuosi
                            jmp     tutki_1984
ei_kv_1900:                 INVOKE  _tulosta_konsoliin, ADDR ei_ole_karkausvuosi, SIZEOF ei_ole_karkausvuosi
tutki_1984:                 INVOKE  _tulosta_konsoliin, ADDR vuosi_1984, SIZEOF vuosi_1984
                            INVOKE  _tutki_karkausvuosi, 1984
                            cmp     eax, 1
                            jne     ei_kv_1984
                            INVOKE  _tulosta_konsoliin, ADDR on_karkausvuosi, SIZEOF on_karkausvuosi
                            jmp     tutki_1985
ei_kv_1984:                 INVOKE  _tulosta_konsoliin, ADDR ei_ole_karkausvuosi, SIZEOF ei_ole_karkausvuosi
tutki_1985:                 INVOKE  _tulosta_konsoliin, ADDR vuosi_1985, SIZEOF vuosi_1985
                            INVOKE  _tutki_karkausvuosi, 1985
                            cmp     eax, 1
                            jne     ei_kv_1985
                            INVOKE  _tulosta_konsoliin, ADDR on_karkausvuosi, SIZEOF on_karkausvuosi
                            jmp     liukulukulaskut
ei_kv_1985:                 INVOKE  _tulosta_konsoliin, ADDR ei_ole_karkausvuosi, SIZEOF ei_ole_karkausvuosi

liukulukulaskut:            finit
                            INVOKE  _ln, [testiluku], ADDR logstatus
                            cmp     [logstatus], LOG_OK
                            jne      yli
                            fstp    REAL8 PTR [reaali_log_tulos]
                            INVOKE  _tulosta_konsoliin, ADDR palaute_ok, SIZEOF palaute_ok
                            jmp     seuraava
yli:                        INVOKE  _tulosta_konsoliin, ADDR palaute_virhe, SIZEOF palaute_virhe
seuraava:                   INVOKE  _log10, [testiluku], ADDR logstatus
                            cmp     [logstatus], LOG_OK
                            jne      yli2
                            fstp    REAL8 PTR [reaali_log_tulos]
                            INVOKE  _tulosta_konsoliin, ADDR palaute_ok, SIZEOF palaute_ok
                            jmp     kompleksi_log
yli2:                       INVOKE  _tulosta_konsoliin, ADDR palaute_virhe, SIZEOF palaute_virhe
kompleksi_log:              INVOKE  _lnz,  ADDR testilukuz,  ADDR tuloslnz, ADDR logstatus
                            cmp     [logstatus], LOG_OK
                            jne     yli3
                            INVOKE  _tulosta_konsoliin, ADDR palaute_lnz_ok, SIZEOF palaute_lnz_ok
                            jmp     exp_reaali
yli3:                       INVOKE  _tulosta_konsoliin, ADDR palaute_lnz_virhe, SIZEOF palaute_lnz_virhe
exp_reaali:                 INVOKE  _exp, [exp_p]
                            fstp    REAL8 PTR [exp_tulos]
                            INVOKE  _exp, [exp_p2]
                            fstp    REAL8 PTR [exp_tulos]
                            ;finit
                            INVOKE  _exp, [exp_p3]
                            fstp    REAL8 PTR [exp_tulos]
                            INVOKE  _tulosta_konsoliin, ADDR palaute_exp_tehty, SIZEOF palaute_exp_tehty
                            INVOKE  _expz, ADDR tuloslnz, ADDR tulosexpz
                            INVOKE  _tulosta_konsoliin, ADDR palaute_expz_tehty, SIZEOF palaute_expz_tehty

lopeta:                     INVOKE  _tulosta_konsoliin, ADDR lopputeksti, SIZEOF lopputeksti
poistu:                     INVOKE  ExitProcess, 0
start                       ENDP
;----------------------------------------------------------------------------
;Tutkii, onko annettu vuosi karkausvuosi.
; C-kieli: int tutki_karkausvuosi(int vuosi)
;in : vuosi
;out: EAX = 1, jos karkausvuosi, muutoin EAX = 0

_tutki_karkausvuosi         PROC    C USES edx ebx, vuosi:DWORD
                            xor     edx, edx                    ;jaettavan yläosa = 0
                            mov     eax, [vuosi]                ;jaettava
                            mov     ebx, 100
                            div     ebx
                            cmp     edx, 0
                            je      vuosisata                   ;mahdollinen karkausvuosi
                            test    edx, 03h                    ;normivuosi. vuoden loppuosa
                            jz      karkaus
                            xor     eax, eax
                            ret
vuosisata:                  test    eax, 03h                    ;vuosisatojen osuus
                            jz      karkaus
                            xor     eax, eax
                            ret
karkaus:                    mov     eax, 1
                            ret
_tutki_karkausvuosi         ENDP
;----------------------------------------------------------------------------

logaritmi                   PROC    C PRIVATE luku:REAL8, virhekoodi:PDWORD, valinta:DWORD
                            lea     eax, [luku]
                            cmp     DWORD PTR [eax], 0
                            jne     tarkista_neg
                            test    DWORD PTR [eax + 4], 0fffffffh
                            jnz     tarkista_neg
                            mov     eax, [virhekoodi]
                            mov     DWORD PTR [eax], LOG_VIRHE_NOLLA
                            ret
tarkista_neg:               test    DWORD PTR [eax + 4], 80000000h
                            jz      laske
                            mov     eax, [virhekoodi]
                            mov     DWORD PTR [eax], LOG_VIRHE_NEG
                            ret
laske:                      cmp     [valinta], 0
                            jne     log2_e
                            fldl2t                              ;log2(10)
                            jmp     loppulaskut
log2_e:                     fldl2e                              ;log2(e)
loppulaskut:                fld1                                ;1.0 -> Y
                            fld     [luku]                      ;X
                            fyl2x                               ;Y*log2(X)
                            fdivrp                              ;log2(X)/log2() = log(X)
                            mov     DWORD PTR [eax], LOG_OK
                            ret
logaritmi                   ENDP
;----------------------------------------------------------------------------
; Laskee 10-kantaisen Briggsin logaritmin positiiviselle reaaliluvulle.
; C-kieli: double log10(double x, int *status)
; in : luku > 0
; out: virhekoodi, 0 = OK
; out: st0 = log10(luku)
;

_log10                      PROC    C luku:REAL8, virhekoodi:PDWORD
                            INVOKE logaritmi, luku, virhekoodi, 0

;                            lea     eax, [luku]
;                            cmp     DWORD PTR [eax], 0
;                            jne     tarkista_neg
;                            test    DWORD PTR [eax + 4], 0fffffffh
;                            jnz     tarkista_neg
;                            mov     eax, [virhekoodi]
;                            mov     DWORD PTR [eax], LOG_VIRHE_NOLLA
;                            ret
;tarkista_neg:               test    DWORD PTR [eax + 4], 80000000h
;                            jz      laske
;                            mov     eax, [virhekoodi]
;                            mov     DWORD PTR [eax], LOG_VIRHE_NEG
;                            ret
;laske:                      fldl2t                              ;log2(10)
;                            fld1                                ;1.0 -> Y
;                            fld     [luku]                      ;X
;                            fyl2x                               ;Y*log2(X)
;                            fdivrp                              ;log2(X)/log2(10) = log10(X)
;                            mov     DWORD PTR [eax], LOG_OK
                            ret
_log10                      ENDP
;----------------------------------------------------------------------------
; Laskee e-kantaisen luonnollisen logaritmin positiiviselle reaaliluvulle.
; C-kieli: double ln(double x, int *status)
; in : luku > 0
; out: virhekoodi, 0 = OK
; out: st0 = ln(luku)
;

_ln                         PROC    C luku:REAL8, virhekoodi:PDWORD
                            INVOKE logaritmi, luku, virhekoodi, 1

;                            lea     eax, [luku]
;                            cmp     DWORD PTR [eax], 0
;                            jne     tarkista_neg
;                            test    DWORD PTR [eax + 4], 0fffffffh
;                            jnz     tarkista_neg
;                            mov     eax, [virhekoodi]
;                            mov     DWORD PTR [eax], LOG_VIRHE_NOLLA
;                            ret
;tarkista_neg:               test    DWORD PTR [eax + 4], 80000000h
;                            jz      laske
;                            mov     eax, [virhekoodi]
;                            mov     DWORD PTR [eax], LOG_VIRHE_NEG
;                            ret
;laske:                      fldl2e                              ;log2(e)
;                            fld1                                ;1.0 -> Y
;                            fld     [luku]                      ;X
;                            fyl2x                               ;Y*log2(X)
;                            fdivrp                              ;log2(X)/log2(e) = ln(X)
;                            mov     DWORD PTR [eax], LOG_OK
                            ret
_ln                         ENDP
;----------------------------------------------------------------------------
; Laskee e-kantaisen luonnollisen logaritmin kompleksiluvulle.
; C-kieli: void exp(const KOMPLEKSILUKU_STR *luku, KOMPLEKSILUKU_STR *tulos, int *status)
; in : luku != (0, 0)
; out: virhekoodi, 0 = OK
; out: muistipaikkaan lnz(luku)

_lnz                        PROC    C USES esi ecx, luku:PKOMPL, tulos:PKOMPL, virhekoodi:PDWORD
;tutkitaan annettu luku
                            xor     esi, esi
                            xor     ecx, ecx
                            mov     eax, [luku]
tutkinta:                   cmp     DWORD PTR [eax + esi], 0
                            jne     laskenta
                            test    DWORD PTR [eax + esi + ((SIZEOF KOMPLEKSILUKU)/4)], 0fffffffh
                            jnz     laskenta
                            add     esi, SIZEOF REAL8           ; +8 tavua
                            inc     ecx
                            cmp     ecx, 2                      ;re-osa ja im-osa, 2 kpl tutkittavaa
                            jne     tutkinta
                            mov     eax, [virhekoodi]
                            mov     DWORD PTR [eax], LOG_VIRHE_NOLLA    ;z = 0 + 0*i
                            ret
laskenta:                   fldl2e                              ;log2(e)
                            fld1                                ;1.0 -> Y
                            fld     REAL8 PTR [eax]
                            fmul    st, st                      ;Re^2
                            fld     REAL8 PTR [eax + (SIZEOF REAL8)]
                            fmul    st, st                      ;Im^2
                            faddp                               ;Re^2 + Im^2
                            fsqrt                               ;r = |z| = |Re + i*Im|
                            fyl2x                               ;Y*log2(r)
                            fdivrp                              ;Re{ln(z)}
                            mov     esi, [tulos]
                            fstp    REAL8 PTR [esi]             ;tuloksen reaaliosan tallennus
                            fld     REAL8 PTR [eax + (SIZEOF REAL8)]    ;Im
                            fld     REAL8 PTR [eax]                     ;Re
                            fpatan                                      ;Arg(z) = Im{ln(z)}
                            fstp    REAL8 PTR [esi + (SIZEOF REAL8)]    ;tuloksen imaginaariosan tallennus
                            mov     eax, [virhekoodi]
                            mov     DWORD PTR [eax], LOG_OK
                            ret
_lnz                        ENDP
;----------------------------------------------------------------------------
; Eksponenttifunktio e^x
; C-kieli: double exp(double x)
;

_exp                        PROC    C potenssi:REAL8
                            fld     [potenssi]
                            fldl2e                              ;log2(e) -> st(0)
                            fmulp                               ;skaalataan log2(e):lla
                            fld     st                          ;kahdennetaan
                            frndint                             ;int(st(0))
                            fsubr   st(0), st(1)                ;vähennetään kokonainen luku
                            f2xm1                               ;2^st(0)-1 -> st(0)
                            fld1                                ;1.0
                            faddp                               ;2^x-1 + 1 -> 2^x
                            fxch
                            frndint                             ;skaalauksen pyöristys -> n
                            fxch
                            fscale                              ;(2^x) * 2^n -> exp(X)
                            ffree   st(1)
                            ret
_exp                        ENDP
;----------------------------------------------------------------------------
; Eksponenttifunktio e^z
; C-kieli: void expz(const KOMPLEKSILUKU_STR *potenssi, KOMPLEKSILUKU_STR *tulos)

_expz                       PROC    C  potenssi:PKOMPL, tulos:PKOMPL
                            mov     eax, [potenssi]
                            INVOKE  _exp, [eax]                 ;e^Re -> st(0)
                            fld     REAL8 PTR [eax + (SIZEOF REAL8)]    ;Im -> st(0)
                            fld     st                          ;kahdennus
                            fcos
                            fmul    st(0), st(2)                ;e^Re * cos(Im)
                            mov     eax, [tulos]
                            fstp    REAL8 PTR [eax]             ;tuloksen Re-osa
                            fsin
                            fmulp                               ;e^Re * sin(Im)
                            fstp    REAL8 PTR [eax + (SIZEOF REAL8)]    ;tuloksen Im-osa
                            ret
_expz                       ENDP
;----------------------------------------------------------------------------
                            END     start
