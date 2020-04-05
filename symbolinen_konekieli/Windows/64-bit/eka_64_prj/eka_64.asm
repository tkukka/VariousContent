                            EXTERN  ExitProcess:proc

                            .DATA

                            .CODE

start                       PROC
                            sub     rsp, 32                         ;varataan pinosta muistia 4*8 tavua
                            sub     rcx, rcx
                            call    ExitProcess
start                       ENDP
                            END
