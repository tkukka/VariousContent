/** \file Board.h
    Lautaluokan esittely.
*/

#ifndef BOARD_H
#define BOARD_H

#include <fstream>
#include <string>
#include <vector>

#include "Graph.h"
#include "Node.h"

/**
 * Shakkilaudan esitys.
 */
class Board {
public:
    /** Laudan tiedostosta lukemisen paluuarvo.
     */
    enum FileStatus {
        READ_OK,          /*!< Lukeminen onnistui. */
        FILE_NOT_OPEN,    /*!< Tiedosto oli avaamatta. */
        FILE_FORMAT_ERROR /*!< Tiedoston muoto väärä. */
    };

    Board();
    ~Board();

    void Reset();
    FileStatus ReadFile(std::ifstream& infile);
    void Print(const Graph::PathType* path) const;
    void ConvertToGraph(Graph& graph) const;
    void GetDimension(int* w, int* h) const;

private:
    // apufunktio kun polkua tulostetaan
    int NodePosition(const Node& n, const Graph::PathType& path) const;

    /**
     * Laudan ruutujen sallitut kirjainmerkit.
     */
    static const char* ALLOWED_CHARS;

    /**
     * Laudan ruutu varattu.
     */
    static const char SQUARE_OCCUPIED = 'P';

    /**
     * Laudan ruutu vapaa.
     */
    static const char SQUARE_FREE = 'E';

    /**
     * Laudan ruutujen tietotyyppi.
     */
    typedef std::vector<std::string> BoardDataType;

    /**
     * Laudan ruudut.
     */
    BoardDataType data;

    /**
     * Laudan leveys.
     */
    size_t width;

    /**
     * Laudan korkeus.
     */
    size_t height;
};

#endif /* BOARD_H */

