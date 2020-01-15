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
    int   count; /* solmujen lukumäärä */
    Node  *top;  /* linkki päällimmäiseen solmuun */
    } Stack;


NodeDataType pop_from_stack(Stack *stack);
void push_to_stack(Stack *stack, NodeDataType data);
void print_stack(Stack *stack);
Stack *create_stack(void);
void destroy_stack(Stack *stack);

#endif /* LS_STACK_H */
