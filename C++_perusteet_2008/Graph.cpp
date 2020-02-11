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
    data.try_emplace(n, adj_nodes);
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
    for (const auto& [node, list]: data) {
        cout << node << ": ";

        // Solmun vierussolmut seuraavaksi ruudulle iteroiden
        for(const auto& n: list) {
            cout << n << "  ";
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
    using QueueType = std::deque<Node>; // Jonon tietotyypin lyhennys

    InitNodes();
    SetDistance(start, 0);
    SetNodeColor(start, NodeColor::GRAY);

    QueueType node_queue{};
    node_queue.emplace_back(start);

    while(node_queue.empty() == false) {
        const auto& CURRENT_NODE( node_queue.front() );
        node_queue.pop_front();

        auto adj = GetAdjNodes(CURRENT_NODE);

        if(!adj) // Vierussolmut puuttuvat?
        {
            return BFSResult::BFS_NO_ADJ_NODES;
        }

        // Käsitellään jokainen vierussolmu
        for(const auto& adj_node: *adj) {
            // Etsitään solmun väri
            const auto color = node_colors.find(adj_node);

            if(color == node_colors.end()) // Väri puuttuu?
            {                                   // Poikkeuksellinen tilanne.
                return BFSResult::BFS_NO_COLOR;
            }

            // Solmussa ei ole käyty ?
            if(color->second == NodeColor::WHITE) {
                SetNodeColor(adj_node, NodeColor::GRAY);
                // Etsitään solmun etäisyys
                const auto dist = distances.find(CURRENT_NODE);

                if(dist == distances.end()) // Etäisyys puuttuu?
                {                                // Poikkeuksellinen tilanne.
                    return BFSResult::BFS_NO_DISTANCE;
                }

                SetDistance(adj_node, (dist->second) + 1);
                SetPredecessor(adj_node, CURRENT_NODE);
                node_queue.emplace_back(adj_node);
            }
        }

        SetNodeColor(CURRENT_NODE, NodeColor::BLACK);
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
        path.emplace_back(start);
    }
    else {
        // etsitään edeltävä solmu
        const auto pre = predecessors.find(end);

        if(pre == predecessors.end()) {
            // cout << "Päätesolmu (" << end << ") ei kuulu graafiin." << endl;
            return PathResult::INVALID_NODE;
        }
        else if(pre->second == NIL_NODE) {
            // cout << "Ei polkua solmusta (" << start << ") solmuun (" << end
            // << ")." << endl;
            return PathResult::NO_PATH;
        }
        else {
            BFS_Path(start, pre->second);
            path.emplace_back(end);
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

    for(const auto& item: path) {
        out_file << item << std::endl; // Solmu tiedostoon
    }

}

/** Alustaa leveyshaun tarvitsemat tiedot solmujen väristä, edeltäjistä ja
 *   etäisyyksistä.
 */
void Graph::InitNodes()
{
    // Pitää käydä kaikki graafin solmut.

    for(const auto& [node, adjacency] : data) {
        SetNodeColor(node, NodeColor::WHITE);
        SetDistance(node, DIST_INFINITE);
        SetPredecessor(node, NIL_NODE);
    }
}

/** Asettaa solmun etäisyyden.
 * Leveyshaku käyttää tätä.
 * @param n Solmu, jonka etäisyys muutetaan.
 * @param d Solmun etäisyys.
 */
void Graph::SetDistance(const Node& n, int d)
{
    distances.insert_or_assign(n, d);
}

/** Asettaa solmun edeltäjän.
 * Leveyshaku käyttää tätä.
 * @param v Solmu, jonka edeltäjä muutetaan.
 * @param u Edeltäjä.
 */
void Graph::SetPredecessor(const Node& v, const Node& u)
{
    predecessors.insert_or_assign(v, u);
}

/** Asettaa solmun värin.
 * Leveyshaku käyttää tätä.
 * @param n Solmu, jonka väri muutetaan.
 * @param color Solmun väri.
 */
void Graph::SetNodeColor(const Node& n, NodeColor color)
{
    node_colors.insert_or_assign(n, color);
}

/** Antaa solmun vierussolmut.
 * @param n Solmu, jonka vierussolmut halutaan.
 * @return Vierussolmut tai tyhjä jos niitä ei ole.
 *
 */
Graph::ListType Graph::GetAdjNodes(const Node& n) const
{
    // etsitään solmun vierussolmulista
    const auto a_list = data.find(n);

    return (a_list == data.end()) ? std::nullopt : ListType{a_list->second};
}

