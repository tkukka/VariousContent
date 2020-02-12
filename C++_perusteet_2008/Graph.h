/** \file Graph.h
    Graafi-luokan esittely.
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <list>
#include <map>
#include <optional>
#include <vector>

#include "Node.h"

/** Leveyshaun paluuarvo
 */
enum class BFSResult {
    BFS_OK,           /*!< Leveyshaku onnistui. */
    BFS_NO_ADJ_NODES, /*!< Solmulta puuttui vierussolmut */
    BFS_NO_COLOR,     /*!< Solmulta puuttui väri */
    BFS_NO_DISTANCE   /*!< Solmulta puuttui etäisyys */
};

/** Polun etsimisen paluuarvo
 */
enum class PathResult {
    PATH_EXIST,  /*!< Polku löytyi. */
    NO_PATH,     /*!< Polkua ei löytynyt. */
    INVALID_NODE /*!< Päätesolmu ei ole edeltäjälistassa. */
};

/** Graafi-luokkaa käytetään shakkilaudan vapaiden ruutujen esittämiseen.
 */
class Graph {

public:
    /** Vierussolmujen tietotyyppi.
     */
    using AdjType = std::list<Node>;

    /** Graafin tietotyyppi.
     */
    using GraphDataType = std::map<Node, AdjType>;

    /** Polun tietotyyppi.
     */
    using PathType = std::vector<Node>;

    Graph();
    ~Graph();

    void AddNodes(const Node& n, const AdjType& adj_nodes);
    void Reset();
    void Print() const;
    BFSResult BFS(const Node& start);
    PathResult BFS_Path(const Node& start, const Node& end);
    const PathType& GetPath() const;
    void PathToFile(std::ofstream& out_file) const;

private:
    /** Solmun värin mahdolliset arvot.
     */
    enum class NodeColor {
        WHITE, /*!< Valkea. */
        GRAY,  /*!< Harmaa. */
        BLACK  /*!< Musta. */
    };

    using ListType = std::optional<AdjType>;

    // Leveyshaun apumetodit
    void InitNodes();
    void SetDistance(const Node& n, int d);
    void SetPredecessor(const Node& v, const Node& u);
    void SetNodeColor(const Node& n, NodeColor color);
    ListType GetAdjNodes(const Node& n) const;

    /** Solmujen etäisyyslistan tietotyyppi.
     */
    using DistanceType = std::map<Node, int>;

    /** Solmujen edeltäjälistan tietotyyppi.
     */
    using PredecessorType = std::map<Node, Node>;

    /** Solmujen värilistan tietotyyppi.
     */
    using ColorType = std::map<Node, NodeColor>;

    /** Sisältää graafin solmut.
     */
    GraphDataType data;

    /** Polku graafissa.
     */
    PathType path;

    /** Eri solmujen etäisyydet leveyshaussa.
     */
    DistanceType distances;

    /** Eri solmujen edeltäjät leveyshaussa.
     */
    PredecessorType predecessors;

    /** Eri solmujen värit leveyshaussa.
     */
    ColorType node_colors;
};

#endif /* GRAPH_H */

