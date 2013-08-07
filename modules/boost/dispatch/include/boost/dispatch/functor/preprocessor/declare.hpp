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
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

#define BOOST_DISPATCH_FUNCTION_DECLARE_M0(z,n,t) , meta::unknown_<A##n>
#define BOOST_DISPATCH_FUNCTION_DECLARE_M1(z,n,t) , (typename meta::hierarchy_of<A##n>::type())

#define BOOST_DISPATCH_FUNCTION_DECLARE_(z,n,t)                                \
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
template< class Site_                                                          \
          BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n,class A)                 \
         >                                                                     \
struct dispatch_call<BOOST_PP_TUPLE_ELEM(2, 1, t)(BOOST_PP_ENUM_PARAMS(n,A)), Site_, true>  \
{                                                                              \
  typedef typename boost::mpl::                                                \
          eval_if< is_void<Site_>                                              \
                 , default_site<Site_>                                         \
                 , mpl::identity<Site_>                                        \
                 >::type Site;                                                 \
                                                                               \
  BOOST_DISPATCH_TYPEOF_                                                       \
  ( BOOST_PP_CAT(dispatching_, BOOST_PP_TUPLE_ELEM(2, 0, t)) ( (typename meta::hierarchy_of<BOOST_PP_TUPLE_ELEM(2, 1, t)>::type()) \
                , (typename meta::hierarchy_of<Site>::type())                  \
                  BOOST_PP_REPEAT(n,BOOST_DISPATCH_FUNCTION_DECLARE_M1,~)      \
                , adl_helper()                                                 \
                )                                                              \
  , type0                                                                      \
  )                                                                            \
  typedef typename mpl::eval_if< is_same<type0, int>, dispatch_call<BOOST_PP_TUPLE_ELEM(2, 1, t)(BOOST_PP_ENUM_PARAMS(n,A)), Site, false>, mpl::identity<type0> >::type type; \
};                                                                             \
/**/

#define BOOST_DISPATCH_FUNCTION_DECLARE(NS, Name, Tag) \
BOOST_DISPATCH_CLOSE(NS) \
namespace boost { namespace dispatch { namespace meta \
{ \
  BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY),BOOST_DISPATCH_FUNCTION_DECLARE_,(Name, Tag)) \
} } } \
BOOST_DISPATCH_REOPEN(NS) \
/**/


#endif
