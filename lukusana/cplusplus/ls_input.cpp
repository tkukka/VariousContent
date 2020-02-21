
#include <iostream>
#include <limits>
#include <string>
#include <stdexcept>

#include "ls_input.h"

namespace LS {

InputStatus InputHandler::validate_and_convert_input(const std::string& input,
    unsigned long& number)
{
    using namespace std;

    /* Tyhjä merkkijono */
    if(input.empty()) {
        cout << "\n\aAnnoit tyhjän syötteen." << endl;
        return InputStatus::INPUT_ERROR;
    }

    const auto find_result = input.find_first_not_of("0123456789");

    if(find_result != string::npos) {
        cout << "\n\aSyötteesi sisälsi muita merkkejä kuin numeroita. "
             << "Ensimmäinen virheellinen merkki: " << input[find_result]
             << endl;
        return InputStatus::INPUT_ERROR;
    }

    size_t pos = 0;
    unsigned long ret = 0;

    try {
        ret = stoul(input, &pos);
    }
    catch(const std::invalid_argument& e) {

        cout << "\n\aSyötteesi sisälsi muita merkkejä kuin numeroita. "
             << "Ensimmäinen virheellinen merkki: " << input[pos] << endl;

        return InputStatus::INPUT_ERROR;
    }
    catch(const std::out_of_range& e) {

        cout << "\n\aAntamasi luku oli suurempi kuin "
             << numeric_limits<unsigned long>::max() << ". ";
        cout << "Luvun on oltava väliltä " << Limits::LOWER_LIMIT << " - "
             << Limits::UPPER_LIMIT << "." << std::endl;
        return InputStatus::INPUT_ERROR;
    }

    /* Syöte lukualueen sisällä? */
    if(ret > Limits::UPPER_LIMIT) {
        cout << "\n\aAntamasi luku ei ollut väliltä " << Limits::LOWER_LIMIT
             << " - " << Limits::UPPER_LIMIT << "." << std::endl;

        return InputStatus::INPUT_ERROR;
    }

    // cout <<'\n' << ret << endl;
    number = ret;

    return InputStatus::INPUT_OK;
}
// ------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Limits& p)
{
    using cast_type = std::underlying_type_t<Limits>;

    os << static_cast<cast_type>(p);
    return os;
}

// ------------------------------------------------------------------------
template <typename T> bool operator<(const T& a, const Limits& b)
{
    using cast_type = std::underlying_type_t<Limits>;

    return a < static_cast<cast_type>(b);
}
// ------------------------------------------------------------------------
template <typename T> bool operator>(const T& a, const Limits& b)
{
    using cast_type = std::underlying_type_t<Limits>;

    return a > static_cast<cast_type>(b);
}

}
