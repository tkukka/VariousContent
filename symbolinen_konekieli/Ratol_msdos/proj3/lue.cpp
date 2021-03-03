        //RaTol Symbolinen konekieli: Harjoitus 5, tehtävä 3
        //Tero Kukka IY96A

        //Tiedosto: lue.cpp
        //Luotu: 25.4.1998

#include <constrea.h>

int Lue(int *taulukko, int max)
{
   int laskuri = 0, syote;

   cout<<"\nAnna luku (1): ";
   cin>>syote;

   while(syote && (laskuri < max))
   {
     *taulukko = syote;
     laskuri++;
     taulukko++;
     cout<<"\nAnna luku ("<< (laskuri + 1) <<"): ";
     cin>>syote;
   }
   cout<<"\nAnnoit "<<laskuri<<" lukua.";

   return laskuri;
}

