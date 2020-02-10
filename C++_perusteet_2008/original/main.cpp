/** \file main.cpp
    Sovelluksen k‰ynnist‰v‰ p‰‰ohjelma.
*/

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "KingsPathApp.h"


/** P‰‰ohjelma.
 *
 */
int main(int argc, char **argv)
{ 
   int ret = 0; //Rutiinien paluuarvo.

   {//Lohko, jotta _CrtDumpMemoryLeaks() j‰‰ ulkopuolelle.
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


