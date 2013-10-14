//
// Copyright (c) 2012-2013 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_DI_FAKE_CONVERTIBLE_HPP
#define BOOST_DI_FAKE_CONVERTIBLE_HPP

#include <boost/type.hpp>

namespace boost {
namespace di {

template<typename T>
class fake_convertible
{
public:
    fake_convertible(T object) // non explicit
        : object_(object)
    { }

    template<typename I>
    I operator()(const type<I>&) const {
        return object_;
    }

private:
    T object_;
};

} // namespace di
} // namespace boost

#endif

