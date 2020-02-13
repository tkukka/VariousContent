/** \file Node.cpp
    Solmuluokan toteutus
*/


#include "Node.h"

/** 
 * Oletusmuodostin.
 */
Node::Node():x(0), y(0)
{
}

/** 
 * Parametrillinen muodostin.
 * @param _x  X-koordinaatti
 * @param _y  Y-koordinaatti
 */
Node::Node(int _x, int _y):x(_x), y(_y)
{
}

/** 
 * Kopiomuodostin.
 * @param source  Solmu, joka kopioidaan.
 */
Node::Node(const Node& source):x(source.x), y(source.y)
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
void Node::SetXY(int _x, int  _y)
{
   x = _x;
   y = _y;
}

/** 
 * Yhtäsuuruuden vertailuoperaattori.
 * @param other Solmu johon verrataan
 */
bool Node::operator==(const Node& other) const
{
   return (x == other.x) && (y == other.y);
}

/** 
 * Toteuttaa map-säiliön less-predikaatin vaatiman operaattorin.
 * @param other Solmu johon verrataan
 */
bool Node::operator<(const Node& other) const
{
   if(x != other.x)
   {
      return (x < other.x);
   }

   return (y < other.y);
}

/** 
 * Tulostaa solmun virtaan.
 * @param output Virta
 */
void Node::Print(std::ostream& output) const
{
    
   output << x << " " << y;
}

/** 
 * Tulostaa solmun virtaan käyttäen operaattoria <<.
 * @param output Virta
 * @param n Solmu
 */
std::ostream& operator<<(std::ostream &output, const Node& n)
{
   n.Print(output);
   return output;
}
