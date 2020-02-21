/** \file KingsPathApp.cpp
    Sovellusluokan toteutus
*/

#include <iostream>
#include <string_view>

#include "Graph.h"
#include "KingsPathApp.h"
#include "Node.h"

// tulostusvakioiden alustus
/**
 * Komentoriviparametrien lukumäärä.
 */
static constexpr int PARAMETER_COUNT = 4;

/**
 * Tulostus, kun ei ole polkua.
 */
static constexpr char OUTPUT_NO_PATH[] = "-1 -1";

/**
 * Tulostus, kun tiedosto on väärää muotoa.
 */
static constexpr char OUTPUT_INVALID_FORMAT[] = "-2 -2";

/**
 * Tulostus, kun tapahtuu ajonaikainen virhe.
 */
static constexpr char OUTPUT_RUNTIME_ERR[] = "-3 -3";

/**
 * Oletusmuodostin.
 */
KingsPathApp::KingsPathApp()
    : display_messages(true)
{
}

/**
 * Hajotin.
 */
KingsPathApp::~KingsPathApp()
{
    // varmuuden vuoksi suljetaan tiedostot
    if(input_file.is_open()) {
        input_file.close();
    }

    if(output_file.is_open()) {
        output_file.close();
    }
}

/**
 * Ohjelman käytön opastusmetodi.
 * @param str Ohjelman nimi (.exe).
 */
void KingsPathApp::Usage(const char* str)
{
    using namespace std;
    cout << "Ohjelman käyttö:" << endl;
    cout << str << " <-show | -quiet> <input file> <output file>" << endl;
}

/** Käsittelee komentoriviparametrit.
 * Avaa tiedostot valmiiksi.
 * @param argc Parametrien lukumäärä
 * @param argv Parametritaulukko
 * @return 0 jos OK tai -1 jos tuli virhe.
 */
int KingsPathApp::ProcessCmdLine(int argc, char** argv)
{
    using namespace std;

    // 1. parametrin vertailtavat arvot
    string_view switch_show{ "-show" };
    string_view switch_quiet{ "-quiet" };

    // Aluksi parametrien lukumäärä oikea?
    if(argc != PARAMETER_COUNT) {
        KingsPathApp::Usage(argv[0]);
        return -1;
    }

    //-show , -quiet jäi antamatta?
    if(switch_show != argv[1] && switch_quiet != argv[1]) {
        KingsPathApp::Usage(argv[0]);
        return -1;
    }

    if(switch_show == argv[1]) {
        display_messages = true;
    }
    else {
        display_messages = false;
    }

    // Tiedosto, josta lauta pitäisi löytyä. Onko olemassa?
    input_file.open(argv[2]);
    if(!input_file.good()) {
        cout << "Tiedostoa " << argv[2] << " ei löydy." << endl;
        return -1;
    }
    // Otetaan nimi ylös.
    input_file_name = argv[2];

    // Tiedosto, johon polku kirjoitetaan.
    output_file.open(argv[3]);
    if(!output_file.good()) {
        cout << "Tiedoston " << argv[3] << " avaaminen ei onnistunut." << endl;
        return -1;
    }

    // Kaikki OK.
    return 0;
}

/** Lukee shakkilaudan.
 *  Ilmoittaa havaitut virheet. Sulkee tiedoston lopuksi.

 * @return 0 jos OK tai -1 jos tuli virhe.
 */

int KingsPathApp::ReadBoard()
{
    using std::cout;
    using std::endl;

    // miten kävi laudan lukemisesssa...
    const auto ret = board.ReadFile(input_file);

    if(ret == FileStatus::FILE_NOT_OPEN) {
        if(display_messages) {
            cout << "Tiedosto " << input_file_name << " ei ole auki." << endl;
        }
        output_file << OUTPUT_RUNTIME_ERR << endl;
        return -1;
    }
    else if(ret == FileStatus::FILE_FORMAT_ERROR) {
        if(display_messages) {
            cout << "Tiedosto " << input_file_name << " ei ole oikeaa muotoa."
                 << endl;
        }
        output_file << OUTPUT_INVALID_FORMAT << endl;
        input_file.close();
        return -1;
    }

    // Kaikki OK.
    input_file.close();
    return 0;
}

/** Tulostaa shakkilaudan.
 *
 */
void KingsPathApp::PrintBoard() const
{
    using std::cout;
    using std::endl;

    if(display_messages) {
        cout << endl;
        board.Print(nullptr);
        cout << endl;
    }
}

/** Hakee lyhyimmän kuninkaan polun.
 *  Tulostaa haun tuloksen. Sulkee tulostustiedoston.
 */
void KingsPathApp::SearchPath()
{
    using std::cout;
    using std::endl;

    Graph graph; // laudan vapaiden ruutujen graafi
    // Lauta graafimuotoon
    board.ConvertToGraph(graph);

    // graph.Print();

    // Tehdään leveyshaku
    const auto retBFS = graph.BFS({ 0, 0 });

    // Oliko haku onnistunut?
    if(retBFS ==
        BFSResult::BFS_NO_ADJ_NODES) { // Tämän tilanteen syy aloitussolmussa.

        if(display_messages) {
            std::cout << "Polkua ei ole." << std::endl;
        }
        output_file << OUTPUT_NO_PATH << endl;
        output_file.close();
        return;
    }
    else if(retBFS == BFSResult::BFS_NO_COLOR) { // erikoinen ja odottamaton
                                                 // tilanne
        if(display_messages) {
            std::cout << "Ajonaikainen virhe. Solmun väri puuttui."
                      << std::endl;
        }
        output_file << OUTPUT_RUNTIME_ERR << endl;
        output_file.close();
        return;
    }
    else if(retBFS == BFSResult::BFS_NO_DISTANCE) { // erikoinen ja odottamaton tilanne
        if(display_messages) {
            std::cout << "Ajonaikainen virhe. Solmun etäisyys puuttui."
                      << std::endl;
        }
        output_file << OUTPUT_RUNTIME_ERR << endl;
        output_file.close();
        return;
    }

    // Laudan oikea alanurkka, koordinaatit?
    const auto [width, height] = board.GetDimension();
    // leveyshaku meni putkeen, etsitään nyt polku
    const auto retPath = graph.BFS_Path({ 0, 0 }, { width - 1, height - 1 });

    // Polku on olemassa?
    if(retPath == PathResult::PATH_EXIST) {
        if(display_messages) {
            std::cout << "Polku on olemassa." << std::endl;
        }

        // Polku ruudulle
        const auto& path = graph.GetPath();

        if(display_messages) {
            cout << endl;
            board.Print(&path);
            cout << endl;
        }
        // Polku tiedostoon
        graph.PathToFile(output_file);
    }
    else if(retPath == PathResult::NO_PATH) { // Poluton tilanne
        if(display_messages) {
            std::cout << "Polkua ei ole." << std::endl;
        }
        output_file << OUTPUT_NO_PATH << endl;
    }
    else // INVALID_NODE
    {
        if(display_messages) {
            std::cout << "Polkua ei ole. Oikean alanurkan ruutu oli varattu?"
                      << std::endl;
        }
        output_file << OUTPUT_NO_PATH << endl;
    }

    output_file.close();
}

