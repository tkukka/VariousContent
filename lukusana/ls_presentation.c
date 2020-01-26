#include <stdlib.h>
#include <assert.h>    /* assert-makro/funktio */
#include "ls_presentation.h"


/*        Tulosteisiin tarvittavat tekstivakiot     */

/*  Ensin lukusanat 0 - 19  valmiiksi määriteltyinä teksteinä.
 *  (Numerot 10 - 19 ovat luonteeltaan epäsäännöllisiä,
 *  joten ne on helpointa määritellä tässä.)
 */

static const char NUMBERS_0_19[][17] =
    {
    u8"nolla",
    u8"yksi",
    u8"kaksi",
    u8"kolme",
    u8"neljä",
    u8"viisi",
    u8"kuusi",
    u8"seitsemän",
    u8"kahdeksan",
    u8"yhdeksän",
    u8"kymmenen",
    u8"yksitoista",
    u8"kaksitoista",
    u8"kolmetoista",
    u8"neljätoista",
    u8"viisitoista",
    u8"kuusitoista",
    u8"seitsemäntoista",
    u8"kahdeksantoista",
    u8"yhdeksäntoista"
    };

/* Monikkomuotoinen tekstivakio kymmenille */
static const char TENS[] = u8"kymmentä";

/* Monikkomuotoinen tekstivakio sadoille */
static const char HUNDREDS[] = u8"sataa";

/* Yksikkömuotoinen tekstivakio luvulle 100 */
static const char ONE_HUNDRED[] = u8"sata";

/* Monikkomuotoisten tekstivakioiden taulukko tuhannen
 * eri potensseille. Taulukon indeksi = 1000:n eksponentti
 */
static const char THOUSANDS_BY_EXP[][10] =
    {
    u8" ",        /* blanko, jota ei tulosteta */
    u8"tuhatta",
    u8"miljoonaa",
    u8"miljardia"
    };

/* Yksikkömuotoisten tekstivakioiden taulukko tuhannen
 * eri potensseille. Taulukon indeksi = 1000:n eksponentti
 */
static const char THOUSAND_BY_EXP[][9] =
    {
    u8" ",     /* blanko, jota ei tulosteta */
    u8"tuhat",
    u8"miljoona",
    u8"miljardi"
    };

/* Tulostuksen tekstivakio välilyönnille. */
static const char SPACE[] = u8" ";

/*   make_string_presentation
 *
 *   Muuntaa annetun luvun sanalliseen esitysmuotoon.
 *   Hyödyntää tekstivakioita, jotka pannaan pinoon
 *   myöhempää tulostusta varten.
 *
 *   Parametrit:
 *          number       lukuarvo, joka muunnetaan
 *
 *   Paluuarvo:
 *          Ei mitään
 *
 */
void make_string_presentation(unsigned long number)
    {

    if (number == 0 )  /* Nollan muunnos on erikoistapaus */
        {
        push_to_stack(NUMBERS_0_19[0]);
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
                        push_to_stack(SPACE);
                        }
                    assert(t <= 3); /* Varmistusta. Toteutus riittää
                                     * miljardeihin asti eli
                                     * maksimi kertaluokka on 1000^3
                                     */

                    if (group_val == 1)
                        { /* Tuhatluvun kerroin on yksi.
                           * Teksti: "tuhat", "miljoona", "miljardi"
                           */
                        push_to_stack(THOUSAND_BY_EXP[t]);
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
                        push_to_stack(THOUSANDS_BY_EXP[t]);
                        }
                    } /* t > 0 */

                /* Tutkitaan ryhmän lukuarvon kahta viimeistä numeroa,
                   ja jaetaan ryhmät kahteen eri tapaukseen */
                if ( last_2 <= 19 ) /* x00...x19 -loppuiset erikoistapaukset*/
                    {
                    if(last_2 != 0) /* Estetään "nolla"-teksti */
                        { /* Teksti: "yksi" ... "yhdeksäntoista" */
                        push_to_stack(NUMBERS_0_19[last_2]);
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
                        push_to_stack(NUMBERS_0_19[group_val % 10]);
                        }
                    /* Käsitellään (monikolliset) kymmenet */
                    group_val /= 10;
                    /* Teksti: "kymmentä" */
                    push_to_stack(TENS);
                    /* Kymmenien kerrointeksti "kaksi"..."yhdeksän" */
                    push_to_stack(NUMBERS_0_19[group_val % 10]);
                    /* Seuraavana satojen kerroin */
                    group_val /= 10;
                     } /* 2 viimeisen numeron käsittelyn loppu */

                /* Lopuksi käsitellään sadat */
                if (group_val == 1) /* Tasan yksi sata? */
                    {  /* Teksti: "sata" */
                    push_to_stack(ONE_HUNDRED);
                    }
                else if (group_val > 1)   /* Muut satalukemat */
                    { /* Teksti: "sataa" */
                    push_to_stack(HUNDREDS);
                    /* Satojen kerrointeksti "kaksi"..."yhdeksän" */
                    push_to_stack(NUMBERS_0_19[group_val]);
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

