#include <stdlib.h>    /* strtoul */
#include <stdio.h>     /* tulostusfunktio printf() */
#include <ctype.h>     /* isdigit-makro/funktio */
#include <errno.h>     /* systeemikutsujen virhekoodit */
#include <limits.h>    /* lukuesitysten maksimit     */
#include <assert.h>    /* assert-makro/funktio */

#include "ls_input.h"


/*   validate_and_convert_input
 *
 *   Tarkistaa, että \0-terminoitu syöte sisältää vain numeromerkkejä.
 *   Sen jälkeen yrittää muuntaa syötteen 32-bittiseksi 10-järjestelmän
 *   etumerkittömäksi luvuksi (unsigned long). Jos muunnos onnistui,
 *   tarkistaa, että lukuarvo on ohjelmalta vaadittujen rajojen sisällä.
 *   Hyväksytty lukuarvo välitetään kutsujalle.
 *
 *   Parametrit:
 *          input       tarkistettava merkkimuotoinen syöte
 *          number      hyväksyttyä syötettä vastaava lukuarvo
 *
 *   Paluuarvo:
 *          INPUT_PARAM_ERROR  jompikumpi parametri oli NULL
 *          INPUT_ERROR   syötettä ei hyväksytty
 *          INPUT_OK      syöte on OK, 'number' sisältää lukuarvon
 *
 */
int validate_and_convert_input(const char *input, unsigned long *number)
    {
    const char  *origin = input; /* Syötteen alku muunnosta varten */
    char        *conv_endp;  /* Muunnoksen pysäyttäneen merkin osoitin */

    if( input == NULL || number == NULL)
        {  /* Parametrit pielessä, palataan kutsuvaan funktioon */
        return INPUT_PARAM_ERROR;
        }

    /* Käydään koko syöte läpi merkki merkiltä.*/
    while( *input != '\0' )
        {
        if( !( isdigit((int) *input) ) ) /* Merkki ei ole numeromerkki? */
            {
#if defined(__BORLANDC__)   || defined(_MSC_VER) /* Skandit kuntoon
                                                    esikääntäjälipuilla */
            printf("\n\aSytteesi sislsi muita merkkej kuin numeroita. "
                "Ensimminen virheellinen merkki: %c\n", *input);
#else
            printf("\n\aSyötteesi sisälsi muita merkkejä kuin numeroita. "
                "Ensimmäinen virheellinen merkki: %c\n", *input);
#endif
            return INPUT_ERROR;
            }
        input++;
        }

    /* Globaali virhekoodi pitää nollata ennen järjestelmäfunktiota,
     * jotta vanha virhekoodi ei sotkisi virheentarkistusta */
    errno = 0;
    *number = strtoul(origin, &conv_endp, 10);

    /* Muunnosvirhe tapahtui, jos lukuarvoksi tuli ääripään luku ja
       virhekoodi ERANGE on asetettu (Borland ylivuotaa tässä hieman) */
    if ( *number == ULONG_MAX && errno == ERANGE )
        {
        printf("\n\aAntamasi luku oli suurempi kuin %lu. ", ULONG_MAX);
#if defined(__BORLANDC__)  || defined(_MSC_VER)  /* Skandit kuntoon
                                                    esikääntäjälipuilla */
        printf("Luvun on oltava vlilt %lu - %lu.\n", LOWER_LIMIT,
            UPPER_LIMIT);
#else
        printf("Luvun on oltava väliltä %lu - %lu.\n", LOWER_LIMIT,
            UPPER_LIMIT);
#endif
        return INPUT_ERROR;
        }

    assert( conv_endp != origin); /* Muunnos muulla tavalla pielessä?*/

    /* Syöte lukualueen sisällä? */
    if ( *number > UPPER_LIMIT )
        {
#if defined(__BORLANDC__)  || defined(_MSC_VER) /* Skandit kuntoon
                                                   esikääntäjälipuilla */
        printf("\n\aAntamasi luku ei ollut vlilt %lu - %lu.\n",
            LOWER_LIMIT, UPPER_LIMIT);
#else
        printf("\n\aAntamasi luku ei ollut väliltä %lu - %lu.\n",
            LOWER_LIMIT, UPPER_LIMIT);
#endif
        return INPUT_ERROR;
        }

    /* Syöte on kunnossa! */
    printf("Annoit luvun: %lu.\n", *number);
    return INPUT_OK;
    }
