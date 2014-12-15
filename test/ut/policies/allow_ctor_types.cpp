//
// Copyright (c) 2014 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "common/fakes/fake_assert.hpp"
#include "common/fakes/fake_data.hpp"
#include <type_traits>
#include "boost/di/policies/allow_ctor_types.hpp"

namespace boost { namespace di { namespace policies {

test nothing_is_allowed = [] {
    struct c { };
    try { allow_ctor_types()(fake_data<int>{}); } catch(const assert_exception&) { };
    try { allow_ctor_types()(fake_data<double>{}); } catch(const assert_exception&) { };
    try { allow_ctor_types()(fake_data<c>{}); } catch(const assert_exception&) { };
};

test type_is_allowed = [] {
    auto test = [](auto type) {
        allow_ctor_types(std::is_same<decltype(type), _>{})(fake_data<decltype(type)>{});
    };

    struct c { };
    test(int{});
    test(float{});
    test(c{});
};

test type_is_not_allowed = [] {
    auto test = [](auto type) {
         try { allow_ctor_types(std::is_same<decltype(type), _>{})(fake_data<void>{}); } catch(const assert_exception&) { }
    };

    struct c { };
    test(int{});
    test(float{});
    test(c{});
};

test type_is_allowed_operator_or = [] {
    auto test = [](auto type1, auto type2, auto allowed) {
        using namespace operators;
        allow_ctor_types(std::is_same<decltype(type1), _>{} || std::is_same<_, decltype(type2)>{})(fake_data<decltype(allowed)>{});
    };

    test(int{}, double{}, int{});
    test(double{}, int{}, int{});
};

test type_is_not_allowed_operator_or = [] {
    auto test = [](auto type1, auto type2, auto allowed) {
        using namespace operators;
        try { allow_ctor_types(
            std::is_same<decltype(type1), _>{} || std::is_same<_, decltype(type2)>{})(fake_data<decltype(allowed)>{});
        } catch(const assert_exception&) { }
    };

    test(int{}, double{}, float{});
    test(double{}, int{}, float{});
};

}}} // boost::di::policies
