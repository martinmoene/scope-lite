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

void on_exit()
{
    is_called = true;
    std::cout << "On exit.\n";
}

void on_fail()
{
    is_called = true;
    std::cout << "On fail.\n";
}

void on_success()
{
    is_called = true;
    std::cout << "On success.\n";
}

CASE( "scope_exit: exit function is called at end of scope" )
{
    is_called = false;

    // scope:
    {
#if scope_USE_POST_CPP98_VERSION
        auto guard = make_scope_exit( on_exit );
#else
        scope_exit guard = make_scope_exit( on_exit );
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
        auto guard = make_scope_exit( on_exit );
#else
        scope_exit guard = make_scope_exit( on_exit );
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
        auto guard = make_scope_exit( on_exit );
#else
        scope_exit guard = make_scope_exit( on_exit );
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
        auto guard = make_scope_fail( on_fail );
#else
        scope_fail guard = make_scope_fail( on_fail );
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
        auto guard = make_scope_fail( on_fail );
#else
        scope_fail guard = make_scope_fail( on_fail );
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
        auto guard = make_scope_fail( on_fail );
#else
        scope_fail guard = make_scope_fail( on_fail );
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
        auto guard = make_scope_success( on_success );
#else
        scope_success guard = make_scope_success( on_success );
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
        auto guard = make_scope_success( on_success );
#else
        scope_success guard = make_scope_success( on_success );
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
        auto guard = make_scope_success( on_success );
#else
        scope_success guard = make_scope_success( on_success );
#endif
        guard.release();

        // throw std::exception();
    }
    catch(...) {}

    EXPECT_NOT( is_called );
}
