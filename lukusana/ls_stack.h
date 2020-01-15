#ifndef LS_STACK_H
#define LS_STACK_H

/* solmun tieto; osoite vakiomerkkijonoon */
typedef const char *NodeDataType; 

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
#ifdef DEBUG
    int   used_count;  /* tilasto: pinon täyttöaste solmuina */
#endif    
    Node  *top;  /* linkki päällimmäiseen solmuun */
    } Stack;

typedef Stack *StackHandle;

NodeDataType pop_from_stack(StackHandle stack);
void push_to_stack(StackHandle stack, NodeDataType data);
void print_stack(StackHandle stack);
StackHandle create_stack(void);
void destroy_stack(StackHandle stack);

#endif /* LS_STACK_H */
