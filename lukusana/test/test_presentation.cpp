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
TEST_CASE( "number spell out 0", "[spell-out]" ) {
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

TEST_CASE( "number spell out 1", "[spell-out]" ) {
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

TEST_CASE( "number spell out 2", "[spell-out]" ) {
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

TEST_CASE( "number spell out 3", "[spell-out]" ) {
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

TEST_CASE( "number spell out 4", "[spell-out]" ) {
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

TEST_CASE( "number spell out 5", "[spell-out]" ) {
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

TEST_CASE( "number spell out 6", "[spell-out]" ) {
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

TEST_CASE( "number spell out 7", "[spell-out]" ) {
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

TEST_CASE( "number spell out 8", "[spell-out]" ) {
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

TEST_CASE( "number spell out 9", "[spell-out]" ) {
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

TEST_CASE( "number spell out 10", "[spell-out]" ) {
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

TEST_CASE( "number spell out 11", "[spell-out]" ) {
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

TEST_CASE( "number spell out 12", "[spell-out]" ) {
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

TEST_CASE( "number spell out 13", "[spell-out]" ) {
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

TEST_CASE( "number spell out 14", "[spell-out]" ) {
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

TEST_CASE( "number spell out 15", "[spell-out]" ) {
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

TEST_CASE( "number spell out 16", "[spell-out]" ) {
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

TEST_CASE( "number spell out 17", "[spell-out]" ) {
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

TEST_CASE( "number spell out 18", "[spell-out]" ) {
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

TEST_CASE( "number spell out 19", "[spell-out]" ) {
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

TEST_CASE( "number spell out 20", "[spell-out]" ) {
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

TEST_CASE( "number spell out 21", "[spell-out]" ) {
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

TEST_CASE( "number spell out 22", "[spell-out]" ) {
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

TEST_CASE( "number spell out 23", "[spell-out]" ) {
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

TEST_CASE( "number spell out 24", "[spell-out]" ) {
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

TEST_CASE( "number spell out 25", "[spell-out]" ) {
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

TEST_CASE( "number spell out 29", "[spell-out]" ) {
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

TEST_CASE( "number spell out 30", "[spell-out]" ) {
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

TEST_CASE( "number spell out 31", "[spell-out]" ) {
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

TEST_CASE( "number spell out 32", "[spell-out]" ) {
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

TEST_CASE( "number spell out 39", "[spell-out]" ) {
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

TEST_CASE( "number spell out 40", "[spell-out]" ) {
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

TEST_CASE( "number spell out 41", "[spell-out]" ) {
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

TEST_CASE( "number spell out 49", "[spell-out]" ) {
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

TEST_CASE( "number spell out 50", "[spell-out]" ) {
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

TEST_CASE( "number spell out 55", "[spell-out]" ) {
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

TEST_CASE( "number spell out 60", "[spell-out]" ) {
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

TEST_CASE( "number spell out 70", "[spell-out]" ) {
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

TEST_CASE( "number spell out 80", "[spell-out]" ) {
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

TEST_CASE( "number spell out 90", "[spell-out]" ) {
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

TEST_CASE( "number spell out 99", "[spell-out]" ) {
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

TEST_CASE( "number spell out 100", "[spell-out]" ) {
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

TEST_CASE( "number spell out 101", "[spell-out]" ) {
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

TEST_CASE( "number spell out 119", "[spell-out]" ) {
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

TEST_CASE( "number spell out 120", "[spell-out]" ) {
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

TEST_CASE( "number spell out 121", "[spell-out]" ) {
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

TEST_CASE( "number spell out 159", "[spell-out]" ) {
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

TEST_CASE( "number spell out 199", "[spell-out]" ) {
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

TEST_CASE( "number spell out 200", "[spell-out]" ) {
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

TEST_CASE( "number spell out 218", "[spell-out]" ) {
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

TEST_CASE( "number spell out 318", "[spell-out]" ) {
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

TEST_CASE( "number spell out 569", "[spell-out]" ) {
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

TEST_CASE( "number spell out 999", "[spell-out]" ) {
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

TEST_CASE( "number spell out 1000", "[spell-out]" ) {
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

TEST_CASE( "number spell out 1001", "[spell-out]" ) {
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

TEST_CASE( "number spell out 1019", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1019;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat yhdeksäntoista");
   }

}

TEST_CASE( "number spell out 1020", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1020;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat kaksikymmentä");
   }

}

TEST_CASE( "number spell out 1021", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1021;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat kaksikymmentäyksi");
   }

}

TEST_CASE( "number spell out 1099", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1099;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat yhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 1100", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1100;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat sata");
   }

}

TEST_CASE( "number spell out 1102", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1102;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat satakaksi");
   }

}

TEST_CASE( "number spell out 1199", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1199;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat satayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 1200", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1200;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat kaksisataa");
   }

}

TEST_CASE( "number spell out 1205", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1205;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat kaksisataaviisi");
   }

}

TEST_CASE( "number spell out 1250", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1250;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat kaksisataaviisikymmentä");
   }

}

TEST_CASE( "number spell out 1299", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1299;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat kaksisataayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 1300", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1300;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat kolmesataa");
   }

}

TEST_CASE( "number spell out 1999", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1999;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat yhdeksänsataayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 2000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksituhatta");
   }

}

TEST_CASE( "number spell out 2020", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2020;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksituhatta kaksikymmentä");
   }

}

TEST_CASE( "number spell out 2501", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2501;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksituhatta viisisataayksi");
   }

}

TEST_CASE( "number spell out 3000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 3000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kolmetuhatta");
   }

}

TEST_CASE( "number spell out 3018", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 3018;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kolmetuhatta kahdeksantoista");
   }

}

TEST_CASE( "number spell out 9999", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 9999;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksäntuhatta yhdeksänsataayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 10000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 10000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kymmenentuhatta");
   }

}

TEST_CASE( "number spell out 10100", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 10100;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kymmenentuhatta sata");
   }

}

TEST_CASE( "number spell out 15000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 15000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"viisitoistatuhatta");
   }

}

TEST_CASE( "number spell out 21999", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 21999;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksikymmentäyksituhatta yhdeksänsataayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 30000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 30000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kolmekymmentätuhatta");
   }

}

TEST_CASE( "number spell out 52879", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 52879;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"viisikymmentäkaksituhatta kahdeksansataaseitsemänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 72009", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 72009;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"seitsemänkymmentäkaksituhatta yhdeksän");
   }

}

TEST_CASE( "number spell out 99999", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 99999;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksänkymmentäyhdeksäntuhatta yhdeksänsataayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 100000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 100000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"satatuhatta");
   }

}

TEST_CASE( "number spell out 100001", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 100001;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"satatuhatta yksi");
   }

}

TEST_CASE( "number spell out 100100", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 100100;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"satatuhatta sata");
   }

}

TEST_CASE( "number spell out 550310", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 550310;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"viisisataaviisikymmentätuhatta kolmesataakymmenen");
   }

}

TEST_CASE( "number spell out 990800", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 990800;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksänsataayhdeksänkymmentätuhatta kahdeksansataa");
   }

}

TEST_CASE( "number spell out 999999", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 999999;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksänsataayhdeksänkymmentäyhdeksäntuhatta yhdeksänsataayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 1000000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1000000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljoona");
   }

}

TEST_CASE( "number spell out 1000001", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1000001;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljoona yksi");
   }

}

TEST_CASE( "number spell out 1000100", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1000100;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljoona sata");
   }

}

TEST_CASE( "number spell out 1001000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1001000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljoona tuhat");
   }

}

TEST_CASE( "number spell out 1100000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1100000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljoona satatuhatta");
   }

}

TEST_CASE( "number spell out 1500000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1500000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljoona viisisataatuhatta");
   }

}

TEST_CASE( "number spell out 1500001", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1500001;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljoona viisisataatuhatta yksi");
   }

}

TEST_CASE( "number spell out 5000674", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 5000674;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"viisimiljoonaa kuusisataaseitsemänkymmentäneljä");
   }

}

TEST_CASE( "number spell out 5426674", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 5426674;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"viisimiljoonaa neljäsataakaksikymmentäkuusituhatta kuusisataaseitsemänkymmentäneljä");
   }

}

TEST_CASE( "number spell out 45000000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 45000000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"neljäkymmentäviisimiljoonaa");
   }

}

TEST_CASE( "number spell out 99000099", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 99000099;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksänkymmentäyhdeksänmiljoonaa yhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 99999999", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 99999999;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksänkymmentäyhdeksänmiljoonaa yhdeksänsataayhdeksänkymmentäyhdeksäntuhatta yhdeksänsataayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 100000000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 100000000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"satamiljoonaa");
   }

}

TEST_CASE( "number spell out 945000000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 945000000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksänsataaneljäkymmentäviisimiljoonaa");
   }

}

TEST_CASE( "number spell out 1000000000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1000000000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljardi");
   }

}

TEST_CASE( "number spell out 1000000001", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1000000001;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljardi yksi");
   }

}

TEST_CASE( "number spell out 1000001000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1000001000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljardi tuhat");
   }

}

TEST_CASE( "number spell out 1001000000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1001000000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljardi miljoona");
   }

}

TEST_CASE( "number spell out 1001001000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1001001000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljardi miljoona tuhat");
   }

}

TEST_CASE( "number spell out 2000000000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2000000000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksimiljardia");
   }

}

TEST_CASE( "number spell out 2000000001", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2000000001;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksimiljardia yksi");
   }

}

TEST_CASE( "number spell out 2000001000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2000001000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksimiljardia tuhat");
   }

}

TEST_CASE( "number spell out 2000100000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2000100000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksimiljardia satatuhatta");
   }

}

TEST_CASE( "number spell out 2001000000", "[spell-out]" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2001000000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksimiljardia miljoona");
   }

}
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

TEST_CASE( "number spell out 1019" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1019;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat yhdeksäntoista");
   }

}

TEST_CASE( "number spell out 1020" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1020;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat kaksikymmentä");
   }

}

TEST_CASE( "number spell out 1021" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1021;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat kaksikymmentäyksi");
   }

}

TEST_CASE( "number spell out 1099" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1099;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat yhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 1100" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1100;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat sata");
   }

}

TEST_CASE( "number spell out 1102" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1102;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat satakaksi");
   }

}

TEST_CASE( "number spell out 1199" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1199;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat satayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 1200" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1200;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat kaksisataa");
   }

}

TEST_CASE( "number spell out 1205" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1205;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat kaksisataaviisi");
   }

}

TEST_CASE( "number spell out 1250" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1250;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat kaksisataaviisikymmentä");
   }

}

TEST_CASE( "number spell out 1299" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1299;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat kaksisataayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 1300" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1300;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat kolmesataa");
   }

}

TEST_CASE( "number spell out 1999" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1999;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"tuhat yhdeksänsataayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 2000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksituhatta");
   }

}

TEST_CASE( "number spell out 2020" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2020;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksituhatta kaksikymmentä");
   }

}

TEST_CASE( "number spell out 2501" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2501;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksituhatta viisisataayksi");
   }

}

TEST_CASE( "number spell out 3000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 3000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kolmetuhatta");
   }

}

TEST_CASE( "number spell out 3018" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 3018;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kolmetuhatta kahdeksantoista");
   }

}

TEST_CASE( "number spell out 9999" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 9999;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksäntuhatta yhdeksänsataayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 10000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 10000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kymmenentuhatta");
   }

}

TEST_CASE( "number spell out 10100" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 10100;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kymmenentuhatta sata");
   }

}

TEST_CASE( "number spell out 15000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 15000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"viisitoistatuhatta");
   }

}

TEST_CASE( "number spell out 21999" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 21999;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksikymmentäyksituhatta yhdeksänsataayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 30000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 30000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kolmekymmentätuhatta");
   }

}

TEST_CASE( "number spell out 52879" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 52879;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"viisikymmentäkaksituhatta kahdeksansataaseitsemänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 72009" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 72009;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"seitsemänkymmentäkaksituhatta yhdeksän");
   }

}

TEST_CASE( "number spell out 99999" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 99999;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksänkymmentäyhdeksäntuhatta yhdeksänsataayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 100000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 100000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"satatuhatta");
   }

}

TEST_CASE( "number spell out 100001" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 100001;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"satatuhatta yksi");
   }

}

TEST_CASE( "number spell out 100100" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 100100;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"satatuhatta sata");
   }

}

TEST_CASE( "number spell out 550310" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 550310;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"viisisataaviisikymmentätuhatta kolmesataakymmenen");
   }

}

TEST_CASE( "number spell out 990800" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 990800;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksänsataayhdeksänkymmentätuhatta kahdeksansataa");
   }

}

TEST_CASE( "number spell out 999999" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 999999;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksänsataayhdeksänkymmentäyhdeksäntuhatta yhdeksänsataayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 1000000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1000000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljoona");
   }

}

TEST_CASE( "number spell out 1000001" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1000001;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljoona yksi");
   }

}

TEST_CASE( "number spell out 1000100" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1000100;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljoona sata");
   }

}

TEST_CASE( "number spell out 1001000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1001000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljoona tuhat");
   }

}

TEST_CASE( "number spell out 1100000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1100000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljoona satatuhatta");
   }

}

TEST_CASE( "number spell out 1500000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1500000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljoona viisisataatuhatta");
   }

}

TEST_CASE( "number spell out 1500001" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1500001;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljoona viisisataatuhatta yksi");
   }

}

TEST_CASE( "number spell out 5000674" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 5000674;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"viisimiljoonaa kuusisataaseitsemänkymmentäneljä");
   }

}

TEST_CASE( "number spell out 5426674" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 5426674;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"viisimiljoonaa neljäsataakaksikymmentäkuusituhatta kuusisataaseitsemänkymmentäneljä");
   }

}

TEST_CASE( "number spell out 45000000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 45000000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"neljäkymmentäviisimiljoonaa");
   }

}

TEST_CASE( "number spell out 99000099" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 99000099;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksänkymmentäyhdeksänmiljoonaa yhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 99999999" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 99999999;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksänkymmentäyhdeksänmiljoonaa yhdeksänsataayhdeksänkymmentäyhdeksäntuhatta yhdeksänsataayhdeksänkymmentäyhdeksän");
   }

}

TEST_CASE( "number spell out 100000000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 100000000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"satamiljoonaa");
   }

}

TEST_CASE( "number spell out 945000000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 945000000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"yhdeksänsataaneljäkymmentäviisimiljoonaa");
   }

}

TEST_CASE( "number spell out 1000000000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1000000000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljardi");
   }

}

TEST_CASE( "number spell out 1000000001" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1000000001;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljardi yksi");
   }

}

TEST_CASE( "number spell out 1000001000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1000001000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljardi tuhat");
   }

}

TEST_CASE( "number spell out 1001000000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1001000000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljardi miljoona");
   }

}

TEST_CASE( "number spell out 1001001000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 1001001000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"miljardi miljoona tuhat");
   }

}

TEST_CASE( "number spell out 2000000000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2000000000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksimiljardia");
   }

}

TEST_CASE( "number spell out 2000000001" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2000000001;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksimiljardia yksi");
   }

}

TEST_CASE( "number spell out 2000001000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2000001000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksimiljardia tuhat");
   }

}

TEST_CASE( "number spell out 2000100000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2000100000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksimiljardia satatuhatta");
   }

}

TEST_CASE( "number spell out 2001000000" ) {
   using namespace std;
   using namespace LS;

   FooStack::init_stack();
   FooStack::clear_stack();
   REQUIRE(FooStack::get_stack_size() == 0);


   string s;
   unsigned long n = 2001000000;
   make_string_presentation(n);

   {
     auto ret = compose(s);
     REQUIRE(ret == u8"kaksimiljardia miljoona");
   }

}

#endif


