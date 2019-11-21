#include <string>
#include "catch.hpp"
#include <iostream>


/***************************************************************************************************/
/* Item 1: C++ is a confedoration of languages: C, Object Orientated C++, Template C++ and The STL */
/***************************************************************************************************/

/***************************************************************************************************/
/* Item 2: Prefer consts, enums and inlines to #defines                                            */
/***************************************************************************************************/
/* No symbolic name is created by the compiler 
   any debug messages will refer only to the value  
   and not the name of the value */
#define ASPECT_RATIO 1.653
const double AspectRatio = 1.653; /* Creates a symbol and can actually yield smaller 
                                    code, as a straight pre-proc sub may create multiple copies */

// Constant pointers
const char * const authorNameNative = "Paul Blay"; // Two const's for a native const string
const std::string authorNameString = "Paul Blay"; // String class probably better than char* in c++

// Class constants
class Const{
    private:
        static const int myConst = 4; // Ensure const is static so there's only one
        // can't be done with #define as they do not respect scope.
};

// Class constant during compliation of the class
class ConstComp{
    private:
        enum{NumTurns = 5}; /* The enum trick - for compilers that (incorrectly) forbid 
                               the in-class specification of intial values for static integral
                               class constants */
        /* ... */
        int scrores[NumTurns];
};

// Let's test how substitution can do us over
#define IS_GREATER(a,b) ((a) > (b) ? (a) : (b))

// the irony is that these test cases are clearly pre-procesor macros =D
TEST_CASE("#define increment once", "[Item 2.2]") {
    int a=5,b=0;
    IS_GREATER(++a,b+10);
    REQUIRE(a == 6); // Lovely, as you might expect, ++a == 6
    // ((++a) > (b+10) is false so (b)
}

TEST_CASE("#define increment twice", "[Item 2.1]") {
    int a=5,b=0;
    IS_GREATER(++a,b);
    REQUIRE(a == 7); // WHAT?! A is incremented twice
    // ((++a) > (b) is true, so (++a)
}

// A solution

template<typename T>
inline T isGreater(const T& a, const T& b)
{
    return (a > b ? a : b);
}

TEST_CASE("inline increment once", "[Item 2.3]") {
    int a=5,b=0;
    (void)isGreater(++a,b+10);
    REQUIRE(a == 6); // Lovely, as you might expect, ++a == 6
}

TEST_CASE("inline still increment once", "[Item 2.4]") {
    int a=5,b=0;
    (void)isGreater(++a,b);
    REQUIRE(a == 6); // Lovely, as you might expect, ++a == 6
}

/***************************************************************************************************/
/*
/***************************************************************************************************/

/***************************************************************************************************/
/* Item 20: User defined types should be passed as 'reference to const'                            */
/***************************************************************************************************/