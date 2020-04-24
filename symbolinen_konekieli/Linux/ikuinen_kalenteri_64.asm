;sivu 500 teoksessa: Antero Vipunen : arvoitusten ja ongelmien, leikkien ja pelien sekä eri harrastelualojen pikkujättiläinen.
;Toimittanut Yrjö Karilas. WSOY, 1990. 15. painos. ISBN:9510121770

                            BITS    64
                            DEFAULT REL

laitelukeminen              EQU     0
laitetulostus               EQU     1
stdin                       EQU     0
stdout                      EQU     1
loppu_hyvin                 EQU     0
lopetus                     EQU     60
RIVINVAIHTO                 EQU     10
ALIN_VUOSI                  EQU     1500
YLIN_VUOSI                  EQU     3499


                            SECTION .rodata                     ;vakiot

otsikko                     DB      "Ikuinen kalenteri. Määrittää viikonpäivän (Ma-Su).", RIVINVAIHTO, RIVINVAIHTO
otsikon_pituus              EQU     ($ - otsikko)

annettu                     DB      RIVINVAIHTO, "Antamasi päivämäärä: "
annettu_pituus              EQU     ($ - annettu)

karkaus                     DB      "Vuosi on karkausvuosi.", RIVINVAIHTO
karkaus_pituus              EQU     ($ - karkaus)

kehote_pv                   DB      "Anna päivä (01-28...31):"
kehote_pv_pituus            EQU     ($ - kehote_pv)

kehote_kk                   DB      "Anna kuukausi (01-12):"
kehote_kk_pituus            EQU     ($ - kehote_kk)

kehote_v                    DB      "Anna vuosi (1500-3499):"
kehote_v_pituus             EQU     ($ - kehote_v)

virhe_ei_luku               DB      "Syötteessä on virhe. Ei ole luku.", RIVINVAIHTO
virhe_ei_luku_pituus        EQU     ($ - virhe_ei_luku)

virhe_paiva                 DB      "Päivä ei ollut sallitulla välillä.", RIVINVAIHTO
virhe_paiva_pituus          EQU     ($ - virhe_paiva)

virhe_kuukausi              DB      "Kuukausi ei ollut sallitulla välillä.", RIVINVAIHTO
virhe_kuukausi_pituus       EQU     ($ - virhe_kuukausi)

virhe_vuosi                 DB      "Vuosi ei ollut sallitulla välillä.", RIVINVAIHTO
virhe_vuosi_pituus          EQU     ($ - virhe_vuosi)

paivamaara_virhe            DB      "Antamasi päivämäärä on virheellinen.", RIVINVAIHTO
paivamaara_virhe_pituus     EQU     ($ - paivamaara_virhe)

piste                       DB      '.'
rivinvaihto                 DB      RIVINVAIHTO

kuukausien_pituudet         DB      31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31

maanantai                   DB      "maanantai", RIVINVAIHTO
maanantai_pituus            EQU     ($ - maanantai)
tiistai                     DB      "tiistai", RIVINVAIHTO
tiistai_pituus              EQU     ($ - tiistai)
keskiviikko                 DB      "keskiviikko", RIVINVAIHTO
keskiviikko_pituus          EQU     ($ - keskiviikko)
torstai                     DB      "torstai", RIVINVAIHTO
torstai_pituus              EQU     ($ - torstai)
perjantai                   DB      "perjantai", RIVINVAIHTO
perjantai_pituus            EQU     ($ - perjantai)
lauantai                    DB      "lauantai", RIVINVAIHTO
lauantai_pituus             EQU     ($ - lauantai)
sunnuntai                   DB      "sunnuntai", RIVINVAIHTO
sunnuntai_pituus            EQU     ($ - sunnuntai)
viikonpaivat                DQ      lauantai, sunnuntai, maanantai, tiistai, keskiviikko, torstai, perjantai                
N_viikonpaivat              DB      lauantai_pituus, sunnuntai_pituus, maanantai_pituus, tiistai_pituus
                            DB      keskiviikko_pituus, torstai_pituus, perjantai_pituus

kuukausiluvut               DB      0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5
vuosisataluvut              DB      0, 5, 3, 1
vuosien_luvut               DB      0, 1, 2, 3, 5, 6, 0
                            DB      1, 3, 4, 5, 6, 1, 2
                            DB      3, 4, 6, 0, 1, 2, 4
                            DB      5, 6, 0, 2, 3, 4, 5

lopputeksti                 DB      RIVINVAIHTO, "Viikonpäivä on "
lopputeksti_pituus          EQU     ($ - lopputeksti)


                            section .data                       ;muuttujat

ascii_luvut                 TIMES   20  DB  32
N_ascii_luvut               EQU     ($ - ascii_luvut)           ;varattu pituus
;ascii_luvut_pituus          DD      0                           ;ajonaikainen käytetty pituus
;ptr_ascii_luvut             DQ      0                           ;osoitin 1. tulostettavaan merkkiin

paiva                       DB      0, 0, 0
N_paiva                     EQU     ($ - paiva)

kuukausi                    DB      0, 0, 0
N_kuukausi                  EQU     ($ - kuukausi)

vuosi                       DB      0, 0, 0, 0, 0
N_vuosi                     EQU     ($ - vuosi)

karkausvuosi                DD      0

paiva_num                   DD      0
kuukausi_num                DD      0
vuosi_num                   DD      0


                            SECTION .text                       ;koodi

                            GLOBAL  _start:function

_start:                     mov     rdi, otsikko
                            mov     esi, otsikon_pituus
                            call    tulosta
;päivän kysyminen
                            mov     rdi, kehote_pv
                            mov     esi, kehote_pv_pituus
                            call    tulosta
                            mov     rdi, paiva
                            mov     esi, N_paiva
                            call    lue
                            cmp     eax, 1
                            jl      .lopetus
                            ;mov     rdi, paiva
                            ;mov     esi, eax
                            ;call    tulosta
                            mov     rdi, paiva
                            mov     esi, eax
                            mov     rdx, paiva_num
                            call    muunna_asc_num
                            cmp     eax, 0
                            jne     .lopetus
;kuukauden kysyminen
                            mov     rdi, kehote_kk
                            mov     esi, kehote_kk_pituus
                            call    tulosta
                            mov     rdi, kuukausi
                            mov     esi, N_kuukausi
                            call    lue
                            cmp     eax, 1
                            jl      .lopetus
                            ;mov     rdi, kuukausi
                            ;mov     esi, eax
                            ;call    tulosta
                            mov     rdi, kuukausi
                            mov     esi, eax
                            mov     rdx, kuukausi_num
                            call    muunna_asc_num
                            cmp     eax, 0
                            jne     .lopetus
;vuoden kysyminen
                            mov     rdi, kehote_v
                            mov     esi, kehote_v_pituus
                            call    tulosta
                            mov     rdi, vuosi
                            mov     esi, N_vuosi
                            call    lue
                            cmp     eax, 1
                            jl      .lopetus
                            ;mov     rdi, vuosi
                            ;mov     esi, eax
                            ;call    tulosta
                            mov     rdi, vuosi
                            mov     esi, eax
                            mov     rdx, vuosi_num
                            call    muunna_asc_num
                            cmp     eax, 0
                            jne     .lopetus
;näytetään mitä tietoja on annettu
                            mov     rdi, annettu
                            mov     esi, annettu_pituus
                            call    tulosta
;päivän muuttaminen ascii-merkeiksi
                            mov     edi, [paiva_num]
                            mov     rsi, ascii_luvut
                            mov     edx, N_ascii_luvut
                            call    muunna_num_asc
                            cmp     eax, -1
                            je      .lopetus
;lasketaan osoite tulostettavan tekstin alkuun
                            mov     ebx, eax
                            mov     eax, N_ascii_luvut
                            sub     eax, ebx
                            lea     rax, [ascii_luvut + rax]
                            mov     rdi, rax
                            mov     esi, ebx
                            ;mov     [ptr_ascii_luvut], rax
                            ;mov     [ascii_luvut_pituus], ebx
                            call    tulosta

                            mov     rdi, piste
                            mov     esi, 1
                            call    tulosta
;kuukauden muuttaminen ascii-merkeiksi
                            mov     edi, [kuukausi_num]
                            mov     rsi, ascii_luvut
                            mov     edx, N_ascii_luvut
                            call    muunna_num_asc
                            cmp     eax, -1
                            je      .lopetus
;lasketaan osoite tulostettavan tekstin alkuun
                            mov     ebx, eax
                            mov     eax, N_ascii_luvut
                            sub     eax, ebx
                            lea     rax, [ascii_luvut + rax]
                            mov     rdi, rax
                            mov     esi, ebx
                            ;mov     [ptr_ascii_luvut], rax
                            ;mov     [ascii_luvut_pituus], ebx
                            call    tulosta

                            mov     rdi, piste
                            mov     esi, 1
                            call    tulosta
;vuoden muuttaminen ascii-merkeiksi
                            mov     edi, [vuosi_num]
                            mov     rsi, ascii_luvut
                            mov     edx, N_ascii_luvut
                            call    muunna_num_asc
                            cmp     eax, -1
                            je      .lopetus
;lasketaan osoite tulostettavan tekstin alkuun
                            mov     ebx, eax
                            mov     eax, N_ascii_luvut
                            sub     eax, ebx
                            lea     rax, [ascii_luvut + rax]
                            mov     rdi, rax
                            mov     esi, ebx
                            ;mov     [ptr_ascii_luvut], rax
                            ;mov     [ascii_luvut_pituus], ebx
                            call    tulosta

                            mov     rdi, rivinvaihto
                            mov     esi, 1
                            call    tulosta
;perustarkistuksia
                            mov     edi, [paiva_num]
                            call    tarkista_paiva
                            cmp     eax, -1
                            je      .paiva_virhe
.paiva_ok:                  mov     edi, [kuukausi_num]
                            call    tarkista_kuukausi
                            cmp     eax, -1
                            je      .kuukausi_virhe
.kuukausi_ok:               mov     edi, [vuosi_num]
                            call    tarkista_vuosi
                            cmp     eax, -1
                            je      .vuosi_virhe
.vuosi_ok:                  mov     edi, [vuosi_num]
                            call    tutki_karkausvuosi
                            mov     [karkausvuosi], eax
;lisää tarkistuksia
                            mov     edi, [paiva_num]
                            mov     esi, [kuukausi_num]
                            mov     edx, [karkausvuosi]
                            call    tarkista_paivamaara
                            cmp     eax, -1
                            je      .paivamaara_virhe
.paivamaara_ok:             cmp     [karkausvuosi], dword 1
                            jne     .yli
                            mov     rdi, karkaus
                            mov     esi, karkaus_pituus
                            call    tulosta
.yli:                       xor     ebx, ebx                    ;haettujen lukujen summa
                            mov     edi, [paiva_num]
                            mov     esi, 7
                            call    modulo                      ;päivän luku jakojäännöksellä
                            add     ebx, eax
                            mov     edi, [kuukausi_num]
                            mov     esi, [karkausvuosi]
                            call    hae_kk_luku                 ;käsitellään kuukausi
                            add     ebx, eax
                            mov     edi, [vuosi_num]
                            call    vuosi_luvuksi               ;käsitellään vuosi
                            add     ebx, eax
;loppuvaihe
                            mov     edi, ebx                    ;lasketaan lopullinen luku (0...6) summasta
                            mov     esi, 7
                            call    modulo
                            mov     ebx, eax                    ;kopioidaan osoitteen laskemista varten
                            mov     rdi, lopputeksti
                            mov     esi, lopputeksti_pituus
                            call    tulosta
                            lea     rax, [viikonpaivat + 8 * ebx]
                            mov     rdi, [rax]
                            lea     rax, [N_viikonpaivat + ebx]
                            movzx   esi, byte [rax]
                            call    tulosta
.lopetus:                   mov     edi, loppu_hyvin
                            mov     eax, lopetus
                            syscall
.paiva_virhe:               mov     rdi, virhe_paiva
                            mov     esi, virhe_paiva_pituus
                            call    tulosta
                            jmp     .lopetus
.kuukausi_virhe:            mov     rdi, virhe_kuukausi
                            mov     esi, virhe_kuukausi_pituus
                            call    tulosta
                            jmp     .lopetus
.vuosi_virhe:               mov     rdi, virhe_vuosi
                            mov     esi, virhe_vuosi_pituus
                            call    tulosta
                            jmp     .lopetus
.paivamaara_virhe:          mov     rdi, paivamaara_virhe
                            mov     esi, paivamaara_virhe_pituus
                            call    tulosta
                            jmp     .lopetus
;----------------------------------------------------------------------------
;vastaa: void tulosta(const char *, size_t)
;in: RDI: tekstin osoite
;in: RSI: tekstin pituus
tulosta:                    mov     edx, esi
                            mov     rsi, rdi
                            mov     edi, stdout
                            mov     eax, laitetulostus
                            syscall
                            ret
;----------------------------------------------------------------------------
;vastaa: void ssize_t lue(char *, size_t *)
;lukee merkit rivinvaihtoon asti. hylkää merkkejä, jos loput merkit ei mahdu annettuun muistiosoitteeseen.
;in, out: RDI: puskurin osoite
;in     : RSI: puskurin pituus
;out    : RAX: merkkien määrä, 0, 1, 2, ... tai RAX < 0 (virhe)
;         Rivinvaihtoa ei lasketa merkkeihin.
lue:                        push    rbp
                            mov     rbp, rsp
                            sub     rsp, 64                     ;varataan pinosta väliaikaismuistia
                            push    rbx
                            push    r12
                            mov     r12, rdi                    ;R12: kopio merkkipuskurin osoitteesta
                            mov     edx, esi                    ;luettava merkkimäärä
                            mov     rsi, rdi                    ;osoite merkkipuskuriin
                            mov     edi, stdin
                            mov     eax, laitelukeminen
                            syscall
                            mov     ebx, eax                    ;RBX: kopio luetusta merkkimäärästä
                            cmp     eax, 1
                            jl      .loppu                      ;virhetilanne (RAX < 0, RAX == 0)
                            cmp     byte [r12 + rax - 1], RIVINVAIHTO
                            je      .rivinvaihto
;annettu merkkejä yli merkkipuskurin koon. tehdään tyhjennystä pinosta varattuun puskuriin.
                            lea     rax, [rbp - 64]
                            mov     r12, rax
.tyhjennys:                 mov     edx, 64                     ;luettava merkkimäärä
                            mov     rsi, r12                    ;osoite merkkipuskuriin
                            mov     edi, stdin
                            mov     eax, laitelukeminen
                            syscall
                            cmp     eax, 1
                            jl      .loppu                      ;virhetilanne (RAX < 0, RAX == 0)
                            cmp     byte [r12 + rax - 1], RIVINVAIHTO
                            jne     .tyhjennys
                            mov     eax, ebx                    ;palautetaan alunperin luettu merkkimäärä
                            jmp     .loppu
.rivinvaihto:               dec     eax                         ;jätetään rivinvaihto pois lukumäärästä
.loppu:                     pop     r12
                            pop     rbx
                            leave
                            ret
;----------------------------------------------------------------------------
;muuntaa asciina esitetyn luvun binääriluvuksi
;in  : RDI : ascii numeroiden taulukko
;in  : RSI : ascii numeroiden lukumäärä (tavuja)
;out : RDX : lukuarvon osoite
;out : RAX : 0 = OK, -1 = virhe
%ifdef ASC_NUM_1
muunna_asc_num:             push    rbx
                            push    r11
                            push    r12
                            mov     r11, rdx                    ;kopio luvun osoitteesta
                            xor     r12d, r12d                  ;summa eli haluttu binääriluku
                            mov     ecx, 1                      ;ECX = 1, 10, 10², ...
.alku:                      dec     esi
                            lea     rbx, [rdi + rsi]
                            movzx   eax, byte [rbx]
                            cmp     eax, 30h                    ;ascii-lukualueella (30h-39h)?
                            jb      .virhe
                            cmp     eax, 39h
                            ja      .virhe
                            and     eax, 0fh                    ;häivytetään '3'
                            mul     ecx                         ;EAX = xn * 10^n, n = 0, 1, 2, ... edx:eax = eax*reg
                            add     r12d, eax                   ;kertyvä summa
                            cmp     esi, 0
                            je      .OK
                            mov     eax, 10
                            mul     ecx
                            mov     ecx, eax                    ;10:n potenssi kasvoi
                            jmp     .alku
.OK:                        xor     eax, eax
                            mov     [r11], r12d                 ;lopputulos muistiin
                            jmp     .loppu
.virhe:                     mov     rdi, virhe_ei_luku
                            mov     esi, virhe_ei_luku_pituus
                            call    tulosta
                            mov     eax, -1
.loppu:                     pop     r12
                            pop     r11
                            pop     rbx
                            ret
%else   ;Hornerin metodi
muunna_asc_num:             push    r11
                            push    rbx
                            push    rcx
                            push    rdx
                            mov     r11, rdx                    ;kopio tulosluvun osoitteesta
                            lea     rsi, [rdi + rsi]            ;loppuosoite
                            mov     ebx, 10
                            mov     eax, -1                     ;summa
                            cmp     rdi, rsi
                            je      .tyhja_mjono
                            movzx   eax, byte [rdi]
                            cmp     eax, 30h                    ;ascii-lukualueella (30h-39h)?
                            jb      .virhe
                            cmp     eax, 39h
                            ja      .virhe
                            and     eax, 0fh                    ;häivytetään '3'
.alku:                      inc     rdi
                            cmp     rdi, rsi
                            je      .loppu
                            movzx   ecx, byte [rdi]
                            cmp     ecx, 30h                    ;ascii-lukualueella (30h-39h)?
                            jb      .virhe
                            cmp     ecx, 39h
                            ja      .virhe
                            and     ecx, 0fh                    ;häivytetään '3'
                            mul     ebx                         ;summa*10
                            add     eax, ecx                    ;summa*10 + 0...9
                            jmp     .alku
.virhe:                     mov     rdi, virhe_ei_luku
                            mov     esi, virhe_ei_luku_pituus
                            call    tulosta
                            mov     eax, -1
                            pop     rdx
                            pop     rcx
                            pop     rbx
                            pop     r11
                            ret
.loppu:                     mov     [r11], eax
                            xor     eax, eax
.tyhja_mjono:               pop     rdx
                            pop     rcx
                            pop     rbx
                            pop     r11
                            ret
%endif
;----------------------------------------------------------------------------
;muuntaa binääriluvun ascii-esitykseksi (ascii-luvuiksi 30h - 39h)
;in  : RDI : lukuarvo
;out : RSI : ascii-merkkitaulukon osoite
;in  : RDX : taulukon koko (tavuina)
;out : RAX : ascii-lukujen määrä, -1 = virhe
muunna_num_asc:             push    rbx
                            push    r12
                            xor     r12d, r12d                  ;luotujen ascii-lukujen kpl-määrä
                            mov     ebx, 10                     ;jakaja
                            mov     rax, rdi                    ;RAX = jaettava, alaosa
                            mov     ecx, edx                    ;RCX = taulukon koko
                            cmp     ecx, 0                      ;nollan kokoinen taulukko?
                            je      .virhe
                            dec     ecx
.jaa:                       xor     edx, edx                    ;RDX = 0 jaettavan yläosa
;RDX:RAX, jakojäännös : osamäärä
                            div     rbx
                            or      edx, 30h                    ;lisätään '3'
                            mov     [rsi + rcx], dl             ;täytetään merkkipuskuria lopusta päin
;ylikirjoitustarkistus
                            cmp     rax, 0
                            jne     .jaettavaa
                            jmp     .yli
.jaettavaa:                 cmp     ecx, 0                      ;taulukon 1. alkio? Jaettavaa jäljellä. Ei mahdu.
                            je      .virhe
.yli:                       dec     ecx                         ;siitymä alkua kohti
                            inc     r12d                        ;ascii-merkkien lukumäärä kasvaa
                            cmp     rax, 0
                            jne     .jaa
                            mov     eax, r12d
                            jmp     .loppu
.virhe:                     mov     eax, -1
.loppu:                     pop     r12
                            pop     rbx
                            ret
;----------------------------------------------------------------------------
;in  : RDI : päivä (numeerinen)
;out : RAX : 0 = OK, -1 = virhe
tarkista_paiva:             cmp     edi, 1
                            jb      .virhe
                            cmp     edi, 31
                            ja      .virhe
                            xor     eax, eax
                            ret
.virhe:                     mov     eax, -1
                            ret
;----------------------------------------------------------------------------
;in  : RDI : kuukausi (numeerinen)
;out : RAX : 0 = OK, -1 = virhe
tarkista_kuukausi:          cmp     edi, 1
                            jb      .virhe
                            cmp     edi, 12
                            ja      .virhe
                            xor     eax, eax
                            ret
.virhe:                     mov     eax, -1
                            ret
;----------------------------------------------------------------------------
;in  : RDI : vuosi (numeerinen)
;out : RAX : 0 = OK, -1 = virhe
tarkista_vuosi:             cmp     edi, ALIN_VUOSI
                            jb      .virhe
                            cmp     edi, YLIN_VUOSI
                            ja      .virhe
                            xor     eax, eax
                            ret
.virhe:                     mov     eax, -1
                            ret
;----------------------------------------------------------------------------
;in : RDI : vuosi (numeerinen)
;out: RAX = 1, jos karkausvuosi, muutoin RAX = 0
tutki_karkausvuosi:         push    rdx
                            push    rbx
                            xor     edx, edx                    ;jaettavan yläosa = 0
                            mov     eax, edi                    ;jaettava (vuosi)
                            mov     ebx, 100
                            div     ebx
                            cmp     edx, 0                      ;tasa vuosisata?
                            je      .vuosisata                  ;mahdollinen karkausvuosi
                            test    edx, 03h                    ;normivuosi. vuoden loppuosa
                            jz      .karkaus
                            xor     eax, eax
                            jmp     .loppu
.vuosisata:                 test    eax, 03h                    ;vuosisatojen osuus
                            jz      .karkaus
                            xor     eax, eax
                            jmp     .loppu
.karkaus:                   mov     eax, 1
.loppu:                     pop     rbx
                            pop     rdx
                            ret
;----------------------------------------------------------------------------
;tarkistaa päivä-kuukausi -yhdistelmän
;in : RDI : päivä
;in : RSI : kuukausi
;in : RDX : karkausvuosi (1) tai ei karkausvuosi (0)
;out: RAX = -1, jos päivämäärä ei kelpaa, muutoin RAX = 0
tarkista_paivamaara:        dec     esi                         ; 0 = tammikuu, ...
                            lea     rax, [kuukausien_pituudet + rsi]
                            movzx   eax, byte [rax]
                            cmp     edx, 1                      ;karkausvuosi?
                            jne     .ei_karkausvuosi
                            cmp     esi, 1                      ;karkausvuosi. helmikuu?
                            jne     .muu_kuukausi
                            inc     eax                         ;28 + 1
.muu_kuukausi:
.ei_karkausvuosi:           cmp     edi, eax
                            ja      .virhe
                            xor     eax, eax
                            ret
.virhe:                     mov     eax, -1
                            ret
;----------------------------------------------------------------------------
;laskee jakojäännöksen
;in : RDI : jaettava
;in : RSI : jakaja
;out: RAX : jakojäännös
modulo:                     push    rdx
                            mov     eax, edi
                            xor     edx, edx
                            div     esi                         ;-> EDX: jakojäännös
                            mov     eax, edx
                            pop     rdx
                            ret
;----------------------------------------------------------------------------
;hakee taulukoidun apuluvun kuukauden perusteella
;in : RDI : kuukausi (1...12)
;in : RSI : karkausvuosi (0 tai 1)
;out: RAX : luku
hae_kk_luku:                dec     edi
                            cmp     esi, 1                      ;onko karkausvuosi?
                            jne     .muu_vuosi
                            cmp     edi, 0                      ;karkausvuosi. tammikuu?
                            je      .tammikuu
                            cmp     edi, 1                      ;karkausvuosi. helmikuu?
                            jne     .muu_vuosi
                            mov     eax, 2
                            ret
.tammikuu:                  mov     eax, 6
                            ret
.muu_vuosi:                 lea     rax, [kuukausiluvut + rdi]
                            movzx   eax, byte [rax]
                            ret
;----------------------------------------------------------------------------
;hakee taulukoidun apuluvun vuosisadan perusteella. 4 luvun sykli.
;in : RDI : vuosisadan kerroin
;out: RAX : luku
hae_vuosisataluku:          and     edi, 03h                    ;4:n jakojäännös
                            lea     rax, [vuosisataluvut + rdi]
                            movzx   eax, byte [rax]
                            ret
;----------------------------------------------------------------------------
;hakee taulukoidun apuluvun vuoden kahden viimeisen numeron perusteella.
;28 luvun sykli
;in : RDI : vuosi kahdella numerolla
;out: RAX : luku
hae_vuosien_luku:           mov     esi, 28
                            call    modulo
                            lea     rax, [vuosien_luvut + rax]
                            movzx   eax, byte [rax]
                            ret
;----------------------------------------------------------------------------
;hakee taulukoista apuluvun vuosiluvun perusteella
;in:  RDI : vuosi
;out: RAX : luku (summa kahdesta muusta luvusta)
vuosi_luvuksi:              mov     eax, edi                    ;jaettavan alaosa = EAX
                            xor     edx, edx                    ;jaettavan yläosa EDX = 0
                            mov     ecx, 100
                            div     ecx
                            mov     ecx, edx                    ;RCX = 2-numeroinen vuosiluvun loppu
                            mov     edi, eax                    ;vuosisadat parametriksi
                            call    hae_vuosisataluku
                            mov     r8d, eax                    ;luku talteen
                            mov     edi, ecx                    ;vuosiluvun loppuosa parametriksi
                            call    hae_vuosien_luku
                            add     eax, r8d                    ;apulukujen summa ulos
                            ret

