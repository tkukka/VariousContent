/** \file KingsPathApp.h
    Sovellusluokan esittely.
*/

#ifndef KINGSPATHAPP_H
#define KINGSPATHAPP_H

#include <fstream>
#include <string>

#include "Board.h"

/**
 * Yksinkertainen sovellusluokka kuninkaan polun selvittämiseksi.
 */
class KingsPathApp {
public:
    KingsPathApp();
    ~KingsPathApp();

    static void Usage(const char* str);
    int ProcessCmdLine(int argc, char** argv);
    int ReadBoard();
    void PrintBoard() const;
    void SearchPath();

private:
    /**
     * Komentoriviparametrien lukumäärä.
     */
    //static const int PARAMETER_COUNT = 4;

    /**
     * Tulostus, kun ei ole polkua.
     */
    //static const char* OUTPUT_NO_PATH;

    /**
     * Tulostus, kun tiedosto on väärää muotoa.
     */
    //static const char* OUTPUT_INVALID_FORMAT;

    /**
     * Tulostus, kun tapahtuu ajonaikainen virhe.
     */
    //static const char* OUTPUT_RUNTIME_ERR;

    /**
     * Näytölle tulostuksen tilamuuttuja.
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

