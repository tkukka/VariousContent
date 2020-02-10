/** \file Graph.h
    Graafi-luokan esittely.
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <list>
#include <map>
#include <vector>

#include "Node.h"

/** Graafi-luokkaa käytetään shakkilaudan vapaiden ruutujen esittämiseen.
 */
class Graph {
public:
    /** Vierussolmujen tietotyyppi.
     */
    typedef std::list<Node> AdjType;

    /** Graafin tietotyyppi.
     */
    typedef std::map<Node, AdjType> GraphDataType;

    /** Polun tietotyyppi.
     */
    typedef std::vector<Node> PathType;

    /** Leveyshaun paluuarvo
     */
    enum BFSResult {
        BFS_OK,           /*!< Leveyshaku onnistui. */
        BFS_NO_ADJ_NODES, /*!< Solmulta puuttui vierussolmut */
        BFS_NO_COLOR,     /*!< Solmulta puuttui väri */
        BFS_NO_DISTANCE   /*!< Solmulta puuttui etäisyys */
    };

    /** Polun etsimisen paluuarvo
     */
    enum PathResult {
        PATH_EXIST,  /*!< Polku löytyi. */
        NO_PATH,     /*!< Polkua ei löytynyt. */
        INVALID_NODE /*!< Päätesolmu ei ole edeltäjälistassa. */
    };

    Graph();
    ~Graph();

    void AddNodes(const Node& n, const AdjType& adj_nodes);
    void Reset(void);
    void Print(void) const;
    BFSResult BFS(const Node& start);
    PathResult BFS_Path(const Node& start, const Node& end);
    const PathType& GetPath(void) const;
    void PathToFile(std::ofstream& out_file) const;

private:
    /** Solmun värin mahdolliset arvot.
     */
    enum NodeColor {
        WHITE, /*!< Valkea. */
        GRAY,  /*!< Harmaa. */
        BLACK  /*!< Musta. */
    };

    // Leveyshaun apumetodit
    void InitNodes(void);
    void SetDistance(const Node& n, int d);
    void SetPredecessor(const Node& v, const Node& u);
    void SetNodeColor(const Node& n, NodeColor color);
    const AdjType* GetAdjNodes(const Node& n) const;

    /** Solmujen etäisyyslistan tietotyyppi.
     */
    typedef std::map<Node, int> DistanceType;

    /** Solmujen edeltäjälistan tietotyyppi.
     */
    typedef std::map<Node, Node> PredecessorType;

    /** Solmujen värilistan tietotyyppi.
     */
    typedef std::map<Node, NodeColor> ColorType;

    /** Sisältää graafin solmut.
     */
    GraphDataType data;

    /** Polku graafissa.
     */
    PathType path;

    /** Eri solmujen etäisyydet leveyshaussa.
     */
    DistanceType distances;

    /**
     * Solmun etäisyys ääretön.
     */
    static const int DIST_INFINITE = -1;

    /** Eri solmujen edeltäjät leveyshaussa.
     */
    PredecessorType predecessors;

    /** Solmu, johon ei tule polkua.
     */
    static const Node NIL_NODE;

    /** Eri solmujen värit leveyshaussa.
     */
    ColorType node_colors;
};

#endif /* GRAPH_H */
