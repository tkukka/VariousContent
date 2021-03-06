/** \file KingsPathApp.cpp
    Sovellusluokan toteutus
*/


#include <iostream>

#include "Node.h"
#include "Graph.h"
#include "KingsPathApp.h"

//tulostusvakioiden alustus
const char* KingsPathApp::OUTPUT_NO_PATH = "-1 -1";
const char* KingsPathApp::OUTPUT_INVALID_FORMAT = "-2 -2";
const char* KingsPathApp::OUTPUT_RUNTIME_ERR = "-3 -3";

/** 
 * Oletusmuodostin.
 */
KingsPathApp::KingsPathApp():display_messages(true)
{

}

/** 
 * Hajotin.
 */
KingsPathApp::~KingsPathApp()
{
   //varmuuden vuoksi suljetaan tiedostot
   if(input_file.is_open())
   {
      input_file.close();
   }

   if (output_file.is_open())
   {
      output_file.close();
   }
   
}

/** 
 * Ohjelman käytön opastusmetodi.
 * @param str Ohjelman nimi (.exe).
 */
void KingsPathApp::Usage(const char *str) const
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
int KingsPathApp::ProcessCmdLine(int argc, char **argv)
{
   using std::cout;
   using std::endl;
   using std::string;

   //1. parametrin vertailtavat arvot
   string switch_show("-show");
   string switch_quiet("-quiet");

   //Aluksi parametrien lukumäärä oikea?
   if(argc != PARAMETER_COUNT)
   {
      Usage(argv[0]);
      return -1;
   }

   //-show , -quiet jäi antamatta?
   if(switch_show != argv[1] && switch_quiet != argv[1])
   {
      Usage(argv[0]);
      return -1;      
   }

   if(switch_show == argv[1])
   {
      display_messages = true;
   }
   else
   {
      display_messages = false;
   }

   //Tiedosto, josta lauta pitäisi löytyä. Onko olemassa?
   input_file.open(argv[2]);
   if(! input_file.good() )
   {
      cout << "Tiedostoa " << argv[2] << " ei löydy." << endl;
      return -1;
   }
   //Otetaan nimi ylös.
   input_file_name = argv[2];

   //Tiedosto, johon polku kirjoitetaan. Pääseekö käsiksi?
   output_file.open(argv[3]);
   if( ! output_file.good() )
   {
      cout << "Tiedoston " << argv[3] << " avaaminen ei onnistunut." << endl;
      return -1;
   }

   //Kaikki OK.
   return 0;
}

/** Lukee shakkilaudan.
 *  Ilmoittaa havaitut virheet. Sulkee tiedoston lopuksi.

 * @return 0 jos OK tai -1 jos tuli virhe.
 */

int KingsPathApp::ReadBoard(void)
{
   using std::cout;
   using std::endl;

   Board::FileStatus ret; //kertoo, miten kävi laudan lukemisesssa

   ret = board.ReadFile(input_file);

   if(ret == Board::FILE_NOT_OPEN)
   {
      if(display_messages)
      {
         cout << "Tiedosto " << input_file_name << " ei ole auki." << endl;
      }
      output_file << OUTPUT_RUNTIME_ERR << endl;
      return -1;
   }
   else if (ret == Board::FILE_FORMAT_ERROR)
   {
      if(display_messages)
      {
         cout << "Tiedosto " << input_file_name << " ei ole oikeaa muotoa." << endl;
      }
      output_file << OUTPUT_INVALID_FORMAT << endl;
      input_file.close();
      return -1;
   }

   //Kaikki OK.
   input_file.close();
   return 0;
}

/** Tulostaa shakkilaudan.
 * 
 */
void KingsPathApp::PrintBoard(void) const
{
   using std::cout;
   using std::endl;

   if(display_messages)
   {
      cout << endl;
      board.Print(0);
      cout << endl;
   }

}

/** Hakee lyhyimmän kuninkaan polun.
 *  Tulostaa haun tuloksen. Sulkee tulostustiedoston.
 */
void KingsPathApp::SearchPath(void)
{
   using std::cout;
   using std::endl;

   Graph graph;            //laudan vapaiden ruutujen graafi
   Node start_node(0,0);   //polun alku
   Node end_node;          //polun loppu
   Graph::BFSResult retBFS; //leveyshaun tulos
   Graph::PathResult retPath; //polun haun tulos
   int width;    //laudan leveys
   int height;   //laudan korkeus

   //Lauta graafimuotoon
   board.ConvertToGraph(graph);

   //graph.Print();

   //Laudan oikea alanurkka..koordinaatit?
   board.GetDimension(&width, &height);
   end_node.SetXY(width- 1, height - 1);

   //Tehdään leveyshaku
   retBFS = graph.BFS(start_node);

   //Oliko haku onnistunut?
   if(retBFS == Graph::BFS_NO_ADJ_NODES)
   {  //Tämän tilanteen syy aloitussolmussa. 

      if(display_messages)
      {
         std::cout << "Polkua ei ole." << std::endl;
      }
      output_file << OUTPUT_NO_PATH << endl;
      output_file.close();
      return;
   }
   else if(retBFS == Graph::BFS_NO_COLOR)
   {  //erikoinen ja odottamaton tilanne
      if(display_messages)
      {
         std::cout << "Ajonaikainen virhe. Solmun väri puuttui." << std::endl;
      }
      output_file << OUTPUT_RUNTIME_ERR << endl;
      output_file.close();
      return;
   }
   else if(retBFS == Graph::BFS_NO_DISTANCE)
   {  //erikoinen ja odottamaton tilanne
      if(display_messages)
      {
         std::cout << "Ajonaikainen virhe. Solmun etäisyys puuttui." << std::endl;
      }
      output_file << OUTPUT_RUNTIME_ERR << endl;
      output_file.close();
      return;
   }

   //leveyshaku meni putkeen, etsitään nyt polku
   retPath = graph.BFS_Path(start_node, end_node);

   //Polku on olemassa?
   if(retPath == Graph::PATH_EXIST)
   {
      if(display_messages)
      {
         std::cout << "Polku on olemassa." << std::endl;
      }
      
      //Polku ruudulle
      const Graph::PathType& path = graph.GetPath();

      if(display_messages)
      {
         cout << endl;
         board.Print(&path);
         cout << endl;
      }
      //Polku tiedostoon  
      graph.PathToFile(output_file);
      output_file.close();

   }
   else if(retPath  == Graph::NO_PATH)
   {  //Poluton tilanne
      if(display_messages)
      {
         std::cout << "Polkua ei ole." << std::endl;
      }
      output_file << OUTPUT_NO_PATH << endl;
      output_file.close();
   }
   else //INVALID_NODE
   {
      if(display_messages)
      {
         std::cout << "Polkua ei ole. Oikean alanurkan ruutu oli varattu?" << std::endl;
      }
      output_file << OUTPUT_NO_PATH << endl;
      output_file.close();
   }

}
