//
// Copyright (c) 2020-2020 Martin Moene
//
// https://github.com/martinmoene/scope-lite
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// C++ standard libraries extensions, version 3
// https://en.cppreference.com/w/cpp/experimental/lib_extensions_3

#ifndef NONSTD_SCOPE_LITE_HPP
#define NONSTD_SCOPE_LITE_HPP

#include <iostream>

#define scope_lite_MAJOR  0
#define scope_lite_MINOR  1
#define scope_lite_PATCH  0

#define scope_lite_VERSION  scope_STRINGIFY(scope_lite_MAJOR) "." scope_STRINGIFY(scope_lite_MINOR) "." scope_STRINGIFY(scope_lite_PATCH)

#define scope_STRINGIFY(  x )  scope_STRINGIFY_( x )
#define scope_STRINGIFY_( x )  #x

// scope-lite configuration:

#define scope_SCOPE_DEFAULT  0
#define scope_SCOPE_NONSTD   1
#define scope_SCOPE_STD      2

#if !defined( scope_CONFIG_SELECT_SCOPE )
# define scope_CONFIG_SELECT_SCOPE  ( scope_HAVE_STD_SCOPE ? scope_SCOPE_STD : scope_SCOPE_NONSTD )
#endif

// #if !defined( scope_CONFIG_STRICT )
// # define scope_CONFIG_STRICT  0
// #endif

// C++ language version detection (C++20 is speculative):
// Note: VC14.0/1900 (VS2015) lacks too much from C++14.

#ifndef   scope_CPLUSPLUS
# if defined(_MSVC_LANG ) && !defined(__clang__)
#  define scope_CPLUSPLUS  (_MSC_VER == 1900 ? 201103L : _MSVC_LANG )
# else
#  define scope_CPLUSPLUS  __cplusplus
# endif
#endif

#define scope_CPP98_OR_GREATER  ( scope_CPLUSPLUS >= 199711L )
#define scope_CPP11_OR_GREATER  ( scope_CPLUSPLUS >= 201103L )
#define scope_CPP14_OR_GREATER  ( scope_CPLUSPLUS >= 201402L )
#define scope_CPP17_OR_GREATER  ( scope_CPLUSPLUS >= 201703L )
#define scope_CPP20_OR_GREATER  ( scope_CPLUSPLUS >= 202000L )

// Use C++yy <scope> if available and requested:

#if scope_CPP20_OR_GREATER && defined(__has_include )
# if __has_include( <scope> )
#  define scope_HAVE_STD_SCOPE  1
# else
#  define scope_HAVE_STD_SCOPE  0
# endif
#else
# define  scope_HAVE_STD_SCOPE  0
#endif

#define  scope_USES_STD_SCOPE  ( (scope_CONFIG_SELECT_SCOPE == scope_SCOPE_STD) || ((scope_CONFIG_SELECT_SCOPE == scope_SCOPE_DEFAULT) && scope_HAVE_STD_SCOPE) )

//
// Using std <scope>:
//

#if scope_USES_STD_SCOPE

#include <scope>

namespace nonstd
{
    using std::scope_exit;
    using std::scope_fail;
    using std::scope_success;
    using std::unique_resource;

    using std::make_scope_exit;
    using std::make_scope_fail;
    using std::make_scope_success;
}

#else // scope_USES_STD_SCOPE

// half-open range [lo..hi):
#define scope_BETWEEN( v, lo, hi ) ( (lo) <= (v) && (v) < (hi) )

// Compiler versions:
//
// MSVC++  6.0  _MSC_VER == 1200  scope_COMPILER_MSVC_VERSION ==  60  (Visual Studio 6.0)
// MSVC++  7.0  _MSC_VER == 1300  scope_COMPILER_MSVC_VERSION ==  70  (Visual Studio .NET 2002)
// MSVC++  7.1  _MSC_VER == 1310  scope_COMPILER_MSVC_VERSION ==  71  (Visual Studio .NET 2003)
// MSVC++  8.0  _MSC_VER == 1400  scope_COMPILER_MSVC_VERSION ==  80  (Visual Studio 2005)
// MSVC++  9.0  _MSC_VER == 1500  scope_COMPILER_MSVC_VERSION ==  90  (Visual Studio 2008)
// MSVC++ 10.0  _MSC_VER == 1600  scope_COMPILER_MSVC_VERSION == 100  (Visual Studio 2010)
// MSVC++ 11.0  _MSC_VER == 1700  scope_COMPILER_MSVC_VERSION == 110  (Visual Studio 2012)
// MSVC++ 12.0  _MSC_VER == 1800  scope_COMPILER_MSVC_VERSION == 120  (Visual Studio 2013)
// MSVC++ 14.0  _MSC_VER == 1900  scope_COMPILER_MSVC_VERSION == 140  (Visual Studio 2015)
// MSVC++ 14.1  _MSC_VER >= 1910  scope_COMPILER_MSVC_VERSION == 141  (Visual Studio 2017)
// MSVC++ 14.2  _MSC_VER >= 1920  scope_COMPILER_MSVC_VERSION == 142  (Visual Studio 2019)

#if defined(_MSC_VER ) && !defined(__clang__)
# define scope_COMPILER_MSVC_VER      (_MSC_VER )
# define scope_COMPILER_MSVC_VERSION  (_MSC_VER / 10 - 10 * ( 5 + (_MSC_VER < 1900 ) ) )
#else
# define scope_COMPILER_MSVC_VER      0
# define scope_COMPILER_MSVC_VERSION  0
#endif

// Courtesy of https://github.com/gsl-lite/gsl-lite
// AppleClang  7.0.0  __apple_build_version__ ==  7000172  scope_COMPILER_APPLECLANG_VERSION ==  700  (Xcode 7.0, 7.0.1)          (LLVM 3.7.0)
// AppleClang  7.0.0  __apple_build_version__ ==  7000176  scope_COMPILER_APPLECLANG_VERSION ==  700  (Xcode 7.1)                 (LLVM 3.7.0)
// AppleClang  7.0.2  __apple_build_version__ ==  7000181  scope_COMPILER_APPLECLANG_VERSION ==  702  (Xcode 7.2, 7.2.1)          (LLVM 3.7.0)
// AppleClang  7.3.0  __apple_build_version__ ==  7030029  scope_COMPILER_APPLECLANG_VERSION ==  730  (Xcode 7.3)                 (LLVM 3.8.0)
// AppleClang  7.3.0  __apple_build_version__ ==  7030031  scope_COMPILER_APPLECLANG_VERSION ==  730  (Xcode 7.3.1)               (LLVM 3.8.0)
// AppleClang  8.0.0  __apple_build_version__ ==  8000038  scope_COMPILER_APPLECLANG_VERSION ==  800  (Xcode 8.0)                 (LLVM 3.9.0)
// AppleClang  8.0.0  __apple_build_version__ ==  8000042  scope_COMPILER_APPLECLANG_VERSION ==  800  (Xcode 8.1, 8.2, 8.2.1)     (LLVM 3.9.0)
// AppleClang  8.1.0  __apple_build_version__ ==  8020038  scope_COMPILER_APPLECLANG_VERSION ==  810  (Xcode 8.3)                 (LLVM 3.9.0)
// AppleClang  8.1.0  __apple_build_version__ ==  8020041  scope_COMPILER_APPLECLANG_VERSION ==  810  (Xcode 8.3.1)               (LLVM 3.9.0)
// AppleClang  8.1.0  __apple_build_version__ ==  8020042  scope_COMPILER_APPLECLANG_VERSION ==  810  (Xcode 8.3.2, 8.3.3)        (LLVM 3.9.0)
// AppleClang  9.0.0  __apple_build_version__ ==  9000037  scope_COMPILER_APPLECLANG_VERSION ==  900  (Xcode 9.0)                 (LLVM 4.0.0?)
// AppleClang  9.0.0  __apple_build_version__ ==  9000038  scope_COMPILER_APPLECLANG_VERSION ==  900  (Xcode 9.1)                 (LLVM 4.0.0?)
// AppleClang  9.0.0  __apple_build_version__ ==  9000039  scope_COMPILER_APPLECLANG_VERSION ==  900  (Xcode 9.2)                 (LLVM 4.0.0?)
// AppleClang  9.1.0  __apple_build_version__ ==  9020039  scope_COMPILER_APPLECLANG_VERSION ==  910  (Xcode 9.3, 9.3.1)          (LLVM 5.0.2?)
// AppleClang  9.1.0  __apple_build_version__ ==  9020039  scope_COMPILER_APPLECLANG_VERSION ==  910  (Xcode 9.4, 9.4.1)          (LLVM 5.0.2?)
// AppleClang 10.0.0  __apple_build_version__ == 10001145  scope_COMPILER_APPLECLANG_VERSION == 1000  (Xcode 10.0, 10.1)          (LLVM 6.0.1?)
// AppleClang 10.0.1  __apple_build_version__ == 10010046  scope_COMPILER_APPLECLANG_VERSION == 1001  (Xcode 10.2, 10.2.1, 10.3)  (LLVM 7.0.0?)
// AppleClang 11.0.0  __apple_build_version__ == 11000033  scope_COMPILER_APPLECLANG_VERSION == 1100  (Xcode 11.1, 11.2, 11.3)    (LLVM 8.0.0?)

#define scope_COMPILER_VERSION( major, minor, patch )  ( 10 * ( 10 * (major) + (minor) ) + (patch) )

#if defined( __apple_build_version__ )
# define scope_COMPILER_APPLECLANG_VERSION scope_COMPILER_VERSION( __clang_major__, __clang_minor__, __clang_patchlevel__ )
# define scope_COMPILER_CLANG_VERSION 0
#elif defined( __clang__ )
# define scope_COMPILER_APPLECLANG_VERSION 0
# define scope_COMPILER_CLANG_VERSION scope_COMPILER_VERSION( __clang_major__, __clang_minor__, __clang_patchlevel__ )
#else
# define scope_COMPILER_APPLECLANG_VERSION 0
# define scope_COMPILER_CLANG_VERSION 0
#endif

#if defined(__GNUC__) && !defined(__clang__)
# define scope_COMPILER_GNUC_VERSION  scope_COMPILER_VERSION(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#else
# define scope_COMPILER_GNUC_VERSION  0
#endif

// Presence of language and library features:

#define scope_HAVE( feature )  ( scope_HAVE_##feature )

#ifdef _HAS_CPP0X
# define scope_HAS_CPP0X  _HAS_CPP0X
#else
# define scope_HAS_CPP0X  0
#endif

#define scope_CPP11_90   (scope_CPP11_OR_GREATER || scope_COMPILER_MSVC_VER >= 1500)
#define scope_CPP11_100  (scope_CPP11_OR_GREATER || scope_COMPILER_MSVC_VER >= 1600)
#define scope_CPP11_110  (scope_CPP11_OR_GREATER || scope_COMPILER_MSVC_VER >= 1700)
#define scope_CPP11_120  (scope_CPP11_OR_GREATER || scope_COMPILER_MSVC_VER >= 1800)
#define scope_CPP11_140  (scope_CPP11_OR_GREATER || scope_COMPILER_MSVC_VER >= 1900)

#define scope_CPP14_000  (scope_CPP14_OR_GREATER)

#define scope_CPP17_000  (scope_CPP17_OR_GREATER)
#define scope_CPP17_140  (scope_CPP17_OR_GREATER || scope_COMPILER_MSVC_VER >= 1900)

// Presence of C++11 language features:

#define scope_HAVE_CONSTEXPR_11           scope_CPP11_140
// #define scope_HAVE_ENUM_CLASS             scope_CPP11_110
#define scope_HAVE_IS_DEFAULT             scope_CPP11_120
#define scope_HAVE_IS_DELETE              scope_CPP11_120
#define scope_HAVE_NOEXCEPT               scope_CPP11_140
#define scope_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG  scope_CPP11_120
#define scope_HAVE_STATIC_ASSERT          scope_CPP11_90

// Presence of C++14 language features:

#define scope_HAVE_CONSTEXPR_14           scope_CPP14_000
#define scope_HAVE_DECAY                  scope_CPP14_000

// Presence of C++17 language features:

#define scope_HAVE_DEDUCTION_GUIDES       scope_CPP17_000
#define scope_HAVE_NODISCARD              scope_CPP17_000

// Presence of C++11 library features:

#define scope_HAVE_IS_TRIVIAL             scope_CPP11_110
#define scope_HAVE_IS_TRIVIALLY_COPYABLE  scope_CPP11_110 && !scope_BETWEEN(scope_COMPILER_GNUC_VERSION, 1, 500) // GCC >= 5
#define scope_HAVE_IS_COPY_CONSTRUCTIBLE  scope_CPP11_110
#define scope_HAVE_IS_MOVE_CONSTRUCTIBLE  scope_CPP11_110
#define scope_HAVE_IS_NOTHROW_CONSTRUCTIBLE scope_CPP11_110
#define scope_HAVE_IS_NOTHROW_MOVE_CONSTRUCTIBLE scope_CPP11_110

#define scope_HAVE_TYPE_TRAITS            scope_CPP11_90
#define scope_HAVE_TR1_TYPE_TRAITS        (!! scope_COMPILER_GNUC_VERSION )

// #define scope_HAVE_IS_UNSIGNED            scope_HAVE_TYPE_TRAITS
// #define scope_HAVE_IS_SAME                scope_HAVE_TYPE_TRAITS
// #define scope_HAVE_IS_SAME_TR1            scope_HAVE_TR1_TYPE_TRAITS

// #define scope_HAVE_CSTDINT                scope_CPP11_90

// Presence of C++14 library features:

// Presence of C++17 library features:

#define scope_HAVE_UNCAUGHT_EXCEPTIONS    scope_CPP17_140

// Presence of C++ language features:

#if scope_HAVE_CONSTEXPR_11
# define scope_constexpr constexpr
#else
# define scope_constexpr /*constexpr*/
#endif

#if scope_HAVE_CONSTEXPR_14
# define scope_constexpr14 constexpr
#else
# define scope_constexpr14 /*constexpr*/
#endif

#if scope_HAVE( IS_DELETE )
# define scope_is_delete = delete
# define scope_is_delete_access public
#else
# define scope_is_delete
# define scope_is_delete_access private
#endif

#if scope_HAVE_NOEXCEPT
# define scope_noexcept noexcept
# define scope_noexcept_op(expr) noexcept(expr)
#else
# define scope_noexcept /*noexcept*/
# define scope_noexcept_op(expr) /*noexcept(expr)*/
#endif

#if scope_HAVE_NODISCARD
# define scope_nodiscard [[nodiscard]]
#else
# define scope_nodiscard /*[[nodiscard]]*/
#endif

// Select C++98 version

#define scope_USE_POST_CPP98_VERSION  scope_CPP11_110

// Additional includes:

#include <exception>    // for exception, terminate(), uncaught_exceptions()
#include <limits>       // std::numeric_limits<>

#if scope_HAVE_TYPE_TRAITS
# include <type_traits>
#elif scope_HAVE_TR1_TYPE_TRAITS
# include <tr1/type_traits>
#endif

// Method enabling (return type):

#if scope_HAVE( TYPE_TRAITS )
# define scope_ENABLE_IF_R_(R, VA)  typename std::enable_if< (VA), R >::type
#else
# define scope_ENABLE_IF_R_(R, VA)  R
#endif

// Method enabling (funtion template argument):

#if scope_HAVE( TYPE_TRAITS ) && scope_HAVE( DEFAULT_FUNCTION_TEMPLATE_ARG )
// VS 2013 seems to have trouble with SFINAE for default non-type arguments:
# if !scope_BETWEEN( scope_COMPILER_MSVC_VERSION, 1, 140 )
#  define scope_ENABLE_IF_(VA) , typename std::enable_if< ( VA ), int >::type = 0
# else
#  define scope_ENABLE_IF_(VA) , typename = typename std::enable_if< ( VA ), ::nonstd::scope::enabler >::type
# endif
#else
# define  scope_ENABLE_IF_(VA)
#endif

namespace nonstd {
namespace scope {

// for bit_ENABLE_IF_():

/*enum*/ class enabler{};

// C++11 emulation:

namespace std11 {

template< class T, T v > struct integral_constant { enum { value = v }; };
typedef integral_constant< bool, true  > true_type;
typedef integral_constant< bool, false > false_type;

#if scope_HAVE( IS_TRIVIAL )
    using std::is_trivial;
#else
    template< class T > struct is_trivial : std11::true_type{};
#endif

#if scope_HAVE( IS_TRIVIALLY_COPYABLE )
    using std::is_trivially_copyable;
#else
    template< class T > struct is_trivially_copyable : std11::true_type{};
#endif

#if scope_HAVE( IS_COPY_CONSTRUCTIBLE )
    using std::is_copy_constructible;
#else
    template< class T > struct is_copy_constructible : std11::true_type{};
#endif

#if scope_HAVE( IS_MOVE_CONSTRUCTIBLE )
    using std::is_move_constructible;
#else
    template< class T > struct is_move_constructible : std11::true_type{};
#endif

#if scope_HAVE( IS_NOTHROW_CONSTRUCTIBLE )
    using std::is_nothrow_constructible;
#else
    template< class T > struct is_nothrow_constructible : std11::true_type{};
#endif

#if scope_HAVE( IS_NOTHROW_COPY_CONSTRUCTIBLE )
    using std::is_nothrow_copy_constructible;
#else
    template< class T > struct is_nothrow_copy_constructible : std11::true_type{};
#endif

#if scope_HAVE( IS_NOTHROW_MOVE_CONSTRUCTIBLE )
    using std::is_nothrow_move_constructible;
#else
    template< class T > struct is_nothrow_move_constructible : std11::true_type{};
#endif

#if scope_HAVE( REFERENCE_WRAPPER )
    using std::reference_wrapper;
#else
    template< class T > struct reference_wrapper{ typedef T type; };
#endif

} // namepsace std11

// C++14 emulation:

namespace std14 {

#if scope_HAVE( DECAY )
    using std::decay;
#else
    template< class T > struct decay{ typedef T type; };
#endif
}

// C++17 emulation (uncaught_exceptions):

// Courtesy of https://github.com/gsl-lite/gsl-lite
// Add uncaught_exceptions for pre-2017 MSVC, GCC and Clang
// Return unsigned char to save stack space, uncaught_exceptions can only increase by 1 in a scope

namespace std17 {

template< typename T >
inline int to_int( T x ) scope_noexcept
{
    return static_cast<int>( x );
}

#if scope_HAVE( UNCAUGHT_EXCEPTIONS )

inline int uncaught_exceptions() scope_noexcept
{
    return to_int( std::uncaught_exceptions() );
}

#elif scope_COMPILER_MSVC_VERSION

extern "C" char * __cdecl _getptd();
inline int uncaught_exceptions() scope_noexcept
{
    return to_int( *reinterpret_cast<unsigned*>(_getptd() + (sizeof(void*) == 8 ? 0x100 : 0x90) ) );
}

#elif scope_COMPILER_CLANG_VERSION || scope_COMPILER_GNUC_VERSION || scope_COMPILER_APPLECLANG_VERSION

extern "C" char * __cxa_get_globals();
inline int uncaught_exceptions() scope_noexcept
{
    return to_int( *reinterpret_cast<unsigned*>(__cxa_get_globals() + sizeof(void*) ) );
}

#endif // scope_HAVE( UNCAUGHT_EXCEPTIONS )

} // namespace std17

//
// For reference:
//

#if 0

template< class EF>
class scope_exit;

template< class EF>
class scope_fail;

template< class EF>
class scope_success;

template<class R,class D>
class unique_resource;

// special factory function:

template<class R,class D, class S=R>
unique_resource<decay_t<R>, decay_t<D>>
make_unique_resource_checked(R&& r, S const& invalid, D&& d)
noexcept(is_nothrow_constructible_v<decay_t<R>, R> && is_nothrow_constructible_v<decay_t<D>, D>);

// optional factory functions (should at least be present for LFTS3):

template< class EF>
scope_exit<decay_t<EF>>
make_scope_exit(EF&& exit_function) ;

template< class EF>
scope_fail<decay_t<EF>>
make_scope_fail(EF&& exit_function) ;

template< class EF>
scope_success<decay_t<EF>>
make_scope_success(EF&& exit_function) ;

template<class R,class D>
unique_resource<decay_t<R>, decay_t<D>>
make_unique_resource( R&& r, D&& d)
noexcept(is_nothrow_constructible_v<decay_t<R>, R> && is_nothrow_constructible_v<decay_t<D>, D>);

template<class R,class D>
unique_resource<R&, decay_t<D>>
make_unique_resource( reference_wrapper<R> r, D&& d) noexcept(is_nothrow_constructible_v<decay_t<D>, D>);

#endif // reference

#if scope_USE_POST_CPP98_VERSION

//
// Post-C++98 version:
//

template< class EF >
class scope_exit
{
public:
    template< class Fn >
    explicit scope_exit( Fn&& fn )
    scope_noexcept_op
    ((
        std11::is_nothrow_constructible<EF, Fn>::value
        || std11::is_nothrow_constructible<EF, Fn&>::value
    ))
        : exit_function( std::forward<Fn>(fn) )     // move/copy
        , execute_on_destruction( true )
    {}

    scope_exit( scope_exit && other )
    scope_noexcept_op
    ((
        std11::is_nothrow_move_constructible<EF>::value
        || std11::is_nothrow_copy_constructible<EF>::value
    ))
        : exit_function( std::move( other.exit_function ) )     // move/copy
        , execute_on_destruction( other.execute_on_destruction )
        // , uncaught_on_creation( other.uncaught_on_creation )
    {}

    ~scope_exit() scope_noexcept_op( true )
    {
        if ( execute_on_destruction )
            exit_function();
    }

    void release() scope_noexcept
    {
        execute_on_destruction = false;
    }

scope_is_delete_access:
    scope_exit( scope_exit const & ) scope_is_delete;

    scope_exit & operator=( scope_exit const & ) scope_is_delete;
    scope_exit & operator=( scope_exit &&      ) scope_is_delete;

private:
    EF exit_function;
    bool execute_on_destruction; // { true };
    // int uncaught_on_creation{ std17::uncaught_exceptions() };
};

template< class EF >
class scope_fail
{
public:
    template< class Fn >
    explicit scope_fail( Fn&& fn )
    scope_noexcept_op
    ((
        std11::is_nothrow_constructible<EF, Fn>::value
        || std11::is_nothrow_constructible<EF, Fn&>::value
    ))
        : exit_function( std::forward<Fn>(fn) )     // move/copy
        , uncaught_on_creation( std17::uncaught_exceptions() )
    {}

    scope_fail( scope_fail && other )
    scope_noexcept_op
    ((
        std11::is_nothrow_move_constructible<EF>::value
        || std11::is_nothrow_copy_constructible<EF>::value
    ))
        : exit_function( std::move( other.exit_function ) )     // move/copy
        // , execute_on_destruction( other.execute_on_destruction )
        , uncaught_on_creation( other.uncaught_on_creation )
    {
        other.uncaught_on_creation = std::numeric_limits<int>::max();
    }

    ~scope_fail() scope_noexcept_op( true )
    {
        if ( uncaught_on_creation < std17::uncaught_exceptions() )
            exit_function();
    }

    void release() scope_noexcept
    {
        uncaught_on_creation = std::numeric_limits<int>::max();
    }

scope_is_delete_access:
    scope_fail( scope_fail const & ) scope_is_delete;

    scope_fail & operator=( scope_fail const & ) scope_is_delete;
    scope_fail & operator=( scope_fail &&      ) scope_is_delete;

private:
    EF exit_function;
    // bool execute_on_destruction{ true };
    int uncaught_on_creation; // { std17::uncaught_exceptions() };
};

template< class EF >
class scope_success
{
public:
    template< class Fn >
    explicit scope_success( Fn&& fn )
    scope_noexcept_op
    ((
        std11::is_nothrow_constructible<EF, Fn>::value
        || std11::is_nothrow_constructible<EF, Fn&>::value
    ))
        : exit_function( std::forward<Fn>(fn) )     // move/copy
        , uncaught_on_creation( std17::uncaught_exceptions() )
    {}

    scope_success( scope_success && other )
    scope_noexcept_op
    ((
        std11::is_nothrow_move_constructible<EF>::value
        || std11::is_nothrow_copy_constructible<EF>::value
    ))
        : exit_function( std::move( other.exit_function ) )     // move/copy
        // , execute_on_destruction( other.execute_on_destruction )
        , uncaught_on_creation( other.uncaught_on_creation )
    {
        other.uncaught_on_creation = -1;
    }

    ~scope_success() scope_noexcept_op( true )
    {
        if ( uncaught_on_creation >= std17::uncaught_exceptions() )
            exit_function();
    }

    void release() scope_noexcept
    {
        uncaught_on_creation = -1;
    }

scope_is_delete_access:
    scope_success( scope_success const & ) scope_is_delete;

    scope_success & operator=( scope_success const & ) scope_is_delete;
    scope_success & operator=( scope_success &&      ) scope_is_delete;

private:
    EF exit_function;
    // bool execute_on_destruction{ true };
    int uncaught_on_creation; // { std17::uncaught_exceptions() };
};

#if scope_HAVE( DEDUCTION_GUIDES )
template< class EF > scope_exit(EF) -> scope_exit<EF>;
template< class EF > scope_fail(EF) -> scope_fail<EF>;
template< class EF > scope_success(EF) -> scope_success<EF>;
#endif

template< class R, class D >
class unique_resource {
public:
    unique_resource();

    template <class RR, class DD>
    unique_resource(RR&& r, DD&& d) scope_noexcept_op(true/*see below*/);

    unique_resource(unique_resource&& rhs) scope_noexcept_op(true/*see below*/);
    ~unique_resource();

    unique_resource& operator=(unique_resource&& rhs) scope_noexcept_op(true/*see below*/);

    void reset() scope_noexcept;

    template <class RR>
    void reset(RR&& r);

    void release() scope_noexcept;
    const R& get() const scope_noexcept;

    /*see below*/void operator*() const scope_noexcept;
    R operator->() const scope_noexcept;

    const D& get_deleter() const scope_noexcept;

private:
//    using R1 = conditional_t< is_reference_v<R>, reference_wrapper<remove_reference_t<R>>, R >; // exposition only
//    R1 resource; // exposition only
//    D deleter; // exposition only
//    bool execute_on_reset{true}; // exposition only
};

#if scope_HAVE( DEDUCTION_GUIDES )
template< typename R, typename D >
unique_resource(R, D) -> unique_resource<R, D>;
#endif

// special factory function:

#if scope_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG

template< class R, class D, class S=R >
unique_resource
<
    typename std14::decay<R>::type
    , typename std14::decay<D>::type
>
make_unique_resource_checked( R && r, S const & invalid, D && d )
scope_noexcept_op
((
    std11::is_nothrow_constructible<typename std14::decay<R>::type, R>::value
    && std11::is_nothrow_constructible<typename std14::decay<D>::type, D>::value
));

#else // scope_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG

// avoid default template arguments:

template< class R, class D >
unique_resource
<
    typename std14::decay<R>::type
    , typename std14::decay<D>::type
>
make_unique_resource_checked( R && r, R const & invalid, D && d )
scope_noexcept_op
((
    std11::is_nothrow_constructible<typename std14::decay<R>::type, R>::value
    && std11::is_nothrow_constructible<typename std14::decay<D>::type, D>::value
));

template< class R, class D, class S >
unique_resource
<
    typename std14::decay<R>::type
    , typename std14::decay<D>::type
>
make_unique_resource_checked( R && r, S const & invalid, D && d )
scope_noexcept_op
((
    std11::is_nothrow_constructible<typename std14::decay<R>::type, R>::value
    && std11::is_nothrow_constructible<typename std14::decay<D>::type, D>::value
));

#endif // scope_HAVE_DEFAULT_FUNCTION_TEMPLATE_ARG

// optional factory functions (should at least be present for LFTS3):

template< class EF >
scope_exit<typename std14::decay<EF>::type>
make_scope_exit( EF && exit_function )
{
    return scope_exit<typename std14::decay<EF>::type>( std::forward<EF>( exit_function ) );
}

template< class EF >
scope_fail<typename std14::decay<EF>::type>
make_scope_fail( EF && exit_function )
{
    return scope_fail<typename std14::decay<EF>::type>( std::forward<EF>( exit_function ) );
}

template< class EF >
scope_success<typename std14::decay<EF>::type>
make_scope_success( EF && exit_function )
{
    return scope_success<typename std14::decay<EF>::type>( std::forward<EF>( exit_function ) );
}

template< class R, class D >
unique_resource<typename std14::decay<R>::type, typename std14::decay<D>::type>
make_unique_resource( R && r, D && d )
scope_noexcept_op
((
    std11::is_nothrow_constructible<typename std14::decay<R>::type, R>::value
    && std11::is_nothrow_constructible<typename std14::decay<D>::type, D>::value
));

template< class R, class D >
unique_resource< R &, typename std14::decay<D>::type >
make_unique_resource( typename std11::reference_wrapper<R>::type r, D && d )
scope_noexcept_op(( std11::is_nothrow_constructible<typename std14::decay<D>::type, D>::value ));

#else // #if scope_CPP11_OR_GREATER || scope_COMPILER_MSVC_VERSION >= 110

//
// C++98 version:
//

struct on_exit_policy
{
    mutable bool invoke_;

    on_exit_policy()
        : invoke_( true )
    {}

    on_exit_policy( on_exit_policy const & other )
        : invoke_( other.invoke_ )
    {
        other.invoke_ = false;
    }

    void release()
    {
        invoke_ = false;
    }

    bool perform()
    {
        return invoke_;
    }
};

struct on_fail_policy
{
    mutable int ucount_;

    on_fail_policy()
        : ucount_( std17::uncaught_exceptions() )
    {}

    on_fail_policy( on_fail_policy const & other )
        : ucount_( other.ucount_ )
    {
        other.ucount_ = std::numeric_limits<int>::max();
    }

    void release()
    {
        ucount_ = std::numeric_limits<int>::max();
    }

    bool perform()
    {
        return ucount_ < std17::uncaught_exceptions();
    }
};

struct on_success_policy
{
    mutable int ucount_;

    on_success_policy()
        : ucount_( std17::uncaught_exceptions() )
    {}

    on_success_policy( on_success_policy const & other )
        : ucount_( other.ucount_ )
    {
        other.ucount_ = -1;
    }

    void release()
    {
        ucount_ = -1;
    }

    bool perform()
    {
        return ucount_ >= std17::uncaught_exceptions();
    }
};

template< typename Policy >
class scope_guard : public Policy
{
public:
    typedef void (*Action)();

    template< typename Fn >
    scope_guard( Fn action )
        : Policy()
        , action_( action )
    {}

    scope_guard( scope_guard const & other )
        : Policy( other )
        , action_( other.action_ )
    {}

    virtual ~scope_guard()
    {
        if ( this->perform() )
            action_();
    }

private:
    scope_guard & operator=( scope_guard const & );

private:
    Action action_;
};

class scope_exit : public scope_guard< on_exit_policy >
{
public:
    template< typename Fn >
    scope_exit( Fn action ) : scope_guard( action ) {}
};

class scope_fail : public scope_guard< on_fail_policy >
{
public:
    template< typename Fn >
    scope_fail( Fn action ) : scope_guard( action ) {}
};

class scope_success : public scope_guard< on_success_policy >
{
public:
    template< typename Fn >
    scope_success( Fn action ) : scope_guard( action ) {}
};

template< class R, class D >
class unique_resource;

template< class R, class D >
class unique_resource {
public:
    unique_resource();

    template< class RR, class DD >
    unique_resource( RR const & r, DD const & d );

    unique_resource(unique_resource const & rhs );

    ~unique_resource();

    unique_resource & operator=( unique_resource const & rhs );

    void reset();

    template< class RR >
    void reset( RR const & r);

    void release();

    R const & get() const;

    /*see below*/void operator*() const;
    R operator->() const;

    D const & get_deleter() const;

private:
//    using R1 = conditional_t< is_reference_v<R>, reference_wrapper<remove_reference_t<R>>, R >; // exposition only
//    R1 resource; // exposition only
//    D deleter; // exposition only
//    bool execute_on_reset{true}; // exposition only
};

template< class EF >
scope_exit make_scope_exit( EF action )
{
    return scope_exit( action );
}

template< class EF >
scope_fail make_scope_fail( EF action )
{
    return scope_fail( action );
}

template< class EF >
scope_success make_scope_success( EF action )
{
    return scope_success( action );
}

// template< class R, class D >
// unique_resource<R,D> make_scope_unique_resource( EF action )
// {
//     return ...
// }

#endif // #if scope_CPP11_OR_GREATER || scope_COMPILER_MSVC_VERSION >= 110

}} // namespace nonstd::scope

//
// Make type available in namespace nonstd:
//

namespace nonstd
{
    using scope::scope_exit;
    using scope::scope_fail;
    using scope::scope_success;
    using scope::unique_resource;

    using scope::make_scope_exit;
    using scope::make_scope_fail;
    using scope::make_scope_success;
}

#endif // scope_USES_STD_SCOPE

#endif // NONSTD_SCOPE_LITE_HPP
