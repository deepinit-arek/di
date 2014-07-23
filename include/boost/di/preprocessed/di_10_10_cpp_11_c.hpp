//
// Copyright (c) 2014 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Preprocessed version of "boost::di"
// DO NOT modify by hand!
//
#ifndef BOOST_DI_PREPROCESSED_DI_10_10_CPP_11_C_HPP
#define BOOST_DI_PREPROCESSED_DI_10_10_CPP_11_C_HPP

#include <vector>
#include <utility>
#include <typeinfo>
#include <string>
#include <map>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_rvalue_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_polymorphic.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_copy_constructible.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type.hpp>
#include <boost/ref.hpp>
#include <boost/non_type.hpp>
#include <boost/none_t.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/max.hpp>
#include <boost/mpl/max_element.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/accumulate.hpp>
#include <boost/function.hpp>
#include "boost/di/inject.hpp"
#include "boost/di/aux_/memory.hpp"
#include "boost/di/aux_/config.hpp"
#include <boost/config.hpp>
#include <boost/bind.hpp>

namespace boost {
namespace di {
namespace type_traits {

template<typename T>
struct remove_accessors
    : remove_cv<
         typename remove_pointer<
             typename remove_reference<T>::type
         >::type
      >
{ };

} // namespace type_traits
} // namespace di
} // namespace boost

namespace boost {
namespace di {
namespace type_traits {

template<typename>
struct make_plain;

BOOST_MPL_HAS_XXX_TRAIT_DEF(element_type)
BOOST_MPL_HAS_XXX_TRAIT_DEF(named_type)

template<typename T, typename = void>
struct deref_type
{
    typedef T type;
};

template<typename T>
struct deref_type<T, typename enable_if<has_element_type<T> >::type>
{
    typedef typename T::element_type type;
};

template<typename T>
struct deref_type<T, typename enable_if<has_named_type<T> >::type>
{
    typedef typename make_plain<typename T::named_type>::type type;
};

template<typename T>
struct make_plain
    : deref_type<
        typename remove_accessors<
            typename deref_type<
                typename remove_accessors<T>::type
            >::type
        >::type
    >
{ };

} // namespace type_traits
} // namespace di
} // namespace boost


namespace boost {
namespace di {

struct no_name { };

template<
    typename T
  , typename TName = no_name
  , typename = void
>
class named
{
    named& operator=(const named&);

public:
    typedef T named_type;
    typedef TName name;

    named(T object) // non explicit
        : object_(object)
    { }

    named(const named& other)
        : object_(other.object_)
    { }

    operator T() const {
        return object_;
    }

private:
    T object_;
};

template<
    typename T
  , typename TName
>
class named<const T&, TName>
{
    named& operator=(const named&);

public:
    typedef const T& named_type;
    typedef TName name;

    named(const T& object) // non explicit
        : object_(object)
    { }

    named(const named& other)
        : object_(other.object_)
    { }

    operator const T&() const {
        return object_;
    }

private:
    const T& object_;
};

template<
    typename T
  , typename TName
>
class named<T&, TName>
{
    named& operator=(const named&);

public:
    typedef T& named_type;
    typedef TName name;

    named(T& object) // non explicit
        : object_(object)
    { }

    named(const named& other)
        : object_(other.object_)
    { }

    operator T&() {
        return object_;
    }

private:
    T& object_;
};

BOOST_DI_FEATURE(RVALUE_REFERENCES)(
    template<
        typename T
      , typename TName
    >
    class named<T&&, TName>
    {
        named& operator=(const named&);

    public:
        typedef T&& named_type;
        typedef TName name;

        named(T&& object) // non explicit
            : object_(std::move(object))
        { }

        named(const named& other)
            : object_(other.object_)
        { }

        operator T&&() {
            return std::move(object_);
        }

    private:
        T object_;
    };
)

template<
    typename T
  , typename TName
>
class named<aux::unique_ptr<T>, TName>
{
    named& operator=(const named&);

public:
    typedef aux::unique_ptr<T> named_type;
    typedef TName name;

    BOOST_DI_FEATURE(RVALUE_REFERENCES)(
        named(aux::unique_ptr<T> object) // non explicit
            : object_(std::move(object))
        { }

        operator aux::unique_ptr<T>() {
            return std::move(object_);
        }
    )

    named(const named& other)
        : object_(new T(*other.object_))
    { }

private:
    aux::unique_ptr<T> object_;
};

template<
    typename T
  , typename TName
>
class named<
    T
  , TName
  , typename enable_if<
        is_polymorphic<typename type_traits::remove_accessors<T>::type>
    >::type
>
{
public:
    typedef T named_type;
    typedef TName name;
};

} // namespace di
} // namespace boost

namespace boost {
namespace di {
namespace wrappers {

template<typename T>
class copy
{
    typedef function<T*()> value_t;

    template<typename I>
    class scoped_ptr
    {
    public:
        explicit scoped_ptr(I* ptr)
            : ptr_(ptr)
        { }

        ~scoped_ptr() { delete ptr_; }
        I& operator*() const { return *ptr_; }

    private:
        I* ptr_;
    };

public:
    template<typename TValueType>
    copy(const TValueType& value) // non explicit
        : value_(value)
    { }

    template<typename I>
    I operator()(const type<I>&, typename disable_if<is_polymorphic<I> >::type* = 0) const {
        scoped_ptr<I> ptr(value_());
        return *ptr;
    }

    template<typename I>
    I* operator()(const type<I*>&) const {
        return value_(); // ownership transfer
    }

    template<typename I>
    const I* operator()(const type<const I*>&) const {
        return value_(); // ownership transfer
    }

    template<typename I>
    aux::shared_ptr<I> operator()(const type<aux::shared_ptr<I> >&) const {
        return aux::shared_ptr<I>(value_());
    }

    template<typename I>
    aux_::shared_ptr<I> operator()(const type<aux_::shared_ptr<I> >&) const {
        return aux_::shared_ptr<I>(value_());
    }

    template<typename I>
    aux::auto_ptr<I> operator()(const type<aux::auto_ptr<I> >&) const {
        return aux::auto_ptr<I>(value_());
    }

    template<typename I>
    aux::unique_ptr<I> operator()(const type<aux::unique_ptr<I> >&) const {
        return aux::unique_ptr<I>(value_());
    }

private:
    value_t value_;
};

} // namespace wrappers
} // namespace di
} // namespace boost

namespace boost {
namespace di {
namespace scopes {

template<template<typename> class TWrapper = wrappers::copy>
class unique
{
public:
    typedef mpl::int_<0> priority;

    template<typename TExpected>
    class scope
    {
    public:
        typedef TWrapper<TExpected> result_type;

        result_type create(const function<TExpected*()>& f) {
            return f;
        }
    };
};

} // namespace scopes
} // namespace di
} // namespace boost

namespace boost {
namespace di {
namespace wrappers {

template<typename T>
class shared
{
    template<typename U, typename TShared = aux::shared_ptr<U> >
    class sp_holder
    {
    public:
        explicit sp_holder(const TShared& value)
            : value_(value)
        { }

    private:
        TShared value_;
    };

public:
    shared() { }

    shared(const aux::shared_ptr<T>& value) // non explicit
        : value_(value)
    { }

    bool operator!() const {
        return !value_;
    }

    void reset(T* ptr = 0) {
        return value_.reset(ptr);
    }

    template<typename I>
    aux::shared_ptr<I> operator()(const type<aux::shared_ptr<I> >&) const {
        return value_;
    }

    template<typename I>
    aux_::shared_ptr<I> operator()(const type<aux_::shared_ptr<I> >&) const {
        aux_::shared_ptr<sp_holder<T> > sp(new sp_holder<T>(value_));
        return aux_::shared_ptr<T>(sp, value_.get());
    }

    template<typename I>
    aux::weak_ptr<I> operator()(const type<aux::weak_ptr<I> >&) const {
        return value_;
    }

private:
    aux::shared_ptr<T> value_;
};

} // namespace wrappers
} // namespace di
} // namespace boost

namespace boost {
namespace di {
namespace scopes {

template<template<typename> class TWrapper = wrappers::shared>
class shared
{
public:
    typedef mpl::int_<0> priority;

    template<typename TExpected>
    class scope
    {
    public:
        typedef TWrapper<TExpected> result_type;

        result_type create(const function<TExpected*()>& f) {
            if (!object_) {
                object_.reset(f());
            }
            return object_;
        }

    private:
        result_type object_;
    };
};

} // namespace scopes
} // namespace di
} // namespace boost


namespace boost {
namespace di {
namespace wrappers {

template<typename T>
class value
{
public:
    value(const T& value) // non explicit
        : value_(value)
    { }

    T operator()(const type<T>&) const {
        return value_;
    }

    T* operator()(const type<T*>&) const {
        return new T(value_);
    }

    const T* operator()(const type<const T*>&) const {
        return new T(value_);
    }

    BOOST_DI_FEATURE(RVALUE_REFERENCES)(
        T&& operator()(const type<T&&>&) {
            return std::move(value_);
        }
    )

    template<typename I>
    aux::shared_ptr<I> operator()(const type<aux::shared_ptr<I> >&) const {
        return aux::shared_ptr<I>(new I(value_));
    }

    template<typename I>
    aux_::shared_ptr<I> operator()(const type<aux_::shared_ptr<I> >&) const {
        return aux_::shared_ptr<I>(new I(value_));
    }

    template<typename I>
    aux::auto_ptr<I> operator()(const type<aux::auto_ptr<I> >&) const {
        return aux::auto_ptr<I>(new I(value_));
    }

    template<typename I>
    aux::unique_ptr<I> operator()(const type<aux::unique_ptr<I> >&) const {
        return aux::unique_ptr<I>(new I(value_));
    }

private:
    T value_;
};

} // namespace wrappers
} // namespace di
} // namespace boost


namespace boost {
namespace di {
namespace type_traits {

template<typename T>
class has_call_operator
{
    struct base_impl { void operator()(...) { } };
    struct base
        : base_impl
        , mpl::if_<is_class<T>, T, mpl::void_>::type
    { base() { } };

    template<typename U>
    static mpl::aux::no_tag test(
        U*
      , non_type<void (base_impl::*)(...), &U::operator()>* = 0
    );

    static mpl::aux::yes_tag test(...);

public:
    typedef has_call_operator type;

    BOOST_STATIC_CONSTANT(
        bool
      , value = sizeof(test((base*)0)) == sizeof(mpl::aux::yes_tag)
    );
};

} // namespace type_traits
} // namespace di
} // namespace boost

BOOST_DI_FEATURE(CPP_11_FUNCTIONAL)(
    namespace boost {

    template<typename T>
    class is_reference_wrapper< ::std::reference_wrapper<T> >
        : public mpl::true_
    { };

    template<typename T>
    class unwrap_reference< ::std::reference_wrapper<T> >
    {
    public:
        typedef T type;
    };

    } // namespace
)

namespace boost {
namespace di {
namespace scopes {

template<template<typename> class TWrapper = wrappers::value>
class external
{
public:
    typedef mpl::int_<1> priority;

    template<typename TExpected>
    class scope
    {
    public:
        typedef TWrapper<TExpected> result_type;

    private:
        class result_type_holder
        {
        public:
            template<typename T>
            explicit result_type_holder(const T& object)
                : object_(object)
            { }

            result_type operator()() const {
                return object_;
            }

        private:
            result_type object_;
        };

        template<typename TValueType, typename T>
        typename disable_if<type_traits::has_call_operator<TValueType>, function<result_type()> >::type
        convert_when_function(const T& object) {
            return object;
        }

        template<typename TValueType, typename T>
        typename enable_if<type_traits::has_call_operator<TValueType>, result_type_holder>::type
        convert_when_function(const T& object) {
            return result_type_holder(object);
        }

    public:
        template<typename T>
        explicit scope(const T& object
                     , typename enable_if_c<
                           type_traits::has_call_operator<T>::value &&
                           !is_reference_wrapper<T>::value
                       >::type* = 0)
            : object_(convert_when_function<TExpected>(object))
        { }

        template<typename T>
        explicit scope(const T& object
                     , typename disable_if_c<
                           type_traits::has_call_operator<T>::value &&
                           !is_reference_wrapper<T>::value
                       >::type* = 0)
            : object_(result_type_holder(object))
        { }

        result_type create() {
            return object_();
        }

    private:
        function<result_type()> object_;
    };
};

} // namespace scopes
} // namespace di
} // namespace boost


namespace boost {
namespace di {
namespace type_traits {

template<typename T>
struct scope_traits
{
    typedef scopes::unique<> type;
};

template<typename T>
struct scope_traits<T&>
{
    typedef scopes::external<> type;
};

template<typename T>
struct scope_traits<const T&>
{
    typedef scopes::unique<> type;
};

template<typename T>
struct scope_traits<T*>
{
    typedef scopes::unique<> type;
};

template<typename T>
struct scope_traits<const T*>
{
    typedef scopes::unique<> type;
};

template<typename T>
struct scope_traits<aux::auto_ptr<T> >
{
    typedef scopes::unique<> type;
};

template<typename T>
struct scope_traits<aux::shared_ptr<T> >
{
    typedef scopes::shared<> type;
};

template<typename T>
struct scope_traits<const aux::shared_ptr<T>&>
{
    typedef scopes::shared<> type;
};

template<typename T>
struct scope_traits<aux_::shared_ptr<T> >
{
    typedef scopes::shared<> type;
};

template<typename T>
struct scope_traits<const aux_::shared_ptr<T>&>
{
    typedef scopes::shared<> type;
};

template<typename T>
struct scope_traits<aux::weak_ptr<T> >
{
    typedef scopes::shared<> type;
};

template<typename T>
struct scope_traits<const aux::weak_ptr<T>&>
{
    typedef scopes::shared<> type;
};

template<typename T>
struct scope_traits<aux::unique_ptr<T> >
{
    typedef scopes::unique<> type;
};

template<typename T>
struct scope_traits<const aux::unique_ptr<T>&>
{
    typedef scopes::unique<> type;
};

BOOST_DI_FEATURE(RVALUE_REFERENCES)(
    template<typename T>
    struct scope_traits<T&&>
    {
        typedef scopes::unique<> type;
    };

    template<typename T>
    struct scope_traits<const T&&>
    {
        typedef scopes::unique<> type;
    };
)

template<typename T, typename TName>
struct scope_traits<named<T, TName> >
{
    typedef typename scope_traits<T>::type type;
};

template<typename T, typename TName>
struct scope_traits<const named<T, TName>&>
{
    typedef typename scope_traits<T>::type type;
};

} // namespace type_traits
} // namespace di
} // namespace boost

namespace boost {
namespace di {
namespace scopes {

class deduce
{
public:
    typedef mpl::int_<0> priority;

    template<typename>
    struct scope
    {
        typedef void result_type;
    };

    template<typename T>
    struct rebind
    {
        typedef typename type_traits::scope_traits<T>::type other;
    };
};

} // namespace scopes
} // namespace di
} // namespace boost

namespace boost {
namespace di {
namespace scopes {

class session_entry { };
class session_exit { };

template<template<typename> class TWrapper = wrappers::shared>
class session
{
public:
    typedef mpl::int_<0> priority;

    template<typename TExpected>
    class scope
    {
    public:
        typedef TWrapper<TExpected> result_type;

        scope()
            : in_scope_(false)
        { }

        void call(const session_entry&) {
            in_scope_ = true;
        }

        void call(const session_exit&) {
            in_scope_ = false;
            object_.reset();
        }

        result_type create(const function<TExpected*()>& f) {
            if (in_scope_ && !object_) {
                object_.reset(f());
            }
            return object_;
        }

    private:
        result_type object_;
        bool in_scope_;
    };
};

} // namespace scopes
} // namespace di
} // namespace boost


namespace boost {
namespace di {
namespace bindings {
namespace detail {

template<typename... T_MPL>
class requires_
{
    template<
        typename TBind
      , typename T
    >
    struct apply_bind
        : TBind::template apply<T>::type
    { };

public:
    typedef requires_ type;

    template<
        typename T
      , typename TMultiplicationFactor = mpl::integral_c<long, 10>
    >
    struct apply
        : mpl::second<
              typename mpl::fold<
                  ::boost::mpl::vector<T_MPL...>
                , mpl::pair<mpl::integral_c<long, 1>, mpl::integral_c<long, 1> >
                , mpl::pair<
                      mpl::times<
                          mpl::first<mpl::_1>
                        , TMultiplicationFactor
                      >
                    , mpl::times<
                          mpl::first<mpl::_1>
                        , mpl::second<mpl::_1>
                        , apply_bind<mpl::_2, T>
                      >
                  >
              >::type
          >
    { };
};

} // namespace detail
} // namespace bindings
} // namespace di
} // namespace boost

namespace boost {
namespace di {
namespace bindings {
namespace detail {

template<typename TContext>
class when_
{
    template<
        typename TBind
      , typename T
    >
    struct apply_bind
        : TBind::template apply<T>::type
    { };

public:
    template<typename T>
    struct apply
        : mpl::if_<
              mpl::empty<TContext>
            , mpl::int_<1>
            , typename mpl::deref<
                  mpl::max_element<
                      mpl::transform_view<
                          TContext
                        , apply_bind<mpl::_1, T>
                      >
                  >
              >::type
          >::type
    { };
};

} // namespace detail
} // namespace bindings
} // namespace di
} // namespace boost

namespace boost {
namespace di {
namespace bindings {
namespace type_traits {

BOOST_MPL_HAS_XXX_TRAIT_DEF(name)

template<typename TName>
class is_required_name
{
    template<typename T, typename = void>
    struct get_name
    {
        struct no_name { };
        typedef no_name type;
    };

    template<typename T>
    struct get_name<T, typename enable_if<
        has_name<typename di::type_traits::remove_accessors<T>::type> >::type
    >
    {
        typedef typename di::type_traits::remove_accessors<T>::type::name type;
    };

public:
    template<typename T>
    struct apply
        : is_same<typename get_name<typename T::type>::type, TName>
    { };
};

} // namespace type_traits
} // namespace bindings
} // namespace di
} // namespace boost

namespace boost {
namespace di {
namespace bindings {
namespace type_traits {

struct is_required_priority
{
    template<typename T>
    struct apply
        : mpl::plus<
              mpl::int_<1>
            , typename T::dependency::scope::priority // lowest = 0, highest = N
          >
    { };
};

} // namespace type_traits
} // namespace bindings
} // namespace di
} // namespace boost

namespace boost {
namespace di {
namespace type_traits {

template<typename T, typename U = mpl::_1>
struct is_same_base_of
    : mpl::or_<
          is_base_of<U, T>
        , is_same<U, T>
      >
{ };

} // namespace type_traits
} // namespace di
} // namespace boost

namespace boost {
namespace di {
namespace bindings {
namespace type_traits {

template<typename TValueType, typename = void>
struct is_required_type
{
    template<typename T>
    struct apply
        : di::type_traits::is_same_base_of<
              TValueType
            , typename di::type_traits::make_plain<typename T::type>::type
          >
    { };
};

template<typename TValueType>
struct is_required_type<TValueType, typename enable_if<mpl::is_sequence<TValueType> >::type>
{
    template<typename T>
    struct apply
        : mpl::count_if<
              TValueType
            , di::type_traits::is_same_base_of<
                  typename di::type_traits::make_plain<typename T::type>::type
                , mpl::_
              >
          >
    { };
};

} // namespace type_traits
} // namespace bindings
} // namespace di
} // namespace boost


namespace boost {
namespace di {
namespace bindings {

namespace detail {

template<typename TExpected, typename TGiven>
struct get_expected
    : mpl::if_<
          mpl::is_sequence<TExpected>
        , TGiven
        , TExpected
      >
{ };

} // namespace detail

template<
    typename TExpected
  , typename TGiven
  , template<
        typename
      , typename
      , typename
      , typename
    > class TDependency
>
struct bind
    : TDependency<
          scopes::deduce
        , typename detail::get_expected<TExpected, TGiven>::type
        , TGiven
        , detail::requires_<
              type_traits::is_required_priority
            , type_traits::is_required_type<TExpected>
          >
      >
{
    template<typename... T_MPL>
    struct when
        : TDependency<
              scopes::deduce
            , typename detail::get_expected<TExpected, TGiven>::type
            , TGiven
            , detail::requires_<
                  type_traits::is_required_priority
                , type_traits::is_required_type<TExpected>
                , detail::when_< ::boost::mpl::vector<T_MPL...> >
              >
          >
    {
        template<typename TName>
        struct named
            : TDependency<
                  scopes::deduce
                , typename detail::get_expected<TExpected, TGiven>::type
                , TGiven
                , detail::requires_<
                      type_traits::is_required_priority
                    , type_traits::is_required_type<TExpected>
                    , type_traits::is_required_name<TName>
                    , detail::when_< ::boost::mpl::vector<T_MPL...> >
                  >
              >
        { };
    };

    template<typename TName>
    struct named
        : TDependency<
              scopes::deduce
            , typename detail::get_expected<TExpected, TGiven>::type
            , TGiven
            , detail::requires_<
                  type_traits::is_required_priority
                , type_traits::is_required_type<TExpected>
                , type_traits::is_required_name<TName>
              >
          >
    {
        template<typename... T_MPL>
        struct when
            : TDependency<
                  scopes::deduce
                , typename detail::get_expected<TExpected, TGiven>::type
                , TGiven
                , detail::requires_<
                      type_traits::is_required_priority
                    , type_traits::is_required_type<TExpected>
                    , type_traits::is_required_name<TName>
                    , detail::when_< ::boost::mpl::vector<T_MPL...> >
                  >
              >
        { };
    };
};

} // namespace bindings
} // namespace di
} // namespace boost


namespace boost {
namespace di {
namespace bindings {

template<typename... T_MPL>
class call_stack
{
    typedef ::boost::mpl::vector<T_MPL...> context_type;

    template<typename TContext, typename TCallStack>
    struct equal
      : mpl::equal<
            mpl::iterator_range<
                typename mpl::advance<
                    typename mpl::begin<TCallStack>::type
                  , typename mpl::max<
                        mpl::int_<0>
                      , mpl::minus<
                            mpl::size<TCallStack>
                          , mpl::size<TContext>
                        >
                    >::type
                >::type
              , typename mpl::end<TCallStack>::type
            >
          , TContext
        >
    { };

    template<typename TContext, typename TCallStack>
    struct apply_impl
        : mpl::if_<
              mpl::empty<TCallStack>
            , mpl::int_<0>
            , mpl::if_<
                  equal<TContext, TCallStack>
                , mpl::size<TContext>
                , mpl::int_<0>
              >
          >
    { };

public:
    template<typename TDependency>
    struct apply
        : apply_impl<
              context_type
            , typename mpl::transform<
                  typename TDependency::call_stack
                , di::type_traits::make_plain<mpl::_>
              >::type
          >::type
    { };
};

} // namespace bindings
} // namespace di
} // namespace boost

namespace boost {
namespace di {
namespace wrappers {

template<typename T>
class reference
{
    reference& operator=(const reference&);

public:
    reference(T& value) // non explicit
        : value_(value)
    { }

    reference(const reference& other)
        : value_(other.value_)
    { }

    T& operator()(const type<T&>&) const {
        return value_;
    }

private:
    T& value_;
};

} // namespace wrappers
} // namespace di
} // namespace boost


    namespace boost {
    namespace di {
    namespace type_traits {

    template<typename>
    struct function_traits;

    template<typename R>
    struct function_traits<R(*)()>
    {
        typedef R result_type;
        typedef mpl::vector0<> type;
    };

    template<typename R, typename T>
    struct function_traits<R(T::*)()>
    {
        typedef R result_type;
        typedef T base_type;
        typedef mpl::vector0<> type;
    };

    template<typename R, typename T>
    struct function_traits<R(T::*)() const>
    {
        typedef R result_type;
        typedef T base_type;
        typedef mpl::vector0<> type;
    };

    template<typename R, typename... Args>
    struct function_traits<R(*)(Args...)>
    {
        typedef R result_type;
        typedef ::boost::mpl::vector<Args...> type;
    };

    template<typename R, typename T, typename... Args>
    struct function_traits<R(T::*)(Args...)>
    {
        typedef R result_type;
        typedef T base_type;
        typedef ::boost::mpl::vector<Args...> type;
    };

    template<typename R, typename T, typename... Args>
    struct function_traits<R(T::*)(Args...) const>
    {
        typedef R result_type;
        typedef T base_type;
        typedef ::boost::mpl::vector<Args...> type;
    };

    } // namespace type_traits
    } // namespace di
    } // namespace boost

namespace boost {
namespace di {
namespace bindings {

BOOST_MPL_HAS_XXX_TRAIT_DEF(result_type)

template<
    typename TScope
  , typename TExpected
  , typename TGiven = TExpected
  , typename TBind =
        detail::requires_<
            bindings::type_traits::is_required_priority
          , bindings::type_traits::is_required_type<TExpected>
        >
>
class dependency : public TScope::template scope<TExpected>
{
    typedef typename TScope::template scope<TExpected> scope_type;
    typedef scopes::external<wrappers::reference> ref_type;
    typedef scopes::external<wrappers::shared> shared_type;
    typedef scopes::external<wrappers::value> value_type;

    template<typename, typename = void>
    struct get_wrapper_impl
    {
        typedef value_type type;
    };

    template<typename T>
    struct get_wrapper_impl<aux::shared_ptr<T> >
    {
        typedef shared_type type;
    };

    template<typename T>
    struct get_wrapper_impl<T, typename enable_if<is_reference_wrapper<T> >::type>
    {
        typedef ref_type type;
    };

    template<
        typename T
      , typename = void
      , typename = void
      , typename = void
    >
    struct get_wrapper
    {
        typedef T type;
    };

    template<typename T>
    struct get_wrapper<T, typename enable_if<has_result_type<T> >::type>
        : get_wrapper_impl<typename T::result_type>
    { };

    template<typename T>
    struct get_wrapper<T, typename enable_if<di::type_traits::has_call_operator<T> >::type
                        , typename disable_if<has_result_type<T> >::type
                        , typename disable_if<is_reference_wrapper<T> >::type>
        : get_wrapper_impl<
              typename di::type_traits::function_traits<
                  BOOST_DI_FEATURE_DECLTYPE(&T::operator())
              >::result_type
          >
    { };

public:
    typedef dependency type;
    typedef TScope scope;
    typedef TExpected expected;
    typedef TGiven given;
    typedef TBind bind;

    template<typename T>
    struct rebind
    {
        typedef dependency<
            typename mpl::if_<
                is_same<scope, scopes::deduce>
              , T
              , TScope
            >::type
          , TExpected
          , TGiven
          , TBind
        > other;
    };

    dependency() { }

    template<typename T>
    explicit dependency(const T& object)
        : scope_type(object)
    { }

    template<typename T>
    static dependency<value_type, expected, T, TBind>
    to(const T& object, typename disable_if<is_reference_wrapper<T> >::type* = 0
                      , typename disable_if<di::type_traits::has_call_operator<T> >::type* = 0) {
        return dependency<value_type, expected, T, TBind>(object);
    }

    template<typename T>
    static dependency<ref_type, typename unwrap_reference<T>::type, T, TBind>
    to(const T& object, typename enable_if<is_reference_wrapper<T> >::type* = 0) {
        return dependency<ref_type, typename unwrap_reference<T>::type, T, TBind>(object);
    }

    template<typename T>
    static dependency<typename get_wrapper<T>::type, expected, T, TBind>
    to(const T& object, typename disable_if<is_reference_wrapper<T> >::type* = 0
                      , typename enable_if<di::type_traits::has_call_operator<T> >::type* = 0) {
        return dependency<typename get_wrapper<T>::type, expected, T, TBind>(object);
    }

    template<typename T>
    static dependency<shared_type, expected, T, TBind>
    to(const aux::shared_ptr<T>& object) {
        return dependency<shared_type, expected, T, TBind>(object);
    }
};

} // namespace bindings
} // namespace di
} // namespace boost


namespace boost {
namespace di {
namespace bindings {

template<
    typename TScope
  , template<
        typename
      , typename
      , typename
      , typename
    > class TDependency
>
class scope
{
    BOOST_MPL_HAS_XXX_TRAIT_DEF(given)

    template<typename T>
    struct is_dependency
        : has_given<T>
    { };

    template<typename T>
    struct dependency
        : TDependency<
              TScope
            , T
            , T
            , detail::requires_<
                  type_traits::is_required_priority
                , type_traits::is_required_type<T>
              >
          >
    { };

    template<typename T, typename U>
    struct rebind
        : T::template rebind<U>::other
    { };

public:
    template<typename... T_MPL>
    struct bind
        : mpl::fold<
              ::boost::mpl::vector<T_MPL...>
            , mpl::vector0<>
            , mpl::push_back<
                  mpl::_1
                , mpl::if_<
                      is_dependency<mpl::_2>
                    , rebind<mpl::_2, TScope>
                    , dependency<mpl::_2>
                  >
              >
          >::type
    { };
};

} // namespace bindings
} // namespace di
} // namespace boost


namespace boost {
namespace di {

template<typename TExpected, typename TGiven = TExpected>
struct bind
    : bindings::bind<TExpected, TGiven, bindings::dependency>
{ };

template<bool V>
struct bind_bool
    : bind<bool, mpl::bool_<V> >
{ };

template<int N>
struct bind_int
    : bind<int, mpl::int_<N> >
{ };

template<typename T>
struct bind_string
    : bind<std::string, T>
{ };

template<typename TScope>
struct scope
    : bindings::scope<TScope, bindings::dependency>
{ };

template<typename... T_MPL>
struct deduce
    : scope<scopes::deduce>::bind<T_MPL...>
{ };

template<typename... T_MPL>
struct unique
    : scope<scopes::unique<> >::bind<T_MPL...>
{ };

template<typename... T_MPL>
struct shared
    : scope<scopes::shared<> >::bind<T_MPL...>
{ };

template<typename... T_MPL>
struct session
    : scope<scopes::session<> >::bind<T_MPL...>
{ };

template<typename... T_MPL>
struct call_stack
    : bindings::call_stack<T_MPL...>
{ };

template<typename... T_MPL>
struct any_of
    : ::boost::mpl::vector<T_MPL...>
{ };

} // namespace di
} // namespace boost


    namespace boost {
    namespace di {
    namespace core {

    BOOST_MPL_HAS_XXX_TRAIT_DEF(types)

    class init { };

    template<typename>
    struct never
        : mpl::false_
    { };

    template<
        typename TSeq = mpl::vector0<>
      , typename TIgnore = never<mpl::_1>
      , typename = void
    >
    class pool
    {
    public:
        typedef pool type;
        typedef TSeq types;

        pool() { }

        template<typename T>
        explicit pool(const pool<T>&, const init&)
        { }

        template<typename T>
        const T& get() const {
            return static_cast<const T&>(*this);
        }
    };

    template<typename TSeq, typename TIgnore>
    class pool<TSeq, TIgnore, typename enable_if_c<mpl::size<TSeq>::value == 1>::type>
        : public mpl::at_c<TSeq, 0>::type

    {
        template<typename T, typename = void>
        struct pool_type
        {
            typedef mpl::vector<T> type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<has_types<T> >::type>
        {
            typedef typename T::types type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<
            typename mpl::apply<TIgnore, T>::type>::type>
        {
            typedef void type; // ignore type
        };

    public:
        typedef pool type;

        struct types
            : mpl::fold<
                  TSeq
                , mpl::vector0<>
                , mpl::copy<
                      pool_type<mpl::_2>
                    , mpl::back_inserter<mpl::_1>
                  >
              >::type
        { };

        pool() { }
        template< typename Args0> explicit pool( const Args0 &args0) : Args0(args0) { }
        template<typename T, typename I>
        explicit pool(
            const pool<T, I>&
          , const init&
          , typename enable_if_c<
                mpl::size<typename pool<T, I>::types>::value == 0
            >::type* = 0)
        { }
        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 1 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) { }

        template<typename T>
        const T& get() const {
            return static_cast<const T&>(*this);
        }
    };

    template<typename TSeq, typename TIgnore>
    class pool<TSeq, TIgnore, typename enable_if_c<mpl::size<TSeq>::value == 2>::type>
        : public mpl::at_c<TSeq, 0>::type , public mpl::at_c<TSeq, 1>::type

    {
        template<typename T, typename = void>
        struct pool_type
        {
            typedef mpl::vector<T> type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<has_types<T> >::type>
        {
            typedef typename T::types type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<
            typename mpl::apply<TIgnore, T>::type>::type>
        {
            typedef void type; // ignore type
        };

    public:
        typedef pool type;

        struct types
            : mpl::fold<
                  TSeq
                , mpl::vector0<>
                , mpl::copy<
                      pool_type<mpl::_2>
                    , mpl::back_inserter<mpl::_1>
                  >
              >::type
        { };

        pool() { }
        template< typename Args0> explicit pool( const Args0 &args0) : Args0(args0) { }

        template< typename Args0 , typename Args1> explicit pool( const Args0 &args0 , const Args1 &args1) : Args0(args0) , Args1(args1) { }
        template<typename T, typename I>
        explicit pool(
            const pool<T, I>&
          , const init&
          , typename enable_if_c<
                mpl::size<typename pool<T, I>::types>::value == 0
            >::type* = 0)
        { }
        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 1 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 2 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) { }

        template<typename T>
        const T& get() const {
            return static_cast<const T&>(*this);
        }
    };

    template<typename TSeq, typename TIgnore>
    class pool<TSeq, TIgnore, typename enable_if_c<mpl::size<TSeq>::value == 3>::type>
        : public mpl::at_c<TSeq, 0>::type , public mpl::at_c<TSeq, 1>::type , public mpl::at_c<TSeq, 2>::type

    {
        template<typename T, typename = void>
        struct pool_type
        {
            typedef mpl::vector<T> type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<has_types<T> >::type>
        {
            typedef typename T::types type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<
            typename mpl::apply<TIgnore, T>::type>::type>
        {
            typedef void type; // ignore type
        };

    public:
        typedef pool type;

        struct types
            : mpl::fold<
                  TSeq
                , mpl::vector0<>
                , mpl::copy<
                      pool_type<mpl::_2>
                    , mpl::back_inserter<mpl::_1>
                  >
              >::type
        { };

        pool() { }
        template< typename Args0> explicit pool( const Args0 &args0) : Args0(args0) { }

        template< typename Args0 , typename Args1> explicit pool( const Args0 &args0 , const Args1 &args1) : Args0(args0) , Args1(args1) { }

        template< typename Args0 , typename Args1 , typename Args2> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2) : Args0(args0) , Args1(args1) , Args2(args2) { }
        template<typename T, typename I>
        explicit pool(
            const pool<T, I>&
          , const init&
          , typename enable_if_c<
                mpl::size<typename pool<T, I>::types>::value == 0
            >::type* = 0)
        { }
        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 1 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 2 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 3 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) { }

        template<typename T>
        const T& get() const {
            return static_cast<const T&>(*this);
        }
    };

    template<typename TSeq, typename TIgnore>
    class pool<TSeq, TIgnore, typename enable_if_c<mpl::size<TSeq>::value == 4>::type>
        : public mpl::at_c<TSeq, 0>::type , public mpl::at_c<TSeq, 1>::type , public mpl::at_c<TSeq, 2>::type , public mpl::at_c<TSeq, 3>::type

    {
        template<typename T, typename = void>
        struct pool_type
        {
            typedef mpl::vector<T> type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<has_types<T> >::type>
        {
            typedef typename T::types type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<
            typename mpl::apply<TIgnore, T>::type>::type>
        {
            typedef void type; // ignore type
        };

    public:
        typedef pool type;

        struct types
            : mpl::fold<
                  TSeq
                , mpl::vector0<>
                , mpl::copy<
                      pool_type<mpl::_2>
                    , mpl::back_inserter<mpl::_1>
                  >
              >::type
        { };

        pool() { }
        template< typename Args0> explicit pool( const Args0 &args0) : Args0(args0) { }

        template< typename Args0 , typename Args1> explicit pool( const Args0 &args0 , const Args1 &args1) : Args0(args0) , Args1(args1) { }

        template< typename Args0 , typename Args1 , typename Args2> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2) : Args0(args0) , Args1(args1) , Args2(args2) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) { }
        template<typename T, typename I>
        explicit pool(
            const pool<T, I>&
          , const init&
          , typename enable_if_c<
                mpl::size<typename pool<T, I>::types>::value == 0
            >::type* = 0)
        { }
        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 1 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 2 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 3 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 4 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) { }

        template<typename T>
        const T& get() const {
            return static_cast<const T&>(*this);
        }
    };

    template<typename TSeq, typename TIgnore>
    class pool<TSeq, TIgnore, typename enable_if_c<mpl::size<TSeq>::value == 5>::type>
        : public mpl::at_c<TSeq, 0>::type , public mpl::at_c<TSeq, 1>::type , public mpl::at_c<TSeq, 2>::type , public mpl::at_c<TSeq, 3>::type , public mpl::at_c<TSeq, 4>::type

    {
        template<typename T, typename = void>
        struct pool_type
        {
            typedef mpl::vector<T> type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<has_types<T> >::type>
        {
            typedef typename T::types type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<
            typename mpl::apply<TIgnore, T>::type>::type>
        {
            typedef void type; // ignore type
        };

    public:
        typedef pool type;

        struct types
            : mpl::fold<
                  TSeq
                , mpl::vector0<>
                , mpl::copy<
                      pool_type<mpl::_2>
                    , mpl::back_inserter<mpl::_1>
                  >
              >::type
        { };

        pool() { }
        template< typename Args0> explicit pool( const Args0 &args0) : Args0(args0) { }

        template< typename Args0 , typename Args1> explicit pool( const Args0 &args0 , const Args1 &args1) : Args0(args0) , Args1(args1) { }

        template< typename Args0 , typename Args1 , typename Args2> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2) : Args0(args0) , Args1(args1) , Args2(args2) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) { }
        template<typename T, typename I>
        explicit pool(
            const pool<T, I>&
          , const init&
          , typename enable_if_c<
                mpl::size<typename pool<T, I>::types>::value == 0
            >::type* = 0)
        { }
        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 1 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 2 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 3 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 4 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 5 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) { }

        template<typename T>
        const T& get() const {
            return static_cast<const T&>(*this);
        }
    };

    template<typename TSeq, typename TIgnore>
    class pool<TSeq, TIgnore, typename enable_if_c<mpl::size<TSeq>::value == 6>::type>
        : public mpl::at_c<TSeq, 0>::type , public mpl::at_c<TSeq, 1>::type , public mpl::at_c<TSeq, 2>::type , public mpl::at_c<TSeq, 3>::type , public mpl::at_c<TSeq, 4>::type , public mpl::at_c<TSeq, 5>::type

    {
        template<typename T, typename = void>
        struct pool_type
        {
            typedef mpl::vector<T> type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<has_types<T> >::type>
        {
            typedef typename T::types type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<
            typename mpl::apply<TIgnore, T>::type>::type>
        {
            typedef void type; // ignore type
        };

    public:
        typedef pool type;

        struct types
            : mpl::fold<
                  TSeq
                , mpl::vector0<>
                , mpl::copy<
                      pool_type<mpl::_2>
                    , mpl::back_inserter<mpl::_1>
                  >
              >::type
        { };

        pool() { }
        template< typename Args0> explicit pool( const Args0 &args0) : Args0(args0) { }

        template< typename Args0 , typename Args1> explicit pool( const Args0 &args0 , const Args1 &args1) : Args0(args0) , Args1(args1) { }

        template< typename Args0 , typename Args1 , typename Args2> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2) : Args0(args0) , Args1(args1) , Args2(args2) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4 , typename Args5> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4 , const Args5 &args5) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) , Args5(args5) { }
        template<typename T, typename I>
        explicit pool(
            const pool<T, I>&
          , const init&
          , typename enable_if_c<
                mpl::size<typename pool<T, I>::types>::value == 0
            >::type* = 0)
        { }
        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 1 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 2 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 3 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 4 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 5 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 6 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 5>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 5 >::type >() ) { }

        template<typename T>
        const T& get() const {
            return static_cast<const T&>(*this);
        }
    };

    template<typename TSeq, typename TIgnore>
    class pool<TSeq, TIgnore, typename enable_if_c<mpl::size<TSeq>::value == 7>::type>
        : public mpl::at_c<TSeq, 0>::type , public mpl::at_c<TSeq, 1>::type , public mpl::at_c<TSeq, 2>::type , public mpl::at_c<TSeq, 3>::type , public mpl::at_c<TSeq, 4>::type , public mpl::at_c<TSeq, 5>::type , public mpl::at_c<TSeq, 6>::type

    {
        template<typename T, typename = void>
        struct pool_type
        {
            typedef mpl::vector<T> type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<has_types<T> >::type>
        {
            typedef typename T::types type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<
            typename mpl::apply<TIgnore, T>::type>::type>
        {
            typedef void type; // ignore type
        };

    public:
        typedef pool type;

        struct types
            : mpl::fold<
                  TSeq
                , mpl::vector0<>
                , mpl::copy<
                      pool_type<mpl::_2>
                    , mpl::back_inserter<mpl::_1>
                  >
              >::type
        { };

        pool() { }
        template< typename Args0> explicit pool( const Args0 &args0) : Args0(args0) { }

        template< typename Args0 , typename Args1> explicit pool( const Args0 &args0 , const Args1 &args1) : Args0(args0) , Args1(args1) { }

        template< typename Args0 , typename Args1 , typename Args2> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2) : Args0(args0) , Args1(args1) , Args2(args2) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4 , typename Args5> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4 , const Args5 &args5) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) , Args5(args5) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4 , typename Args5 , typename Args6> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4 , const Args5 &args5 , const Args6 &args6) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) , Args5(args5) , Args6(args6) { }
        template<typename T, typename I>
        explicit pool(
            const pool<T, I>&
          , const init&
          , typename enable_if_c<
                mpl::size<typename pool<T, I>::types>::value == 0
            >::type* = 0)
        { }
        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 1 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 2 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 3 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 4 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 5 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 6 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 5>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 5 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 7 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 5>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 5 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 6>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 6 >::type >() ) { }

        template<typename T>
        const T& get() const {
            return static_cast<const T&>(*this);
        }
    };

    template<typename TSeq, typename TIgnore>
    class pool<TSeq, TIgnore, typename enable_if_c<mpl::size<TSeq>::value == 8>::type>
        : public mpl::at_c<TSeq, 0>::type , public mpl::at_c<TSeq, 1>::type , public mpl::at_c<TSeq, 2>::type , public mpl::at_c<TSeq, 3>::type , public mpl::at_c<TSeq, 4>::type , public mpl::at_c<TSeq, 5>::type , public mpl::at_c<TSeq, 6>::type , public mpl::at_c<TSeq, 7>::type

    {
        template<typename T, typename = void>
        struct pool_type
        {
            typedef mpl::vector<T> type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<has_types<T> >::type>
        {
            typedef typename T::types type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<
            typename mpl::apply<TIgnore, T>::type>::type>
        {
            typedef void type; // ignore type
        };

    public:
        typedef pool type;

        struct types
            : mpl::fold<
                  TSeq
                , mpl::vector0<>
                , mpl::copy<
                      pool_type<mpl::_2>
                    , mpl::back_inserter<mpl::_1>
                  >
              >::type
        { };

        pool() { }
        template< typename Args0> explicit pool( const Args0 &args0) : Args0(args0) { }

        template< typename Args0 , typename Args1> explicit pool( const Args0 &args0 , const Args1 &args1) : Args0(args0) , Args1(args1) { }

        template< typename Args0 , typename Args1 , typename Args2> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2) : Args0(args0) , Args1(args1) , Args2(args2) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4 , typename Args5> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4 , const Args5 &args5) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) , Args5(args5) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4 , typename Args5 , typename Args6> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4 , const Args5 &args5 , const Args6 &args6) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) , Args5(args5) , Args6(args6) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4 , typename Args5 , typename Args6 , typename Args7> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4 , const Args5 &args5 , const Args6 &args6 , const Args7 &args7) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) , Args5(args5) , Args6(args6) , Args7(args7) { }
        template<typename T, typename I>
        explicit pool(
            const pool<T, I>&
          , const init&
          , typename enable_if_c<
                mpl::size<typename pool<T, I>::types>::value == 0
            >::type* = 0)
        { }
        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 1 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 2 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 3 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 4 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 5 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 6 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 5>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 5 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 7 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 5>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 5 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 6>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 6 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 8 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 5>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 5 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 6>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 6 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 7>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 7 >::type >() ) { }

        template<typename T>
        const T& get() const {
            return static_cast<const T&>(*this);
        }
    };

    template<typename TSeq, typename TIgnore>
    class pool<TSeq, TIgnore, typename enable_if_c<mpl::size<TSeq>::value == 9>::type>
        : public mpl::at_c<TSeq, 0>::type , public mpl::at_c<TSeq, 1>::type , public mpl::at_c<TSeq, 2>::type , public mpl::at_c<TSeq, 3>::type , public mpl::at_c<TSeq, 4>::type , public mpl::at_c<TSeq, 5>::type , public mpl::at_c<TSeq, 6>::type , public mpl::at_c<TSeq, 7>::type , public mpl::at_c<TSeq, 8>::type

    {
        template<typename T, typename = void>
        struct pool_type
        {
            typedef mpl::vector<T> type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<has_types<T> >::type>
        {
            typedef typename T::types type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<
            typename mpl::apply<TIgnore, T>::type>::type>
        {
            typedef void type; // ignore type
        };

    public:
        typedef pool type;

        struct types
            : mpl::fold<
                  TSeq
                , mpl::vector0<>
                , mpl::copy<
                      pool_type<mpl::_2>
                    , mpl::back_inserter<mpl::_1>
                  >
              >::type
        { };

        pool() { }
        template< typename Args0> explicit pool( const Args0 &args0) : Args0(args0) { }

        template< typename Args0 , typename Args1> explicit pool( const Args0 &args0 , const Args1 &args1) : Args0(args0) , Args1(args1) { }

        template< typename Args0 , typename Args1 , typename Args2> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2) : Args0(args0) , Args1(args1) , Args2(args2) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4 , typename Args5> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4 , const Args5 &args5) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) , Args5(args5) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4 , typename Args5 , typename Args6> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4 , const Args5 &args5 , const Args6 &args6) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) , Args5(args5) , Args6(args6) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4 , typename Args5 , typename Args6 , typename Args7> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4 , const Args5 &args5 , const Args6 &args6 , const Args7 &args7) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) , Args5(args5) , Args6(args6) , Args7(args7) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4 , typename Args5 , typename Args6 , typename Args7 , typename Args8> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4 , const Args5 &args5 , const Args6 &args6 , const Args7 &args7 , const Args8 &args8) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) , Args5(args5) , Args6(args6) , Args7(args7) , Args8(args8) { }
        template<typename T, typename I>
        explicit pool(
            const pool<T, I>&
          , const init&
          , typename enable_if_c<
                mpl::size<typename pool<T, I>::types>::value == 0
            >::type* = 0)
        { }
        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 1 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 2 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 3 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 4 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 5 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 6 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 5>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 5 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 7 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 5>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 5 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 6>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 6 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 8 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 5>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 5 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 6>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 6 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 7>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 7 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 9 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 5>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 5 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 6>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 6 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 7>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 7 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 8>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 8 >::type >() ) { }

        template<typename T>
        const T& get() const {
            return static_cast<const T&>(*this);
        }
    };

    template<typename TSeq, typename TIgnore>
    class pool<TSeq, TIgnore, typename enable_if_c<mpl::size<TSeq>::value == 10>::type>
        : public mpl::at_c<TSeq, 0>::type , public mpl::at_c<TSeq, 1>::type , public mpl::at_c<TSeq, 2>::type , public mpl::at_c<TSeq, 3>::type , public mpl::at_c<TSeq, 4>::type , public mpl::at_c<TSeq, 5>::type , public mpl::at_c<TSeq, 6>::type , public mpl::at_c<TSeq, 7>::type , public mpl::at_c<TSeq, 8>::type , public mpl::at_c<TSeq, 9>::type

    {
        template<typename T, typename = void>
        struct pool_type
        {
            typedef mpl::vector<T> type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<has_types<T> >::type>
        {
            typedef typename T::types type;
        };

        template<typename T>
        struct pool_type<T, typename enable_if<
            typename mpl::apply<TIgnore, T>::type>::type>
        {
            typedef void type; // ignore type
        };

    public:
        typedef pool type;

        struct types
            : mpl::fold<
                  TSeq
                , mpl::vector0<>
                , mpl::copy<
                      pool_type<mpl::_2>
                    , mpl::back_inserter<mpl::_1>
                  >
              >::type
        { };

        pool() { }
        template< typename Args0> explicit pool( const Args0 &args0) : Args0(args0) { }

        template< typename Args0 , typename Args1> explicit pool( const Args0 &args0 , const Args1 &args1) : Args0(args0) , Args1(args1) { }

        template< typename Args0 , typename Args1 , typename Args2> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2) : Args0(args0) , Args1(args1) , Args2(args2) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4 , typename Args5> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4 , const Args5 &args5) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) , Args5(args5) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4 , typename Args5 , typename Args6> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4 , const Args5 &args5 , const Args6 &args6) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) , Args5(args5) , Args6(args6) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4 , typename Args5 , typename Args6 , typename Args7> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4 , const Args5 &args5 , const Args6 &args6 , const Args7 &args7) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) , Args5(args5) , Args6(args6) , Args7(args7) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4 , typename Args5 , typename Args6 , typename Args7 , typename Args8> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4 , const Args5 &args5 , const Args6 &args6 , const Args7 &args7 , const Args8 &args8) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) , Args5(args5) , Args6(args6) , Args7(args7) , Args8(args8) { }

        template< typename Args0 , typename Args1 , typename Args2 , typename Args3 , typename Args4 , typename Args5 , typename Args6 , typename Args7 , typename Args8 , typename Args9> explicit pool( const Args0 &args0 , const Args1 &args1 , const Args2 &args2 , const Args3 &args3 , const Args4 &args4 , const Args5 &args5 , const Args6 &args6 , const Args7 &args7 , const Args8 &args8 , const Args9 &args9) : Args0(args0) , Args1(args1) , Args2(args2) , Args3(args3) , Args4(args4) , Args5(args5) , Args6(args6) , Args7(args7) , Args8(args8) , Args9(args9) { }
        template<typename T, typename I>
        explicit pool(
            const pool<T, I>&
          , const init&
          , typename enable_if_c<
                mpl::size<typename pool<T, I>::types>::value == 0
            >::type* = 0)
        { }
        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 1 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 2 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 3 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 4 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 5 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 6 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 5>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 5 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 7 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 5>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 5 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 6>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 6 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 8 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 5>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 5 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 6>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 6 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 7>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 7 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 9 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 5>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 5 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 6>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 6 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 7>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 7 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 8>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 8 >::type >() ) { }

        template<typename T, typename I> explicit pool( const pool<T, I>& p , const init& , typename enable_if_c< mpl::size<typename pool<T, I>::types>::value == 10 >::type* = 0) : mpl::at_c<typename pool<T, I>::types, 0>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 0 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 1>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 1 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 2>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 2 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 3>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 3 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 4>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 4 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 5>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 5 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 6>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 6 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 7>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 7 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 8>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 8 >::type >() ) , mpl::at_c<typename pool<T, I>::types, 9>::type( p.template get< typename mpl::at_c< typename pool<T, I>::types , 9 >::type >() ) { }

        template<typename T>
        const T& get() const {
            return static_cast<const T&>(*this);
        }
    };

    } // namespace core
    } // namespace di
    } // namespace boost


namespace boost {
namespace di {
namespace type_traits {

namespace detail {

template<
    typename T
  , typename TSignature
>
class is_convertible
{
    template<typename U>
    static mpl::aux::yes_tag test(non_type<TSignature, &U::operator()>*);

    template<typename>
    static mpl::aux::no_tag test(...);

public:
    typedef is_convertible type;

    BOOST_STATIC_CONSTANT(
        bool
      , value = sizeof(test<T>(0)) == sizeof(mpl::aux::yes_tag)
    );
};

} // namespace detail

template<
    typename TValueType
  , typename T
>
struct is_convertible_to_ref
    : detail::is_convertible<TValueType, const T&(TValueType::*)(const boost::type<const T&>&) const>
{ };

} // namespace type_traits
} // namespace di
} // namespace boost


namespace boost {
namespace di {
namespace wrappers {

namespace detail {

template<typename TResult, typename T, typename TValueType>
inline typename disable_if<is_copy_constructible<T>, const TResult&>::type
copy(std::vector<aux::shared_ptr<void> >& refs, const TValueType& value) {
    aux::shared_ptr<TResult> object(value(boost::type<T*>()));
    refs.push_back(object);
    return *object;
}

template<typename T>
struct holder
{
    explicit holder(const T& value)
        : held(value)
    { }

    T held;
};

template<typename TResult, typename T, typename TValueType>
inline typename enable_if<is_copy_constructible<T>, const TResult&>::type
copy(std::vector<aux::shared_ptr<void> >& refs, const TValueType& value) {
    aux::shared_ptr<holder<TResult> > object(new holder<TResult>(value(boost::type<T>())));
    refs.push_back(object);
    return object->held;
}

template<typename T>
class universal_impl
{
public:
    template<typename TValueType>
    universal_impl(std::vector<aux::shared_ptr<void> >&, const TValueType& value)
        : value_(boost::bind<T>(value, boost::type<T>()))
    { }

    operator T() const {
        return value_();
    }

private:
    function<T()> value_;
};

template<typename T>
class universal_impl<aux::auto_ptr<T> >
{
public:
    template<typename TValueType>
    universal_impl(std::vector<aux::shared_ptr<void> >& refs, const TValueType& value)
        : value_(new aux::auto_ptr<T>(value(boost::type<aux::auto_ptr<T> >()).release()))
    {
        refs.push_back(aux::shared_ptr<aux::auto_ptr<T> >(value_));
    }

    operator aux::auto_ptr<T>&() {
        return *value_;
    }

private:
    aux::auto_ptr<T>* value_; // weak
};

template<typename T>
class universal_impl<const T&>
{
public:
    template<typename TValueType>
    universal_impl(std::vector<aux::shared_ptr<void> >&
                 , const TValueType& value
                 , typename enable_if<type_traits::is_convertible_to_ref<TValueType, T> >::type* = 0)
        : value_(boost::bind<const T&>(value, boost::type<const T&>()))
    { }

    template<typename TValueType>
    universal_impl(std::vector<aux::shared_ptr<void> >& refs
                 , const TValueType& value
                 , typename disable_if<type_traits::is_convertible_to_ref<TValueType, T> >::type* = 0)
        : value_(boost::bind(&copy<T, T, TValueType>, boost::ref(refs), value))
    { }

    operator const T&() const {
        return value_();
    }

private:
    function<const T&()> value_;
};

template<typename T, typename TName>
class universal_impl<named<T, TName> >
{
public:
    template<typename TValueType>
    universal_impl(std::vector<aux::shared_ptr<void> >&, const TValueType& value)
        : value_(boost::bind<T>(value, boost::type<T>()))
    { }

    operator T() const {
        return value_();
    }

    operator named<T, TName>() const {
        return value_();
    }

private:
    function<T()> value_;
};

template<typename T, typename TName>
class universal_impl<named<const T&, TName> >
{
public:
    template<typename TValueType>
    universal_impl(std::vector<aux::shared_ptr<void> >&
                 , const TValueType& value
                 , typename enable_if<type_traits::is_convertible_to_ref<TValueType, T> >::type* = 0)
        : value_(boost::bind<const T&>(value, boost::type<const T&>()))
    { }

    template<typename TValueType>
    universal_impl(std::vector<aux::shared_ptr<void> >& refs
                 , const TValueType& value
                 , typename disable_if<type_traits::is_convertible_to_ref<TValueType, T> >::type* = 0)
        : value_(boost::bind(&copy<T, T, TValueType>, boost::ref(refs), value))
    { }

    operator named<const T&, TName>() const {
        return value_();
    }

private:
    function<named<const T&, TName>()> value_;
};

template<typename T, typename TName>
class universal_impl<const named<T, TName>&>
{
public:
    template<typename TValueType>
    universal_impl(std::vector<aux::shared_ptr<void> >& refs
                 , const TValueType& value)
        : value_(boost::bind(&copy<named<T, TName>, T, TValueType>, boost::ref(refs), value))
    { }

    operator const named<T, TName>&() const {
        return value_();
    }

private:
    function<const named<T, TName>&()> value_;
};

template<typename T, typename TName>
class universal_impl<const named<const T&, TName>&>
{
    universal_impl& operator=(const universal_impl&);

public:
    template<typename TValueType>
    universal_impl(std::vector<aux::shared_ptr<void> >& refs
                 , const TValueType& value
                 , typename enable_if<type_traits::is_convertible_to_ref<TValueType, T> >::type* = 0)
        : refs_(refs)
        , value_(boost::bind<const T&>(value, boost::type<const T&>()))
    { }

    template<typename TValueType>
    universal_impl(std::vector<aux::shared_ptr<void> >& refs
                 , const TValueType& value
                 , typename disable_if<type_traits::is_convertible_to_ref<TValueType, T> >::type* = 0)
        : refs_(refs)
        , value_(boost::bind(&copy<T, T, TValueType>, boost::ref(refs), value))
    { }

    operator const named<const T&, TName>&() const {
        aux::shared_ptr<holder<named<const T&, TName> > > object(
            new holder<named<const T&, TName> >(value_())
        );
        refs_.push_back(object);
        return object->held;
    }

private:
    std::vector<aux::shared_ptr<void> >& refs_;
    function<named<const T&, TName>()> value_;
};

} // namespace detail

template<typename T>
class universal : public detail::universal_impl<T>
{
public:
    typedef universal type;
    typedef T element_type;

    template<typename TValueType>
    universal(std::vector<aux::shared_ptr<void> >& refs, const TValueType& value)
        : detail::universal_impl<T>(refs, value)
    { }
};

} // namespace wrappers
} // namespace di
} // namespace boost

namespace boost {
namespace di {
namespace core {

template<typename TDependecies>
class binder
{
    template<
        typename T
      , typename TCallStack
      , typename TDependency
    >
    struct data
    {
        typedef T type;
        typedef TCallStack call_stack;
        typedef TDependency dependency;
    };

    template<
        typename TDependency
      , typename T
      , typename TCallStack
    >
    struct apply
        : TDependency::bind::template apply<data<T, TCallStack, TDependency> >::type
    { };

public:
    template<
        typename T
      , typename TCallStack
      , typename TDefault =
            bindings::dependency<
                scopes::deduce
              , typename type_traits::make_plain<T>::type
            >
    >
    struct resolve
        : mpl::deref<
              mpl::second<
                  typename mpl::fold<
                      TDependecies
                    , mpl::pair<mpl::int_<0>, TDefault>
                    , mpl::if_<
                          mpl::greater<
                              apply<
                                  mpl::_2
                                , T
                                , TCallStack
                              >
                            , mpl::first<mpl::_1>
                          >
                        , mpl::pair<apply<mpl::_2, T, TCallStack>, mpl::_2>
                        , mpl::_1
                      >
                  >::type
              >
          >::type::template
              rebind<typename scopes::deduce::rebind<T>::other>::other
    { };
};

} // namespace core
} // namespace di
} // namespace boost


namespace boost {
namespace di {
namespace core {

template<
    typename T = none_t
  , typename TCallStack = none_t
  , typename TCreator = none_t
  , typename TAllocator = none_t
  , typename TDeps = none_t
  , typename TRefs = none_t
  , typename TVisitor = none_t
  , typename TPolicies = none_t
>
class any_type
{
    any_type& operator=(const any_type&);

    template<typename TValueType, typename TRefType>
    struct ref_type
        : mpl::if_<
              is_same<TValueType, none_t>
            , TValueType
            , TRefType
          >
    { };

public:
    any_type() { }

    any_type(TCreator& creator
           , const TAllocator& allocator
           , TDeps& deps
           , TRefs& refs
           , const TVisitor& visitor
           , const TPolicies& policies)
        : creator_(creator)
        , allocator_(allocator)
        , deps_(deps)
        , refs_(refs)
        , visitor_(visitor)
        , policies_(policies)
    { }

    any_type(const any_type& other)
        : creator_(other.creator_)
        , allocator_(other.allocator_)
        , deps_(other.deps_)
        , refs_(other.refs_)
        , visitor_(other.visitor_)
        , policies_(other.policies_)
    { }

    template<
        typename U
        BOOST_DI_FEATURE(FUNCTION_TEMPLATE_DEFAULT_ARGS)(
            , typename = typename disable_if<
                type_traits::is_same_base_of<
                    typename type_traits::make_plain<U>::type
                  , typename type_traits::make_plain<T>::type
                >
            >::type
        )
    >
    operator const U&() const {
        return creator_.template create<const U&, none_t, TCallStack>(
            allocator_, deps_, refs_, visitor_, policies_
        );
    }

    template<
        typename U
        BOOST_DI_FEATURE(FUNCTION_TEMPLATE_DEFAULT_ARGS)(
            , typename = typename disable_if<
                type_traits::is_same_base_of<
                    typename type_traits::make_plain<U>::type
                  , typename type_traits::make_plain<T>::type
                >
            >::type
        )
    >
    operator U&() const {
        return creator_.template create<U&, none_t, TCallStack>(
            allocator_, deps_, refs_, visitor_, policies_
        );
    }

    template<typename U>
    operator aux::auto_ptr<U>&() {
        return creator_.template create<aux::auto_ptr<U>, none_t, TCallStack>(
            allocator_, deps_, refs_, visitor_, policies_
        );
    }

    BOOST_DI_WKND(MSVC)(
        template<typename U>
        operator aux::unique_ptr<U>() {
            return creator_.template create<aux::unique_ptr<U>, none_t, TCallStack>(
                allocator_, deps_, refs_, visitor_, policies_
            );
        }
    )

    BOOST_DI_WKND(NO_MSVC)(
        template<
            typename U
            BOOST_DI_FEATURE(FUNCTION_TEMPLATE_DEFAULT_ARGS)(
                , typename = typename disable_if<
                    type_traits::is_same_base_of<
                        typename type_traits::make_plain<U>::type
                      , typename type_traits::make_plain<T>::type
                    >
                >::type
            )
        >
        operator U() {
            return creator_.template create<U, none_t, TCallStack>(
                allocator_, deps_, refs_, visitor_, policies_
            );
        }
    )

private:
    typename ref_type<TCreator, TCreator&>::type creator_;
    typename ref_type<TAllocator, const TAllocator&>::type allocator_;
    typename ref_type<TDeps, TDeps&>::type deps_;
    typename ref_type<TRefs, TRefs&>::type refs_;
    typename ref_type<TVisitor, const TVisitor&>::type visitor_;
    typename ref_type<TPolicies, const TPolicies&>::type policies_;
};

} // namespace core
} // namespace di

template<
    typename T
  , typename TCallStack
  , typename TCreator
  , typename TAllocator
  , typename TDeps
  , typename TRefs
  , typename TVisitor
  , typename TPolicies
>
struct is_integral<
    di::core::any_type<
        T
      , TCallStack
      , TCreator
      , TAllocator
      , TDeps
      , TRefs
      , TVisitor
      , TPolicies
   >
> : mpl::true_ { };

} // namespace boost

BOOST_DI_FEATURE(CPP_11_TYPE_TRAITS)(
    namespace std {

    template<
        typename T
      , typename TCallStack
      , typename TCreator
      , typename TAllocator
      , typename TDeps
      , typename TRefs
      , typename TVisitor
      , typename TPolicies
    >
    struct is_integral<
        boost::di::core::any_type<
            T
          , TCallStack
          , TCreator
          , TAllocator
          , TDeps
          , TRefs
          , TVisitor
          , TPolicies
        >
    > : ::boost::mpl::true_ { };

    } // namespace std
)


    namespace boost {
    namespace di {
    namespace type_traits {

    template<typename, typename>
    class has_ctor;

    template<typename T>
    class has_ctor<T, mpl::int_<1> >
    {
        template<typename U>
        static mpl::aux::yes_tag test(BOOST_DI_FEATURE_DECLTYPE(U(di::core::any_type<T>()))*);

        template<typename>
        static mpl::aux::no_tag test(...);

    public:
        typedef has_ctor type;

        BOOST_DI_FEATURE(FUNCTION_TEMPLATE_DEFAULT_ARGS)(
            BOOST_STATIC_CONSTANT(
                bool
              , value = sizeof(test<T>(0)) == sizeof(mpl::aux::yes_tag)
            );
        )

        BOOST_DI_FEATURE(NO_FUNCTION_TEMPLATE_DEFAULT_ARGS)(
            BOOST_STATIC_CONSTANT(
                bool
              , value = false
            );
        )
    };

    template<typename T>
    class has_ctor<T, mpl::int_<2> >
    {
    public:
        template<typename U>
        static mpl::aux::yes_tag test(
            BOOST_DI_FEATURE_DECLTYPE(U(
                di::core::any_type<T>() , di::core::any_type<T>() )
            )*
        );

        template<typename>
        static mpl::aux::no_tag test(...);

    public:
        typedef has_ctor type;

        BOOST_STATIC_CONSTANT(
            bool
          , value = sizeof(test<T>(0)) == sizeof(mpl::aux::yes_tag)
        );
    };

    template<typename T>
    class has_ctor<T, mpl::int_<3> >
    {
    public:
        template<typename U>
        static mpl::aux::yes_tag test(
            BOOST_DI_FEATURE_DECLTYPE(U(
                di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() )
            )*
        );

        template<typename>
        static mpl::aux::no_tag test(...);

    public:
        typedef has_ctor type;

        BOOST_STATIC_CONSTANT(
            bool
          , value = sizeof(test<T>(0)) == sizeof(mpl::aux::yes_tag)
        );
    };

    template<typename T>
    class has_ctor<T, mpl::int_<4> >
    {
    public:
        template<typename U>
        static mpl::aux::yes_tag test(
            BOOST_DI_FEATURE_DECLTYPE(U(
                di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() )
            )*
        );

        template<typename>
        static mpl::aux::no_tag test(...);

    public:
        typedef has_ctor type;

        BOOST_STATIC_CONSTANT(
            bool
          , value = sizeof(test<T>(0)) == sizeof(mpl::aux::yes_tag)
        );
    };

    template<typename T>
    class has_ctor<T, mpl::int_<5> >
    {
    public:
        template<typename U>
        static mpl::aux::yes_tag test(
            BOOST_DI_FEATURE_DECLTYPE(U(
                di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() )
            )*
        );

        template<typename>
        static mpl::aux::no_tag test(...);

    public:
        typedef has_ctor type;

        BOOST_STATIC_CONSTANT(
            bool
          , value = sizeof(test<T>(0)) == sizeof(mpl::aux::yes_tag)
        );
    };

    template<typename T>
    class has_ctor<T, mpl::int_<6> >
    {
    public:
        template<typename U>
        static mpl::aux::yes_tag test(
            BOOST_DI_FEATURE_DECLTYPE(U(
                di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() )
            )*
        );

        template<typename>
        static mpl::aux::no_tag test(...);

    public:
        typedef has_ctor type;

        BOOST_STATIC_CONSTANT(
            bool
          , value = sizeof(test<T>(0)) == sizeof(mpl::aux::yes_tag)
        );
    };

    template<typename T>
    class has_ctor<T, mpl::int_<7> >
    {
    public:
        template<typename U>
        static mpl::aux::yes_tag test(
            BOOST_DI_FEATURE_DECLTYPE(U(
                di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() )
            )*
        );

        template<typename>
        static mpl::aux::no_tag test(...);

    public:
        typedef has_ctor type;

        BOOST_STATIC_CONSTANT(
            bool
          , value = sizeof(test<T>(0)) == sizeof(mpl::aux::yes_tag)
        );
    };

    template<typename T>
    class has_ctor<T, mpl::int_<8> >
    {
    public:
        template<typename U>
        static mpl::aux::yes_tag test(
            BOOST_DI_FEATURE_DECLTYPE(U(
                di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() )
            )*
        );

        template<typename>
        static mpl::aux::no_tag test(...);

    public:
        typedef has_ctor type;

        BOOST_STATIC_CONSTANT(
            bool
          , value = sizeof(test<T>(0)) == sizeof(mpl::aux::yes_tag)
        );
    };

    template<typename T>
    class has_ctor<T, mpl::int_<9> >
    {
    public:
        template<typename U>
        static mpl::aux::yes_tag test(
            BOOST_DI_FEATURE_DECLTYPE(U(
                di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() )
            )*
        );

        template<typename>
        static mpl::aux::no_tag test(...);

    public:
        typedef has_ctor type;

        BOOST_STATIC_CONSTANT(
            bool
          , value = sizeof(test<T>(0)) == sizeof(mpl::aux::yes_tag)
        );
    };

    template<typename T>
    class has_ctor<T, mpl::int_<10> >
    {
    public:
        template<typename U>
        static mpl::aux::yes_tag test(
            BOOST_DI_FEATURE_DECLTYPE(U(
                di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() , di::core::any_type<T>() )
            )*
        );

        template<typename>
        static mpl::aux::no_tag test(...);

    public:
        typedef has_ctor type;

        BOOST_STATIC_CONSTANT(
            bool
          , value = sizeof(test<T>(0)) == sizeof(mpl::aux::yes_tag)
        );
    };

    } // namespace type_traits
    } // namespace di
    } // namespace boost


namespace boost {
namespace di {
namespace type_traits {

template<typename T>
class has_boost_di_injector__
{
    struct base_impl { void boost_di_injector__(...) { } };
    struct base
        : base_impl
        , mpl::if_<is_class<T>, T, mpl::void_>::type
    { base() { } };

    template<typename U>
    static mpl::aux::no_tag test(
        U*
      , non_type<void (base_impl::*)(...), &U::boost_di_injector__>* = 0
    );

    static mpl::aux::yes_tag test(...);

public:
    typedef has_boost_di_injector__ type;

    BOOST_STATIC_CONSTANT(
        bool
      , value = sizeof(test((base*)0)) == sizeof(mpl::aux::yes_tag)
    );
};

} // namespace type_traits
} // namespace di
} // namespace boost


namespace boost {
namespace di {
namespace detail {

template<typename T>
struct get_value
    : mpl::int_<T::value>
{ };

template<typename T>
struct get_longest_ctor
    : mpl::fold<
        mpl::range_c<int, 1, 10 + 1>
      , mpl::int_<0>
      , mpl::if_<
            type_traits::has_ctor<T, get_value<mpl::_2> >
          , mpl::_2
          , mpl::_1
        >
      >::type
{ };

} // detail

template<typename T>
struct ctor_traits
    : mpl::fold<
          mpl::range_c<int, 0, detail::get_longest_ctor<T>::value>
        , mpl::vector0<>
        , mpl::push_back<mpl::_1, core::any_type<> >
      >
{ };

template<typename T>
struct ctor_traits<std::basic_string<T> > // basic_string ctors are ambiguous
{
    static void boost_di_injector__();
};

namespace type_traits {

template<typename T, typename = void>
struct ctor_traits
    : di::ctor_traits<T>::type
{ };

template<typename T>
struct ctor_traits<T, typename enable_if<has_boost_di_injector__<di::ctor_traits<T> > >::type>
    : function_traits<BOOST_DI_FEATURE_DECLTYPE(&di::ctor_traits<T>::boost_di_injector__)>::type
{ };

template<typename T>
struct ctor_traits<T, typename enable_if<has_boost_di_injector__<T> >::type>
    : function_traits<BOOST_DI_FEATURE_DECLTYPE(&T::boost_di_injector__)>::type
{ };

} // namespace type_traits
} // namespace di
} // namespace boost


    namespace boost {
    namespace di {
    namespace core {

    template<
        typename TDependecies = mpl::vector0<>
      , template<typename> class TBinder = binder
      , template<
            typename = ::boost::none_t
          , typename = ::boost::none_t
          , typename = ::boost::none_t
          , typename = ::boost::none_t
          , typename = ::boost::none_t
          , typename = ::boost::none_t
          , typename = ::boost::none_t
          , typename = ::boost::none_t
        >
        class TAnyType = ::boost::di::core::any_type
    >
    class creator
    {
        template<typename TDependency>
        struct scope_create
            : type_traits::function_traits<
                  BOOST_DI_FEATURE_DECLTYPE(&TDependency::create)
              >::type
        { };

        class type_comparator
        {
        public:
            bool operator()(const std::type_info* lhs, const std::type_info* rhs) const {
                return lhs->before(*rhs);
            }
        };

        typedef std::map<
            const std::type_info*
          , aux::shared_ptr<void>
          , type_comparator
        > scopes_type;

        template<
            typename T
          , typename TCallStack
          , typename TDependency
        >
        struct data
        {
            typedef T type;
            typedef TCallStack call_stack;
            typedef TDependency dependency;
            typedef TBinder<TDependecies> binder;
        };

    public:
        explicit creator(const TBinder<TDependecies>& binder = TBinder<TDependecies>())
            : binder_(binder)
        { }

        template<
            typename T
          , typename TParent // ignore copy/move ctor
          , typename TCallStack
          , typename TAllocator
          , typename TDeps
          , typename TRefs
          , typename TVisitor
          , typename TPolicies
        >
        typename enable_if<
            is_same<T, TAnyType<> >
          , TAnyType<
                TParent
              , TCallStack
              , creator
              , TAllocator
              , TDeps
              , TRefs
              , TVisitor
              , TPolicies
            >
        >::type
        create(const TAllocator& allocator
             , TDeps& deps
             , TRefs& refs
             , const TVisitor& visitor
             , const TPolicies& policies) {
            return TAnyType<
                TParent
              , TCallStack
              , creator
              , TAllocator
              , TDeps
              , TRefs
              , TVisitor
              , TPolicies
            >(*this, allocator, deps, refs, visitor, policies);
        }

        template<
            typename T
          , typename // TParent - not used
          , typename TCallStack
          , typename TAllocator
          , typename TDeps
          , typename TRefs
          , typename TVisitor
          , typename TPolicies
        >
        typename disable_if<is_same<T, TAnyType<> >, wrappers::universal<T> >::type
        create(const TAllocator& allocator
             , TDeps& deps
             , TRefs& refs
             , const TVisitor& visitor
             , const TPolicies& policies) {
            typedef typename TBinder<TDependecies>::template
                resolve<T, TCallStack>::type dependency_type;

            BOOST_DI_FEATURE_EXAMINE_CALL_STACK(
                typedef typename mpl::push_back<TCallStack, T>::type call_stack_type;
            )

            BOOST_DI_FEATURE_NO_EXAMINE_CALL_STACK(
                typedef TCallStack call_stack_type;
            )

            typedef data<T, call_stack_type, dependency_type> data_type;
            assert_policies<typename TPolicies::types, data_type>(policies);
            (visitor)(data_type());

            return create_impl<T, dependency_type, call_stack_type>(
                allocator, deps, refs, visitor, policies
            );
        }

    private:

    template<
        typename T
      , typename TDependency
      , typename TCtor
      , typename TCallStack
      , typename TAllocator
      , typename TDeps
      , typename TRefs
      , typename TVisitor
      , typename TPolicies
    >
    typename enable_if_c<
        mpl::size<TCtor>::value == 0
      , typename TDependency::expected*
    >::type
    create_impl(const TAllocator& allocator
              , TDeps& deps
              , TRefs& refs
              , const TVisitor& visitor
              , const TPolicies& policies) {
        (void)deps;
        (void)refs;
        (void)visitor;
        (void)policies;
        return allocator.template
            allocate<typename TDependency::expected, typename TDependency::given>(
               

            );

      }

    template<
        typename T
      , typename TDependency
      , typename TCtor
      , typename TCallStack
      , typename TAllocator
      , typename TDeps
      , typename TRefs
      , typename TVisitor
      , typename TPolicies
    >
    typename enable_if_c<
        mpl::size<TCtor>::value == 1
      , typename TDependency::expected*
    >::type
    create_impl(const TAllocator& allocator
              , TDeps& deps
              , TRefs& refs
              , const TVisitor& visitor
              , const TPolicies& policies) {
        (void)deps;
        (void)refs;
        (void)visitor;
        (void)policies;
        return allocator.template
            allocate<typename TDependency::expected, typename TDependency::given>(
                create< typename mpl::at_c<TCtor, 0>::type , T , TCallStack >(allocator, deps, refs, visitor, policies)

            );

      }

    template<
        typename T
      , typename TDependency
      , typename TCtor
      , typename TCallStack
      , typename TAllocator
      , typename TDeps
      , typename TRefs
      , typename TVisitor
      , typename TPolicies
    >
    typename enable_if_c<
        mpl::size<TCtor>::value == 2
      , typename TDependency::expected*
    >::type
    create_impl(const TAllocator& allocator
              , TDeps& deps
              , TRefs& refs
              , const TVisitor& visitor
              , const TPolicies& policies) {
        (void)deps;
        (void)refs;
        (void)visitor;
        (void)policies;
        return allocator.template
            allocate<typename TDependency::expected, typename TDependency::given>(
                create< typename mpl::at_c<TCtor, 0>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 1>::type , T , TCallStack >(allocator, deps, refs, visitor, policies)

            );

      }

    template<
        typename T
      , typename TDependency
      , typename TCtor
      , typename TCallStack
      , typename TAllocator
      , typename TDeps
      , typename TRefs
      , typename TVisitor
      , typename TPolicies
    >
    typename enable_if_c<
        mpl::size<TCtor>::value == 3
      , typename TDependency::expected*
    >::type
    create_impl(const TAllocator& allocator
              , TDeps& deps
              , TRefs& refs
              , const TVisitor& visitor
              , const TPolicies& policies) {
        (void)deps;
        (void)refs;
        (void)visitor;
        (void)policies;
        return allocator.template
            allocate<typename TDependency::expected, typename TDependency::given>(
                create< typename mpl::at_c<TCtor, 0>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 1>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 2>::type , T , TCallStack >(allocator, deps, refs, visitor, policies)

            );

      }

    template<
        typename T
      , typename TDependency
      , typename TCtor
      , typename TCallStack
      , typename TAllocator
      , typename TDeps
      , typename TRefs
      , typename TVisitor
      , typename TPolicies
    >
    typename enable_if_c<
        mpl::size<TCtor>::value == 4
      , typename TDependency::expected*
    >::type
    create_impl(const TAllocator& allocator
              , TDeps& deps
              , TRefs& refs
              , const TVisitor& visitor
              , const TPolicies& policies) {
        (void)deps;
        (void)refs;
        (void)visitor;
        (void)policies;
        return allocator.template
            allocate<typename TDependency::expected, typename TDependency::given>(
                create< typename mpl::at_c<TCtor, 0>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 1>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 2>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 3>::type , T , TCallStack >(allocator, deps, refs, visitor, policies)

            );

      }

    template<
        typename T
      , typename TDependency
      , typename TCtor
      , typename TCallStack
      , typename TAllocator
      , typename TDeps
      , typename TRefs
      , typename TVisitor
      , typename TPolicies
    >
    typename enable_if_c<
        mpl::size<TCtor>::value == 5
      , typename TDependency::expected*
    >::type
    create_impl(const TAllocator& allocator
              , TDeps& deps
              , TRefs& refs
              , const TVisitor& visitor
              , const TPolicies& policies) {
        (void)deps;
        (void)refs;
        (void)visitor;
        (void)policies;
        return allocator.template
            allocate<typename TDependency::expected, typename TDependency::given>(
                create< typename mpl::at_c<TCtor, 0>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 1>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 2>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 3>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 4>::type , T , TCallStack >(allocator, deps, refs, visitor, policies)

            );

      }

    template<
        typename T
      , typename TDependency
      , typename TCtor
      , typename TCallStack
      , typename TAllocator
      , typename TDeps
      , typename TRefs
      , typename TVisitor
      , typename TPolicies
    >
    typename enable_if_c<
        mpl::size<TCtor>::value == 6
      , typename TDependency::expected*
    >::type
    create_impl(const TAllocator& allocator
              , TDeps& deps
              , TRefs& refs
              , const TVisitor& visitor
              , const TPolicies& policies) {
        (void)deps;
        (void)refs;
        (void)visitor;
        (void)policies;
        return allocator.template
            allocate<typename TDependency::expected, typename TDependency::given>(
                create< typename mpl::at_c<TCtor, 0>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 1>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 2>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 3>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 4>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 5>::type , T , TCallStack >(allocator, deps, refs, visitor, policies)

            );

      }

    template<
        typename T
      , typename TDependency
      , typename TCtor
      , typename TCallStack
      , typename TAllocator
      , typename TDeps
      , typename TRefs
      , typename TVisitor
      , typename TPolicies
    >
    typename enable_if_c<
        mpl::size<TCtor>::value == 7
      , typename TDependency::expected*
    >::type
    create_impl(const TAllocator& allocator
              , TDeps& deps
              , TRefs& refs
              , const TVisitor& visitor
              , const TPolicies& policies) {
        (void)deps;
        (void)refs;
        (void)visitor;
        (void)policies;
        return allocator.template
            allocate<typename TDependency::expected, typename TDependency::given>(
                create< typename mpl::at_c<TCtor, 0>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 1>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 2>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 3>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 4>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 5>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 6>::type , T , TCallStack >(allocator, deps, refs, visitor, policies)

            );

      }

    template<
        typename T
      , typename TDependency
      , typename TCtor
      , typename TCallStack
      , typename TAllocator
      , typename TDeps
      , typename TRefs
      , typename TVisitor
      , typename TPolicies
    >
    typename enable_if_c<
        mpl::size<TCtor>::value == 8
      , typename TDependency::expected*
    >::type
    create_impl(const TAllocator& allocator
              , TDeps& deps
              , TRefs& refs
              , const TVisitor& visitor
              , const TPolicies& policies) {
        (void)deps;
        (void)refs;
        (void)visitor;
        (void)policies;
        return allocator.template
            allocate<typename TDependency::expected, typename TDependency::given>(
                create< typename mpl::at_c<TCtor, 0>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 1>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 2>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 3>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 4>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 5>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 6>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 7>::type , T , TCallStack >(allocator, deps, refs, visitor, policies)

            );

      }

    template<
        typename T
      , typename TDependency
      , typename TCtor
      , typename TCallStack
      , typename TAllocator
      , typename TDeps
      , typename TRefs
      , typename TVisitor
      , typename TPolicies
    >
    typename enable_if_c<
        mpl::size<TCtor>::value == 9
      , typename TDependency::expected*
    >::type
    create_impl(const TAllocator& allocator
              , TDeps& deps
              , TRefs& refs
              , const TVisitor& visitor
              , const TPolicies& policies) {
        (void)deps;
        (void)refs;
        (void)visitor;
        (void)policies;
        return allocator.template
            allocate<typename TDependency::expected, typename TDependency::given>(
                create< typename mpl::at_c<TCtor, 0>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 1>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 2>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 3>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 4>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 5>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 6>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 7>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 8>::type , T , TCallStack >(allocator, deps, refs, visitor, policies)

            );

      }

    template<
        typename T
      , typename TDependency
      , typename TCtor
      , typename TCallStack
      , typename TAllocator
      , typename TDeps
      , typename TRefs
      , typename TVisitor
      , typename TPolicies
    >
    typename enable_if_c<
        mpl::size<TCtor>::value == 10
      , typename TDependency::expected*
    >::type
    create_impl(const TAllocator& allocator
              , TDeps& deps
              , TRefs& refs
              , const TVisitor& visitor
              , const TPolicies& policies) {
        (void)deps;
        (void)refs;
        (void)visitor;
        (void)policies;
        return allocator.template
            allocate<typename TDependency::expected, typename TDependency::given>(
                create< typename mpl::at_c<TCtor, 0>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 1>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 2>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 3>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 4>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 5>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 6>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 7>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 8>::type , T , TCallStack >(allocator, deps, refs, visitor, policies) , create< typename mpl::at_c<TCtor, 9>::type , T , TCallStack >(allocator, deps, refs, visitor, policies)

            );

      }

        template<
            typename T
          , typename TDependency
          , typename TCallStack
          , typename TAllocator
          , typename TDeps
          , typename TRefs
          , typename TVisitor
          , typename TPolicies
        >
        typename enable_if_c<
            !mpl::size<scope_create<TDependency> >::value
          , wrappers::universal<T>
        >::type
        create_impl(const TAllocator&
                  , TDeps& deps
                  , TRefs& refs
                  , const TVisitor&
                  , const TPolicies&) {
            return wrappers::universal<T>(
                refs, acquire<TDependency>(deps).create()
            );
        }

        template<
            typename T
          , typename TDependency
          , typename TCallStack
          , typename TAllocator
          , typename TDeps
          , typename TRefs
          , typename TVisitor
          , typename TPolicies
        >
        typename disable_if_c<
            !mpl::size<scope_create<TDependency> >::value
          , wrappers::universal<T> >::type
        create_impl(const TAllocator& allocator
                  , TDeps& deps
                  , TRefs& refs
                  , const TVisitor& visitor
                  , const TPolicies& policies) {
            typedef typename type_traits::ctor_traits<
                typename TDependency::given
            >::type ctor_type;

            return wrappers::universal<T>(
                refs
              , acquire<TDependency>(deps).create(
                    boost::bind(
                        &creator::create_impl<
                            T
                          , TDependency
                          , ctor_type
                          , TCallStack
                          , TAllocator
                          , TDeps
                          , TRefs
                          , TVisitor
                          , TPolicies
                        >
                      , this
                      , boost::cref(allocator)
                      , boost::ref(deps)
                      , boost::ref(refs)
                      , boost::cref(visitor)
                      , boost::cref(policies)
                    )
                )
            );
        }

        template<typename TSeq, typename, typename TPolicies>
        static typename enable_if<mpl::empty<TSeq> >::type
        assert_policies(const TPolicies&) { }

        template<typename TSeq, typename T, typename TPolicies>
        static typename disable_if<mpl::empty<TSeq> >::type
        assert_policies(const TPolicies& policies) {
            typedef typename mpl::front<TSeq>::type policy;
            static_cast<const policy&>(policies).template assert_policy<T>();
            assert_policies<typename mpl::pop_front<TSeq>::type, T>(policies);
        }

        template<typename TDependency, typename TDeps>
        typename enable_if<is_base_of<TDependency, TDeps>, TDependency&>::type
        acquire(TDeps& deps) {
            return static_cast<TDependency&>(deps);
        }

        template<typename TDependency, typename TDeps>
        typename disable_if<is_base_of<TDependency, TDeps>, TDependency&>::type
        acquire(TDeps&) {
            typename scopes_type::const_iterator it = scopes_.find(&typeid(TDependency));
            if (it != scopes_.end()) {
                return *static_cast<TDependency*>(it->second.get());
            }

            aux::shared_ptr<TDependency> dependency(new TDependency());
            scopes_[&typeid(TDependency)] = dependency;
            return *dependency;
        }

        TBinder<TDependecies> binder_;
        scopes_type scopes_;
    };

    } // namespace core
    } // namespace di
    } // namespace boost


namespace boost {
namespace di {
namespace type_traits {

template<typename T>
class has_value
{
    struct base_impl { int value; };
    struct base
        : base_impl
        , mpl::if_<is_class<T>, T, mpl::void_>::type
    { base() { } };

    template<typename U>
    static mpl::aux::no_tag test(
        U*
      , non_type<int base_impl::*, &U::value>* = 0
    );

    static mpl::aux::yes_tag test(...);

public:
    typedef has_value type;

    BOOST_STATIC_CONSTANT(
        bool
      , value = sizeof(test((base*)0)) == sizeof(mpl::aux::yes_tag)
    );
};

} // namespace type_traits
} // namespace di
} // namespace boost


    namespace boost {

    namespace mpl {
        struct string_tag;
        template<typename> struct c_str;
    } // namespace mpl

    namespace di {
    namespace core {

    BOOST_MPL_HAS_XXX_TRAIT_DEF(tag)

    template<typename, typename = void>
    struct is_mpl_string
        : mpl::false_
    { };

    template<typename T>
    struct is_mpl_string<T, typename enable_if<has_tag<T> >::type>
        : is_same<mpl::string_tag, typename T::tag>
    { };

    template<typename T>
    struct is_explicit
        : mpl::or_<
              type_traits::has_value<T>
            , is_mpl_string<T>
          >
    { };

    class allocator
    {
    public:
        template<typename TExpected, typename TGiven>
        typename disable_if<is_explicit<TGiven>, TExpected*>::type
        allocate() const {
            return new TGiven();
        }

        template<typename TExpected, typename TGiven>
        typename enable_if<type_traits::has_value<TGiven>, TExpected*>::type
        allocate() const {
            return new TExpected(TGiven::value);
        }

        template<typename TExpected, typename TGiven>
        typename enable_if<is_mpl_string<TGiven>, TExpected*>::type
        allocate() const {
            return new TExpected(mpl::c_str<TGiven>::value);
        }

    template<typename TExpected, typename TGiven, typename... TArgs>
    TExpected* allocate(TArgs&&... args) const {
        return new TGiven(::std::forward<decltype(args)>(args)...);
    }
    };

    } // namespace core
    } // namespace di
    } // namespace boost


namespace boost {
namespace di {
namespace type_traits {

template<typename, typename = void>
class has_call;

template<typename T>
class has_call<T, void>
{
    struct base_impl { void call() { } };
    struct base : T, base_impl { base() { } };

    template<typename U>
    static mpl::aux::no_tag test(
        U*
      , non_type<void (base_impl::*)(), &U::call>* = 0
    );

    template<typename>
    static mpl::aux::yes_tag test(...);

public:
    typedef has_call type;

    BOOST_STATIC_CONSTANT(
        bool
      , value = sizeof(test<base>(0)) == sizeof(mpl::aux::yes_tag)
    );
};

template<typename T, typename TAction>
class has_call
{
    template<typename>
    struct void_ { };

    template<typename S, typename U>
    friend U& operator,(const U&, void_<S>);

    struct base : T
    {
        using T::call;
        mpl::aux::no_tag call(...) const;
    };

    template<typename, typename = void>
    struct base_call
        : mpl::false_
    { };

    template<typename TDummy>
    struct base_call<mpl::true_, TDummy>
        : is_same<
              BOOST_DI_FEATURE_DECLTYPE(
                 ((((base*)0)->call(*(TAction*)0)), void_<T>())
              )
            , void_<T>
          >
    { };

public :
    typedef has_call type;

    BOOST_STATIC_CONSTANT(
        bool
      , value = base_call<mpl::bool_<has_call<T>::value> >::value
    );
};

} // namespace type_traits
} // namespace di
} // namespace boost


    namespace boost {
    namespace di {
    namespace core {

    template<
        typename TDependecies = mpl::vector0<>
      , template<
            typename
          , template<typename> class = ::boost::di::core::binder
          , template<
                typename
              , typename
              , typename
              , typename
              , typename
              , typename
              , typename
              , typename
            >
            class = ::boost::di::core::any_type
        > class TCreator = creator
      , template<
            typename = ::boost::mpl::vector0<>
          , typename = ::boost::di::core::never< ::boost::mpl::_1 >
          , typename = void
        > class TPool = pool
      , typename TDefaultAllocator = allocator
    >
    class module
        : public TPool<TDependecies>
    {
        template<
            typename
          , template<
                typename
              , template<typename> class
              , template<
                    typename
                  , typename
                  , typename
                  , typename
                  , typename
                  , typename
                  , typename
                  , typename
                >
                class
            > class
          , template<typename, typename, typename> class
          , typename
        > friend class module;

        class empty_visitor
        {
        public:
            template<typename T>
            void operator()(const T&) const { }
        };

    public:
        typedef TDependecies deps;

        explicit module(const TCreator<TDependecies>& creator = TCreator<TDependecies>())
            : creator_(creator)
        { }

    // bind<...>, etc.   -> ignore
    // module<....>      -> get all dependencies from the module
    // dependency<....>  -> pass

    template<typename... TArgs>
    explicit module(const TArgs&... args)
        : TPool<deps>(
              TPool<
                  ::boost::mpl::vector<TArgs...>
                , mpl::not_<
                      mpl::or_<
                          mpl::contains<deps, mpl::_>
                        , has_types<mpl::_>
                      >
                  >
              >(args...)
            , init()
          )
    { }

    template<typename T, typename... TPolicies>
    T create(const TPolicies&... policies) {
        typedef mpl::vector0<> call_stack;
        TPool< ::boost::mpl::vector<TPolicies...> > policies_(policies...);
        std::vector<aux::shared_ptr<void> > refs_;

        return creator_.template create<T, T, call_stack>(
            TDefaultAllocator()
          , static_cast<TPool<deps>&>(*this)
          , refs_
          , empty_visitor()
          , policies_
        );
    }

    template<typename T, typename TAllocator, typename... TPolicies>
    T allocate(const TAllocator& allocator, const TPolicies&... policies) {
        typedef mpl::vector0<> call_stack;
        TPool< ::boost::mpl::vector<TPolicies...> > policies_(policies...);
        std::vector<aux::shared_ptr<void> > refs_;

        return creator_.template create<T, T, call_stack>(
            allocator
          , static_cast<TPool<deps>&>(*this)
          , refs_
          , empty_visitor()
          , policies_
        );
    }

        template<typename T>
        T create() {
            typedef mpl::vector0<> call_stack;
            std::vector<aux::shared_ptr<void> > refs_;

            return creator_.template create<T, T, call_stack>(
                TDefaultAllocator()
              , static_cast<TPool<deps>&>(*this)
              , refs_
              , empty_visitor()
              , TPool<>()
            );
        }

        template<typename T, typename TAllocator>
        T allocate(const TAllocator& allocator) {
            typedef mpl::vector0<> call_stack;
            std::vector<aux::shared_ptr<void> > refs_;

            return creator_.template create<T, T, call_stack>(
                allocator
              , static_cast<TPool<deps>&>(*this)
              , refs_
              , empty_visitor()
              , TPool<>()
            );
        }

        template<typename T, typename TVisitor>
        T visit(const TVisitor& visitor) {
            typedef mpl::vector0<> call_stack;
            std::vector<aux::shared_ptr<void> > refs_;

            return creator_.template create<T, T, call_stack>(
                TDefaultAllocator()
              , static_cast<TPool<deps>&>(*this)
              , refs_
              , visitor
              , TPool<>()
            );
        }

        template<typename TAction>
        void call(const TAction& action) {
            call_impl<deps>(static_cast<TPool<deps>&>(*this), action);
        }

    private:
        template<typename TSeq, typename T, typename TAction>
        typename enable_if<mpl::empty<TSeq> >::type call_impl(T&, const TAction&) { }

        template<typename TSeq, typename T, typename TAction>
        typename enable_if<
            mpl::and_<
                mpl::not_<mpl::empty<TSeq> >
              , type_traits::has_call<typename mpl::front<TSeq>::type, TAction>
            >
        >::type
        call_impl(T& deps, const TAction& action) {
            static_cast<typename mpl::front<TSeq>::type&>(deps).call(action);
            call_impl<typename mpl::pop_front<TSeq>::type>(deps, action);
        }

        template<typename TSeq, typename T, typename TAction>
        typename disable_if<
            mpl::or_<
                mpl::empty<TSeq>
              , type_traits::has_call<typename mpl::front<TSeq>::type, TAction>
            >
        >::type
        call_impl(T& deps, const TAction& action) {
            call_impl<typename mpl::pop_front<TSeq>::type>(deps, action);
        }

        TCreator<TDependecies> creator_;
    };

    } // namespace core
    } // namespace di
    } // namespace boost


namespace boost {
namespace di {
namespace type_traits {

template<typename T>
class has_configure
{
    struct base_impl { void configure() { } };
    struct base
        : base_impl
        , mpl::if_<is_class<T>, T, mpl::void_>::type
    { base() { } };

    template<typename U>
    static mpl::aux::no_tag test(
        U*
      , non_type<void (base_impl::*)(), &U::configure>* = 0
    );

    template<typename>
    static mpl::aux::yes_tag test(...);

public:
    typedef has_configure type;

    BOOST_STATIC_CONSTANT(
        bool
      , value = sizeof(test<base>(0)) == sizeof(mpl::aux::yes_tag)
    );
};

} // namespace type_traits
} // namespace di
} // namespace boost


    namespace boost {
    namespace di {

    namespace detail {

    template<typename T>
    struct default_scope
        : scope<scopes::deduce>::bind<T>
    { };

    BOOST_MPL_HAS_XXX_TRAIT_DEF(deps)

    template<typename T>
    struct is_module
        : mpl::or_<
              has_deps<T>
            , type_traits::has_configure<T>
          >
    { };

    template<typename T, typename = void>
    struct get_module
    {
        typedef T type;
    };

    template<typename T>
    struct get_module<T, typename enable_if<type_traits::has_configure<T> >::type>
    {
        typedef typename type_traits::function_traits<
            BOOST_DI_FEATURE_DECLTYPE(&T::configure)
        >::result_type type;
    };

    template<typename T, typename = void>
    struct get_deps
    {
        typedef typename T::deps type;
    };

    template<typename T>
    struct get_deps<T, typename enable_if<type_traits::has_configure<T> >::type>
    {
        typedef typename get_module<T>::type::deps type;
    };

    template<
        typename TSeq
      , typename TDefaultScope = default_scope<mpl::_2>
    >
    struct concepts
        : mpl::fold<
              TSeq
            , mpl::vector0<>
            , mpl::copy<
                  mpl::if_<
                      mpl::is_sequence<mpl::_2>
                    , mpl::_2
                    , mpl::if_<
                          is_module<mpl::_2>
                        , get_deps<mpl::_2>
                        , TDefaultScope
                      >
                  >
                , mpl::back_inserter<mpl::_1>
              >
          >::type
    { };

    } // namespace detail

    template<typename... T_MPL>
    class injector
        : public core::module<
              typename detail::concepts<
                  ::boost::mpl::vector<T_MPL...>
              >::type
          >
    {
        template<typename TSeq = mpl::vector0<> >
        struct joint_concepts
            : detail::concepts<
                  mpl::joint_view<
                      ::boost::mpl::vector<T_MPL...>
                    , TSeq
                  >
              >::type
        { };

    public:
        injector() { }

    template<typename... TArgs>
    explicit injector(const TArgs&... args)
        : core::module<typename joint_concepts<>::type>(
              pass_arg(args)...
          )
    { }

    private:
        template<typename T>
        const T& pass_arg(const T& arg
                        , typename disable_if<type_traits::has_configure<T> >::type* = 0) const {
            return arg;
        }

        template<typename T>
        typename detail::get_module<T>::type
        pass_arg(const T& arg
               , typename enable_if<type_traits::has_configure<T> >::type* = 0) const {
            return arg.configure();
        }
    };

    } // namespace di
    } // namespace boost


    namespace boost {
    namespace di {

    BOOST_MPL_HAS_XXX_TRAIT_DEF(scope)

    inline injector<> make_injector() {
        return injector<>();
    }

    template<typename... TArgs>
    injector<typename detail::concepts< ::boost::mpl::vector<TArgs...> >::type>
    inline make_injector(const TArgs&... args) {
        return injector<
            typename detail::concepts<
                ::boost::mpl::vector<TArgs...>
              , mpl::if_<
                    has_scope<mpl::_2>
                  , detail::default_scope<mpl::_2>
                  , mpl::_2 // argument not supported
                >
            >::type
        >(args...);
    }

    } // namespace di
    } // namespace boost

namespace boost {
namespace di {

template<typename T>
class provider
{
public:
    virtual ~provider() { }
    virtual T get() const = 0;
};

} // namespace di
} // namespace boost


namespace boost {
namespace di {
namespace policies {

BOOST_MPL_HAS_XXX_TRAIT_DEF(element_type)
BOOST_MPL_HAS_XXX_TRAIT_DEF(value_type)

struct allow_smart_ptrs
{
    template<typename T>
    struct allow
        : has_element_type<typename type_traits::remove_accessors<T>::type>
    { };
};

struct allow_refs
{
    template<typename T>
    struct allow
        : mpl::and_<
              mpl::not_<is_const<typename remove_reference<T>::type> >
            , is_reference<T>
            , mpl::not_<
                  has_element_type<typename type_traits::remove_accessors<T>::type>
              >
          >
    { };
};

struct allow_const_refs
{
    template<typename T>
    struct allow
        : mpl::and_<
              is_const<typename remove_reference<T>::type>
            , is_reference<T>
            , mpl::not_<
                  has_element_type<typename type_traits::remove_accessors<T>::type>
              >
          >
    { };
};

struct allow_rvalue_refs
{
    template<typename T>
    struct allow
        : is_rvalue_reference<T>
    { };
};

struct allow_ptrs
{
    template<typename T>
    struct allow
        : is_pointer<T>
    { };
};

struct allow_copies
{
    template<typename T>
    struct allow
        : mpl::and_<
               mpl::not_<is_reference<T> >
             , mpl::not_<is_pointer<T> >
             , mpl::not_<is_rvalue_reference<T> >
             , mpl::not_<has_element_type<typename type_traits::remove_accessors<T>::type> >
          >
    { };
};

BOOST_DI_WKND(NO_MSVC)(
    template<typename... TArgs_MPL>
    class parameters_permission
    {
        typedef ::boost::mpl::vector<TArgs_MPL...> allow_types;

        template<typename T>
        struct value_type
        {
            typedef typename T::value_type type;
        };

        template<typename TAllow, typename T>
        struct is_parameter_permitted_impl
            : TAllow::template allow<T>
        { };

        template<typename, typename, typename = void>
        struct is_parameter_permitted_nested_impl
            : mpl::true_
        { };

        template<typename TAllow, typename T>
        struct is_parameter_permitted_nested_impl<
            TAllow
          , T
          , typename enable_if<has_value_type<T> >::type
        >
            : TAllow::template allow<typename value_type<T>::type>
        { };

        template<typename T>
        struct is_parameter_permitted_nested
            : mpl::bool_<
                  mpl::count_if<
                      allow_types
                    , is_parameter_permitted_nested_impl<
                          mpl::_
                        , typename type_traits::remove_accessors<T>::type
                      >
                  >::value != 0
              >
        { };

        template<typename T>
        struct is_parameter_permitted
            : mpl::bool_<
                  mpl::count_if< allow_types
                    , mpl::and_<
                          is_parameter_permitted_impl<mpl::_, T>
                        , is_parameter_permitted_nested<T>
                      >
                  >::value != 0
              >
        { };

    public:
        template<typename T>
        void assert_policy() const {
            BOOST_DI_ASSERT_MSG(
                is_parameter_permitted<typename T::type>::value
              , PARAMETER_NOT_PERMITTED
              , typename T::type
            );
        }
    };
)

} // namespace policies
} // namespace di
} // namespace boost


namespace boost {
namespace di {
namespace policies {

class circular_dependencies
{
    template<typename TCallStack>
    struct is_unique_call_stack
        : mpl::bool_<
              static_cast<std::size_t>(mpl::accumulate<
                  typename mpl::transform<
                      TCallStack
                    , mpl::count<TCallStack, mpl::_>
                  >::type
                , mpl::int_<0>
                , mpl::plus<mpl::_1, mpl::_2>
              >::type::value
            ) == mpl::size<TCallStack>::value
          >
    { };

public:
    template<typename T>
    void assert_policy() const {
       BOOST_DI_ASSERT_MSG(
            is_unique_call_stack<typename T::call_stack>::value
          , CIRCULAR_DEPENDENCIES_ARE_NOT_ALLOWED
          , typename T::call_stack
        );
    }
};

} // namespace policies
} // namespace di
} // namespace boost


namespace boost {
namespace di {
namespace policies {

template<typename TValueType>
struct allow_type
{
    template<typename T>
    struct allow
        : is_same<T, TValueType>
    { };
};

template<typename TExpr>
struct allow_type_expr
{
    template<typename T>
    struct allow
        : mpl::apply<TExpr, T>::type
    { };
};

template<typename... TArgs_MPL>
class creation_permission
{
    typedef ::boost::mpl::vector<TArgs_MPL...> permitted_types;

    struct not_resolved
    {
        typedef not_resolved type;

        template<typename>
        struct rebind
        {
            typedef not_resolved other;
        };
    };

    template<typename TAllow, typename T>
    struct is_type_permitted_impl
        : TAllow::template allow<T>
    { };

    template<typename T>
    struct is_type_permitted
        : mpl::or_<
              mpl::not_<
                  is_same<
                      typename T::binder::template resolve<
                          typename T::type
                        , mpl::vector0<>
                        , not_resolved
                      >::type
                    , not_resolved
                  >
              >
            , mpl::bool_<
                  mpl::count_if<
                      permitted_types
                    , is_type_permitted_impl<mpl::_, typename T::type>
                  >::value != 0
              >
          >
    { };

public:
    template<typename T>
    void assert_policy() const {
       BOOST_DI_ASSERT_MSG(
            is_type_permitted<T>::value
          , TYPE_HAS_TO_BE_EXPLICITLY_BINDED
          , typename T::type
        );
    }
};

} // namespace policies
} // namespace di
} // namespace boost


namespace boost {
namespace di {
namespace policies {

template<typename TScope>
struct allow_scope
{
    template<typename T>
    struct allow
        : is_same<T, TScope>
    { };
};

template<>
struct allow_scope<scopes::deduce>; // disabled

template<typename... TArgs_MPL>
class scopes_permission
{
    typedef ::boost::mpl::vector<TArgs_MPL...> permitted_types;

    template<typename TAllow, typename TScope>
    struct is_scope_permitted_impl
        : TAllow::template allow<TScope>
    { };

    template<typename TScope>
    struct is_scope_permitted
        : mpl::bool_<
              mpl::count_if<
                  permitted_types
                , is_scope_permitted_impl<mpl::_, TScope>
              >::value != 0
          >
    { };

public:
    template<typename T>
    void assert_policy() const {
        BOOST_DI_ASSERT_MSG(
            is_scope_permitted<typename T::dependency::scope>::value
          , SCOPE_NOT_PERMITTED
          , typename T::dependency::scope
        );
    }
};

} // namespace policies
} // namespace di
} // namespace boost

#endif
