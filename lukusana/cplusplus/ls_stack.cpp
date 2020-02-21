
#include <iostream>
#include <iterator>

#include "ls_stack.h"

namespace LS {

std::vector<NodeDataType> FooStack::stk;
// ------------------------------------------------------------------------
void FooStack::init_stack()
{
    stk.reserve(MAX_SIZE);
}
// ------------------------------------------------------------------------
int FooStack::push_to_stack(NodeDataType data)
{
    if(stk.size() < MAX_SIZE) {
        stk.emplace_back(data);
        return 1;
    }

    return 0;
}
// ------------------------------------------------------------------------
NodeDataType FooStack::pop_from_stack()
{
    if(!stk.empty()) {
        auto r = stk.back();
        stk.pop_back();
        return r;
    }

    return nullptr;
}
// ------------------------------------------------------------------------
void FooStack::print_stack()
{

    std::copy(std::crbegin(stk), std::crend(stk),
        std::ostream_iterator<NodeDataType>(std::cout));
}
// ------------------------------------------------------------------------
std::size_t FooStack::get_stack_size()
{
    return stk.size();
}
// ------------------------------------------------------------------------
void FooStack::clear_stack()
{
    stk.clear();
}
// ------------------------------------------------------------------------
void FooStack::close_stack()
{
}
}
