        //RaTol Symbolinen konekieli: Harjoitus 5, tehtävä 3
        //Tero Kukka IY96A

        //Tiedosto: tulosta.cpp
        //Luotu: 25.4.1998

#include <constrea.h>

int Tulosta(int *taulukko, int kpl)
{
   for (int ind = 0; ind < kpl; ind++)
   {
      cout<<"\n"<<*taulukko;
      taulukko++;
   }

   return 0;
}

