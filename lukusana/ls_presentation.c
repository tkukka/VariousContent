#include <stdlib.h>
#include <assert.h>    /* assert-makro/funktio */
#include "ls_presentation.h"


/*        Tulosteisiin tarvittavat tekstivakiot     */

/*  Ensin lukusanat 0 - 19  valmiiksi määriteltyinä teksteinä.
 *  (Numerot 10 - 19 ovat luonteeltaan epäsäännöllisiä,
 *  joten ne on helpointa määritellä tässä.)
 */

static NodeDataType NUMBERS_0_19[] =
    {
    "nolla",
    "yksi",
    "kaksi",
    "kolme",
#if defined(__BORLANDC__) || defined(_MSC_VER) /* Skandit kuntoon
                                                  esikääntäjälipuilla */
    "nelj",
#else
    "neljä",
#endif
    "viisi",
    "kuusi",
#if defined(__BORLANDC__) || defined(_MSC_VER)
    "seitsemn",
#else
    "seitsemän",
#endif
    "kahdeksan",
#if defined(__BORLANDC__) || defined(_MSC_VER)
    "yhdeksn",
#else
    "yhdeksän",
#endif
    "kymmenen",
    "yksitoista",
    "kaksitoista",
    "kolmetoista",
#if defined(__BORLANDC__) || defined(_MSC_VER)
    "neljtoista",
#else
    "neljätoista",
#endif
    "viisitoista",
    "kuusitoista",
#if defined(__BORLANDC__) || defined(_MSC_VER)
    "seitsemntoista",
#else
    "seitsemäntoista",
#endif
    "kahdeksantoista",
#if defined(__BORLANDC__) || defined(_MSC_VER)
    "yhdeksntoista"
#else
    "yhdeksäntoista"
#endif
    };

/* Monikkomuotoinen tekstivakio kymmenille */
#if defined(__BORLANDC__) || defined(_MSC_VER)   /* Skandit kuntoon
                                                    esikääntäjälipuilla */
static NodeDataType TENS = "kymment";
#else
static NodeDataType TENS = "kymmentä";
#endif

/* Monikkomuotoinen tekstivakio sadoille */
static NodeDataType HUNDREDS = "sataa";

/* Yksikkömuotoinen tekstivakio luvulle 100 */
static NodeDataType ONE_HUNDRED = "sata";

/* Monikkomuotoisten tekstivakioiden taulukko tuhannen
 * eri potensseille. Taulukon indeksi = 1000:n eksponentti
 */
static NodeDataType THOUSANDS_BY_EXP[] =
    {
    " ",        /* blanko, jota ei tulosteta */
    "tuhatta",
    "miljoonaa",
    "miljardia"
    };

/* Yksikkömuotoisten tekstivakioiden taulukko tuhannen
 * eri potensseille. Taulukon indeksi = 1000:n eksponentti
 */
static NodeDataType THOUSAND_BY_EXP[] =
    {
    " ",     /* blanko, jota ei tulosteta */
    "tuhat",
    "miljoona",
    "miljardi"
    };

/* Tulostuksen tekstivakio välilyönnille. */
static NodeDataType SPACE = " ";

/*   make_string_presentation
 *
 *   Muuntaa annetun luvun sanalliseen esitysmuotoon.
 *   Hyödyntää tekstivakioita, jotka pannaan pinoon
 *   myöhempää tulostusta varten.
 *
 *   Parametrit:
 *          number       lukuarvo, joka muunnetaan
 *          stack        pino, johon muunnoksen tekstit tallennetaan
 *
 *   Paluuarvo:
 *          Ei mitään
 *
 */
void make_string_presentation(unsigned long number, StackHandle stack)
    {
    assert(stack != NULL); /* Validi pinon osoitin? */

    if (number == 0 )  /* Nollan muunnos on erikoistapaus */
        {
        push_to_stack(stack, NUMBERS_0_19[0]);
        return;
        }

    /* Nollaa suurempien lukujen muunnos */
        {
        unsigned long prev_group_val = 0;
        /* prev_group_val:
         *   hoitaa sananvälin (SPACE) pois lopusta tapauksissa
         *      mmm 000
         *      mmm 000 000
         *      mmm 000 000 000
         *
         *   m > 0
         */
        int t = 0; /* Tuhatluvun eksponentti / ryhmälaskuri */
        int earlier_nonzero_group = 0;
        /* earlier_nonzero_group:
         *   hoitaa sananvälin (SPACE) tapauksissa
         *      mmm 000 zzz
         *      mmm 000 000 zzz
         *      mmm 000 zzz nnn
         *
         *   m, z > 0, n >= 0
         */

        /* Silmukassa käsitellään annettua lukua 'number' kolmen numeron
         * ryhmissä. Ryhmän lukuarvo on 1000:n jakojäännös. Jakojäännöksestä
         * voidaan edelleen poimia alimman tason lukuarvoja, joita vastaava
         * tekstivakio on olemassa. Lopuksi luvusta tiputetaan viimeiset 3
         * numeroa eli se jaetaan 1000:lla. Seuraava 3 numeron ryhmä aloittaa
         * uuden kierroksen ellei käyttäjän antama luku ole käsitelty.
         * Luku on käsitelty, kun jako 1000:lla tuottaa viimein nollan.
         */
        while (number != 0)
            {
            /* Käsiteltävän numeroryhmän lukuarvo 0 - 999. Samalla se on
             * tuhansien, miljoonien ja miljardien kerroin. Lukuarvo
             * jaetaan edelleen osiin oikean tekstin löytämiseksi
             */
            unsigned long group_val  = number % 1000;

            if (group_val != 0) /* Vain nollasta eroava ryhmän lukuarvo
                                 * käsitellään */
                {
                unsigned long last_2 = group_val % 100;  /* Numeroryhmän 2
                                                          * viimeistä
                                                          * numeroa
                                                          */

                /* Ensin tuhannet, miljoonat ja miljardit tekstiksi.
                 * Tuhansien eksponentti vähintään 1?
                 */
                if (t > 0)
                    {
                    /* Erotetaan edellisen ryhmän teksti välilyönnillä */
                    if (prev_group_val || earlier_nonzero_group)
                        {
                        push_to_stack(stack, SPACE);
                        }
                    assert(t <= 3); /* Varmistusta. Toteutus riittää
                                     * miljardeihin asti eli
                                     * maksimi kertaluokka on 1000^3
                                     */

                    if (group_val == 1)
                        { /* Tuhatluvun kerroin on yksi.
                           * Teksti: "tuhat", "miljoona", "miljardi"
                           */
                        push_to_stack(stack, THOUSAND_BY_EXP[t]);
                        prev_group_val = number % 1000;

                        if (prev_group_val)
                            {
                            earlier_nonzero_group = 1;
                            }

                        /* Numeroryhmä käsitelty. Hypätään suoraan luvussa
                         * vasemmalle 3 numeroa, siis
                         * seuraavaan kolmen numeron ryhmään */
                        number /= 1000;
                        t++; /* Myös 1000:n eksponentti kasvaa */
                        continue;
                        }
                    else
                        {
                        /* Tuhatluvun kerroin on 2...999
                         * Teksti: "tuhatta", "miljoonaa", "miljardia"
                         */
                        push_to_stack(stack, THOUSANDS_BY_EXP[t]);
                        }
                    } /* t > 0 */

                /* Tutkitaan ryhmän lukuarvon kahta viimeistä numeroa,
                   ja jaetaan ryhmät kahteen eri tapaukseen */
                if ( last_2 <= 19 ) /* x00...x19 -loppuiset erikoistapaukset*/
                    {
                    if(last_2 != 0) /* Estetään "nolla"-teksti */
                        { /* Teksti: "yksi" ... "yhdeksäntoista" */
                        push_to_stack(stack, NUMBERS_0_19[last_2]);
                        }
                    /* Seuraavana satojen kerroin */
                    group_val /= 100;
                    }
                else /* x20...x99-loppuiset ovat säännöllisiä*/
                    {
                    /* Käsitellään ensin ykköset.
                     * Tasakympit hypätään yli, jotta ei tulisi
                     *  "nolla" tulostukseen
                     */
                    if (group_val % 10 != 0 )
                        {
                        /* Teksti: "yksi" ... "yhdeksän" */
                        push_to_stack(stack, NUMBERS_0_19[group_val % 10]);
                        }
                    /* Käsitellään (monikolliset) kymmenet */
                    group_val /= 10;
                    /* Teksti: "kymmentä" */
                    push_to_stack(stack, TENS);
                    /* Kymmenien kerrointeksti "kaksi"..."yhdeksän" */
                    push_to_stack(stack, NUMBERS_0_19[group_val % 10]);
                    /* Seuraavana satojen kerroin */
                    group_val /= 10;
                     } /* 2 viimeisen numeron käsittelyn loppu */

                /* Lopuksi käsitellään sadat */
                if (group_val == 1) /* Tasan yksi sata? */
                    {  /* Teksti: "sata" */
                    push_to_stack(stack, ONE_HUNDRED);
                    }
                else if (group_val > 1)   /* Muut satalukemat */
                    { /* Teksti: "sataa" */
                    push_to_stack(stack, HUNDREDS);
                    /* Satojen kerrointeksti "kaksi"..."yhdeksän" */
                    push_to_stack(stack, NUMBERS_0_19[group_val]);
                    }

                } /* if (group_val != 0) */

            prev_group_val = number % 1000;

            if (prev_group_val)
                {
                earlier_nonzero_group = 1;
                }

            number /= 1000; /* Siirrytään seuraan 3 numeron ryhmään, siis
                             * seuraavaan tuhatluvun eksponenttiin */
            t++;            /* Tuhansien eksponentti kasvaa */
            }  /* while (number != 0) */
        }
    }

