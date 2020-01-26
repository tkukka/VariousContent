/*  Oulun yliopisto / Tietojenkäsittelytieteiden laitos
 *  Kurssi: C-ohjelmointi 812316A, lukuvuosi 2004-2005
 *  Kurssin harjoitustyö: "Luvun sanallinen muoto" (koodi 1.05)
 *  Tiedosto: lukusana.c  10.01.2005
 *  Tekijä:   Tero Kukka
 *            Oulun yliopisto / Sähkö- ja tietotekniikan osasto
 *            Tietotekniikan koulutusohjelma 2004
 */

#include <stdlib.h>
#include <stdio.h>     /* tulostusfunktio printf() */

#include "ls_input.h"
#include "ls_stack.h"
#include "ls_presentation.h"

/* Symboliset esikääntäjävakiot: */

#define ARG_PROGRAM_NAME  argv[0]  /* Ohjelman komentoriviargumentti */
#define ARG_USER_INPUT    argv[1]  /* Ohjelman komentoriviargumentti */


/*
 *         Pääohjelma
 */
int main(int argc, char *argv[])
    {
    unsigned long number;  /* Käyttäjän antama luku */

    printf("Ohjelma muuttaa annetun luvun sanalliseen muotoon.\n");

    if (argc != 2) /* Ohjelman parametreja tasan kaksi kpl? */
        { /* Parametrien määrä ei ole oikea */
        if (argc > 2)
            {
            printf("\nAnnoit liian monta parametria. ");
            }

        printf("Ohjelman käyttö: %s <luku>\n", ARG_PROGRAM_NAME );
        printf("\nLuvun on oltava väliltä %lu - %lu.\n", LOWER_LIMIT,
            UPPER_LIMIT);

        return EXIT_FAILURE;
        }

    /* Tarkista syöte ja muunna se merkkimuodosta kokonaisluvuksi */
    if( validate_and_convert_input(ARG_USER_INPUT, &number ) )
        {  /* Jokin virhe tapahtui, ohjelman suoritus lopetetaan */
        return EXIT_FAILURE;
        }

    /* Alustetaan pino, muunnetaan luku sanalliseen muotoon ja
       tulostetaan esitys pinosta */
    StackHandle stack = init_stack();
    make_string_presentation(number, stack);
    printf("Antamasi luku sanallisessa muodossa: ");
    print_stack();
    /* Tyhjätään pino ja lopetetaan ohjelma */
    clear_stack();
    close_stack();
    printf("\n");
    return EXIT_SUCCESS;  /* Ohjelma suoritettu onnistuneesti */
    }

/* Tiedoston loppu */

