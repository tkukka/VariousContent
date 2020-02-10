/** \file Board.cpp
    Lautaluokan toteutus
*/

#include "Board.h"

//sallittujen merkkien alustus
const char* Board::ALLOWED_CHARS = "EP";

/** 
 * Oletusmuodostin.
 */
Board::Board():width(0), height(0)
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
void Board::Reset(void)
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
Board::FileStatus Board::ReadFile(std::ifstream& infile)
{
   using std::string;
   using std::getline;
   //using std::cout;
   //using std::endl;
   
   //tsekataan onko auki 
   if(infile.is_open() == false)
   {
      return FILE_NOT_OPEN;
   }

   string::size_type char_index;     //Ilmaisee paikan, miss� haettu merkki on
   string::size_type row_length = 0; //Rivin leveys tiedostossa
   bool first_row_measured = false;  //Rivin leveys luetaan 1. rivilt�. T�m� lippu apuna.
   string line;   //Luettu tekstirivi
   int rows = 0;  //Tiedostosta luettujen rivien lukum��r�

   //Nollataan laudan tiedot
   Reset();

   //K�yd��n l�pi tiedoston rivit kunnes tiedosto loppuu
   while(infile.eof() == false)
   {
      getline(infile, line); //luetaan rivi
      
      //Onko tyhj� rivi?
      if(line.empty())
      {
         //Tiedosto ei lopussa viel�?
         if(infile.eof() == false)
         {  //keskell� tiedostoa tyhj� rivi => virhe
            return FILE_FORMAT_ERROR;
         }

         //Viimeinen rivi voi olla tyhj�. Poistutaan ilman h�ly�.
         break;
      }

      //Etsit��n v��ri� merkkej�
      char_index = line.find_first_not_of(ALLOWED_CHARS);
      //L�ytyik� kiellettyj�?
      if(char_index != string::npos) 
      {
         return FILE_FORMAT_ERROR;
      }
      
      //Otetaan yl�s 1. rivin pituus
      if(first_row_measured == false)
      {
         row_length = line.length();
         first_row_measured = true;
      }

      //Tutkitaan jokaisen luetun rivin pituus
      if(row_length != line.length() )
      {
         //cout << "File row len error" << endl;
         return FILE_FORMAT_ERROR;
      }

      //Rivi on OK
      rows++;
      data.push_back(line);
   }
   
   //Otetaan viel� lopussa shakkilaudan mitat
   height = rows;
   width = row_length;
   return READ_OK;
}

/** Tulostaa shakkilaudan ruudulle polun kanssa tai ilman.
 * Sama metodi tulostaa laudalle kuninkaan polun, jos sellainen annetaan.
 * Suurin n�yt�ll� j�rkev�sti toimiva laudan leveys 9 ruutua.
 *
 * @param path Polku, tai 0 jos tulostetaan vain lauta ilman polkua.
 *  
 */
void Board::Print(const Graph::PathType* path) const
{
   using std::cout;
   using std::endl;
   using std::string;

   //ei lautaa
   if (data.empty() == true)
   {
      cout << "Laudassa ei ruutuja" << endl;
      return;
   }

   //Yl�osan vaakaan juoksevat numerot. Sarakkeet.
   for(size_t i = 0; i < width; i++)
   {
      cout << "\t" << i;
   }
   cout << endl;

   //ruudun koordinaatit
   int row = 0;
   int column = 0;
   BoardDataType::const_iterator row_iter = data.begin(); //tekstirivin iteraattori
   
   while(row_iter != data.end())
   {
      cout << row; 
      column = 0;
      
      string::const_iterator char_iter = (*row_iter).begin(); //yksitt�isten merkkien iteraattori
      while(char_iter != (*row_iter).end() )
      {
         //tulostetaan varattu ruutu?
         if((*char_iter) == SQUARE_OCCUPIED)
         {
            cout  << "\t" << (*char_iter);
         }
         else
         { //vapaa ruutu tulostuu

            if(path) //jos polku tulostetaan laudalle
            {
               //pit�� tutkia onko nykyinen vapaa ruutu jossain kohdassa polkua.
               //v�h�n tehotonta...
               Node temp(column, row);
               int index = NodePosition(temp, *path);
               if(index >= 0) //t�m� ruutu on polussa?
               {
                  cout  << "\t" << (index+1) ;
               }
               else
               {
                  cout  << "\t";
               }

            }
            else
            {
               cout  << "\t";
            }
         }

         ++char_iter;
         ++column;
      }
      
      cout << endl;
     
      ++row;
      ++row_iter;
   }

}

/** Hakee, miss� kohtaa polkua on jokin annettu solmu.
 * K�ytet��n apumetodina kun polkua tulostetaan laudalle.
 
 * @param n Haettava solmu
 * @param path Polku, josta solmua haetaan.
 * @return Indeksi (sijainti) polussa
 */
int Board::NodePosition(const Node& n, const Graph::PathType& path) const
{
   Graph::PathType::const_iterator iter = path.begin(); //Solmujen iteraattori
   int position = 0; //sijainti polussa. 0 = ensimm�inen

   while(iter != path.end())
   {
      if( (*iter) == n) //l�ytyi?
      {
         return position;
      }
      ++iter;
      ++position;
   }
   //ei ole polussa
   return -1;
}

/** Muuttaa laudan graafiksi.
 * @param graph Graafi, johon solmut tallennetaan.
 */
void Board::ConvertToGraph(Graph& graph) const
{
   //using std::cout;
   //using std::endl;
   using std::string;

   //ei lautaa mist� ottaa ruutuja?
   if (data.empty() == true)
   {
      return;
   }

   //tehd��n laudasta kopio, koska lis�t��n kaksi rivi� varattuja ruutuja.
   BoardDataType copy_data = data;
   int row_length = static_cast<int>(copy_data[0].length()); //laudan rivin leveys yl�s
   string filler(row_length, SQUARE_OCCUPIED);    //tehd��n t�yterivi varatuista ruuduista
  
   //Lis�t��n nyt 2 apurivi� indeksoinnin helpottamiseksi
   BoardDataType::iterator first_element = copy_data.begin();
   copy_data.insert(first_element, filler); //rivi laudan alkuun
   copy_data.push_back(filler);             //rivi laudan loppuun

   //montako rivi� laudassa nyt, otetaan yl�s silmukkaa varten
   int row_count = static_cast<int>(copy_data.size());
  
   int counter = 0; //montako solmua, joilla oli vierussolmuja
   int actual_row = 0; //seuraa todellista rivi� alkuper�isessa laudassa
   Graph::AdjType adj_nodes;         //ker�� vierussolmut

   //kierret��n rivej� alkaen toisesta rivist� aina toiseksi viimeiseen asti
   for(int i = 1; i < (row_count-1); i++, actual_row++)
   {
      //otetaan yl�s kolme rivi� laudasta: edellinen, nykyinen ja seuraava.
      const string& prev_row = copy_data[i-1];
      const string& current_row = copy_data[i];
      const string& next_row = copy_data[i+1];

      //kierret��n sarakkeita (yksitt�isi� merkkej� rivill�)
      for(int j = 0; j < row_length; j++)
      {
         adj_nodes.clear();

         //cout << "(" << j << ", " << actual_row  << "): ";
        
         Node current_node(j, actual_row); //Tehd��n t�st� nykyisest� ruudusta solmu.

         //onko nykyinen ruutu tyhj�?
         if (current_row[j] == SQUARE_FREE) 
         {
            /* Tutkitaan 8 naapuriruutua. J�rjestys:
             *    1 2 3
             *    4   5
             *    6 7 8
             */

            if(j > 0)     /* 1 */
            {
               if(prev_row[j-1] == SQUARE_FREE) 
               {
                  //cout << "(" << j-1 << ", " << actual_row-1 << ") ";
                  //oli vapaa, lis�t��n vierussolmuksi
                  Node n(j-1, actual_row-1);
                  adj_nodes.push_back(n);

               }
            }

            if(prev_row[j] == SQUARE_FREE)  /* 2 */
            {
               //cout << "(" << j << ", " << actual_row-1 << ") ";
               //oli vapaa, lis�t��n vierussolmuksi
               Node n(j, actual_row-1);
               adj_nodes.push_back(n);
            }

            if(j < (row_length-1))  /* 3 */
            {
               if(prev_row[j+1] == SQUARE_FREE) 
               {
                  //cout << "(" << j+1 << ", " << actual_row-1 << ") ";
                  //oli vapaa, lis�t��n vierussolmuksi
                  Node n(j+1, actual_row-1);
                  adj_nodes.push_back(n);
               }
             
            }

            if(j > 0)   /* 4 */
            {
               if (current_row[j-1] == SQUARE_FREE) 
               {
                  //cout << "(" << j-1 << ", " << actual_row << ") ";
                  //oli vapaa, lis�t��n vierussolmuksi                  
                  Node n(j-1, actual_row);
                  adj_nodes.push_back(n);
               }
            }

            if(j < (row_length-1))  /* 5 */
            {
               if (current_row[j+1] == SQUARE_FREE) 
               {
                  //cout << "(" << j+1 << ", " << actual_row << ") ";
                  //oli vapaa, lis�t��n vierussolmuksi                  
                  Node n(j+1, actual_row);
                  adj_nodes.push_back(n);
               }
            }

            if(j > 0)  /* 6 */
            {
               if (next_row[j-1] == SQUARE_FREE) 
               {
                  //cout << "(" << j-1 << ", " << actual_row+1 << ") ";
                  //oli vapaa, lis�t��n vierussolmuksi
                  Node n(j-1, actual_row+1);
                  adj_nodes.push_back(n);
               }
            }

            if (next_row[j] == SQUARE_FREE)  /* 7 */
            {
               //std::cout << "(" << j << ", " << actual_row+1 << ") ";
               //oli vapaa, lis�t��n vierussolmuksi
               Node n(j, actual_row+1);
               adj_nodes.push_back(n);
            }

            if(j < (row_length-1))  /* 8 */
            {
               if (next_row[j+1] == SQUARE_FREE) 
               {
                  //std::cout << "(" << j+1 << ", " << actual_row+1 << ") ";
                  //oli vapaa, lis�t��n vierussolmuksi
                  Node n(j+1, actual_row+1);
                  adj_nodes.push_back(n);
               }
            }

         } //if ( current_row[j] == SQUARE_FREE  )

         //Ei lis�t� yksin�isi� vapaita shakkiruutuja graafiin
         if(adj_nodes.empty() == false )
         {
            counter++;
            graph.AddNodes(current_node, adj_nodes);
         }

      } //for (sarakkeet)

   } //for (rivit)

   //std::cout << "Solmuja oli " << counter << std::endl;
}

/** Palauttaa laudan leveyden ja korkeuden.
 *
 * @param w Leveys
 * @param h Korkeus
 *  
 */
void Board::GetDimension(int* w, int* h) const
{
   *w = static_cast<int>(width);
   *h = static_cast<int>(height);
}
