//
// Copyright (c) 2020-2020 Martin Moene
//
// https://github.com/martinmoene/scope-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "scope-main.t.hpp"

#define scope_PRESENT( x ) \
    std::cout << #x << ": " << (x) << "\n"

#define scope_ABSENT( x ) \
    std::cout << #x << ": (undefined)\n"

lest::tests & specification()
{
    static lest::tests tests;
    return tests;
}

CASE( "scope-lite version" "[.scope][.version]" )
{
    scope_PRESENT( scope_lite_MAJOR );
    scope_PRESENT( scope_lite_MINOR );
    scope_PRESENT( scope_lite_PATCH );
    scope_PRESENT( scope_lite_VERSION );
}

CASE( "scope-lite configuration" "[.scope][.config]" )
{
    scope_PRESENT( scope_HAVE_STD_SCOPE );
    scope_PRESENT( scope_USES_STD_SCOPE );
    scope_PRESENT( scope_SCOPE_DEFAULT );
    scope_PRESENT( scope_SCOPE_NONSTD );
    scope_PRESENT( scope_SCOPE_STD );
    scope_PRESENT( scope_CONFIG_SELECT_SCOPE );
    scope_PRESENT( scope_CONFIG_NO_EXTENSIONS );
    scope_PRESENT( scope_CONFIG_NO_CONSTEXPR );
    // scope_PRESENT( scope_CONFIG_NO_EXCEPTIONS );
    scope_PRESENT( scope_USE_POST_CPP98_VERSION );
    scope_PRESENT( scope_CPLUSPLUS );
}

CASE( "__cplusplus" "[.stdc++]" )
{
    scope_PRESENT( __cplusplus );

#ifdef _MSVC_LANG
    scope_PRESENT( _MSVC_LANG );
#else
    scope_ABSENT(  _MSVC_LANG );
#endif
}

CASE( "Compiler version" "[.compiler]" )
{
#if scope_USES_STD_SCOPE
    std::cout << "(Compiler version not available: using stdandard <scope>)\n";
#else
    scope_PRESENT( scope_COMPILER_CLANG_VERSION );
    scope_PRESENT( scope_COMPILER_GNUC_VERSION );
    scope_PRESENT( scope_COMPILER_MSVC_VERSION );
#endif
}

CASE( "Presence of C++ language features" "[.stdlanguage]" )
{
#if scope_USES_STD_SCOPE
    std::cout << "(Presence of C++ language features not available: using stdandard <scope>)\n";
#else
    scope_PRESENT( scope_HAVE_CONSTEXPR_11 );
    scope_PRESENT( scope_HAVE_CONSTEXPR_14 );
    scope_PRESENT( scope_HAVE_DECAY );
    scope_PRESENT( scope_HAVE_DEDUCTION_GUIDES );
    scope_PRESENT( scope_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG );
    scope_PRESENT( scope_HAVE_NODISCARD );
    scope_PRESENT( scope_HAVE_NOEXCEPT );
    scope_PRESENT( scope_HAVE_IS_DEFAULT );
    scope_PRESENT( scope_HAVE_IS_DELETE );
    scope_PRESENT( scope_HAVE_STATIC_ASSERT );
#endif
}

CASE( "Presence of C++ library features" "[.stdlibrary]" )
{
#if scope_USES_STD_SCOPE
    std::cout << "(Presence of C++ library features not available: using stdandard <scope>)\n";
#else
    scope_PRESENT( scope_HAVE_TYPE_TRAITS );
    scope_PRESENT( scope_HAVE_TR1_TYPE_TRAITS );
    scope_PRESENT( scope_HAVE_IS_SAME );
    scope_PRESENT( scope_HAVE_IS_TRIVIAL );
    scope_PRESENT( scope_HAVE_IS_TRIVIALLY_COPYABLE );
    scope_PRESENT( scope_HAVE_IS_CONSTRUCTIBLE );
    scope_PRESENT( scope_HAVE_IS_COPY_CONSTRUCTIBLE );
    scope_PRESENT( scope_HAVE_IS_MOVE_CONSTRUCTIBLE );
    scope_PRESENT( scope_HAVE_IS_NOTHROW_CONSTRUCTIBLE );
    scope_PRESENT( scope_HAVE_IS_NOTHROW_MOVE_CONSTRUCTIBLE );
    scope_PRESENT( scope_HAVE_UNCAUGHT_EXCEPTIONS );
#endif

#if defined _HAS_CPP0X
    scope_PRESENT( _HAS_CPP0X );
#else
    scope_ABSENT(  _HAS_CPP0X );
#endif

#if defined __cpp_lib_experimental_scope
    scope_PRESENT( __cpp_lib_experimental_scope );
#else
    scope_ABSENT(  __cpp_lib_experimental_scope );
#endif
}

int main( int argc, char * argv[] )
{
    return lest::run( specification(), argc, argv );
}

#if 0
g++            -I../include -o scope-lite.t.exe scope-main.t.cpp && scope-lite.t.exe --pass
g++ -std=c++98 -I../include -o scope-lite.t.exe scope-main.t.cpp && scope-lite.t.exe --pass
g++ -std=c++03 -I../include -o scope-lite.t.exe scope-main.t.cpp && scope-lite.t.exe --pass
g++ -std=c++0x -I../include -o scope-lite.t.exe scope-main.t.cpp && scope-lite.t.exe --pass
g++ -std=c++11 -I../include -o scope-lite.t.exe scope-main.t.cpp && scope-lite.t.exe --pass
g++ -std=c++14 -I../include -o scope-lite.t.exe scope-main.t.cpp && scope-lite.t.exe --pass
g++ -std=c++17 -I../include -o scope-lite.t.exe scope-main.t.cpp && scope-lite.t.exe --pass

cl -EHsc -I../include -Febit-lite.t.exe scope-main.t.cpp && scope-lite.t.exe --pass
#endif

// end of file
