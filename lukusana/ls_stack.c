#include <stdlib.h>    /* malloc, free -funktiot */
#include <stdio.h>     /* tulostusfunktio printf() */
#include <assert.h>    /* assert-makro/funktio */

#include "ls_stack.h"


static Stack my_stack;
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
    free(ptr);  /* Solmun viemän muistin vapautus */
    my_stack.count--;
    return node_data;
    }

/*   push_to_stack
 *
 *   Pistää pinoon osoitteen tekstivakioon.
 *
 *   Parametrit:
 *          stack        osoite pinoon, jolle operaatio tehdään
 *          data         teksti
 *
 *   Paluuarvo:
 *          Ei mitään
 *
 */
void push_to_stack(StackHandle stack, NodeDataType data)
    {
    Node  *new_node = NULL;
#if defined(DEBUG)
    assert(stack_initialized);
#endif    
    assert(stack != NULL); /* Validi pinon osoitin? */
    /* Luodaan uusi solmu, alustetaan solmun tiedot ja
       asetetaan se sitten pinoon päällimmäiseksi */
    new_node = (Node *) malloc( sizeof(Node) );
    assert(new_node != NULL); /* Muistinvaraus OK? */
    new_node->next = stack->top;
    new_node->data = data;
    stack->top = new_node;
    stack->count++;
#if defined(DEBUG) && defined(LS_STACK_USAGE)
    if (stack->count > my_stack.used_count)
        {
        my_stack.used_count = stack->count;    
        }
#endif      
    }

/*   print_stack
 *
 *   Tulostaa annetusta pinosta kaiken datan/tekstin peräkkäin.
 *
 *
 *   Parametrit:
 *          Ei mitään
 *
 *   Paluuarvo:
 *          Ei mitään
 *
 */
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
 *          Osoite pinoon
 *
 */
StackHandle init_stack(void)
    {
    my_stack.count = 0;
#if defined(DEBUG) && defined(LS_STACK_USAGE)
    my_stack.used_count = 0;
#endif    
    my_stack.top = NULL;
#if defined(DEBUG)
    stack_initialized = 1;
#endif
    return &my_stack;
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
    printf("\nPinossa oli solmuja: %d\n", my_stack.used_count);
#endif
   
    my_stack.count = 0;
#if defined(DEBUG) && defined(LS_STACK_USAGE)
    my_stack.used_count = 0;
#endif        
    my_stack.top = NULL;  
    }

