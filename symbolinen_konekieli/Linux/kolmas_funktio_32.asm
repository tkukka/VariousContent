                            BITS    32

                            SECTION .text
                            GLOBAL  pienin:function
; Palauttaa pienimmän luvun annetuista luvuista. 0-kokoiseksi ilmoitettu taulukko, paluuarvo = ei määritelty.
; vastaa: int pienin(const int *, size_t). EAX = pienin luku
; oletukset: int 32-bit ; size_t 32-bit

pienin:                     push    ebp                     ;ABI: säilytettävä rekisteri
                            mov     ebp, esp
                            push    ebx                     ;ABI: säilytettävä rekisteri
                            mov     ebx, [ebp + 8]          ;lukujonon alku
                            mov     ecx, [ebp + 12]         ;lukujen määrä
                            cmp     ebx, 0                  ;null?
                            je      lopetus
                            cmp     ecx, 1
                            jnae    lopetus                 ;vähintään 1 luku
                            mov     eax, [ebx]              ;1. luku
                            dec     ecx
                            add     ebx, 4
.silmukka:                  cmp     ecx, 0
                            je      lopetus
                            cmp     [ebx], eax
                            jge     .ohi                    ;luku >= eax? ei käy
                            mov     eax, [ebx]
.ohi:                       add     ebx, 4
                            dec     ecx
                            jmp     .silmukka
lopetus:                    pop     ebx
                            leave
                            ret

