/*  Oulun yliopisto / Tietojenk�sittelytieteiden laitos
 *  Kurssi: C-ohjelmointi 812316A, lukuvuosi 2004-2005
 *  Kurssin harjoitusty�: "Luvun sanallinen muoto" (koodi 1.05)
 *  Tiedosto: lukusana.c  10.01.2005
 *  Tekij�:   Tero Kukka
 *            Oulun yliopisto / S�hk�- ja tietotekniikan osasto
 *            Tietotekniikan koulutusohjelma 2004
 */

#include <stdlib.h>    /* strtoul, malloc, free -funktiot */
#include <stdio.h>     /* tulostusfunktio printf() */
#include <ctype.h>     /* isdigit-makro/funktio */
#include <errno.h>     /* systeemikutsujen virhekoodit */
#include <limits.h>    /* lukuesitysten maksimit     */
#include <assert.h>    /* assert-makro/funktio */

/* Symboliset esik��nt�j�vakiot: */
#define LOWER_LIMIT   0ul          /* Pienin luku, jotka hyv�ksyt��n */
#define UPPER_LIMIT   10000000ul   /* Suurin luku, jotka hyv�ksyt��n */
#define ARG_PROGRAM_NAME  argv[0]  /* Ohjelman komentoriviargumentti */
#define ARG_USER_INPUT    argv[1]  /* Ohjelman komentoriviargumentti */
#define INPUT_OK      0  /* Sy�tteen tarkastusfunktion paluuarvo */
#define INPUT_ERROR   -1 /* Sy�tteen tarkastusfunktion paluuarvo */
#define INPUT_PARAM_ERROR  -2 /* Sy�tteen tarkastusfunktion paluuarvo */

/* Solmun tietotyyppi tulostettavaa teksti� varten */
typedef struct node
    {
    struct node *next; /* seuraavan solmun osoite */
    const char  *data; /* itse tieto; osoite vakiomerkkijonoon */
    } Node;


/* Linkitetyn pinon tietotyyppi */
typedef struct
    {
    int   count; /* solmujen lukum��r� */
    Node  *top;  /* linkki p��llimm�iseen solmuun */
    } Stack;

/*        Tulosteisiin tarvittavat tekstivakiot     */

/*  Ensin lukusanat 0 - 19  valmiiksi m��riteltyin� tekstein�.
 *  (Numerot 10 - 19 ovat luonteeltaan ep�s��nn�llisi�,
 *  joten ne on helpointa m��ritell� t�ss�.)
 */

static const char *NUMBERS_0_19[] =
    {
    "nolla",
    "yksi",
    "kaksi",
    "kolme",
#if defined(__BORLANDC__) || defined(_MSC_VER) /* Skandit kuntoon
                                                  esik��nt�j�lipuilla */
    "nelj�",
#else
    "nelj�",
#endif
    "viisi",
    "kuusi",
#if defined(__BORLANDC__) || defined(_MSC_VER)
    "seitsem�n",
#else
    "seitsem�n",
#endif
    "kahdeksan",
#if defined(__BORLANDC__) || defined(_MSC_VER)
    "yhdeks�n",
#else
    "yhdeks�n",
#endif
    "kymmenen",
    "yksitoista",
    "kaksitoista",
    "kolmetoista",
#if defined(__BORLANDC__) || defined(_MSC_VER)
    "nelj�toista",
#else
    "nelj�toista",
#endif
    "viisitoista",
    "kuusitoista",
#if defined(__BORLANDC__) || defined(_MSC_VER)
    "seitsem�ntoista",
#else
    "seitsem�ntoista",
#endif
    "kahdeksantoista",
#if defined(__BORLANDC__) || defined(_MSC_VER)
    "yhdeks�ntoista"
#else
    "yhdeks�ntoista"
#endif
    };

/* Monikkomuotoinen tekstivakio kymmenille */
#if defined(__BORLANDC__) || defined(_MSC_VER)   /* Skandit kuntoon
                                                    esik��nt�j�lipuilla */
static const char *TENS = "kymment�";
#else
static const char *TENS = "kymment�";
#endif

/* Monikkomuotoinen tekstivakio sadoille */
static const char *HUNDREDS = "sataa";

/* Yksikk�muotoinen tekstivakio luvulle 100 */
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

/* Yksikk�muotoisten tekstivakioiden taulukko tuhannen
 * eri potensseille. Taulukon indeksi = 1000:n eksponentti
 */
static const char *THOUSAND_BY_EXP[] =
    {
    " ",     /* blanko, jota ei tulosteta */
    "tuhat",
    "miljoona",
    "miljardi"
    };

/* Tulostuksen tekstivakio v�lily�nnille. */
static const char *SPACE = " ";

/*
 *     Aliohjelmien esittelyt
 *     (Kuvaukset toteutusten yhteydess�)
 */

int validate_and_convert_input(const char *input, unsigned long *number);
const char *pop_from_stack(Stack *stack);
void push_to_stack(Stack *stack, const char *data);
void print_stack(Stack *stack);
Stack *create_stack(void);
void destroy_stack(Stack *stack);
void make_string_presentation(unsigned long number, Stack *stack);


/*
 *         P��ohjelma
 */
int main(int argc, char *argv[])
    {
    Stack *stack = NULL;   /* Ohjelman k�ytt�m� dyn.varattava pino */
    unsigned long number;  /* K�ytt�j�n antama luku */

    printf("Ohjelma muuttaa annetun luvun sanalliseen muotoon.\n");

    if (argc != 2) /* Ohjelman parametreja tasan kaksi kpl? */
        { /* Parametrien m��r� ei ole oikea */
        if (argc > 2)
            {
            printf("\nAnnoit liian monta parametria. ");
            }
#if defined(__BORLANDC__)  || defined(_MSC_VER)  /* Skandit kuntoon
                                                    esik��nt�j�lipuilla */
        printf("Ohjelman k�ytt�: %s <luku>\n", ARG_PROGRAM_NAME );
        printf("\nLuvun on oltava v�lilt� %lu - %lu.\n", LOWER_LIMIT,
            UPPER_LIMIT);
#else
        printf("Ohjelman k�ytt�: %s <luku>\n", ARG_PROGRAM_NAME );
        printf("\nLuvun on oltava v�lilt� %lu - %lu.\n", LOWER_LIMIT,
            UPPER_LIMIT);
#endif
        return 1;
        }

    /* Tarkista sy�te ja muunna se merkkimuodosta kokonaisluvuksi */
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
 *   Tarkistaa, ett� \0-terminoitu sy�te sis�lt�� vain numeromerkkej�.
 *   Sen j�lkeen yritt�� muuntaa sy�tteen 32-bittiseksi 10-j�rjestelm�n
 *   etumerkitt�m�ksi luvuksi (unsigned long). Jos muunnos onnistui,
 *   tarkistaa, ett� lukuarvo on ohjelmalta vaadittujen rajojen sis�ll�.
 *   Hyv�ksytty lukuarvo v�litet��n kutsujalle.
 *
 *   Parametrit:
 *          input       tarkistettava merkkimuotoinen sy�te
 *          number      hyv�ksytty� sy�tett� vastaava lukuarvo
 *
 *   Paluuarvo:
 *          INPUT_PARAM_ERROR  jompikumpi parametri oli NULL
 *          INPUT_ERROR   sy�tett� ei hyv�ksytty
 *          INPUT_OK      sy�te on OK, 'number' sis�lt�� lukuarvon
 *
 */
int validate_and_convert_input(const char *input, unsigned long *number)
    {
    const char  *origin = input; /* Sy�tteen alku muunnosta varten */
    char        *conv_endp;  /* Muunnoksen pys�ytt�neen merkin osoitin */

    if( input == NULL || number == NULL)
        {  /* Parametrit pieless�, palataan kutsuvaan funktioon */
        return INPUT_PARAM_ERROR;
        }

    /* K�yd��n koko sy�te l�pi merkki merkilt�.*/
    while( *input != 0 )
        {
        if( !( isdigit((int) *input) ) ) /* Merkki ei ole numeromerkki? */
            {
#if defined(__BORLANDC__)   || defined(_MSC_VER) /* Skandit kuntoon
                                                    esik��nt�j�lipuilla */
            printf("\n\aSy�tteesi sis�lsi muita merkkej� kuin numeroita. "
                "Ensimm�inen virheellinen merkki: %c\n", *input);
#else
            printf("\n\aSy�tteesi sis�lsi muita merkkej� kuin numeroita. "
                "Ensimm�inen virheellinen merkki: %c\n", *input);
#endif
            return INPUT_ERROR;
            }
        input++;
        }

    /* Globaali virhekoodi pit�� nollata ennen j�rjestelm�funktiota,
     * jotta vanha virhekoodi ei sotkisi virheentarkistusta */
    errno = 0;
    *number = strtoul(origin, &conv_endp, 10);

    /* Muunnosvirhe tapahtui, jos lukuarvoksi tuli ��rip��n luku ja
       virhekoodi ERANGE on asetettu (Borland ylivuotaa t�ss� hieman) */
    if ( *number == ULONG_MAX && errno == ERANGE )
        {
        printf("\n\aAntamasi luku oli suurempi kuin %lu. ", ULONG_MAX);
#if defined(__BORLANDC__)  || defined(_MSC_VER)  /* Skandit kuntoon
                                                    esik��nt�j�lipuilla */
        printf("Luvun on oltava v�lilt� %lu - %lu.\n", LOWER_LIMIT,
            UPPER_LIMIT);
#else
        printf("Luvun on oltava v�lilt� %lu - %lu.\n", LOWER_LIMIT,
            UPPER_LIMIT);
#endif
        return INPUT_ERROR;
        }

    assert( conv_endp != origin); /* Muunnos muulla tavalla pieless�?*/

    /* Sy�te lukualueen sis�ll�? */
    if ( *number < LOWER_LIMIT || *number > UPPER_LIMIT )
        {
#if defined(__BORLANDC__)  || defined(_MSC_VER) /* Skandit kuntoon
                                                   esik��nt�j�lipuilla */
        printf("\n\aAntamasi luku ei ollut v�lilt� %lu - %lu.\n",
            LOWER_LIMIT, UPPER_LIMIT);
#else
        printf("\n\aAntamasi luku ei ollut v�lilt� %lu - %lu.\n",
            LOWER_LIMIT, UPPER_LIMIT);
#endif
        return INPUT_ERROR;
        }

    /* Sy�te on kunnossa! */
    printf("Annoit luvun: %lu.\n", *number);
    return INPUT_OK;
    }

/*   pop_from_stack
 *
 *   Poistaa pinosta solmun ja palauttaa sen sis�lt�m�n tekstivakion
 *   osoitteen kutsujalle
 *
 *   Parametrit:
 *          stack        osoite pinoon, jolle operaatio tehd��n
 *
 *   Paluuarvo:
 *          osoite tekstivakioon tai NULL, jos
 *          pino oli tyhj�
 */
const char *pop_from_stack(Stack *stack)
    {
    const char    *node_data; /* Solmun datan palauttamiseen tarvittava
                                 lyhytaikainen s�il� */
    Node          *ptr;  /* Poistettavan solmun osoitin */

    assert(stack != NULL); /* Validi pinon osoitin? */
    if(stack->count == 0)
      { /* Pino on tyhj�, joten kutsuja saa NULL:in */
      return NULL;
      }
    /* Otetaan k�sittelyyn pinon p��llimm�inen solmu */
    ptr = stack->top;
    assert(ptr != NULL); /* Tarkista onko pino sekaisin */
    stack->top = ptr->next;  /* Linkit� ohi poistettavan solmun */
    node_data = ptr->data; /* Kopiointi return:ia varten */
    free(ptr);  /* Solmun viem�n muistin vapautus */
    stack->count--;
    return node_data;
    }

/*   push_to_stack
 *
 *   Pist�� pinoon osoitteen tekstivakioon.
 *
 *   Parametrit:
 *          stack        osoite pinoon, jolle operaatio tehd��n
 *          data         tekstivakion osoite
 *
 *   Paluuarvo:
 *          Ei mit��n
 *
 */
void push_to_stack(Stack *stack, const char *data)
    {
    Node  *new_node = NULL;

    assert(stack != NULL); /* Validi pinon osoitin? */
    /* Luodaan uusi solmu, alustetaan solmun tiedot ja
       asetetaan se sitten pinoon p��llimm�iseksi */
    new_node = (Node *) malloc( sizeof(Node) );
    assert(new_node != NULL); /* Muistinvaraus OK? */
    new_node->next = stack->top;
    new_node->data = data;
    stack->top = new_node;
    stack->count++;
    }

/*   print_stack
 *
 *   Tulostaa annetusta pinosta kaiken datan/tekstin per�kk�in.
 *   Lopussa pino on tyhj�.
 *
 *   Parametrit:
 *          stack        osoite pinoon, jonka sis�lt� tulostetaan
 *
 *   Paluuarvo:
 *          Ei mit��n
 *
 */
void print_stack(Stack *stack)
    {
    const char  *data;  /* Kulloinkin k�sitelt�v�n solmun data */

    assert(stack != NULL); /* Validi pinon osoitin? */
    printf("Antamasi luku sanallisessa muodossa: ");
    data = pop_from_stack(stack);
    while ( data != NULL) /* K�y l�pi solmuja kunnes NULL ilmoittaa lopun */
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
 *          Ei mit��n
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
 *   Tuhoaa pinon. Pinon on oltava tyhj�.
 *
 *   Parametrit:
 *          stack       pino, joka tuhotaan
 *
 *   Paluuarvo:
 *          Ei mit��n
 *
 */
void destroy_stack(Stack *stack)
    {
    assert(stack != NULL); /* Validi pinon osoitin? */
    assert(stack->count == 0); /* Pinon oltava tyhj� */
    if(stack)
        {
        free(stack);
        }
    }

/*   make_string_presentation
 *
 *   Muuntaa annetun luvun sanalliseen esitysmuotoon.
 *   Hy�dynt�� tekstivakioita, jotka pannaan pinoon
 *   my�hemp�� tulostusta varten.
 *
 *   Parametrit:
 *          number       lukuarvo, joka muunnetaan
 *          stack        pino, johon muunnoksen tekstit tallennetaan
 *
 *   Paluuarvo:
 *          Ei mit��n
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
        int t = 0; /* Tuhatluvun eksponentti / ryhm�laskuri */

        /* Silmukassa k�sitell��n annettua lukua 'number' kolmen numeron
         * ryhmiss�. Ryhm�n lukuarvo on 1000:n jakoj��nn�s. Jakoj��nn�ksest�
         * voidaan edelleen poimia alimman tason lukuarvoja, joita vastaava
         * tekstivakio on olemassa. Lopuksi luvusta tiputetaan viimeiset 3
         * numeroa eli se jaetaan 1000:lla. Seuraava 3 numeron ryhm� aloittaa
         * uuden kierroksen ellei k�ytt�j�n antama luku ole k�sitelty.
         * Luku on k�sitelty, kun jako 1000:lla tuottaa viimein nollan.
         */
        while (number != 0)
            {
            /* K�sitelt�v�n numeroryhm�n lukuarvo 0 - 999. Samalla se on
             * tuhansien, miljoonien ja miljardien kerroin. Lukuarvo
             * jaetaan edelleen osiin oikean tekstin l�yt�miseksi
             */
            unsigned long group_val  = number % 1000;

            if (group_val != 0) /* Vain nollasta eroava ryhm�n lukuarvo
                                 * k�sitell��n */
                {
                unsigned long last_2 = group_val % 100;  /* Numeroryhm�n 2
                                                          * viimeist�
                                                          * numeroa
                                                          */

                /* Ensin tuhannet, miljoonat ja miljardit tekstiksi.
                 * Tuhansien eksponentti v�hint��n 1?
                 */
                if (t > 0)
                    {
                    /* Erotetaan edellisen ryhm�n teksti v�lily�nnill� */
                    push_to_stack(stack, SPACE);
                    assert(t <= 3); /* Varmistusta. Toteutus riitt��
                                     * miljardeihin asti eli
                                     * maksimi kertaluokka on 1000^3
                                     */

                    if (group_val == 1)
                        { /* Tuhatluvun kerroin on yksi.
                           * Teksti: "tuhat", "miljoona", "miljardi"
                           */
                        push_to_stack(stack, THOUSAND_BY_EXP[t]);
                        /* Numeroryhm� k�sitelty. Hyp�t��n suoraan luvussa
                         * vasemmalle 3 numeroa, siis
                         * seuraavaan kolmen numeron ryhm��n */
                        number /= 1000;
                        t++; /* My�s 1000:n eksponentti kasvaa */
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

                /* Tutkitaan ryhm�n lukuarvon kahta viimeist� numeroa,
                   ja jaetaan ryhm�t kahteen eri tapaukseen */
                if ( last_2 <= 19 ) /* x00...x19 -loppuiset erikoistapaukset*/
                    {
                    if(last_2 != 0) /* Estet��n "nolla"-teksti */
                        { /* Teksti: "yksi" ... "yhdeks�ntoista" */
                        push_to_stack(stack, NUMBERS_0_19[last_2]);
                        }
                    /* Seuraavana satojen kerroin */
                    group_val /= 100;
                    }
                else /* x20...x99-loppuiset ovat s��nn�llisi�*/
                    {
                    /* K�sitell��n ensin ykk�set.
                     * Tasakympit hyp�t��n yli, jotta ei tulisi
                     *  "nolla" tulostukseen
                     */
                    if (group_val % 10 != 0 )
                        {
                        /* Teksti: "yksi" ... "yhdeks�n" */
                        push_to_stack(stack, NUMBERS_0_19[group_val % 10]);
                        }
                    /* K�sitell��n (monikolliset) kymmenet */
                    group_val /= 10;
                    /* Teksti: "kymment�" */
                    push_to_stack(stack, TENS);
                    /* Kymmenien kerrointeksti "kaksi"..."yhdeks�n" */
                    push_to_stack(stack, NUMBERS_0_19[group_val % 10]);
                    /* Seuraavana satojen kerroin */
                    group_val /= 10;
                     } /* 2 viimeisen numeron k�sittelyn loppu */

                /* Lopuksi k�sitell��n sadat */
                if (group_val == 1) /* Tasan yksi sata? */
                    {  /* Teksti: "sata" */
                    push_to_stack(stack, ONE_HUNDRED);
                    }
                else if (group_val > 1)   /* Muut satalukemat */
                    { /* Teksti: "sataa" */
                    push_to_stack(stack, HUNDREDS);
                    /* Satojen kerrointeksti "kaksi"..."yhdeks�n" */
                    push_to_stack(stack, NUMBERS_0_19[group_val]);
                    }

                } /* if (group_val != 0) */

            number /= 1000; /* Siirryt��n seuraan 3 numeron ryhm��n, siis
                             * seuraavaan tuhatluvun eksponenttiin */
            t++;            /* Tuhansien eksponentti kasvaa */
            }  /* while (number != 0) */
        } /* else number != 0*/
    }

/* Tiedoston loppu */



