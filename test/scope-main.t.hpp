//
// Copyright (c) 2020-2020 Martin Moene
//
// https://github.com/martinmoene/scope-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TEST_BIT_LITE_H_INCLUDED
#define TEST_BIT_LITE_H_INCLUDED

#include "nonstd/scope.hpp"

#include "lest_cpp03.hpp"

#define CASE( name ) lest_CASE( specification(), name )

// Attribute externally visible for -fwhole-program:

#if defined(__GNUC__) && !defined(__clang__)
# define scope_ATTRIBUTE_EXT_VIS  __attribute__((externally_visible))
#else
# define scope_ATTRIBUTE_EXT_VIS
#endif

extern lest::tests & specification() scope_ATTRIBUTE_EXT_VIS;

#endif // TEST_BIT_LITE_H_INCLUDED

// end of file
