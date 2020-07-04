#include "nonstd/scope.hpp"

#include <cstdio>
#include <iostream>

using namespace nonstd;

namespace fs {

    FILE * open( char const * path, char const * mode )
    {
        std::cout << "Opening file '" << path << "', closing?: ";
        return ::fopen( path, mode );
    }

    void close( FILE * fp )
    {
        std::cout << "yes, closing file\n";
        ::fclose( fp );
    }
}

#if scope_CPP11_110
# define AMP(v) v
#else
# define AMP(v) &(v)
#endif

int main()
{

    { auto file = make_unique_resource_checked(
        fs::open( "03-unique_resource.cpp", "r"), nullptr, AMP( fs::close ) ); }

    { auto file = make_unique_resource_checked(
        fs::open( "potentially_nonexistent_file.txt", "r"), nullptr, AMP( fs::close ) ); }

}

// cl -nologo -EHsc -I../include 03-unique_resource.cpp && 03-unique_resource
// echo %ERRORLEVEL%

// g++ -std=c++11 -Wall -I../include -o 03-unique_resource 03-unique_resource.cpp && ./03-unique_resource || echo $?
