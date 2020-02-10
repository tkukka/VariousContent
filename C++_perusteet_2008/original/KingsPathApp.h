/** \file KingsPathApp.h
    Sovellusluokan esittely.
*/

#ifndef KINGSPATHAPP_H
#define KINGSPATHAPP_H

#include <string>
#include <fstream>

#include "Board.h"

/**
  * Yksinkertainen sovellusluokka kuninkaan polun selvitt‰miseksi.
  */
class KingsPathApp
{
public:
   KingsPathApp();
   ~KingsPathApp();

   void Usage(const char *str) const;
   int ProcessCmdLine(int argc, char **argv);
   int ReadBoard(void);
   void PrintBoard(void) const;
   void SearchPath(void);

private:
   /**
    * Komentoriviparametrien lukum‰‰r‰.
    */
   static const int PARAMETER_COUNT = 4;

   /**
    * Tulostus, kun ei ole polkua.
    */
   static const char* OUTPUT_NO_PATH;

   /**
    * Tulostus, kun tiedosto on v‰‰r‰‰ muotoa.
    */
   static const char* OUTPUT_INVALID_FORMAT;
   
   /**
    * Tulostus, kun tapahtuu ajonaikainen virhe.
    */
   static const char* OUTPUT_RUNTIME_ERR;

   /**
    * N‰ytˆlle tulostuksen tilamuuttuja.
    */
   bool display_messages;

   /**
    * Sovelluksen shakkilauta.
    */
   Board board;

   /**
    * Tiedoston nimi, josta lauta luetaan.
    */
   std::string input_file_name;

   /**
    * Tiedosto, josta lauta luetaan.
    */
   std::ifstream input_file;

    /**
    * Tiedosto, johon polku tulostuu.
    */
   std::ofstream output_file;

};

#endif
