#include <string>
#ifdef CATCH2
#include "catch.hpp"
#else
#include "doctest.h"
#endif
#include "../cplusplus/ls_stack.h"
#ifdef CATCH2
TEST_CASE( "stack operation 1", "[stack]" ) {
   using namespace LS;

   INFO("Stack Test case 1");
   FooStack::init_stack();
   FooStack::clear_stack();

   SECTION( "push" ) {
        NodeDataType t = " - 1. test\n";
        REQUIRE(FooStack::push_to_stack(t) == 1);
        REQUIRE(FooStack::get_stack_size() == 1);
        FooStack::print_stack();
    }
}

TEST_CASE( "stack operation 2", "[stack]" ) {
   using namespace LS;

   INFO("Stack Test case 2");
   FooStack::init_stack();
   FooStack::clear_stack();

   SECTION( "push pop 1" ) {
        NodeDataType t = "2. test";
        REQUIRE(FooStack::push_to_stack(t) == 1);
        REQUIRE(FooStack::get_stack_size() == 1);
        FooStack::print_stack();
        auto r = FooStack::pop_from_stack();
        std::string s{r};
        REQUIRE(FooStack::get_stack_size() == 0);
        REQUIRE(s == "2. test");

    }

   SECTION( "push pop 2" ) {
        NodeDataType t = "3. test";
        REQUIRE(FooStack::push_to_stack(t) == 1);
        REQUIRE(FooStack::push_to_stack(t) == 1);
        REQUIRE(FooStack::push_to_stack(t) == 1);
        REQUIRE(FooStack::push_to_stack(t) == 1);
        REQUIRE(FooStack::push_to_stack(t) == 1);
        REQUIRE(FooStack::get_stack_size() == 5);
        FooStack::print_stack();
        FooStack::clear_stack();
        REQUIRE(FooStack::get_stack_size() == 0);
        auto r = FooStack::pop_from_stack();
        REQUIRE(r == nullptr);

    }

}

TEST_CASE( "stack operation 3", "[stack]" ) {
   using namespace LS;

   INFO("Stack Test case 3");
   FooStack::init_stack();
   FooStack::clear_stack();

   SECTION( "push pop" ) {
        NodeDataType t = "test 4";
        NodeDataType t2 = "test -";
        REQUIRE(FooStack::push_to_stack(t) == 1);
        REQUIRE(FooStack::push_to_stack(t2) == 1);
        auto r = FooStack::pop_from_stack();
        r = FooStack::pop_from_stack();
        std::string s{r};
        REQUIRE(s == "test 4");
    }
}

TEST_CASE( "stack operation 4", "[stack]" ) {
   using namespace LS;

   INFO("Stack Test case 4");
   FooStack::init_stack();
   //FooStack::clear_stack();

   SECTION( "push to limit" ) {
        NodeDataType t = "test 5";
        FooStack::clear_stack();
        int i;
        for (i = 0; i < 500; ++i)
        {
          auto r = FooStack::push_to_stack(t);
          if (!r)
          {
             break;
          }
        }
        REQUIRE(FooStack::get_stack_size() == 25);
        REQUIRE(i == 25);
    }


    SECTION( "clear" ) {
        FooStack::clear_stack();
        REQUIRE(FooStack::get_stack_size() == 0);
    }

}
//---------------------------------------------------------------------------
#else
TEST_CASE( "stack operation 1" ) {
   using namespace LS;

   INFO("Stack Test case 1");
   FooStack::init_stack();
   FooStack::clear_stack();

   SUBCASE( "push" ) {
        NodeDataType t = " - 1. test\n";
        REQUIRE(FooStack::push_to_stack(t) == 1);
        REQUIRE(FooStack::get_stack_size() == 1);
        FooStack::print_stack();
    }
}

TEST_CASE( "stack operation 2") {
   using namespace LS;

   INFO("Stack Test case 2");
   FooStack::init_stack();
   FooStack::clear_stack();

   SUBCASE( "push pop 1" ) {
        NodeDataType t = "2. test";
        REQUIRE(FooStack::push_to_stack(t) == 1);
        REQUIRE(FooStack::get_stack_size() == 1);
        FooStack::print_stack();
        auto r = FooStack::pop_from_stack();
        std::string s{r};
        REQUIRE(FooStack::get_stack_size() == 0);
        REQUIRE(s == "2. test");

    }

   SUBCASE( "push pop 2" ) {
        NodeDataType t = "3. test";
        REQUIRE(FooStack::push_to_stack(t) == 1);
        REQUIRE(FooStack::push_to_stack(t) == 1);
        REQUIRE(FooStack::push_to_stack(t) == 1);
        REQUIRE(FooStack::push_to_stack(t) == 1);
        REQUIRE(FooStack::push_to_stack(t) == 1);
        REQUIRE(FooStack::get_stack_size() == 5);
        FooStack::print_stack();
        FooStack::clear_stack();
        REQUIRE(FooStack::get_stack_size() == 0);
        auto r = FooStack::pop_from_stack();
        REQUIRE(r == nullptr);

    }

}

TEST_CASE( "stack operation 3" ) {
   using namespace LS;

   INFO("Stack Test case 3");
   FooStack::init_stack();
   FooStack::clear_stack();

   SUBCASE( "push pop" ) {
        NodeDataType t = "test 4";
        NodeDataType t2 = "test -";
        REQUIRE(FooStack::push_to_stack(t) == 1);
        REQUIRE(FooStack::push_to_stack(t2) == 1);
        auto r = FooStack::pop_from_stack();
        r = FooStack::pop_from_stack();
        std::string s{r};
        REQUIRE(s == "test 4");
    }
}

TEST_CASE( "stack operation 4" ) {
   using namespace LS;

   INFO("Stack Test case 4");
   FooStack::init_stack();
   //FooStack::clear_stack();

   SUBCASE( "push to limit" ) {
        NodeDataType t = "test 5";
        FooStack::clear_stack();
        int i;
        for (i = 0; i < 500; ++i)
        {
          auto r = FooStack::push_to_stack(t);
          if (!r)
          {
             break;
          }
        }
        REQUIRE(FooStack::get_stack_size() == 25);
        REQUIRE(i == 25);
    }


    SUBCASE( "clear" ) {
        FooStack::clear_stack();
        REQUIRE(FooStack::get_stack_size() == 0);
    }

}
#endif

