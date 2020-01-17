#ifndef LS_INPUT_H
#define LS_INPUT_H


/* Symboliset esikääntäjävakiot: */
#define LOWER_LIMIT   0ul          /* Pienin luku, jotka hyväksytään */
#define UPPER_LIMIT   10000000ul   /* Suurin luku, jotka hyväksytään */
#define INPUT_OK      0  /* Syötteen tarkastusfunktion paluuarvo */
#define INPUT_ERROR   -1 /* Syötteen tarkastusfunktion paluuarvo */
#define INPUT_PARAM_ERROR  -2 /* Syötteen tarkastusfunktion paluuarvo */


int validate_and_convert_input(const char *input, unsigned long *number);


#endif

