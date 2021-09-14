// #include "nonstd/scope.hpp"

int global = 1;

int main()
{
    // local scope:
    {
        // local resource to be processed at cleanup:

        int & resource = global;

#if 0
        nonstd::scope_exit<...> guard = nonstd::make_scope_exit( cleanup(resource) );
#else
        // cannot be template at block scope:

        struct cleanup
        {
            int & resource;

            cleanup( int & resource_ )
            : resource( resource_)
            {}

            ~cleanup()
            {
                resource = 42;
            }
        };

        cleanup guard( resource );

        // code using resource:
        // ...
#endif
    } // end local scope

    return global;
}

// g++ -std=c++98 -Wall -I../include -o 04-local-scope-cpp98-handwritten 04-local-scope-cpp98-handwritten.cpp && ./04-local-scope-cpp98-handwritten || echo $?
