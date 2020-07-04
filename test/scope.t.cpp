//
// Copyright (c) 2020-2020 Martin Moene
//
// https://github.com/martinmoene/scope-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "scope-main.t.hpp"

#include <functional>
#include <iostream>

using namespace nonstd;


static bool is_called = false;

namespace on {

void exit()
{
    is_called = true;
    std::cout << "On exit.\n";
}

void fail()
{
    is_called = true;
    std::cout << "On fail.\n";
}

void success()
{
    is_called = true;
    std::cout << "On success.\n";
}
} // namespace on

CASE( "scope_exit: exit function is called at end of scope" )
{
    is_called = false;

    // scope:
    {
#if scope_USE_POST_CPP98_VERSION
        auto guard = make_scope_exit( on::exit );
#else
        scope_exit guard = make_scope_exit( on::exit );
#endif
    }

    EXPECT( is_called );
}

CASE( "scope_exit: exit function is called at end of scope (lambda)" )
{
#if scope_USE_POST_CPP98_VERSION
    is_called = false;

    // scope:
    {
        auto guard = make_scope_exit( [](){ is_called = true; } );
    }

    EXPECT( is_called );
#else
    EXPECT( !!"lambda is not available (no C++11)" );
#endif
}

CASE( "scope_exit: exit function is called when an exception occurs" )
{
    is_called = false;

    try
    {
#if scope_USE_POST_CPP98_VERSION
        auto guard = make_scope_exit( on::exit );
#else
        scope_exit guard = make_scope_exit( on::exit );
#endif
        throw std::exception();
    }
    catch(...) {}

    EXPECT( is_called );
}

CASE( "scope_exit: exit function is not called at end of scope when released" )
{
    is_called = false;

    // scope:
    {
#if scope_USE_POST_CPP98_VERSION
        auto guard = make_scope_exit( on::exit );
#else
        scope_exit guard = make_scope_exit( on::exit );
#endif
        guard.release();
    }

    EXPECT_NOT( is_called );
}

CASE( "scope_fail: exit function is called when an exception occurs" )
{
    is_called = false;

    try
    {
#if scope_USE_POST_CPP98_VERSION
        auto guard = make_scope_fail( on::fail );
#else
        scope_fail guard = make_scope_fail( on::fail );
#endif
        throw std::exception();
    }
    catch(...) {}

    EXPECT( is_called );
}

CASE( "scope_fail: exit function is not called when no exception occurs" )
{
    is_called = false;

    try
    {
#if scope_USE_POST_CPP98_VERSION
        auto guard = make_scope_fail( on::fail );
#else
        scope_fail guard = make_scope_fail( on::fail );
#endif
        // throw std::exception();
    }
    catch(...) {}

    EXPECT_NOT( is_called );
}

CASE( "scope_fail: exit function is not called when released" )
{
    is_called = false;

    try
    {
#if scope_USE_POST_CPP98_VERSION
        auto guard = make_scope_fail( on::fail );
#else
        scope_fail guard = make_scope_fail( on::fail );
#endif
        guard.release();

        throw std::exception();
    }
    catch(...) {}

    EXPECT_NOT( is_called );
}

CASE( "scope_success: exit function is called when no exception occurs" )
{
    is_called = false;

    try
    {
#if scope_USE_POST_CPP98_VERSION
        auto guard = make_scope_success( on::success );
#else
        scope_success guard = make_scope_success( on::success );
#endif
        // throw std::exception();
    }
    catch(...) {}

    EXPECT( is_called );
}

CASE( "scope_success: exit function is not called when an exception occurs" )
{
    is_called = false;

    try
    {
#if scope_USE_POST_CPP98_VERSION
        auto guard = make_scope_success( on::success );
#else
        scope_success guard = make_scope_success( on::success );
#endif
        throw std::exception();
    }
    catch(...) {}

    EXPECT_NOT( is_called );
}

CASE( "scope_success: exit function is not called when released" )
{
    is_called = false;

    try
    {
#if scope_USE_POST_CPP98_VERSION
        auto guard = make_scope_success( on::success );
#else
        scope_success guard = make_scope_success( on::success );
#endif
        guard.release();

        // throw std::exception();
    }
    catch(...) {}

    EXPECT_NOT( is_called );
}

struct Resource
{
    static int& state()
    {
        static int state_ = 0;
        return state_;
    }

    static int open ( bool success )
    {
        std::cout << "Resource open: " << (success?"success: ":"failure: [no close]\n");
        return state() = success ? 7 : 0;
    }

    static void close( int )
    {
        state() = 42;
        std::cout << "close, state():" << state() << "\n";
    }
};

CASE( "unique_resource: a successfully acquired resource is deleted" )
{
    // scope:
    {
#if scope_USE_POST_CPP98_VERSION
    auto checked_resource = make_unique_resource_checked(
        Resource::open( true ), 0, &Resource::close
    );
#else
    unique_resource<int, void(*)(int)> checked_resource = make_unique_resource_checked(
        Resource::open( true ), 0, &Resource::close // note & (necessary decay is not available)
    );
#endif
    }

    EXPECT( Resource::state() == 42 );
}

CASE( "unique_resource: an unsuccessfully acquired resource is not deleted" )
{
    // scope:
    {
#if scope_USE_POST_CPP98_VERSION
    auto checked_resource = make_unique_resource_checked(
        Resource::open( false ), 0, &Resource::close
    );
#else
    unique_resource<int, void(*)(int)> checked_resource = make_unique_resource_checked(
        Resource::open( false ), 0, &Resource::close // note & (necessary decay is not available)
    );
#endif
    }

    EXPECT( Resource::state() == 0 );
}

CASE( "unique_resource: assign" )
{
}

CASE( "unique_resource: reset()" )
{
}

CASE( "unique_resource: reset(other)" )
{
}

CASE( "unique_resource: release()" )
{
}

CASE( "unique_resource: get()" )
{
}

CASE( "unique_resource: op*()" )
{
}

CASE( "unique_resource: op->()" )
{
}

CASE( "unique_resource: get_deleter()" )
{
}
