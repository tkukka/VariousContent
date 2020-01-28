
#include <iostream>
#include <string>

#include "ls_input.h"
#include "ls_presentation.h"
#include "ls_stack.h"

/*
 *         Pääohjelma
 */
int main(int argc, char* argv[])
{
    using namespace std;
    using namespace LS;
    using LS::InputStatus;
    using LS::Limits;

    string prg{ argv[0] };
    unsigned long number; /* Käyttäjän antama luku */

    cout << "Ohjelma muuttaa annetun luvun sanalliseen muotoon." << endl;

    if(argc != 2) /* Ohjelman parametreja tasan kaksi kpl? */
    {             /* Parametrien määrä ei ole oikea */
        if(argc > 2) {
            cout << "\nAnnoit liian monta parametria. ";
        }

        cout << "Ohjelman käyttö: " << prg << " <luku>" << endl;
        cout << "\nLuvun on oltava väliltä " << Limits::LOWER_LIMIT << " - "
             << Limits::UPPER_LIMIT << "." << endl;

        return 1;
    }

    string argument{ argv[1] };

    /* Tarkista syöte ja muunna se merkkimuodosta kokonaisluvuksi */
    if(LS::InputHandler::validate_and_convert_input(argument, number) !=
        InputStatus::INPUT_OK) { /* Jokin virhe tapahtui, ohjelman suoritus
                                    lopetetaan */
        return 1;
    }

    /* Alustetaan pino, muunnetaan luku sanalliseen muotoon ja
       tulostetaan esitys pinosta */
    FooStack::init_stack();
    make_string_presentation(number);
    cout << "Antamasi luku sanallisessa muodossa: ";
    FooStack::print_stack();
    /* Tyhjätään pino ja lopetetaan ohjelma */
    FooStack::clear_stack();
    FooStack::close_stack();
    cout << endl;
    return 0; /* Ohjelma suoritettu onnistuneesti */
}

/* Tiedoston loppu */
