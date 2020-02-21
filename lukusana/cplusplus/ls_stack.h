#ifndef LS_STACK_H
#define LS_STACK_H

#include <vector>

namespace LS {

/* pinon tieto; osoite vakiomerkkijonoon */
using NodeDataType = const char*;

class FooStack {

public:
    static void init_stack();
    static int push_to_stack(NodeDataType data);
    static NodeDataType pop_from_stack();

    static void print_stack();
    static std::size_t get_stack_size();

    static void clear_stack();
    static void close_stack();

private:
    static constexpr int MAX_SIZE = 25;
    static std::vector<NodeDataType> stk;
};
}
#endif /* LS_STACK_H */
