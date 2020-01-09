#ifndef TEST1_H
#define TEST1_H

class MyClass {
private:
    int x{ 111 }; // c++11

public:
    MyClass() = default; // c++11
    auto get()           // c++11
    {
        return x;
    }
};
#endif
