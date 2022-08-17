# scope-lite - C++ standard libraries extensions, version 3: Generic scope and RAII Wrapper.

[![Language](https://img.shields.io/badge/C%2B%2B-98/11/14/17/20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B#Standardization) [![License](https://img.shields.io/badge/license-BSL-blue.svg)](https://opensource.org/licenses/BSL-1.0) [![Build Status](https://github.com/martinmoene/scope-lite/actions/workflows/ci.yml/badge.svg)](https://github.com/martinmoene/scope-lite/actions/workflows/ci.yml) [![Build Status](https://travis-ci.org/martinmoene/scope-lite.svg?branch=master)](https://travis-ci.org/martinmoene/scope-lite) [![Build status](https://ci.appveyor.com/api/projects/status/gpmw4gt271itoy2n?svg=true)](https://ci.appveyor.com/project/martinmoene/scope-lite) [![Version](https://badge.fury.io/gh/martinmoene%2Fscope-lite.svg)](https://github.com/martinmoene/scope-lite/releases) [![download](https://img.shields.io/badge/latest-download-blue.svg)](https://raw.githubusercontent.com/martinmoene/scope-lite/master/include/nonstd/scope.hpp) [![Conan](https://img.shields.io/badge/on-conan-blue.svg)](https://conan.io/center/scope-lite) [![Try it online](https://img.shields.io/badge/on-wandbox-blue.svg)](https://wandbox.org/permlink/exGAvIm9c9ygRTg0) [![Try it on godbolt online](https://img.shields.io/badge/on-godbolt-blue.svg)](https://godbolt.org/z/3RGyhz)

**Contents**  

- [Example usage](#example-usage)
- [In a nutshell](#in-a-nutshell)
- [License](#license)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Synopsis](#synopsis)
- [Reported to work with](#reported-to-work-with)
- [Building the tests](#building-the-tests)
- [Other implementations of scope](#other-implementations-of-scope)
- [Notes and references](#notes-and-references)
- [Appendix](#appendix)

## Example usage

```Cpp
#include "nonstd/scope.hpp"

using namespace nonstd;

int count = 0;

namespace on { void exit() { ++count; } }

int main()
{
    { auto guard = make_scope_exit(  on::exit ); } // note: on::exit w/o &
    { auto guard = make_scope_exit( &on::exit ); } // note: &on::exit

    return count;
}
```

Note: do not let stdlib's [global function `on_exit()`](https://man7.org/linux/man-pages/man3/on_exit.3.html) bite you. Thanks to [Björn Fahller](https://github.com/rollbear).

### Compile and run

```Text
$ g++ -std=c++11 -Wall -I../include -o 01-basic 01-basic.cpp && ./01-basic || echo $?
2
```

## In a nutshell

**scope lite** is a single-file header-only library to provide [C++ standard libraries extensions, version 3](https://en.cppreference.com/w/cpp/experimental/lib_extensions_3) for use with C++98 and later. If available, the standard library is used, unless [configured](#configuration) otherwise.

**Features and properties of scope lite** are ease of installation (single header), freedom of dependencies other than the standard library.

**Limitations of scope lite** are ... .

## License

*scope lite* is distributed under the [Boost Software License](https://github.com/martinmoene/scope-lite/blob/master/LICENSE.txt).

## Dependencies

*scope lite* has no other dependencies than the [C++ standard library](http://en.cppreference.com/w/cpp/header).

## Installation

*scope lite* is a single-file header-only library. Put `scope.hpp` in the [include](include) folder directly into the project source tree or somewhere reachable from your project.

## Synopsis

**Contents**  

- [scope-lite - C++ standard libraries extensions, version 3: Generic scope and RAII Wrapper.](#scope-lite---c-standard-libraries-extensions-version-3-generic-scope-and-raii-wrapper)

### Documentation of C++ standard libraries extensions, version 3

Depending on the compiler and C++ standard used, *scope lite* behaves less or more like the standard's version. To get an idea of the capabilities of *scope lite* with your configuration, look at the output of the [tests](test/scope.t.cpp), issuing `scope-main.t --pass @`. For the standard's documentation, see [C++ standard libraries extensions, version 3](https://en.cppreference.com/w/cpp/experimental/lib_extensions_3).  

### Configuration

#### Tweak header

If the compiler supports [`__has_include()`](https://en.cppreference.com/w/cpp/preprocessor/include), *scope lite* supports the [tweak header](https://vector-of-bool.github.io/2020/10/04/lib-configuration.html) mechanism. Provide your *tweak header* as `nonstd/scope.tweak.hpp` in a folder in the include-search-path. In the tweak header, provide definitions as documented below, like `#define scope_CPLUSPLUS 201103L`.

#### Standard selection macro

\-D<b>scope\_CPLUSPLUS</b>=199711L  
Define this macro to override the auto-detection of the supported C++ standard, if your compiler does not set the `__cplusplus` macro correctly.

#### Select standard library version or *scope lite*

At default, *scope lite* uses the standard library's version if it is available and lets you use it via namespace `nonstd`. You can however override this default and explicitly request to use the standard's version or *scope lite*'s header via the following macros.

-D<b>scope\_CONFIG\_SELECT\_SCOPE</b>=scope_SCOPE_DEFAULT  
Define this to `scope_SCOPE_STD` to select standard's version. Define this to `scope_SCOPE_NONSTD` to select *scope lite*. Default is undefined, which has the same effect as defining to `scope_SCOPE_DEFAULT`.

#### Disable extensions

-D<b>scope\_CONFIG\_NO\_EXTENSIONS</b>=0  
Define this to 1 if you want to compile without extensions. Default is undefined.

#### Disable constexpr extension

-D<b>scope\_CONFIG\_NO\_CONSTEXPR</b>=0  
Define this to 1 if you want to adhere to [C++ standard libraries extensions, version 3](https://en.cppreference.com/w/cpp/experimental/lib_extensions_3) and not use `constexpr` scope guards. Default is undefined.

## Reported to work with

TBD

<!-- ## Building the tests

TBD
-->

## Other implementations of scope

- [Example implementation](https://github.com/PeterSommerlad/SC22WG21_Papers/tree/master/workspace/P0052_scope_exit/src). Peter Sommerlad. 2018.

## Notes and references

*Interface and specification*

- Cppreference. [C++ standard libraries extensions, version 3](https://en.cppreference.com/w/cpp/experimental/lib_extensions_3)

*Proposals*

- [p0052 - Generic scope and RAII Wrapper for the Standard Library](http://wg21.link/p0052). Peter Sommerlad and Andrew L. Sandoval with contributions by Eric Niebler and Daniel Krügler

## Appendix

The [test program](test/scope.t.cpp) provides information on the compiler, the C++ language and library capabilities and the tests performed.

### A.1 Compile-time information

The version of *scope lite* is available via tag `[.version]`. The following tags are available for information on the compiler and on the C++ standard library used: `[.compiler]`, `[.stdc++]`, `[.stdlanguage]` and `[.stdlibrary]`.

### A.2 scope lite test specification

<details>
<summary>click to expand</summary>
<p>

```Text
scope_exit: exit function is called at end of scope
scope_exit: exit function is called at end of scope (lambda)
scope_exit: exit function is called at end of scope (constexpr) [extension]
scope_exit: exit function is called when an exception occurs
scope_exit: exit function is not called at end of scope when released
scope_fail: exit function is called when an exception occurs
scope_fail: exit function is called when an exception occurs (lambda)
scope_fail: exit function is not called when no exception occurs
scope_fail: exit function is not called when no exception occurs (constexpr) [extension]
scope_fail: exit function is not called when released
scope_success: exit function is called when no exception occurs
scope_success: exit function is called when no exception occurs (lambda)
scope_success: exit function is called when no exception occurs (constexpr) [extension]
scope_success: exit function is not called when an exception occurs
scope_success: exit function is not called when released
unique_resource: a successfully acquired resource is deleted
unique_resource: an unsuccessfully acquired resource is not deleted
unique_resource: move construction moves the managed resource and the deleter from the give one's [move-construction]
unique_resource: assignment replaces the managed resource and the deleter with the give one's [move-assignment]
unique_resource: reset() executes deleter
unique_resource: reset(resource) deletes original resource and replaces it with the given one
unique_resource: release() releases the ownership and prevents execution of deleter
unique_resource: get() provides the underlying resource handle
unique_resource: get_deleter() provides the deleter used for disposing of the managed resource
unique_resource: op*() provides the pointee if the resource handle is a pointer
unique_resource: op->() provides the pointee if the resource handle is a pointer 
unique_resource: [move-construction][resource-copy-ctor-throws]
unique_resource: [move-construction][deleter-copy-ctor-throws]
tweak header: reads tweak header if supported [tweak]
```

</p>
</details>
