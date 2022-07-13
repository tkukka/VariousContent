#ifndef DIRECTION_H
#define DIRECTION_H

enum class Direction : int
{
    North = 0,
    NorthEast,
    East,
    SouthEast,
    South,
    SouthWest,
    West,
    NorthWest
};


Direction RandomDirection();

#endif
