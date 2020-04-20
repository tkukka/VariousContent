;Visual Studio, koodisivu 1252
                            .686                                ;uudemmat x87-k�skyt, CPUID
                            .MODEL  FLAT, STDCALL               ;stdcall: 32-bit WinAPI kutsutapa oletukseksi
                            OPTION  CASEMAP:NONE                ;erottele ISOT ja pienet kirjaimet tunnuksissa

                            INCLUDE ..\makrot_w32.txt
                            INCLUDE ..\makrot_32.txt

_tutki_karkausvuosi         PROTO    C  vuosi:DWORD
_ympyran_ala                PROTO    C  sade:REAL8
_pallon_tilavuus            PROTO    C  sade:REAL8

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
palaute_lnz_ok              BYTE    CRLF, 'lnz(z) laskettu.'
palaute_lnz_virhe           BYTE    CRLF, 'lnz(z) virhe.'
palaute_exp_tehty           BYTE    CRLF, 'exp(x) laskettu.'
palaute_expz_tehty          BYTE    CRLF, 'expz(z) laskettu.'
palaute_powz_tehty          BYTE    CRLF, 'powz(z,z) laskettu.'
palaute_powz_virhe          BYTE    CRLF, 'powz(z,z) virhe.'

                            .DATA

testiluku                   REAL8           101.0
reaali_log_tulos            REAL8           ?
logstatus                   DWORD           ?
testilukuz                  KOMPLEKSILUKU   {5.0, 7.0}
tuloslnz                    KOMPLEKSILUKU   {}
tulosexpz                   KOMPLEKSILUKU   {}
exp_p                       REAL8           -0.4
exp_p2                      REAL8           -0.1
exp_p3                      REAL8           0.5
exp_tulos                   REAL8           ?
tekija1                     KOMPLEKSILUKU   {2.0, -1.0}
tekija2                     KOMPLEKSILUKU   {10.0, 3.0}
tulo_z                      KOMPLEKSILUKU   {}
powz_tulos                  KOMPLEKSILUKU   {}
powz_luku                   KOMPLEKSILUKU   {3.0, 1.0}
powz_potenssi               KOMPLEKSILUKU   {2.0, 2.0}
powz_status                 DWORD           ?

vec                         VEKTORI         {3.0, 0.0, 4.0}
vpituus                     REAL8           ?
ala                         REAL8           ?
tilavuus                    REAL8           ?

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
                            INVOKE  _mulz, ADDR tekija1, ADDR tekija2, ADDR tulo_z
                            INVOKE  _powz, ADDR powz_luku, ADDR powz_potenssi, ADDR powz_tulos, ADDR powz_status
                            cmp     [powz_status], POWZ_OK
                            jne     powz_virhe
                            INVOKE  _tulosta_konsoliin, ADDR palaute_powz_tehty, SIZEOF palaute_powz_tehty
                            jmp     vektori_laskut
powz_virhe:                 INVOKE  _tulosta_konsoliin, ADDR palaute_powz_virhe, SIZEOF palaute_powz_virhe

vektori_laskut:             INVOKE  _vektorin_pituus, ADDR vec
                            fstp    REAL8 PTR [vpituus]
                            INVOKE  _ympyran_ala, [vpituus]
                            fstp    REAL8 PTR [ala]
                            INVOKE  _pallon_tilavuus, [vpituus]
                            fstp    REAL8 PTR [tilavuus]

lopeta:                     INVOKE  _tulosta_konsoliin, ADDR lopputeksti, SIZEOF lopputeksti
poistu:                     INVOKE  ExitProcess, 0
start                       ENDP
;----------------------------------------------------------------------------
;Tutkii, onko annettu vuosi karkausvuosi.
; C-kieli: int tutki_karkausvuosi(int vuosi)
;in : vuosi
;out: EAX = 1, jos karkausvuosi, muutoin EAX = 0

_tutki_karkausvuosi         PROC    C USES edx ebx, vuosi:DWORD
                            xor     edx, edx                    ;jaettavan yl�osa = 0
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
; Apufunktio. Laskee ln- tai log10-logaritmin valinnan mukaan.

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
; C-kieli: void lnz(const KOMPLEKSILUKU_STR *luku, KOMPLEKSILUKU_STR *tulos, int *status)
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

_exp                        PROC    C potenssi:REAL8
                            fld     [potenssi]
                            fldl2e                              ;log2(e) -> st(0)
                            fmulp                               ;skaalataan log2(e):lla
                            fld     st                          ;kahdennetaan
                            frndint                             ;int(st(0))
                            fsubr   st(0), st(1)                ;v�hennet��n kokonainen luku
                            f2xm1                               ;2^st(0)-1 -> st(0)
                            fld1                                ;1.0
                            faddp                               ;2^x-1 + 1 -> 2^x
                            fxch
                            frndint                             ;skaalauksen py�ristys -> n
                            fxch
                            fscale                              ;(2^x) * 2^n -> exp(X)
                            ffree   st(1)
                            ret
_exp                        ENDP
;----------------------------------------------------------------------------
; Eksponenttifunktio e^z
; C-kieli: void expz(const KOMPLEKSILUKU_STR *potenssi, KOMPLEKSILUKU_STR *tulos)

_expz                       PROC    C potenssi:PKOMPL, tulos:PKOMPL
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
; Kompleksilukujen kertolasku
; C-kieli: void mulz(const KOMPLEKSILUKU_STR *lukuA, const KOMPLEKSILUKU_STR *lukuB, KOMPLEKSILUKU_STR *tulos)

_mulz                       PROC    C USES ebx esi, lukuA:PKOMPL, lukuB:PKOMPL, tulos:PKOMPL
                            mov     eax, [lukuA]
                            mov     ebx, [lukuB]
                            fld     REAL8 PTR [eax]             ;A.Re
                            fld     REAL8 PTR [ebx]             ;B.Re
                            fmulp
                            fld     REAL8 PTR [eax + (SIZEOF REAL8)]    ;A.Im
                            fld     REAL8 PTR [ebx + (SIZEOF REAL8)]    ;B.Im
                            fmulp
                            fsubp                                       ;A.Re * B.Re - A.Im * B.Im
                            mov     esi, [tulos]
                            fstp    REAL8 PTR [esi]             ;tulon Re-osa
                            fld     REAL8 PTR [eax]             ;A.Re
                            fld     REAL8 PTR [ebx + (SIZEOF REAL8)]    ;B.Im
                            fmulp
                            fld     REAL8 PTR [eax + (SIZEOF REAL8)]    ;A.Im
                            fld     REAL8 PTR [ebx]             ;B.Re
                            fmulp
                            faddp                                       ;A.Re * B.Im + A.Im * B.Re
                            fstp    REAL8 PTR [esi + (SIZEOF REAL8)]    ;tulon Im-osa
                            ret
_mulz                       ENDP
;----------------------------------------------------------------------------
; Kompleksilukujen potenssi z1 ^ z2 = expz(z2*lnz(z1))
; C-kieli: void powz(const KOMPLEKSILUKU_STR *luku, const KOMPLEKSILUKU_STR *potenssi, 
;                    KOMPLEKSILUKU_STR *tulos, int *status)

_powz                       PROC    C luku:PKOMPL, potenssi:PKOMPL, tulos:PKOMPL, virhekoodi:PDWORD
                            LOCAL   mulz_tulos:KOMPLEKSILUKU, lnz_tulos:KOMPLEKSILUKU, lnz_status:DWORD
                            INVOKE  _lnz, luku, ADDR lnz_tulos, ADDR lnz_status
                            cmp     [lnz_status], LOG_OK
                            je      jatkolasku
                            mov     eax, [virhekoodi]
                            mov     DWORD PTR [eax], POWZ_VIRHE
                            ret
jatkolasku:                 INVOKE  _mulz, potenssi, ADDR lnz_tulos, ADDR mulz_tulos
                            INVOKE  _expz, ADDR mulz_tulos, tulos
                            mov     eax, [virhekoodi]
                            mov     DWORD PTR [eax], POWZ_OK
                            ret
_powz                       ENDP
;----------------------------------------------------------------------------
; Laskee vektorin (x,y,z) pituuden
; C-kieli: double vektorin_pituus(const VEKTORI_STR *v)

_vektorin_pituus            PROC    C vektori:PVEKTORI
                            mov     eax, [vektori]
                            fld     REAL8 PTR [eax]             ;v.x
                            fmul    st, st
                            fld     REAL8 PTR [eax + (SIZEOF REAL8)]    ;v.y
                            fmul    st, st
                            fld     REAL8 PTR [eax + 2*(SIZEOF REAL8)]  ;v.z
                            fmul    st, st
                            faddp
                            faddp
                            fsqrt
                            ret
_vektorin_pituus            ENDP
;----------------------------------------------------------------------------
; Laskee r-s�teisen ympyr�n alan
; C-kieli: double ympyran_ala(double r)

_ympyran_ala                PROC    C sade:REAL8
                            fld     [sade]                      ;r
                            fmul    st, st                      ;r^2
                            fldpi                               ;3.14 -> st(0)
                            fmulp                               ;pii*r^2
                            ret
_ympyran_ala                ENDP
;----------------------------------------------------------------------------
; Laskee r-s�teisen pallon tilavuuden
; C-kieli: double pallon_tilavuus(double r)

_pallon_tilavuus            PROC    C sade:REAL8
                            fld     [sade]                      ;r
                            fld     st
                            fmul    st, st                      ;r^2
                            fmulp                               ;r^3
                            fldpi                               ;3.14 -> st(0)
                            fmulp                               ;pii*r^3
                            fld1                                ;1.0 -> st(0)
                            fadd    st, st                      ;2.0 -> st(0)
                            fxch                                ;pii*r^3 -> st(0)
                            fscale                              ;st(0)*2^2
                            fxch                                ;2.0 -> st(0)
                            fld1                                ;1.0 -> st(0)
                            faddp                               ;3.0 -> st(0)
                            fdivp                               ;4*pii*r^3 / 3
                            ret
_pallon_tilavuus            ENDP
;----------------------------------------------------------------------------
                            END     start
