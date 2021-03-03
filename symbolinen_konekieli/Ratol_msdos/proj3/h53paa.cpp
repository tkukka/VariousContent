        //RaTol Symbolinen konekieli: Harjoitus 5, tehtävä 3
        //Tero Kukka IY96A

        //Tiedosto: h53paa.cpp
        //Luotu: 25.4.1998

#include <constrea.h>
#include "header.h"

int main(void)
{
   int taulu[100], lkm;

   lkm = Lue(taulu, 100);
   lajittele(taulu, lkm);
   Tulosta(taulu, lkm);

   return 0;
}

