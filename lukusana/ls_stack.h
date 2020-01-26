#ifndef LS_STACK_H
#define LS_STACK_H


#undef LS_STACK_ARRAY

#undef LS_STACK_USAGE

/* solmun tieto; osoite vakiomerkkijonoon */
typedef const char *NodeDataType;

#ifdef LS_STACK_ARRAY /* Osoitintaulukko */

typedef struct
    {
    int   count; /* alkioiden lukumäärä pinossa */
#if defined(DEBUG) && defined(LS_STACK_USAGE)
    int   used_count;  /* tilasto: pinon täyttöaste  */
#endif
    NodeDataType *stack_data; /* osoite pinon data-alueelle */
    } Stack;

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
#endif

typedef Stack *StackHandle;

NodeDataType pop_from_stack(void);
int push_to_stack(StackHandle stack, NodeDataType data);
void print_stack(void);
int get_stack_size(void);
StackHandle init_stack(void);
void clear_stack(void);
void close_stack(void);

#endif /* LS_STACK_H */

