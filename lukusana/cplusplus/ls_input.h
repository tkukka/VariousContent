#ifndef LS_INPUT_H
#define LS_INPUT_H

#include <type_traits>

namespace LS {

enum class Limits : unsigned long {
    LOWER_LIMIT = 0ul,
    UPPER_LIMIT = 10000000ul
};

enum class InputStatus : int {
    INPUT_OK = 0,
    INPUT_ERROR = -1,
    INPUT_PARAM_ERROR = -2
};

class InputHandler {
public:
    InputHandler(){};
    ~InputHandler(){};
    static InputStatus validate_and_convert_input(const std::string& input,
        unsigned long& number);

private:
};

std::ostream& operator<<(std::ostream& os, const Limits& p);

template <typename T> bool operator<(const T& a, const Limits& b);

template <typename T> bool operator>(const T& a, const Limits& b);
}

#endif
