#include "nonstd/scope.hpp"

using namespace nonstd;

int count = 0;

namespace on { void exit() { ++count; } }

int main()
{
    { scope_exit<> guard = make_scope_exit(  on::exit ); } // note: on::exit w/o &
    { scope_exit<> guard = make_scope_exit( &on::exit ); } // note: &on::exit

    return count;
}

// g++ -std=c++98 -Wall -I../include -o 01-basic-cpp98 01-basic-cpp98.cpp && ./01-basic-cpp98 || echo $?
