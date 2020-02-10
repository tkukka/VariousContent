/** \file Graph.cpp
    Graafi-luokan toteutus
*/

#include <deque>

#include "Graph.h"

//poluttoman solmun vakion alustus
const Node Graph::NIL_NODE(-1, -1);

/** 
 * Oletusmuodostin.
 */
Graph::Graph()
{
    
}

/** 
 * Hajotin.
 */
Graph::~Graph()
{

}

/** Lis‰‰ solmun vierussolmuineen graafiin. 
 * Asettaa samalla solmuun liittyv‰t vierussolmut
 * @param n Solmu, johon vierussolmut kuuluvat.
 * @param adj_nodes Vierussolmut
 */
void Graph::AddNodes(const Node& n,  const AdjType& adj_nodes)
{
   data.insert(std::make_pair(n, adj_nodes));
}

/** Asettaa graafin takaisin alkutilaan.
 *  Poistaa solmut ja leveyshaun k‰ytt‰m‰t aputiedot.
 *  
 */
void Graph::Reset(void)
{
   data.clear();          //Kaikki solmut pois
   distances.clear();     //Et‰isyydet pois
   predecessors.clear();  //Edelt‰j‰t pois
   node_colors.clear();   //V‰rilista pois
   path.clear();          //Polku pois
}

/** Tulostaa graafin solmut ruudulle.
 *  Ensin tulee solmu ja sitten sen vierussolmut.
 */
void Graph::Print(void) const
{
   using std::cout;
   using std::endl;

   cout << "Graafissa on " << data.size() << " solmua" << endl;

   //k‰y l‰pi kaikki solmut iteraattorin avulla
   for (GraphDataType::const_iterator iter = data.begin(); 
        iter != data.end(); 
        ++iter)
   {
      cout << (iter->first) << ": ";

      //Solmun vierussolmut seuraavaksi ruudulle iteroiden
      const AdjType& list = iter->second;
      
      for(AdjType::const_iterator node_iter = list.begin(); 
         node_iter != list.end(); 
         ++node_iter)
      {
         cout << (*node_iter) << "  ";
      }

      cout << endl;
   }

}

/** Suorittaa graafissa leveyshaun. 
 * Perustuu harjoitustyˆn liitteen pseudokoodiin.
 * @param start Solmu josta haku alkaa
 * @return Menikˆ haku ongelmitta (BFSResult).
 * @see BFSResult
 */
Graph::BFSResult Graph::BFS(const Node& start)
{
   typedef std::deque<Node> QueueType; //Jonon tietotyypin lyhennys
   
   QueueType node_queue;

   InitNodes();

   SetDistance(start, 0);
   SetNodeColor(start, GRAY);
   node_queue.clear();

   node_queue.push_back(start);

   while(node_queue.empty() == false)
   {
      Node current_node = node_queue.front();
      node_queue.pop_front();
      
      const AdjType* adj = GetAdjNodes(current_node);

      if(! adj) //Vierussolmut puuttuvat?
      {
         return BFS_NO_ADJ_NODES;
      }

      //K‰sitell‰‰n jokainen vierussolmu 
      for(AdjType::const_iterator adj_iter = adj->begin();
         adj_iter != adj->end(); 
         ++adj_iter)
      {
         //Etsit‰‰n solmun v‰ri
         ColorType::const_iterator color_iter =  node_colors.find(*adj_iter);
         
         if(color_iter == node_colors.end()) //V‰ri puuttuu?
         {  //Poikkeuksellinen tilanne.
            return BFS_NO_COLOR; 
         }

         //Solmussa ei ole k‰yty ?
         if(color_iter->second == WHITE)
         {
            SetNodeColor((*adj_iter), GRAY);
            //Etsit‰‰n solmun et‰isyys 
            DistanceType::const_iterator dist_iter = distances.find(current_node);

            if(dist_iter == distances.end()) //Et‰isyys puuttuu?
            {  //Poikkeuksellinen tilanne.
               return BFS_NO_DISTANCE; 
            }

            SetDistance((*adj_iter), (dist_iter->second) + 1);
            SetPredecessor((*adj_iter), current_node);
            node_queue.push_back(*adj_iter);

         }
      }

      SetNodeColor(current_node, BLACK);
   }

   return BFS_OK;
}

/** Suorittaa graafissa polun hakemisen kahden solmun v‰lill‰. 
 * Perustuu harjoitustyˆn liitteen pseudokoodiin. Olettaa ett‰ Graph::BFS() on 
 * suoritettu ensin.
 * @param start Solmu, josta polun pit‰isi alkaa.
 * @param end Solmu, johon polun pit‰isi p‰‰tty‰.
 * @return Onko polkua (PathResult).
 * @see PathResult
 * @see BFS
 */
Graph::PathResult Graph::BFS_Path(const Node& start, const Node& end)
{
   //using std::cout;
   //using std::endl;
   

   if(start == end)
   {
      path.push_back(start);
   }
   else
   {
      //etsit‰‰n edelt‰v‰ solmu
      PredecessorType::const_iterator iter = predecessors.find(end);
      
      if (iter == predecessors.end()  )
      {
         //cout << "P‰‰tesolmu (" << end << ") ei kuulu graafiin." << endl;
         return INVALID_NODE;
      }
      else if(iter->second == NIL_NODE )
      {
         //cout << "Ei polkua solmusta (" << start << ") solmuun (" << end << ")." << endl;
         return NO_PATH;
      }
      else
      {
         BFS_Path(start, iter->second); 
         path.push_back(end);
      }
   }

   return PATH_EXIST;
}

/** Antaa leveyshaun polun graafissa.
 * Polussa on j‰rkev‰ arvo, jos leveushaun polku on haettu Graph::BFS_Path 
 * -metodilla.
 * @return Polun.
 * @see PathType
 */
const Graph::PathType& Graph::GetPath(void) const
{
   return path;
}

/** Tulostaa leveyshaun polun tiedostoon.
 * Kutsuja sulkee tiedoston.
 * @param out_file Tiedosto, johon tulostetaan.
 * 
 */
void Graph::PathToFile(std::ofstream& out_file) const
{
   PathType::const_iterator iter = path.begin(); //aloitussolmu iteraattoriin

   while(iter != path.end())
   {
      out_file << (*iter) << std::endl; //Solmu tiedostoon
      ++iter;
   }
}

/** Alustaa leveyshaun tarvitsemat tiedot solmujen v‰rist‰, edelt‰jist‰ ja 
 *   et‰isyyksist‰.
 */
void Graph::InitNodes(void)
{
   //Pit‰‰ k‰yd‰ kaikki graafin solmut l‰pi iteraattorilla.

   for (GraphDataType::const_iterator iter = data.begin(); 
      iter != data.end(); 
      ++iter)
   {

      SetNodeColor((iter->first), WHITE);
      SetDistance((iter->first), DIST_INFINITE);
      SetPredecessor((iter->first), NIL_NODE);
   }

}

/** Asettaa solmun et‰isyyden.
 * Leveyshaku k‰ytt‰‰ t‰t‰.
 * @param n Solmu, jonka et‰isyys muutetaan.
 * @param d Solmun et‰isyys.
 */
void Graph::SetDistance(const Node &n, int d)
{  
   distances.erase(n);
   distances.insert(std::make_pair(n, d));
}

/** Asettaa solmun edelt‰j‰n.
 * Leveyshaku k‰ytt‰‰ t‰t‰.
 * @param v Solmu, jonka edelt‰j‰ muutetaan.
 * @param u Edelt‰j‰.
 */
void Graph::SetPredecessor(const Node &v, const Node &u)
{
   predecessors.erase(v);
   predecessors.insert(std::make_pair(v, u));
}

/** Asettaa solmun v‰rin.
 * Leveyshaku k‰ytt‰‰ t‰t‰.
 * @param n Solmu, jonka v‰ri muutetaan.
 * @param color Solmun v‰ri.
 */
void Graph::SetNodeColor(const Node &n, NodeColor color)
{
   node_colors.erase(n);
   node_colors.insert(std::make_pair(n, color));
}

/** Antaa solmun vierussolmut.
 * @param n Solmu, jonka vierussolmut halutaan.
 * @return Vierussolmut (osoitin) tai 0 jos niit‰ ei ole.
 * @see AdjType
 */
const Graph::AdjType* Graph::GetAdjNodes(const Node& n) const
{
   //etsit‰‰n solmun vierussolmulista
   GraphDataType::const_iterator iter = data.find(n);

   if(iter == data.end() )
   {
       return 0; //ei ole vierussolmuja
   }

   return &(iter->second);
}
