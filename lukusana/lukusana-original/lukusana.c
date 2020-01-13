/*  Oulun yliopisto / Tietojenkäsittelytieteiden laitos
 *  Kurssi: C-ohjelmointi 812316A, lukuvuosi 2004-2005
 *  Kurssin harjoitustyö: "Luvun sanallinen muoto" (koodi 1.05)
 *  Tiedosto: lukusana.c  10.01.2005
 *  Tekijä:   Tero Kukka
 *            Oulun yliopisto / Sähkö- ja tietotekniikan osasto
 *            Tietotekniikan koulutusohjelma 2004
 */

#include <stdlib.h>    /* strtoul, malloc, free -funktiot */
#include <stdio.h>     /* tulostusfunktio printf() */
#include <ctype.h>     /* isdigit-makro/funktio */
#include <errno.h>     /* systeemikutsujen virhekoodit */
#include <limits.h>    /* lukuesitysten maksimit     */
#include <assert.h>    /* assert-makro/funktio */

/* Symboliset esikääntäjävakiot: */
#define LOWER_LIMIT   0ul          /* Pienin luku, jotka hyväksytään */
#define UPPER_LIMIT   10000000ul   /* Suurin luku, jotka hyväksytään */
#define ARG_PROGRAM_NAME  argv[0]  /* Ohjelman komentoriviargumentti */
#define ARG_USER_INPUT    argv[1]  /* Ohjelman komentoriviargumentti */
#define INPUT_OK      0  /* Syötteen tarkastusfunktion paluuarvo */
#define INPUT_ERROR   -1 /* Syötteen tarkastusfunktion paluuarvo */
#define INPUT_PARAM_ERROR  -2 /* Syötteen tarkastusfunktion paluuarvo */

/* Solmun tietotyyppi tulostettavaa tekstiä varten */
typedef struct node
    {
    struct node *next; /* seuraavan solmun osoite */
    const char  *data; /* itse tieto; osoite vakiomerkkijonoon */
    } Node;


/* Linkitetyn pinon tietotyyppi */
typedef struct
    {
    int   count; /* solmujen lukumäärä */
    Node  *top;  /* linkki päällimmäiseen solmuun */
    } Stack;

/*        Tulosteisiin tarvittavat tekstivakiot     */

/*  Ensin lukusanat 0 - 19  valmiiksi määriteltyinä teksteinä.
 *  (Numerot 10 - 19 ovat luonteeltaan epäsäännöllisiä,
 *  joten ne on helpointa määritellä tässä.)
 */

static const char *NUMBERS_0_19[] =
    {
    "nolla",
    "yksi",
    "kaksi",
    "kolme",
#if defined(__BORLANDC__) || defined(_MSC_VER) /* Skandit kuntoon
                                                  esikääntäjälipuilla */
    "nelj„",
#else
    "neljä",
#endif
    "viisi",
    "kuusi",
#if defined(__BORLANDC__) || defined(_MSC_VER)
    "seitsem„n",
#else
    "seitsemän",
#endif
    "kahdeksan",
#if defined(__BORLANDC__) || defined(_MSC_VER)
    "yhdeks„n",
#else
    "yhdeksän",
#endif
    "kymmenen",
    "yksitoista",
    "kaksitoista",
    "kolmetoista",
#if defined(__BORLANDC__) || defined(_MSC_VER)
    "nelj„toista",
#else
    "neljätoista",
#endif
    "viisitoista",
    "kuusitoista",
#if defined(__BORLANDC__) || defined(_MSC_VER)
    "seitsem„ntoista",
#else
    "seitsemäntoista",
#endif
    "kahdeksantoista",
#if defined(__BORLANDC__) || defined(_MSC_VER)
    "yhdeks„ntoista"
#else
    "yhdeksäntoista"
#endif
    };

/* Monikkomuotoinen tekstivakio kymmenille */
#if defined(__BORLANDC__) || defined(_MSC_VER)   /* Skandit kuntoon
                                                    esikääntäjälipuilla */
static const char *TENS = "kymment„";
#else
static const char *TENS = "kymmentä";
#endif

/* Monikkomuotoinen tekstivakio sadoille */
static const char *HUNDREDS = "sataa";

/* Yksikkömuotoinen tekstivakio luvulle 100 */
static const char *ONE_HUNDRED = "sata";

/* Monikkomuotoisten tekstivakioiden taulukko tuhannen
 * eri potensseille. Taulukon indeksi = 1000:n eksponentti
 */
static const char *THOUSANDS_BY_EXP[] =
    {
    " ",        /* blanko, jota ei tulosteta */
    "tuhatta",
    "miljoonaa",
    "miljardia"
    };

/* Yksikkömuotoisten tekstivakioiden taulukko tuhannen
 * eri potensseille. Taulukon indeksi = 1000:n eksponentti
 */
static const char *THOUSAND_BY_EXP[] =
    {
    " ",     /* blanko, jota ei tulosteta */
    "tuhat",
    "miljoona",
    "miljardi"
    };

/* Tulostuksen tekstivakio välilyönnille. */
static const char *SPACE = " ";

/*
 *     Aliohjelmien esittelyt
 *     (Kuvaukset toteutusten yhteydessä)
 */

int validate_and_convert_input(const char *input, unsigned long *number);
const char *pop_from_stack(Stack *stack);
void push_to_stack(Stack *stack, const char *data);
void print_stack(Stack *stack);
Stack *create_stack(void);
void destroy_stack(Stack *stack);
void make_string_presentation(unsigned long number, Stack *stack);


/*
 *         Pääohjelma
 */
int main(int argc, char *argv[])
    {
    Stack *stack = NULL;   /* Ohjelman käyttämä dyn.varattava pino */
    unsigned long number;  /* Käyttäjän antama luku */

    printf("Ohjelma muuttaa annetun luvun sanalliseen muotoon.\n");

    if (argc != 2) /* Ohjelman parametreja tasan kaksi kpl? */
        { /* Parametrien määrä ei ole oikea */
        if (argc > 2)
            {
            printf("\nAnnoit liian monta parametria. ");
            }
#if defined(__BORLANDC__)  || defined(_MSC_VER)  /* Skandit kuntoon
                                                    esikääntäjälipuilla */
        printf("Ohjelman k„ytt”: %s <luku>\n", ARG_PROGRAM_NAME );
        printf("\nLuvun on oltava v„lilt„ %lu - %lu.\n", LOWER_LIMIT,
            UPPER_LIMIT);
#else
        printf("Ohjelman käyttö: %s <luku>\n", ARG_PROGRAM_NAME );
        printf("\nLuvun on oltava väliltä %lu - %lu.\n", LOWER_LIMIT,
            UPPER_LIMIT);
#endif
        return 1;
        }

    /* Tarkista syöte ja muunna se merkkimuodosta kokonaisluvuksi */
    if( validate_and_convert_input(ARG_USER_INPUT, &number ) )
        {  /* Jokin virhe tapahtui, ohjelman suoritus lopetetaan */
        return 1;
        }
    /* Luodaan pino, muunnetaan luku sanalliseen muotoon ja
       tulostetaan esitys pinosta */
    stack = create_stack();
    if(stack != NULL)
        {
        make_string_presentation(number, stack);
        print_stack(stack);
        /* Vapautetaan pinon muisti ja lopetetaan ohjelma */
        destroy_stack(stack);
        stack = NULL;
        printf("\n");
        return 0;  /* Ohjelma suoritettu onnistuneesti */
        }
    else
        {  /* Muisti loppui(?), ohjelman suoritus lopetetaan */
        return 1;
        }
    }

/*
 *        Aliohjelmien toteutukset
 */

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
    while( *input != 0 )
        {
        if( !( isdigit((int) *input) ) ) /* Merkki ei ole numeromerkki? */
            {
#if defined(__BORLANDC__)   || defined(_MSC_VER) /* Skandit kuntoon
                                                    esikääntäjälipuilla */
            printf("\n\aSy”tteesi sis„lsi muita merkkej„ kuin numeroita. "
                "Ensimm„inen virheellinen merkki: %c\n", *input);
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
        printf("Luvun on oltava v„lilt„ %lu - %lu.\n", LOWER_LIMIT,
            UPPER_LIMIT);
#else
        printf("Luvun on oltava väliltä %lu - %lu.\n", LOWER_LIMIT,
            UPPER_LIMIT);
#endif
        return INPUT_ERROR;
        }

    assert( conv_endp != origin); /* Muunnos muulla tavalla pielessä?*/

    /* Syöte lukualueen sisällä? */
    if ( *number < LOWER_LIMIT || *number > UPPER_LIMIT )
        {
#if defined(__BORLANDC__)  || defined(_MSC_VER) /* Skandit kuntoon
                                                   esikääntäjälipuilla */
        printf("\n\aAntamasi luku ei ollut v„lilt„ %lu - %lu.\n",
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

/*   pop_from_stack
 *
 *   Poistaa pinosta solmun ja palauttaa sen sisältämän tekstivakion
 *   osoitteen kutsujalle
 *
 *   Parametrit:
 *          stack        osoite pinoon, jolle operaatio tehdään
 *
 *   Paluuarvo:
 *          osoite tekstivakioon tai NULL, jos
 *          pino oli tyhjä
 */
const char *pop_from_stack(Stack *stack)
    {
    const char    *node_data; /* Solmun datan palauttamiseen tarvittava
                                 lyhytaikainen säilö */
    Node          *ptr;  /* Poistettavan solmun osoitin */

    assert(stack != NULL); /* Validi pinon osoitin? */
    if(stack->count == 0)
      { /* Pino on tyhjä, joten kutsuja saa NULL:in */
      return NULL;
      }
    /* Otetaan käsittelyyn pinon päällimmäinen solmu */
    ptr = stack->top;
    assert(ptr != NULL); /* Tarkista onko pino sekaisin */
    stack->top = ptr->next;  /* Linkitä ohi poistettavan solmun */
    node_data = ptr->data; /* Kopiointi return:ia varten */
    free(ptr);  /* Solmun viemän muistin vapautus */
    stack->count--;
    return node_data;
    }

/*   push_to_stack
 *
 *   Pistää pinoon osoitteen tekstivakioon.
 *
 *   Parametrit:
 *          stack        osoite pinoon, jolle operaatio tehdään
 *          data         tekstivakion osoite
 *
 *   Paluuarvo:
 *          Ei mitään
 *
 */
void push_to_stack(Stack *stack, const char *data)
    {
    Node  *new_node = NULL;

    assert(stack != NULL); /* Validi pinon osoitin? */
    /* Luodaan uusi solmu, alustetaan solmun tiedot ja
       asetetaan se sitten pinoon päällimmäiseksi */
    new_node = (Node *) malloc( sizeof(Node) );
    assert(new_node != NULL); /* Muistinvaraus OK? */
    new_node->next = stack->top;
    new_node->data = data;
    stack->top = new_node;
    stack->count++;
    }

/*   print_stack
 *
 *   Tulostaa annetusta pinosta kaiken datan/tekstin peräkkäin.
 *   Lopussa pino on tyhjä.
 *
 *   Parametrit:
 *          stack        osoite pinoon, jonka sisältö tulostetaan
 *
 *   Paluuarvo:
 *          Ei mitään
 *
 */
void print_stack(Stack *stack)
    {
    const char  *data;  /* Kulloinkin käsiteltävän solmun data */

    assert(stack != NULL); /* Validi pinon osoitin? */
    printf("Antamasi luku sanallisessa muodossa: ");
    data = pop_from_stack(stack);
    while ( data != NULL) /* Käy läpi solmuja kunnes NULL ilmoittaa lopun */
        {
        printf("%s", data);
        data = pop_from_stack(stack);
        }
    }

/*   create_stack
 *
 *   Luo pinon ja alustaa sen valmiiksi.
 *
 *   Parametrit:
 *          Ei mitään
 *
 *   Paluuarvo:
 *          Osoite luotuun pinoon
 *
 */
Stack *create_stack(void)
    {
    Stack   *stack = NULL;
    /* Varataan muisti ja alustetaan pino */
    stack = (Stack *) malloc( sizeof(Stack) );
    if(stack != NULL)
        {
        stack->count = 0;
        stack->top = NULL;
        }
    return stack;
    }

/*   destroy_stack
 *
 *   Tuhoaa pinon. Pinon on oltava tyhjä.
 *
 *   Parametrit:
 *          stack       pino, joka tuhotaan
 *
 *   Paluuarvo:
 *          Ei mitään
 *
 */
void destroy_stack(Stack *stack)
    {
    assert(stack != NULL); /* Validi pinon osoitin? */
    assert(stack->count == 0); /* Pinon oltava tyhjä */
    if(stack)
        {
        free(stack);
        }
    }

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
void make_string_presentation(unsigned long number, Stack *stack)
    {
    assert(stack != NULL); /* Validi pinon osoitin? */

    if (number == 0 )  /* Nollan muunnos on erikoistapaus */
        {
        push_to_stack(stack, NUMBERS_0_19[0]);
        }
    else  /* Nollaa suurempien lukujen muunnos */
        {
        int t = 0; /* Tuhatluvun eksponentti / ryhmälaskuri */

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
                    push_to_stack(stack, SPACE);
                    assert(t <= 3); /* Varmistusta. Toteutus riittää
                                     * miljardeihin asti eli
                                     * maksimi kertaluokka on 1000^3
                                     */

                    if (group_val == 1)
                        { /* Tuhatluvun kerroin on yksi.
                           * Teksti: "tuhat", "miljoona", "miljardi"
                           */
                        push_to_stack(stack, THOUSAND_BY_EXP[t]);
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

            number /= 1000; /* Siirrytään seuraan 3 numeron ryhmään, siis
                             * seuraavaan tuhatluvun eksponenttiin */
            t++;            /* Tuhansien eksponentti kasvaa */
            }  /* while (number != 0) */
        } /* else number != 0*/
    }

/* Tiedoston loppu */



