//
// Copyright (c) 2014 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "fake_assert.hpp" // has to be first
#include "boost/di/policies/creation_ownership.hpp"

#include "boost/di/aux_/memory.hpp"
#include <boost/test/test_case_template.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/identity.hpp>

namespace boost {
namespace di {
namespace policies {

using clear_ownerhsip_types = mpl::vector<
    int
  , int*
  , const int*
  , aux::shared_ptr<int>
>;

BOOST_AUTO_TEST_CASE_TEMPLATE(clear_ownerhsip, T, clear_ownerhsip_types) {
    BOOST_CHECK_NO_THROW(
        (
            creation_ownership::assert_policy<
                mpl::vector0<>
              , mpl::identity<T>
            >()
        )
    );
}

using not_clear_ownerhsip_types = mpl::vector<
    int&
  , const int&
>;

BOOST_AUTO_TEST_CASE_TEMPLATE(not_clear_ownerhsip, T, not_clear_ownerhsip_types) {
    BOOST_REQUIRE_EXCEPTION(
        (
            creation_ownership::assert_policy<
                mpl::vector0<>
              , mpl::identity<T>
            >()
        )
      , assert_exception
      , [](const assert_exception& e) {
            return e.get_msg() == "CREATION_OWNERSHIP_IS_NOT_CLEAR" &&
                   e.get_type() == typeid(T);
        }
    );
}

} // namespace policies
} // namespace di
} // namespace boost
