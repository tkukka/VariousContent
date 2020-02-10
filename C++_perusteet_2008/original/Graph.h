/** \file Graph.h
    Graafi-luokan esittely.
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <map>
#include <vector>
#include <fstream>

#include "Node.h"

/** Graafi-luokkaa k‰ytet‰‰n shakkilaudan vapaiden ruutujen esitt‰miseen.
 */
class Graph
{
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
   enum BFSResult {BFS_OK, /*!< Leveyshaku onnistui. */
                   BFS_NO_ADJ_NODES, /*!< Solmulta puuttui vierussolmut */
                   BFS_NO_COLOR, /*!< Solmulta puuttui v‰ri */
                   BFS_NO_DISTANCE /*!< Solmulta puuttui et‰isyys */
   };

   /** Polun etsimisen paluuarvo
    */
   enum PathResult {PATH_EXIST, /*!< Polku lˆytyi. */
                    NO_PATH, /*!< Polkua ei lˆytynyt. */
                    INVALID_NODE /*!< P‰‰tesolmu ei ole edelt‰j‰listassa. */
   };
   

   Graph();
   ~Graph();
   
   void AddNodes(const Node& n,  const AdjType& adj_nodes);
   void Reset(void);
   void Print(void) const;
   BFSResult BFS(const Node& start);
   PathResult BFS_Path(const Node& start, const Node& end);
   const PathType& GetPath(void) const;
   void PathToFile(std::ofstream& out_file) const;
  

private:
   /** Solmun v‰rin mahdolliset arvot.
    */
   enum NodeColor {WHITE, /*!< Valkea. */
                 GRAY,  /*!< Harmaa. */
                 BLACK  /*!< Musta. */
   };

   //Leveyshaun apumetodit
   void InitNodes(void);
   void SetDistance(const Node &n, int d);
   void SetPredecessor(const Node &v, const Node &u);
   void SetNodeColor(const Node &n, NodeColor color);
   const AdjType* GetAdjNodes(const Node& n) const;


   /** Solmujen et‰isyyslistan tietotyyppi.
    */
   typedef std::map<Node, int> DistanceType;
   
   /** Solmujen edelt‰j‰listan tietotyyppi.
    */
   typedef std::map<Node, Node> PredecessorType;
   
   /** Solmujen v‰rilistan tietotyyppi.
    */
   typedef std::map<Node, NodeColor> ColorType;


   /** Sis‰lt‰‰ graafin solmut.
    */
   GraphDataType data;
   
   /** Polku graafissa.
    */
   PathType path;
   
   /** Eri solmujen et‰isyydet leveyshaussa.
    */
   DistanceType distances;

   /**
    * Solmun et‰isyys ‰‰retˆn. 
    */
   static const int DIST_INFINITE = -1;
   
   /** Eri solmujen edelt‰j‰t leveyshaussa.
    */
   PredecessorType predecessors;

   /** Solmu, johon ei tule polkua.
    */
   static const Node NIL_NODE;
   
   /** Eri solmujen v‰rit leveyshaussa.
    */
   ColorType node_colors;

};

#endif /* GRAPH_H */

