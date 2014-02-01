//
// Copyright (c) 2014 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <memory>
#include <boost/di.hpp>

namespace di = boost::di;

namespace {
struct if0 { virtual ~if0() { } virtual void dummy() = 0; };
struct c0if0 : if0 { virtual void dummy() { } };
struct c2 { BOOST_DI_INJECT(c2, std::shared_ptr<if0> /*shared*/) { } };
struct c3 { BOOST_DI_INJECT(c3, std::shared_ptr<if0> /*shared*/) { } };
struct c4 { BOOST_DI_INJECT(c4, std::unique_ptr<c2> /*unique*/, std::unique_ptr<c3> /*unique*/) { } };
} // namespace

int main() {
    di::make_injector(di::deduce<c0if0>()).create<c4>();
    //di::injector<c0if0>().create<c4>();

    return 0;
}
