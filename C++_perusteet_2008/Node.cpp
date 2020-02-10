/** \file Node.cpp
    Solmuluokan toteutus
*/

#include "Node.h"

/**
 * Oletusmuodostin.
 */
Node::Node()
    : x(0)
    , y(0)
{
}

/**
 * Parametrillinen muodostin.
 * @param _x  X-koordinaatti
 * @param _y  Y-koordinaatti
 */
Node::Node(int _x, int _y)
    : x(_x)
    , y(_y)
{
}

/**
 * Kopiomuodostin.
 * @param source  Solmu, joka kopioidaan.
 */
Node::Node(const Node& source)
    : x(source.x)
    , y(source.y)
{
}

/**
 * Hajotin.
 */
Node::~Node()
{
}

/**
 * Asettaa solmun koordinaatit.
 * @param _x Uusi X-koordinaatti
 * @param _y Uusi Y-koordinaatti
 */
void Node::SetXY(int _x, int _y)
{
    x = _x;
    y = _y;
}

/**
 * Yhtäsuuruuden vertailuoperaattori.
 *
 */
bool operator==(const Node& a, const Node& b)
{
    return (a.X() == b.X() ) && ( a.Y() == b.Y() );
}

/**
 * Toteuttaa map-säiliön less-predikaatin vaatiman operaattorin.
 *
 */
bool operator<(const Node& a, const Node& b)
{
    if(a.X() != b.X()) {
        return (a.X() < b.X());
    }

    return (a.Y() < b.Y());
}

/**
 * Tulostaa solmun virtaan.
 * @param output Virta
 */
std::ostream& Node::Print(std::ostream& output) const
{
    return (output << x << " " << y);
}

/**
 * Tulostaa solmun virtaan käyttäen operaattoria <<.
 * @param output Virta
 * @param n Solmu
 */
std::ostream& operator<<(std::ostream& output, const Node& n)
{
    return n.Print(output);
}

