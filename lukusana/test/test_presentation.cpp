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

#endif


