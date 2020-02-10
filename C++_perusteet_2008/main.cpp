/** \file main.cpp
    Sovelluksen käynnistävä pääohjelma.
*/

#include "KingsPathApp.h"

/** Pääohjelma.
 *
 */
int main(int argc, char** argv)
{
    int ret = 0; // Rutiinien paluuarvo.

    KingsPathApp app;

    ret = app.ProcessCmdLine(argc, argv);

    // Komentorivi ok?
    if(ret == 0) {
        ret = app.ReadBoard();

        // Laudan lukeminen meni oikein?
        if(ret == 0) {
            app.PrintBoard();
            app.SearchPath();
        }
    }

    return ret;
}

