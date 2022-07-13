#ifndef POSITION_H
#define POSITION_H

#include <cstdlib>
#include <iostream>

class Position
{
public:
    Position() = default;
    Position(const Position&) = default;
    Position& operator=(const Position&) = default;
    void SetPosition(int aX, int aY) { iX = aX; iY = aY; }
    int XPos() const { return iX; }
    int YPos() const { return iY; }
    static void SetMax(int aMax) { max = aMax; }
    static int Max() { return max; }
private:
    int iX = 0;
    int iY = 0;
    inline static int max = 0;
};

inline bool isNear(const Position& pos1, const Position& pos2)
{
    const auto diff_x = std::abs(pos1.XPos() - pos2.XPos());
    const auto diff_y = std::abs(pos1.YPos() - pos2.YPos());
    
    return (diff_x == 0 && diff_y == 0) || (diff_x == 1 && diff_y == 0) || (diff_x == 1 && diff_y == 1) || (diff_x == 0 && diff_y == 1); 
}

inline std::ostream& operator<<(std::ostream& o, const Position& pos)
{
    o << "P:(" << pos.XPos() << ", " << pos.YPos() << ')';
    return o;
}


#endif
