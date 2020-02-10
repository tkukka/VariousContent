/** \file Node.h
    Solmuluokan esittely.
*/

#ifndef NODE_H
#define NODE_H

#include <iostream>

/** Solmuluokka graafia varten.
 */
class Node {
public:
    Node();
    Node(int _x, int _y);
    Node(const Node& source);
    ~Node();

    void SetXY(int _x, int _y);
    std::ostream& Print(std::ostream& output) const;
    int X() const { return x; }
    int Y() const { return y; }

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

bool operator==(const Node& a, const Node& b);
bool operator<(const Node& a, const Node& b);
std::ostream& operator<<(std::ostream& output, const Node& n);

#endif

