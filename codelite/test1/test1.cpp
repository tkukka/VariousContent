#include <array>
#include <iostream>
#include <iterator>
#include <string_view> //c++17
#include <tuple>       // c++11

#include "test1.h"

// c++11
using std::cout;
using std::tuple;
using MyType = tuple<int, char>;
using std::string_view; // c++17
using ArrRow = std::array<char, 10>;
using Grid = std::array<ArrRow, 10>;
//-----------------------------
decltype(auto) operator<<(std::ostream& o, MyType& t);
//--------------------------------------------------------
decltype(auto) operator<<(std::ostream& o, MyType& t)
{
    auto [value1, value2] = t;           // c++17
    return o << value1 << " " << value2; // c++14
}

void func(string_view text);

//--------------------------------------------------------
int main(void)
{
    MyClass testclass;
    MyType x{ 8, 'K' }; // c++11

    cout << "MyType/tuple: " << x << " testclass.x: " << testclass.get() << "\n";
    func("some text");

    Grid mygrid;

    for(auto&& i = std::begin(mygrid); i != std::end(mygrid); ++i) {

        for(auto&& j = std::begin(*i); j != std::end(*i); ++j) {
            *j = 'k';
        }
    }
    cout << "\n";
    for(Grid::size_type i = 0; i < mygrid.size(); ++i) {
        for(ArrRow::size_type j = 0; j < mygrid.at(i).size(); ++j) {
            cout << mygrid.at(i).at(j) << " ";
        }
    }

    return 0;
}

//--------------------------------------------------------
void func(string_view text)
{
    cout << "\033[31mtext: \033[0m" << text << "\n";
}