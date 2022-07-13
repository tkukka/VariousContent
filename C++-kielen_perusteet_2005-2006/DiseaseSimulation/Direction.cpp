#include <array>
#include "Randomizer.h"
#include "Direction.h"


inline constexpr const std::array<Direction, 8> DIRECTIONS
{
    Direction::North,
    Direction::NorthEast,
    Direction::East,
    Direction::SouthEast,
    Direction::South,
    Direction::SouthWest,
    Direction::West,
    Direction::NorthWest
};

Direction RandomDirection()
{
    static auto rnd = Randomizer::GetRandomizer();

    return DIRECTIONS[rnd->RandomNumber(0, DIRECTIONS.size() - 1)];
}
