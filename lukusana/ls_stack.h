#ifndef LS_STACK_H
#define LS_STACK_H


#define LS_STACK_ARRAY

#undef LS_STACK_USAGE

/* solmun tieto; osoite vakiomerkkijonoon */
typedef const char *NodeDataType;

NodeDataType pop_from_stack(void);
int push_to_stack(NodeDataType data);
void print_stack(void);
int get_stack_size(void);
void init_stack(void);
void clear_stack(void);
void close_stack(void);

#endif /* LS_STACK_H */

