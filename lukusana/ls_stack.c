#include <stdlib.h> 
#include <stdio.h>     /* tulostusfunktio printf() */
#include <assert.h>    /* assert-makro/funktio */

#include "ls_stack.h"


static Stack my_stack;


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
NodeDataType pop_from_stack(StackHandle stack)
    {
    NodeDataType  node_data; /* Solmun datan palauttamiseen tarvittava
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
 *          data         teksti
 *
 *   Paluuarvo:
 *          Ei mitään
 *
 */
void push_to_stack(StackHandle stack, NodeDataType data)
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
#ifdef DEBUG
    if (stack->count > my_stack.used_count)
        {
        my_stack.used_count = stack->count;    
        }
#endif      
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
void print_stack(StackHandle stack)
    {
    NodeDataType data;  /* Kulloinkin käsiteltävän solmun data */

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
StackHandle create_stack(void)
    {
    my_stack.count = 0;
#ifdef DEBUG
    my_stack.used_count = 0;
#endif    
    my_stack.top = NULL;    
        
    return &my_stack;
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
void destroy_stack(StackHandle stack)
    {
    assert(stack != NULL); /* Validi pinon osoitin? */
    assert(stack->count == 0); /* Pinon oltava tyhjä */
#ifdef DEBUG
    printf("\nPinossa oli solmuja: %d\n", my_stack.used_count);
#endif
   
    my_stack.count = 0;
#ifdef DEBUG
    my_stack.used_count = 0;
#endif        
    my_stack.top = NULL;  
    }
