#include <string>
#include <string_view>
#ifdef CATCH2
#include "catch.hpp"
#else
#include "doctest.h"
#endif
#include "../cplusplus/ls_presentation.h"

// string_view usage discussion
// https://quuxplusone.github.io/blog/2018/03/27/string-view-is-a-borrow-type/
// https://github.com/isocpp/CppCoreGuidelines/issues/1038
// https://dzone.com/articles/performance-of-stdstring-view-vs-stdstring-from-c1

static std::string_view compose(std::string& s);
//static void comp(std::string& s, unsigned long n, std::string_view ans);


static std::string_view compose(std::string& s)
{
   using namespace std;
   using namespace LS;

   auto item = FooStack::pop_from_stack();
   while(item != nullptr)
   {
      s += item;
      item = FooStack::pop_from_stack();
   }

   return string_view(s);
}
#if 0
static void comp(std::string& s, unsigned long n, std::string_view ans)
{
   using namespace std;
   using namespace LS;

   INFO("Test n = " << n << "( " << ans << " )");
   make_string_presentation(n);
   auto ret = compose(s);
   REQUIRE(ret == ans);
}
#endif
#ifdef CATCH2

//---------------------------------------------------------------------------
#else
TEST_CASE( "number spell out 0" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 0;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"nolla");
   }

}

TEST_CASE( "number spell out 1" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yksi");
   }

}

TEST_CASE( "number spell out 2" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksi");
   }

}

TEST_CASE( "number spell out 3" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 3;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kolme");
   }

}

TEST_CASE( "number spell out 4" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 4;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"neljä");
   }

}

TEST_CASE( "number spell out 5" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 5;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"viisi");
   }

}

TEST_CASE( "number spell out 6" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 6;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kuusi");
   }

}

TEST_CASE( "number spell out 7" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 7;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"seitsemän");
   }

}

TEST_CASE( "number spell out 8" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 8;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kahdeksan");
   }

}

TEST_CASE( "number spell out 9" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 9;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksän");
   }

}

TEST_CASE( "number spell out 10" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 10;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kymmenen");
   }

}

TEST_CASE( "number spell out 11" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 11;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yksitoista");
   }

}

TEST_CASE( "number spell out 12" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 12;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksitoista");
   }

}

TEST_CASE( "number spell out 13" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 13;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kolmetoista");
   }

}

TEST_CASE( "number spell out 14" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 14;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"neljätoista");
   }

}

TEST_CASE( "number spell out 15" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 15;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"viisitoista");
   }

}

TEST_CASE( "number spell out 16" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 16;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kuusitoista");
   }

}

TEST_CASE( "number spell out 17" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 17;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"seitsemäntoista");
   }

}

TEST_CASE( "number spell out 18" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 18;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kahdeksantoista");
   }

}

TEST_CASE( "number spell out 19" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 19;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksäntoista");
   }

}

TEST_CASE( "number spell out 20" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 20;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksikymmentä");
   }

}

TEST_CASE( "number spell out 21" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 21;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksikymmentäyksi");
   }

}

TEST_CASE( "number spell out 22" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 22;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksikymmentäkaksi");
   }

}

TEST_CASE( "number spell out 23" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 23;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksikymmentäkolme");
   }

}

TEST_CASE( "number spell out 24" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 24;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksikymmentäneljä");
   }

}

TEST_CASE( "number spell out 25" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 25;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksikymmentäviisi");
   }

}

TEST_CASE( "number spell out 29" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 29;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksikymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 30" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 30;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kolmekymmentä");
   }

}

TEST_CASE( "number spell out 31" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 31;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kolmekymmentäyksi");
   }

}

TEST_CASE( "number spell out 32" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 32;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kolmekymmentäkaksi");
   }

}

TEST_CASE( "number spell out 39" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 39;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kolmekymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 40" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 40;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"neljäkymmentä");
   }

}

TEST_CASE( "number spell out 41" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 41;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"neljäkymmentäyksi");
   }

}

TEST_CASE( "number spell out 49" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 49;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"neljäkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 50" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 50;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"viisikymmentä");
   }

}

TEST_CASE( "number spell out 55" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 55;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"viisikymmentäviisi");
   }

}

TEST_CASE( "number spell out 60" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 60;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kuusikymmentä");
   }

}

TEST_CASE( "number spell out 70" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 70;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"seitsemänkymmentä");
   }

}

TEST_CASE( "number spell out 80" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 80;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kahdeksankymmentä");
   }

}

TEST_CASE( "number spell out 90" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 90;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksänkymmentä");
   }

}

TEST_CASE( "number spell out 99" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 99;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 100" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 100;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"sata");
   }

}

TEST_CASE( "number spell out 101" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 101;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"satayksi");
   }

}

TEST_CASE( "number spell out 119" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 119;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"satayhdeksäntoista");
   }

}

TEST_CASE( "number spell out 120" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 120;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"satakaksikymmentä");
   }

}

TEST_CASE( "number spell out 121" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 121;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"satakaksikymmentäyksi");
   }

}

TEST_CASE( "number spell out 159" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 159;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"sataviisikymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 199" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 199;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"satayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 200" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 200;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksisataa");
   }

}

TEST_CASE( "number spell out 218" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 218;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksisataakahdeksantoista");
   }

}

TEST_CASE( "number spell out 318" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 318;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kolmesataakahdeksantoista");
   }

}

TEST_CASE( "number spell out 569" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 569;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"viisisataakuusikymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 999" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 999;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksänsataayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 1000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat");
   }

}

TEST_CASE( "number spell out 1001" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1001;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat yksi");
   }

}
#endif


