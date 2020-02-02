#include <iostream>
#include <fstream>
#include <string>

static std::string buffer;

#if __cplusplus == 201703L  // C++17
static constexpr int MAX = 120;
#elif __cplusplus == 199711L  // C++98 C++03
#define MAX 120
#endif


int main()
{
   using namespace std;
#if __cplusplus == 201703L
   string filename = u8"eng-uk_web_2002_1M-words.txt";
#elif __cplusplus == 199711L
   string filename = "eng-uk_web_2002_1M-words.txt";
#endif
   buffer.reserve(MAX);

   cout << "C++ file reading '" << filename << "' ... " << endl;
#if __cplusplus == 201703L
   ifstream istrm(filename);
#elif __cplusplus == 199711L
   ifstream istrm(filename.c_str() );
#endif

   if (!istrm.is_open()) {
      cout << "Failed to open " << filename << endl;
      return 1;
   }

   int i = 0;

   while(getline(istrm, buffer)) {
      ++i;
   }

   //if (istrm.eof()) cout << "File EOF" << endl;
   //if (istrm.fail()) cout << "Read error" << endl;

   cout << "Lines: " << i << endl;
   cout << "C++ file reading done." << endl;
   return 0;
}

