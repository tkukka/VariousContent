#include <string>
#ifdef CATCH2
#include "catch.hpp"
#else
#include "doctest.h"
#endif
#include "../cplusplus/ls_input.h"
#ifdef CATCH2

TEST_CASE( "input validation 1", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{""};
   unsigned long n{0};

   SECTION( "Empty input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 2", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"-"};
   unsigned long n{0};

   SECTION( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 3", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"+"};
   unsigned long n{0};

   SECTION( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 4", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"."};
   unsigned long n{0};

   SECTION( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 5", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"+7"};
   unsigned long n{0};

   SECTION( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 6", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"-8"};
   unsigned long n{0};

   SECTION( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 7", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"9."};
   unsigned long n{0};

   SECTION( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 8", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{" "};
   unsigned long n{0};

   SECTION( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 9", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"1 1"};
   unsigned long n{0};

   SECTION( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 10", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{" 12"};
   unsigned long n{0};

   SECTION( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 11", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"12 "};
   unsigned long n{0};

   SECTION( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 12", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"14a"};
   unsigned long n{0};

   SECTION( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 13", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"15e2"};
   unsigned long n{0};

   SECTION( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 14", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"10000001"}; // yli 10 milj.
   unsigned long n{0};

   SECTION( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 15", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"010000001"}; // yli 10 milj.
   unsigned long n{0};

   SECTION( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 16", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"0000000000000000000000000000000000000010000001"}; // yli 10 milj.
   unsigned long n{0};

   SECTION( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 17", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"10000002"}; // yli 10 milj.
   unsigned long n{0};

   SECTION( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 18", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"0"};
   unsigned long n{0};

   SECTION( "OK input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_OK);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 19", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"00"};
   unsigned long n{0};

   SECTION( "OK input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_OK);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 20", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"000000000000000000000000000000000000000000000"};
   unsigned long n{0};

   SECTION( "OK input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_OK);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 21", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"000000000000000000000000000000000000000000001"};
   unsigned long n{0};

   SECTION( "OK input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_OK);
        REQUIRE(n == 1);
    }
}

TEST_CASE( "input validation 23", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"1"};
   unsigned long n{0};

   SECTION( "OK input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_OK);
        REQUIRE(n == 1);
    }
}

TEST_CASE( "input validation 24", "[validate_and_convert_input]" ) {
   using namespace LS;
   std::string s{"499999"};
   unsigned long n{0};

   SECTION( "OK input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_OK);
        REQUIRE(n == 499999);
    }
}
//---------------------------------------------------------------------------
#else
TEST_CASE( "input validation 1" ) {
   using namespace LS;
   std::string s{""};
   unsigned long n{0};

   SUBCASE( "Empty input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 2") {
   using namespace LS;
   std::string s{"-"};
   unsigned long n{0};

   SUBCASE( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 3" ) {
   using namespace LS;
   std::string s{"+"};
   unsigned long n{0};

   SUBCASE( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 4" ) {
   using namespace LS;
   std::string s{"."};
   unsigned long n{0};

   SUBCASE( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 5" ) {
   using namespace LS;
   std::string s{"+7"};
   unsigned long n{0};

   SUBCASE( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 6" ) {
   using namespace LS;
   std::string s{"-8"};
   unsigned long n{0};

   SUBCASE( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 7" ) {
   using namespace LS;
   std::string s{"9."};
   unsigned long n{0};

   SUBCASE( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 8" ) {
   using namespace LS;
   std::string s{" "};
   unsigned long n{0};

   SUBCASE( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 9" ) {
   using namespace LS;
   std::string s{"1 1"};
   unsigned long n{0};

   SUBCASE( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 10" ) {
   using namespace LS;
   std::string s{" 12"};
   unsigned long n{0};

   SUBCASE( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 11") {
   using namespace LS;
   std::string s{"12 "};
   unsigned long n{0};

   SUBCASE( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 12") {
   using namespace LS;
   std::string s{"14a"};
   unsigned long n{0};

   SUBCASE( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 13" ) {
   using namespace LS;
   std::string s{"15e2"};
   unsigned long n{0};

   SUBCASE( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 14" ) {
   using namespace LS;
   std::string s{"10000001"}; // yli 10 milj.
   unsigned long n{0};

   SUBCASE( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 15") {
   using namespace LS;
   std::string s{"010000001"}; // yli 10 milj.
   unsigned long n{0};

   SUBCASE( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 16" ) {
   using namespace LS;
   std::string s{"0000000000000000000000000000000000000010000001"}; // yli 10 milj.
   unsigned long n{0};

   SUBCASE( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 17" ) {
   using namespace LS;
   std::string s{"10000002"}; // yli 10 milj.
   unsigned long n{0};

   SUBCASE( "Invalid input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_ERROR);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 18") {
   using namespace LS;
   std::string s{"0"};
   unsigned long n{0};

   SUBCASE( "OK input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_OK);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 19" ) {
   using namespace LS;
   std::string s{"00"};
   unsigned long n{0};

   SUBCASE( "OK input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_OK);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 20" ) {
   using namespace LS;
   std::string s{"000000000000000000000000000000000000000000000"};
   unsigned long n{0};

   SUBCASE( "OK input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_OK);
        REQUIRE(n == 0);
    }
}

TEST_CASE( "input validation 21" ) {
   using namespace LS;
   std::string s{"000000000000000000000000000000000000000000001"};
   unsigned long n{0};

   SUBCASE( "OK input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_OK);
        REQUIRE(n == 1);
    }
}

TEST_CASE( "input validation 23" ) {
   using namespace LS;
   std::string s{"1"};
   unsigned long n{0};

   SUBCASE( "OK input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_OK);
        REQUIRE(n == 1);
    }
}

TEST_CASE( "input validation 24" ) {
   using namespace LS;
   std::string s{"499999"};
   unsigned long n{0};

   SUBCASE( "OK input string" ) {
        REQUIRE(InputHandler::validate_and_convert_input(s, n) == InputStatus::INPUT_OK);
        REQUIRE(n == 499999);
    }
}

#endif

