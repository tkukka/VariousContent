/** \file Node.h
    Solmuluokan esittely.
*/

#ifndef NODE_H
#define NODE_H

#include <iostream>

/** Solmuluokka graafia varten.
 */
class Node
{
public:
   Node();
   Node(int _x, int _y);
   Node(const Node& source);
   ~Node();

   void SetXY(int _x, int _y);
   bool operator==(const Node& other) const;
   bool operator<(const Node& other) const;
   void Print(std::ostream &output) const;

private:
   /** 
    * Solmun X-koordinaatti
    */
   int x;
   /** 
    * Solmun Y-koordinaatti
    */
   int y;
};

std::ostream& operator<<(std::ostream &output, const Node& n);


#endif
