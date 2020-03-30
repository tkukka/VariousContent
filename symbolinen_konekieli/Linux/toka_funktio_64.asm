                            BITS    64

                            SECTION .text

                            GLOBAL  pienin:function
; Palauttaa pienimmän luvun annetuista luvuista. 0-kokoiseksi ilmoitettu taulukko -> paluuarvo ei määritelty.
; vastaa: long pienin(const long *, size_t).
; oletukset: long 64-bit ; size_t 64-bit
; in: RDI = long * (taulukon osoite)
; in: RSI = taulukon koko
; out: RAX = pienin luku
pienin:                     cmp     rdi, 0                  ;taulukon osoite null?
                            je      .lopetus
                            cmp     rsi, 1                  ;vähintään 1 luku
                            jnae    .lopetus
                            mov     rax, [rdi]              ;1. luku
                            dec     rsi
                            add     rdi, 8
.silmukka:                  cmp     rsi, 0
                            je      .lopetus
                            cmp     [rdi], rax
                            jge     .ohi                    ;luku >= RAX? ei käy
                            mov     rax, [rdi]
.ohi:                       add     rdi, 8
                            dec     rsi
                            jmp     .silmukka
.lopetus:                   ret

