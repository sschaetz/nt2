//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_DETAILS_DISPATCH_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_DETAILS_DISPATCH_HPP_INCLUDED

#include <boost/dispatch/details/typeof.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/functor/forward.hpp>
#include <boost/dispatch/functor/details/call.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/is_void.hpp>

#define WITH_CARETS(n, A) <BOOST_PP_ENUM_PARAMS(n, A)>
#define WITHOUT_CARETS(n, A)

#include <boost/preprocessor/array/enum.hpp>

#include <boost/dispatch/meta/result_of.hpp>

#if !defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/functor/details/preprocessed/dispatch.hpp>
#else
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/dispatch.hpp")
#undef BOOST_DISPATCH_TYPEOF_
#undef BOOST_FORCEINLINE
#endif

//==============================================================================
// Local macro to generate the fall-through dispatch overload
// What the fuck with adl_helper ? Well, as pointed out by Johannes Schaub
// it is mandated by the standard so ADL kicks in on resolving calls to
// dispatching without having to order them BEFORE the actual dispatch_call
// class definitions. Without it, the whole system brittles.
//==============================================================================
#define M0(z,n,t) , meta::unknown_<A##n>
#define M2(z,n,t) A##n

#define BOOST_DISPATCH_DEFAULT_UNKNOWN_DISPATCH(z,n,t)                          \
template< class Tag, class Site                                                 \
          BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n,class A)>                 \
BOOST_FORCEINLINE                                                               \
boost::dispatch::meta::                                                         \
implement<tag::unknown_, Site, Tag(BOOST_PP_ENUM(n,M2,~))>                      \
dispatching ( meta::unknown_<Tag>, meta::unknown_<Site> BOOST_PP_REPEAT(n,M0,~) \
            , adl_helper = adl_helper()                                         \
            )                                                                   \
{                                                                               \
  boost::dispatch::meta::implement<tag::unknown_, Site                          \
                      , Tag(BOOST_PP_ENUM(n,M2,~))                              \
                      > that;                                                   \
  return that;                                                                  \
}                                                                               \
/**/

//==============================================================================
// Actual dispatching mechanism implementation
//==============================================================================
namespace boost { namespace dispatch { namespace meta
{
  struct adl_helper {};

  //============================================================================
  // Default dispatch overload set for catching calls to unsupported functor
  // overload or unregistered types.
  //============================================================================
  BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY),BOOST_DISPATCH_DEFAULT_UNKNOWN_DISPATCH,~)

} } }

#undef M0
#undef M2
#undef BOOST_DISPATCH_DEFAULT_UNKNOWN_DISPATCH

//==============================================================================
// Local macro to generate the dispatch selector
//==============================================================================
#define M0(z,n,t) , (A##n())
/**/

#define BOOST_DISPATCH_DISPATCH_CALL(z,n,t)                                    \
template<BOOST_PP_ENUM_PARAMS(n,class A)>                                      \
struct apply BOOST_PP_IF(BOOST_PP_EQUAL(n, BOOST_DISPATCH_MAX_ARITY), WITHOUT_CARETS, WITH_CARETS)(n, A)  \
{                                                                              \
  typedef typename default_site<Tag>::type Site;                               \
                                                                               \
  BOOST_DISPATCH_TYPEOF_                                                       \
  ( dispatching ( (typename meta::hierarchy_of<Tag>::type())                   \
                , (typename meta::hierarchy_of<Site>::type())                  \
                  BOOST_PP_REPEAT(n,M0,~)                                      \
                , adl_helper()                                                 \
                )                                                              \
  , type                                                                       \
  )                                                                            \
};                                                                             \
                                                                               \
template<BOOST_PP_ENUM_PARAMS(n,class A)>                                      \
BOOST_FORCEINLINE static                                                       \
typename apply<BOOST_PP_ENUM_PARAMS(n, A)>::type \
call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const &a))                              \
{                                                                              \
  return typename apply<BOOST_PP_ENUM_PARAMS(n, A)>::type(); \
}                                                                              \
/**/

namespace boost { namespace dispatch { namespace meta
{
  //==============================================================================
  // dispatch_call finds the proper call overload for evaluating a given
  // functor over a set of types on a given site
  //==============================================================================
  template<class Tag>
  struct dispatch_call_default
  {
    template<BOOST_PP_ENUM_BINARY_PARAMS(BOOST_DISPATCH_MAX_ARITY, class A, = void BOOST_PP_INTERCEPT)>
    struct apply;

    BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY),BOOST_DISPATCH_DISPATCH_CALL,~)
  };

  template<class Tag>
  struct dispatch_call : dispatch_call_default<Tag>
  {
  };

  template<class T>
  typename meta::hierarchy_of<T const>::type as_hierarchy(T const&)
  {
    return typename meta::hierarchy_of<T const>::type();
  }

  template<class T>
  typename meta::hierarchy_of<T>::type as_hierarchy(T&)
  {
    return typename meta::hierarchy_of<T>::type();
  }

} } }

#undef M0
#undef BOOST_DISPATCH_DISPATCH_TYPES_TPL
#undef BOOST_DISPATCH_DISPATCH_TYPES
#undef BOOST_DISPATCH_DISPATCH_CALL

#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

#include <boost/preprocessor/array/elem.hpp>

#define BOOST_DISPATCH_MAKE_CALL_TYPE_GEN_(z, n, t) typename boost::dispatch::meta::hierarchy_of<BOOST_DISPATCH_PP_STRIP(BOOST_PP_ARRAY_ELEM(n, t))>::type
#define BOOST_DISPATCH_MAKE_CALL_TYPE_GEN2_(z, n, t) BOOST_DISPATCH_PP_STRIP(BOOST_PP_ARRAY_ELEM(n, t))
#define BOOST_DISPATCH_MAKE_CALL_GEN_(z, n, t) boost::dispatch::meta::as_hierarchy(BOOST_PP_ARRAY_ELEM(n, t))

#define BOOST_DISPATCH_MAKE_CALL_GEN(Tag, N, Args) boost::dispatch::meta::dispatch_call<Tag>::call(BOOST_PP_ENUM(N, BOOST_DISPATCH_MAKE_CALL_GEN_, (N, Args))) Args
#define BOOST_DISPATCH_MAKE_CALL_TYPE_GEN(Tag, N, Args) typename boost::dispatch::meta::result_of< typename boost::dispatch::meta::dispatch_call<Tag>::template apply<BOOST_PP_ENUM(N, BOOST_DISPATCH_MAKE_CALL_TYPE_GEN_, (N, Args))>::type (BOOST_PP_ENUM(N, BOOST_DISPATCH_MAKE_CALL_TYPE_GEN2_, (N, Args))) >::type
#define BOOST_DISPATCH_MAKE_CALL_TYPEDEF_GEN(Tag, N, Args, Typename) typedef BOOST_DISPATCH_MAKE_CALL_TYPE_GEN(Tag, N, Args) Typename;

#define BOOST_DISPATCH_MAKE_CALL(Tag, Name, N, Args) BOOST_DISPATCH_MAKE_CALL_GEN(Tag, N, Args)
#define BOOST_DISPATCH_MAKE_CALL_TYPE(Tag, Name, N, Args) BOOST_DISPATCH_MAKE_CALL_TYPE_GEN(Tag, N, Args)
#define BOOST_DISPATCH_MAKE_CALL_TYPEDEF(Tag, Name, N, Args, Typename) typedef BOOST_DISPATCH_MAKE_CALL_TYPE(Tag, Name, N, Args) Typename;

#endif
