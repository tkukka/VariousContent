/** \file Board.cpp
    Lautaluokan toteutus
*/
#include <iterator>

#include "Board.h"

/**
 * Laudan ruutujen sallitut kirjainmerkit.
 */
static constexpr char ALLOWED_CHARS[] = "EP";

/**
 * Laudan ruutu varattu.
 */
static constexpr char SQUARE_OCCUPIED = 'P';

/**
 * Laudan ruutu vapaa.
 */
static constexpr char SQUARE_FREE = 'E';

/**
 * Oletusmuodostin.
 */
Board::Board()
    : data{}
    , width{ 0 }
    , height{ 0 }
{
}

/**
 * Hajotin.
 */
Board::~Board()
{
}

/**
 * Palauttaa laudan alkutilaan.
 */
void Board::Reset()
{
    data.clear();
    width = 0;
    height = 0;
}

/** Lukee shakkilaudan tiedostosta.
 * Kutsuja sulkee tiedoston.
 * @param infile Tiedosto, josta luetaan.
 * @return Lukemisen onnistuminen.
 * @see FileStatus
 */
FileStatus Board::ReadFile(std::ifstream& infile)
{
    using std::getline;
    using std::string;

    // tsekataan onko auki
    if(infile.is_open() == false) {
        return FileStatus::FILE_NOT_OPEN;
    }

    string::size_type row_length = 0; // Rivin leveys tiedostossa
    bool first_row_measured = false;  // Rivin leveys luetaan 1. riviltä. Tämä lippu apuna.
    int rows = 0; // Tiedostosta luettujen rivien lukumäärä

    // Nollataan laudan tiedot
    Reset();

    string line; // Luettu tekstirivi
    // Käydään läpi tiedoston rivit kunnes tiedosto loppuu
    while(getline(infile, line)) {

        // Onko tyhjä rivi?
        if(line.empty()) {
            // Tiedosto ei lopussa vielä?
            if(infile.eof() == false) { // keskellä tiedostoa tyhjä rivi => virhe
                return FileStatus::FILE_FORMAT_ERROR;
            }

            // Viimeinen rivi voi olla tyhjä. Poistutaan ilman hälyä.
            break;
        }

        // Etsitään vääriä merkkejä
        const auto char_index = line.find_first_not_of(ALLOWED_CHARS);
        // Löytyikö kiellettyjä?
        if(char_index != string::npos) {
            return FileStatus::FILE_FORMAT_ERROR;
        }

        // Otetaan ylös 1. rivin pituus
        if(first_row_measured == false) {
            row_length = line.length();
            first_row_measured = true;
        }

        // Tutkitaan jokaisen luetun rivin pituus
        if(row_length != line.length()) {
            // cout << "File row len error" << endl;
            return FileStatus::FILE_FORMAT_ERROR;
        }

        // Rivi on OK
        ++rows;
        data.emplace_back(line);
    }

    // Otetaan vielä lopussa shakkilaudan mitat
    height = rows;
    width = static_cast<int>(row_length);
    return FileStatus::READ_OK;
}

/** Tulostaa shakkilaudan ruudulle polun kanssa tai ilman.
 * Sama metodi tulostaa laudalle kuninkaan polun, jos sellainen annetaan.
 * Suurin näytöllä järkevästi toimiva laudan leveys 9 ruutua.
 *
 * @param path Polku, tai nullptr jos tulostetaan vain lauta ilman polkua.
 *
 */
void Board::Print(const Graph::PathType* path) const
{
    using std::cout;
    using std::endl;
    using std::string;

    // ei lautaa
    if(data.empty()) {
        cout << "Laudassa ei ruutuja" << endl;
        return;
    }

    // Yläosan vaakaan juoksevat numerot. Sarakkeet.
    for(int i = 0; i < width; ++i) {
        cout << "\t" << i;
    }
    cout << endl;

    // ruudun koordinaatit
    int row = 0;
    int column;

    for(const auto& data_row : data) {
        cout << row;
        column = 0;

        for(const auto c : data_row) {
            // tulostetaan varattu ruutu?
            if(c == SQUARE_OCCUPIED) {
                cout << "\t" << c;
            }
            else { // vapaa ruutu tulostuu

                if(path) // jos polku tulostetaan laudalle
                {
                    // pitää tutkia onko nykyinen vapaa ruutu jossain kohdassa
                    // polkua. vähän tehotonta...
                    const auto index = Board::NodePosition({ column, row }, *path);
                    if(index >= 0) // tämä ruutu on polussa?
                    {
                        cout << "\t"
                             << "\033[1;37;44m" << (index + 1) << "\033[0m";
                    }
                    else {
                        cout << "\t";
                    }
                }
                else {
                    cout << "\t";
                }
            }
            ++column;
        }

        cout << endl;
        ++row;
    }
}

/** Hakee, missä kohtaa polkua on jokin annettu solmu.
 * Käytetään apumetodina kun polkua tulostetaan laudalle.

 * @param n Haettava solmu
 * @param path Polku, josta solmua haetaan.
 * @return Indeksi (sijainti) polussa
 */
int Board::NodePosition(const Node& n, const Graph::PathType& path)
{
    int position = 0; // sijainti polussa. 0 = ensimmäinen

    for(const auto& path_item : path) {
        if(path_item == n) {
            return position;
        }
        ++position;
    }

    // ei ole polussa
    return -1;
}

/** Muuttaa laudan graafiksi.
 * @param graph Graafi, johon solmut tallennetaan.
 */
void Board::ConvertToGraph(Graph& graph) const
{
    // using std::cout;
    // using std::endl;
    using namespace std;

    // ei lautaa mistä ottaa ruutuja?
    if(data.empty()) {
        return;
    }

    // tehdään laudasta kopio, koska lisätään kaksi riviä varattuja ruutuja.
    BoardDataType copy_data = data;
    const auto row_length = static_cast<int>(copy_data[0].length()); // laudan rivin leveys ylös

    const string FILLER(row_length, SQUARE_OCCUPIED); // tehdään täyterivi varatuista ruuduista

    // Lisätään nyt 2 apuriviä indeksoinnin helpottamiseksi
    copy_data.emplace(cbegin(copy_data), FILLER); // rivi laudan alkuun
    copy_data.emplace_back(FILLER);               // rivi laudan loppuun

    // montako riviä laudassa nyt, otetaan ylös silmukkaa varten
    const auto row_count = copy_data.size();

    // int counter = 0;    // montako solmua, joilla oli vierussolmuja
    int actual_row = 0; // seuraa todellista riviä alkuperäisessa laudassa
    Graph::AdjType adj_nodes; // kerää vierussolmut

    // kierretään rivejä alkaen toisesta rivistä aina toiseksi viimeiseen asti
    for(std::size_t i = 1; i < (row_count - 1); ++i, ++actual_row) {
        // otetaan ylös kolme riviä laudasta: edellinen, nykyinen ja seuraava.
        const auto& prev_row = copy_data[i - 1];
        const auto& current_row = copy_data[i];
        const auto& next_row = copy_data[i + 1];

        // kierretään sarakkeita (yksittäisiä merkkejä rivillä)
        for(int j = 0; j < row_length; ++j) {
            adj_nodes.clear();

            // cout << "(" << j << ", " << actual_row  << "): ";

            // onko nykyinen ruutu tyhjä?
            if(current_row[j] == SQUARE_FREE) {
                /* Tutkitaan 8 naapuriruutua. Järjestys:
                 *    1 2 3
                 *    4   5
                 *    6 7 8
                 */

                if(j > 0) /* 1 */
                {
                    if(prev_row[j - 1] == SQUARE_FREE) {
                        // cout << "(" << j-1 << ", " << actual_row-1 << ") ";
                        // oli vapaa, lisätään vierussolmuksi
                        adj_nodes.emplace_back(j - 1, actual_row - 1);
                    }
                }

                if(prev_row[j] == SQUARE_FREE) /* 2 */
                {
                    // cout << "(" << j << ", " << actual_row-1 << ") ";
                    // oli vapaa, lisätään vierussolmuksi
                    adj_nodes.emplace_back(j, actual_row - 1);
                }

                if(j < (row_length - 1)) /* 3 */
                {
                    if(prev_row[j + 1] == SQUARE_FREE) {
                        // cout << "(" << j+1 << ", " << actual_row-1 << ") ";
                        // oli vapaa, lisätään vierussolmuksi
                        adj_nodes.emplace_back(j + 1, actual_row - 1);
                    }
                }

                if(j > 0) /* 4 */
                {
                    if(current_row[j - 1] == SQUARE_FREE) {
                        // cout << "(" << j-1 << ", " << actual_row << ") ";
                        // oli vapaa, lisätään vierussolmuksi
                        adj_nodes.emplace_back(j - 1, actual_row);
                    }
                }

                if(j < (row_length - 1)) /* 5 */
                {
                    if(current_row[j + 1] == SQUARE_FREE) {
                        // cout << "(" << j+1 << ", " << actual_row << ") ";
                        // oli vapaa, lisätään vierussolmuksi
                        adj_nodes.emplace_back(j + 1, actual_row);
                    }
                }

                if(j > 0) /* 6 */
                {
                    if(next_row[j - 1] == SQUARE_FREE) {
                        // cout << "(" << j-1 << ", " << actual_row+1 << ") ";
                        // oli vapaa, lisätään vierussolmuksi
                        adj_nodes.emplace_back(j - 1, actual_row + 1);
                    }
                }

                if(next_row[j] == SQUARE_FREE) /* 7 */
                {
                    // std::cout << "(" << j << ", " << actual_row+1 << ") ";
                    // oli vapaa, lisätään vierussolmuksi
                    adj_nodes.emplace_back(j, actual_row + 1);
                }

                if(j < (row_length - 1)) /* 8 */
                {
                    if(next_row[j + 1] == SQUARE_FREE) {
                        // std::cout << "(" << j+1 << ", " << actual_row+1 <<
                        // ") "; oli vapaa, lisätään vierussolmuksi
                        adj_nodes.emplace_back(j + 1, actual_row + 1);
                    }
                }

            } // if ( current_row[j] == SQUARE_FREE  )

            // Ei lisätä yksinäisiä vapaita shakkiruutuja graafiin
            if(adj_nodes.empty() == false) {
                //++counter;
                graph.AddNodes({ j, actual_row }, adj_nodes);
            }

        } // for (sarakkeet)

    } // for (rivit)

    // std::cout << "Solmuja oli " << counter << std::endl;
}

/** Palauttaa laudan leveyden ja korkeuden.
 *
 *
 */
std::tuple<int, int> Board::GetDimension() const
{
    return { width, height };
}

