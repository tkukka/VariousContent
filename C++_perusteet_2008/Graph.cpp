/** \file Graph.cpp
    Graafi-luokan toteutus
*/

#include <deque>

#include "Graph.h"


/**
 * Solmun etäisyys ääretön.
 */
static constexpr int DIST_INFINITE = -1;

/** Solmu, johon ei tule polkua.
 */
static const Node NIL_NODE{-1, -1};

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

/** Lisää solmun vierussolmuineen graafiin.
 * Asettaa samalla solmuun liittyvät vierussolmut
 * @param n Solmu, johon vierussolmut kuuluvat.
 * @param adj_nodes Vierussolmut
 */
void Graph::AddNodes(const Node& n, const AdjType& adj_nodes)
{
    data.insert(std::make_pair(n, adj_nodes));
}

/** Asettaa graafin takaisin alkutilaan.
 *  Poistaa solmut ja leveyshaun käyttämät aputiedot.
 *
 */
void Graph::Reset()
{
    data.clear();         // Kaikki solmut pois
    distances.clear();    // Etäisyydet pois
    predecessors.clear(); // Edeltäjät pois
    node_colors.clear();  // Värilista pois
    path.clear();         // Polku pois
}

/** Tulostaa graafin solmut ruudulle.
 *  Ensin tulee solmu ja sitten sen vierussolmut.
 */
void Graph::Print() const
{
    using std::cout;
    using std::endl;

    cout << "Graafissa on " << data.size() << " solmua" << endl;

    // käy läpi kaikki solmut iteraattorin avulla
    for(GraphDataType::const_iterator iter = data.begin(); iter != data.end();
        ++iter) {
        cout << (iter->first) << ": ";

        // Solmun vierussolmut seuraavaksi ruudulle iteroiden
        const AdjType& list = iter->second;

        for(AdjType::const_iterator node_iter = list.begin();
            node_iter != list.end(); ++node_iter) {
            cout << (*node_iter) << "  ";
        }

        cout << endl;
    }
}

/** Suorittaa graafissa leveyshaun.
 * Perustuu harjoitustyön liitteen pseudokoodiin.
 * @param start Solmu josta haku alkaa
 * @return Menikö haku ongelmitta (BFSResult).
 * @see BFSResult
 */
BFSResult Graph::BFS(const Node& start)
{
    typedef std::deque<Node> QueueType; // Jonon tietotyypin lyhennys

    QueueType node_queue;

    InitNodes();

    SetDistance(start, 0);
    SetNodeColor(start, NodeColor::GRAY);
    node_queue.clear();

    node_queue.push_back(start);

    while(node_queue.empty() == false) {
        Node current_node = node_queue.front();
        node_queue.pop_front();

        const AdjType* adj = GetAdjNodes(current_node);

        if(!adj) // Vierussolmut puuttuvat?
        {
            return BFSResult::BFS_NO_ADJ_NODES;
        }

        // Käsitellään jokainen vierussolmu
        for(AdjType::const_iterator adj_iter = adj->begin();
            adj_iter != adj->end(); ++adj_iter) {
            // Etsitään solmun väri
            ColorType::const_iterator color_iter = node_colors.find(*adj_iter);

            if(color_iter == node_colors.end()) // Väri puuttuu?
            {                                   // Poikkeuksellinen tilanne.
                return BFSResult::BFS_NO_COLOR;
            }

            // Solmussa ei ole käyty ?
            if(color_iter->second == NodeColor::WHITE) {
                SetNodeColor((*adj_iter), NodeColor::GRAY);
                // Etsitään solmun etäisyys
                DistanceType::const_iterator dist_iter =
                    distances.find(current_node);

                if(dist_iter == distances.end()) // Etäisyys puuttuu?
                {                                // Poikkeuksellinen tilanne.
                    return BFSResult::BFS_NO_DISTANCE;
                }

                SetDistance((*adj_iter), (dist_iter->second) + 1);
                SetPredecessor((*adj_iter), current_node);
                node_queue.push_back(*adj_iter);
            }
        }

        SetNodeColor(current_node, NodeColor::BLACK);
    }

    return BFSResult::BFS_OK;
}

/** Suorittaa graafissa polun hakemisen kahden solmun välillä.
 * Perustuu harjoitustyön liitteen pseudokoodiin. Olettaa että Graph::BFS() on
 * suoritettu ensin.
 * @param start Solmu, josta polun pitäisi alkaa.
 * @param end Solmu, johon polun pitäisi päättyä.
 * @return Onko polkua (PathResult).
 * @see PathResult
 * @see BFS
 */
PathResult Graph::BFS_Path(const Node& start, const Node& end)
{
    // using std::cout;
    // using std::endl;

    if(start == end) {
        path.push_back(start);
    }
    else {
        // etsitään edeltävä solmu
        PredecessorType::const_iterator iter = predecessors.find(end);

        if(iter == predecessors.end()) {
            // cout << "Päätesolmu (" << end << ") ei kuulu graafiin." << endl;
            return PathResult::INVALID_NODE;
        }
        else if(iter->second == NIL_NODE) {
            // cout << "Ei polkua solmusta (" << start << ") solmuun (" << end
            // << ")." << endl;
            return PathResult::NO_PATH;
        }
        else {
            BFS_Path(start, iter->second);
            path.push_back(end);
        }
    }

    return PathResult::PATH_EXIST;
}

/** Antaa leveyshaun polun graafissa.
 * Polussa on järkevä arvo, jos leveushaun polku on haettu Graph::BFS_Path
 * -metodilla.
 * @return Polun.
 * @see PathType
 */
const Graph::PathType& Graph::GetPath() const
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
    PathType::const_iterator iter = path.begin(); // aloitussolmu iteraattoriin

    while(iter != path.end()) {
        out_file << (*iter) << std::endl; // Solmu tiedostoon
        ++iter;
    }
}

/** Alustaa leveyshaun tarvitsemat tiedot solmujen väristä, edeltäjistä ja
 *   etäisyyksistä.
 */
void Graph::InitNodes()
{
    // Pitää käydä kaikki graafin solmut läpi iteraattorilla.

    for(GraphDataType::const_iterator iter = data.begin(); iter != data.end();
        ++iter) {

        SetNodeColor((iter->first), NodeColor::WHITE);
        SetDistance((iter->first), DIST_INFINITE);
        SetPredecessor((iter->first), NIL_NODE);
    }
}

/** Asettaa solmun etäisyyden.
 * Leveyshaku käyttää tätä.
 * @param n Solmu, jonka etäisyys muutetaan.
 * @param d Solmun etäisyys.
 */
void Graph::SetDistance(const Node& n, int d)
{
    distances.erase(n);
    distances.insert(std::make_pair(n, d));
}

/** Asettaa solmun edeltäjän.
 * Leveyshaku käyttää tätä.
 * @param v Solmu, jonka edeltäjä muutetaan.
 * @param u Edeltäjä.
 */
void Graph::SetPredecessor(const Node& v, const Node& u)
{
    predecessors.erase(v);
    predecessors.insert(std::make_pair(v, u));
}

/** Asettaa solmun värin.
 * Leveyshaku käyttää tätä.
 * @param n Solmu, jonka väri muutetaan.
 * @param color Solmun väri.
 */
void Graph::SetNodeColor(const Node& n, NodeColor color)
{
    node_colors.erase(n);
    node_colors.insert(std::make_pair(n, color));
}

/** Antaa solmun vierussolmut.
 * @param n Solmu, jonka vierussolmut halutaan.
 * @return Vierussolmut (osoitin) tai 0 jos niitä ei ole.
 * @see AdjType
 */
const Graph::AdjType* Graph::GetAdjNodes(const Node& n) const
{
    // etsitään solmun vierussolmulista
    GraphDataType::const_iterator iter = data.find(n);

    if(iter == data.end()) {
        return 0; // ei ole vierussolmuja
    }

    return &(iter->second);
}

