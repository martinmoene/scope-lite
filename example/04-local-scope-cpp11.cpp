#include "nonstd/scope.hpp"

int global = 1;

int main()
{
    // local resource to be processed at cleanup:

    { int & resource = global; auto guard = nonstd::make_scope_exit( [&](){ resource = 42; } ); }

    return global;
}

// cl -nologo -EHsc -I../include 04-local-scope-cpp11.cpp && 04-local-scope-cpp11
// echo %ERRORLEVEL%

// g++ -std=c++11 -Wall -I../include -o 04-local-scope-cpp11 04-local-scope-cpp11.cpp && ./04-local-scope-cpp11 || echo $?
