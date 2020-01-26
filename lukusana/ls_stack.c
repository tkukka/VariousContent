#include <stdlib.h>    /* malloc, free -funktiot */
#include <stdio.h>     /* tulostusfunktio printf() */
#include <assert.h>    /* assert-makro/funktio */

#include "ls_stack.h"





#ifdef LS_STACK_ARRAY /* Osoitintaulukko */

typedef struct
    {
    int   count; /* alkioiden lukumäärä pinossa */
#if defined(DEBUG) && defined(LS_STACK_USAGE)
    int   used_count;  /* tilasto: pinon täyttöaste  */
#endif
    NodeDataType *stack_data; /* osoite pinon data-alueelle */
    } Stack;


#define ARRAY_MAX 25

static NodeDataType stack_arr[ARRAY_MAX];

static Stack my_stack = {
                        .count = 0,
#if defined(DEBUG) && defined(LS_STACK_USAGE)
                        .used_count = 0,
#endif
                        .stack_data = stack_arr
                        };

#else   /* Linkitetty lista */

/* Solmun tietotyyppi tulostettavaa tekstiä varten */
typedef struct node
    {
    struct node *next; /* seuraavan solmun osoite */
    NodeDataType data;
    } Node;

/* Linkitetyn pinon tietotyyppi */
typedef struct
    {
    int   count; /* solmujen lukumäärä pinossa */
#if defined(DEBUG) && defined(LS_STACK_USAGE)
    int   used_count;  /* tilasto: pinon täyttöaste  */
#endif
    Node  *top;  /* linkki päällimmäiseen solmuun */
    } Stack;


static Stack my_stack;
#endif

#if defined(DEBUG)
static int stack_initialized = 0;
#endif

/*   pop_from_stack
 *
 *   Poistaa pinosta solmun ja palauttaa sen sisältämän tekstivakion
 *   osoitteen kutsujalle
 *
 *   Parametrit:
 *          Ei mitään
 *
 *   Paluuarvo:
 *          osoite tekstivakioon tai NULL, jos
 *          pino oli tyhjä
 */
#ifdef LS_STACK_ARRAY
NodeDataType pop_from_stack(void)
    {
#if defined(DEBUG)
    assert(stack_initialized);
#endif

    if(my_stack.count == 0)
      { /* Pino on tyhjä, joten kutsuja saa NULL:in */
      return NULL;
      }
    my_stack.count--;

    return my_stack.stack_data[my_stack.count];
    }

#else /* Linkitetty lista */

NodeDataType pop_from_stack(void)
    {
    NodeDataType  node_data; /* Solmun datan palauttamiseen tarvittava
                                 lyhytaikainen säilö */
    Node          *ptr;  /* Poistettavan solmun osoitin */
#if defined(DEBUG)
    assert(stack_initialized);
#endif
    if(my_stack.count == 0)
      { /* Pino on tyhjä, joten kutsuja saa NULL:in */
      return NULL;
      }
    /* Otetaan käsittelyyn pinon päällimmäinen solmu */
    ptr = my_stack.top;
    assert(ptr != NULL); /* Tarkista onko pino sekaisin */
    my_stack.top = ptr->next;  /* Linkitä ohi poistettavan solmun */
    node_data = ptr->data; /* Kopiointi return:ia varten */
    free((void*)ptr);  /* Solmun viemän muistin vapautus */
    my_stack.count--;
    return node_data;
    }
#endif

/*   push_to_stack
 *
 *   Pistää pinoon osoitteen tekstivakioon.
 *
 *   Parametrit:
 *          data         teksti
 *
 *   Paluuarvo:
 *          0            pinoon lisääminen epäonnistui
 *          1            pinoon lisääminen onnistui
 */
#ifdef LS_STACK_ARRAY
int push_to_stack(NodeDataType data)
    {
#if defined(DEBUG)
    assert(stack_initialized);
#endif

    if (my_stack.count < ARRAY_MAX)
        {
        my_stack.stack_data[my_stack.count] = data;
        my_stack.count++;

#if defined(DEBUG) && defined(LS_STACK_USAGE)
        if (my_stack.count > my_stack.used_count)
            {
            my_stack.used_count = my_stack.count;
            }
#endif
        return 1;
        }

    return 0;
    }

#else /* Linkitetty lista pinona */

int push_to_stack(NodeDataType data)
    {
    Node  *new_node = NULL;
#if defined(DEBUG)
    assert(stack_initialized);
#endif

    /* Luodaan uusi solmu, alustetaan solmun tiedot ja
       asetetaan se sitten pinoon päällimmäiseksi */
    new_node = (Node *) malloc( sizeof(Node) );
    assert(new_node != NULL); /* Muistinvaraus OK? */
    if (new_node)
        {
        new_node->next = my_stack.top;
        new_node->data = data;
        my_stack.top = new_node;
        my_stack.count++;
#if defined(DEBUG) && defined(LS_STACK_USAGE)
        if (my_stack.count > my_stack.used_count)
            {
            my_stack.used_count = my_stack.count;
            }
#endif
        return 1;
        }
    return 0;
    }
#endif

/*   print_stack
 *
 *   Tulostaa pinosta kaiken datan/tekstin peräkkäin.
 *
 *
 *   Parametrit:
 *          Ei mitään
 *
 *   Paluuarvo:
 *          Ei mitään
 *
 */
#ifdef LS_STACK_ARRAY
void print_stack(void)
    {
#if defined(DEBUG)
    assert(stack_initialized);
#endif

    for(int i = (my_stack.count - 1); i >= 0; --i)
        {
        printf("%s", my_stack.stack_data[i]);
        }
    }

#else

void print_stack(void)
    {
#if defined(DEBUG)
    assert(stack_initialized);
#endif

    for(const Node *ptr = my_stack.top; ptr != NULL; ptr = ptr->next)
        {
        printf("%s", ptr->data);
        }
    }
#endif
/*   get_stack_size
 *
 *   Palauttaa pinon tallennettujen solmujen lukumäärän.
 *
 *   Parametrit:
 *          Ei mitään
 *
 *   Paluuarvo:
 *          solmujen lukumäärä
 *
 */
int get_stack_size(void)
    {
#if defined(DEBUG)
    assert(stack_initialized);
#endif
    return my_stack.count;
    }

/*   clear_stack
 *
 *   Tyhjentää pinon solmuista.
 *
 *   Parametrit:
 *          Ei mitään
 *
 *   Paluuarvo:
 *          Ei mitään
 *
 */
void clear_stack(void)
    {
    NodeDataType data;  /* Kulloinkin käsiteltävän solmun data */
    
    data = pop_from_stack();
    while ( data != NULL) /* Käy läpi solmuja kunnes NULL ilmoittaa lopun */
        {
        data = pop_from_stack();
        }
    }

/*   init_stack
 *
 *   Alustaa pinon valmiiksi.
 *
 *   Parametrit:
 *          Ei mitään
 *
 *   Paluuarvo:
 *          Ei mitään
 *
 */
void init_stack(void)
    {
    my_stack.count = 0;
#if defined(DEBUG) && defined(LS_STACK_USAGE)
    my_stack.used_count = 0;
#endif

#ifndef LS_STACK_ARRAY
    my_stack.top = NULL;
#endif

#if defined(DEBUG)
    stack_initialized = 1;
#endif
    }

/*   close_stack
 *
 *   Sulkee pinon. Pinon on oltava tyhjä.
 *
 *   Parametrit:
 *          Ei mitään
 *
 *   Paluuarvo:
 *          Ei mitään
 *
 */
void close_stack(void)
    {
    assert(my_stack.count == 0); /* Pinon oltava tyhjä */
#if defined(DEBUG) && defined(LS_STACK_USAGE)
    printf("\nPinossa oli alkioita: %d\n", my_stack.used_count);
#endif
   
    my_stack.count = 0;
#if defined(DEBUG) && defined(LS_STACK_USAGE)
    my_stack.used_count = 0;
#endif

#ifndef LS_STACK_ARRAY
    my_stack.top = NULL;
#endif
    }

