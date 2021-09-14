#include "nonstd/scope.hpp"

int global = 1;

void function()
{
    ++global;
}

template< typename T >
struct functor
{
    T & resource;

    functor( T & resource_ )
    : resource( resource_)
    {}

    void operator()()
    {
        resource += 40;
    }
};

int main()
{
    // scope 1:
    {
        nonstd::scope_exit</*void(*)()*/> guard = nonstd::make_scope_exit( function );

        // code using resource:
        // ...
        // guard.release();
    } // end scope 1

    // scope 2:
    {
        // local resource to be processed at cleanup:
        // class functor cannot be local.

        int & resource = global;

        nonstd::scope_exit<functor<int> > guard = nonstd::make_scope_exit( functor<int>(resource) );

        // code using resource:
        // ...
        // guard.release();
    } // end scope 2

    return global;
}

// g++ -std=c++98 -Wall -I../include -o 04-local-scope-cpp98 04-local-scope-cpp98.cpp && ./04-local-scope-cpp98 || echo $?
// 42 // (1 + 1 + 40)
