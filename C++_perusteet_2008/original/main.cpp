/** \file main.cpp
    Sovelluksen käynnistävä pääohjelma.
*/

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "KingsPathApp.h"


/** Pääohjelma.
 *
 */
int main(int argc, char **argv)
{ 
   int ret = 0; //Rutiinien paluuarvo.

   {//Lohko, jotta _CrtDumpMemoryLeaks() jää ulkopuolelle.
      KingsPathApp app;
     
      ret = app.ProcessCmdLine(argc, argv);
      
      //Komentorivi ok?
      if(ret == 0)
      {
         ret = app.ReadBoard();
         
         //Laudan lukeminen meni oikein?
         if(ret == 0)
         {
            app.PrintBoard();
            app.SearchPath();
         }
      }
   }

   _CrtDumpMemoryLeaks();
   return ret;
}


