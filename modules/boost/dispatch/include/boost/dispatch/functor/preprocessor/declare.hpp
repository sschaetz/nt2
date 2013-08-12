//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_PREPROCESSOR_DECLARE_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_PREPROCESSOR_DECLARE_HPP_INCLUDED

#include <boost/dispatch/functor/details/namespace.hpp>
#include <boost/dispatch/details/parameters.hpp>
#include <boost/dispatch/functor/details/dispatch.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>

#define BOOST_DISPATCH_FUNCTION_DECLARE_M0(z,n,t) , meta::unknown_<A##n>
#define BOOST_DISPATCH_FUNCTION_DECLARE_M1(z,n,t) , (A##n())

#define BOOST_DISPATCH_FUNCTION_DECLARE_F(z,n,t)                               \
template< class Tag, class Site                                                \
          BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n,class A)>                \
BOOST_FORCEINLINE                                                              \
int                                                                            \
BOOST_PP_CAT(dispatching_, BOOST_PP_TUPLE_ELEM(2, 0, t)) ( meta::unknown_<Tag>, meta::unknown_<Site> BOOST_PP_REPEAT(n,BOOST_DISPATCH_FUNCTION_DECLARE_M0,~) \
            , adl_helper = adl_helper()                                        \
            )                                                                  \
{                                                                              \
  return 0;                                                                    \
}                                                                              \
/**/

#define BOOST_DISPATCH_FUNCTION_DECLARE_T(z,n,t)                                \
template<BOOST_PP_ENUM_PARAMS(n, class A)>                                     \
struct apply BOOST_PP_IF(BOOST_PP_EQUAL(n, BOOST_DISPATCH_MAX_ARITY), WITHOUT_CARETS, WITH_CARETS)(n, A) \
{ \
  typedef typename default_site<A0>::type Site;                                \
                                                                               \
  BOOST_DISPATCH_TYPEOF_                                                       \
  ( BOOST_PP_CAT(dispatching_, BOOST_PP_TUPLE_ELEM(2, 0, t)) ( (typename meta::hierarchy_of<BOOST_PP_TUPLE_ELEM(2, 1, t)>::type()) \
                , (typename meta::hierarchy_of<Site>::type())                  \
                  BOOST_PP_REPEAT(n,BOOST_DISPATCH_FUNCTION_DECLARE_M1,~)      \
                , adl_helper()                                                 \
                )                                                              \
  , type0                                                                      \
  )                                                                            \
  typedef typename mpl::eval_if< is_same<type0, int>, dispatch_call_default<BOOST_PP_TUPLE_ELEM(2, 1, t)>::template apply<BOOST_PP_ENUM_PARAMS(n,A)>, mpl::identity<type0> >::type type; \
};                                                                             \
template<BOOST_PP_ENUM_PARAMS(n,class A)>                                      \
BOOST_FORCEINLINE static \
typename apply<BOOST_PP_ENUM_PARAMS(n, A)>::type                               \
call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const &a))      \
{                                                                              \
  return typename apply<BOOST_PP_ENUM_PARAMS(n, A)>::type();                    \
}
/**/

#define BOOST_DISPATCH_FUNCTION_DECLARE(NS, Name, Tag) \
BOOST_DISPATCH_CLOSE(NS) \
namespace boost { namespace dispatch { namespace meta \
{ \
  BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY),BOOST_DISPATCH_FUNCTION_DECLARE_F,(Name, Tag)) \
  template<>                                                                     \
  struct dispatch_call<Tag> \
  { \
    template<BOOST_PP_ENUM_BINARY_PARAMS(BOOST_DISPATCH_MAX_ARITY, class A, = void BOOST_PP_INTERCEPT)> \
    struct apply; \
    BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY),BOOST_DISPATCH_FUNCTION_DECLARE_T,(Name, Tag)) \
  }; \
} } } \
BOOST_DISPATCH_REOPEN(NS) \
/**/


#endif
