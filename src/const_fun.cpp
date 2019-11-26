#include <string>
#include "catch.hpp"
#include <iostream>


TEST_CASE("A const mess", "[Const the data]") {
    int a1 = 40;            // Some data
    const int* b1 = &a1;    // Pointer to const data (the non-const data we just defined)
    a1 = 41;
    REQUIRE(*b1 == 41);

    char* c1 = (char*)(b1); // New non const pointer to char cast const ... blegh *explode*
    *c1 = 'A';
    REQUIRE(*c1 == 'A');
    REQUIRE(*b1 == (int)'A');
}


