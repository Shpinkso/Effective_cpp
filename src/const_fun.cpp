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


static unsigned int calls = 0;

class TextBlock{
    private:
    std::string data;
    public:
    TextBlock():data("hello"){};
    const char& operator[](std::size_t position) const
    {
        calls++;
        if(position < data.size())
        {
            return data[position];
        }
        return data[0];
    }
    // and now the non-const overload
    char& operator[](std::size_t position)
    {
        calls++;
        return const_cast<char&>(
            static_cast<const TextBlock&>(*this)[position]
        );
    }

};

TEST_CASE("Overloading array dereference", "[Const the data]") {
    TextBlock T;
    TextBlock const ST;
    char c;
    REQUIRE(calls == 0);
    c = T[1];
    REQUIRE(calls == 2);
    calls = 0;
    c = ST[1];
    REQUIRE(calls == 1);
    REQUIRE(c == 'e');
}