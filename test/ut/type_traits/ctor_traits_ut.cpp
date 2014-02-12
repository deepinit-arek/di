//
// Copyright (c) 2014 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "boost/di/type_traits/ctor_traits.hpp"

#include <boost/test/unit_test.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/equal.hpp>
#include "boost/mpl/string.hpp"
#include "boost/config.hpp"

#include "boost/di/inject.hpp"
#include "boost/di/named.hpp"
#include "boost/di/aux_/memory.hpp"

namespace boost {
namespace di {

struct traits { };

template<typename>
struct ctor_traits;

template<>
struct ctor_traits<traits>
{
    static void BOOST_DI_INJECTOR();
};

namespace type_traits {

struct empty
{
    static void BOOST_DI_INJECTOR();
};

struct int_double
{
    static void BOOST_DI_INJECTOR(int, double);
};

struct extensions
{
    static void BOOST_DI_INJECTOR(char*, const int&);
};

struct ctor1
{
    ctor1(int);
};

struct ctor2
{
    ctor2(char*, const int&);
};

struct ctor_complex
{
    ctor_complex(int, double&, aux::shared_ptr<int>, float&, const char*, const std::string&, void*) { }
};

struct ctor_inject_named
{
    static void BOOST_DI_INJECTOR(
        named<int, mpl::string<'1'> >
      , named<int, mpl::string<'2'> >
    );

    ctor_inject_named(int, int);
};

BOOST_AUTO_TEST_CASE(ctor) {
    BOOST_CHECK((mpl::equal<mpl::vector0<>, ctor_traits<void>::type>::value));
    BOOST_CHECK((mpl::equal<mpl::vector0<>, ctor_traits<empty>::type>::value));
    BOOST_CHECK((mpl::equal<mpl::vector0<>, ctor_traits<traits>::type>::value));
    BOOST_CHECK((mpl::equal<mpl::vector0<>, ctor_traits<empty>::type>::value));
    BOOST_CHECK((mpl::equal<mpl::vector2<int, double>, ctor_traits<int_double>::type>::value));
    BOOST_CHECK((mpl::equal<mpl::vector2<char*, const int&>, ctor_traits<extensions>::type>::value));
    BOOST_CHECK((mpl::equal<mpl::vector2<any_type, any_type>, ctor_traits<ctor2>::type>::value));
    BOOST_CHECK((mpl::equal<mpl::vector<any_type, any_type, any_type, any_type, any_type, any_type, any_type>, ctor_traits<ctor_complex>::type>::value));
    BOOST_CHECK((mpl::equal<
        mpl::vector2<
            named<int, mpl::string<'1'> >
          , named<int, mpl::string<'2'> >
        >
      , ctor_traits<ctor_inject_named>::type>::value
    ));

#if defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)
    BOOST_CHECK((mpl::equal<mpl::vector<>, ctor_traits<ctor1>::type>::value));
#else
    BOOST_CHECK((mpl::equal<mpl::vector1<any_type>, ctor_traits<ctor1>::type>::value));
#endif
}

} // namespace type_traits
} // namespace di
} // namespace boost
