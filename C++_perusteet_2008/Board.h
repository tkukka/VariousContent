/** \file Board.h
    Lautaluokan esittely.
*/

#ifndef BOARD_H
#define BOARD_H

#include <fstream>
#include <string>
#include <vector>
#include <tuple>

#include "Graph.h"
#include "Node.h"


/** Laudan tiedostosta lukemisen paluuarvo.
 */
enum class FileStatus {
    READ_OK,          /*!< Lukeminen onnistui. */
    FILE_NOT_OPEN,    /*!< Tiedosto oli avaamatta. */
    FILE_FORMAT_ERROR /*!< Tiedoston muoto väärä. */
    };

/**
 * Shakkilaudan esitys.
 */
class Board {

public:

    Board();
    ~Board();

    void Reset();
    FileStatus ReadFile(std::ifstream& infile);
    void Print(const Graph::PathType* path) const;
    void ConvertToGraph(Graph& graph) const;
    std::tuple<int, int> GetDimension() const;

private:
    // apufunktio kun polkua tulostetaan
    static int NodePosition(const Node& n, const Graph::PathType& path);

    /**
     * Laudan ruutujen tietotyyppi.
     */
    using BoardDataType = std::vector<std::string>;

    /**
     * Laudan ruudut.
     */
    BoardDataType data;

    /**
     * Laudan leveys.
     */
    int width;

    /**
     * Laudan korkeus.
     */
    int height;
};

#endif /* BOARD_H */

