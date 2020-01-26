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

#undef LS_STACK_USAGE

/* Linkitetyn pinon tietotyyppi */
typedef struct
    {
    int   count; /* solmujen lukumäärä pinossa */
#if defined(DEBUG) && defined(LS_STACK_USAGE)
    int   used_count;  /* tilasto: pinon täyttöaste solmuina */
#endif    
    Node  *top;  /* linkki päällimmäiseen solmuun */
    } Stack;

typedef Stack *StackHandle;

NodeDataType pop_from_stack(void);
int push_to_stack(StackHandle stack, NodeDataType data);
void print_stack(void);
int get_stack_size(void);
StackHandle init_stack(void);
void clear_stack(void);
void close_stack(void);

#endif /* LS_STACK_H */

