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
 *          Ei mitään
 *
 *   Paluuarvo:
 *          Ei mitään
 *
 */
void print_stack(void)
    {
    NodeDataType data;  /* Kulloinkin käsiteltävän solmun data */
    
    printf("Antamasi luku sanallisessa muodossa: ");
    data = pop_from_stack();
    while ( data != NULL) /* Käy läpi solmuja kunnes NULL ilmoittaa lopun */
        {
        printf("%s", data);
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
#ifdef DEBUG
    my_stack.used_count = 0;
#endif    
    my_stack.top = NULL;
    return &my_stack;
    }

/*   close_stack
 *
 *   Tuhoaa pinon. Pinon on oltava tyhjä.
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
#ifdef DEBUG
    printf("\nPinossa oli solmuja: %d\n", my_stack.used_count);
#endif
   
    my_stack.count = 0;
#ifdef DEBUG
    my_stack.used_count = 0;
#endif        
    my_stack.top = NULL;  
    }
