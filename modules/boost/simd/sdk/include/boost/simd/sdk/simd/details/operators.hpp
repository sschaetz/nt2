//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_OPERATORS_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_OPERATORS_HPP_INCLUDED

#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <boost/dispatch/functor/functor.hpp>
#include <boost/dispatch/meta/is_iterator.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/dispatch/meta/proxy.hpp>
#include <boost/dispatch/meta/is_scalar.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/proto/traits.hpp>

#define BOOST_SIMD_OVERLOAD_UNARY_OP(Tag, Op)                                  \
namespace tag { struct Tag; }                                                  \
template<class A0>                                                             \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
lazy_enable_if< is_value<A0>                                                   \
              , dispatch::meta::                                               \
                call< tag::Tag(A0 const&) >                                    \
         >::type                                                               \
operator Op                                                                    \
(                                                                              \
  A0 const & a0                                                                \
)                                                                              \
{                                                                              \
  return typename dispatch::make_functor<tag::Tag, A0>::type()(a0);            \
}                                                                              \
/**/

#define BOOST_SIMD_OVERLOAD_UNARY_OP_INC(Tag, Op)                              \
namespace tag { struct Tag; }                                                  \
template<class A0>                                                             \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
enable_if< is_value<A0>                                                        \
         , A0&                                                                 \
         >::type                                                               \
operator Op                                                                    \
(                                                                              \
  A0 & a0                                                                      \
)                                                                              \
{                                                                              \
  return a0 = typename dispatch::make_functor<tag::Tag, A0>::type()(a0, 1);    \
}                                                                              \
template<class A0>                                                             \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
enable_if< is_value<A0>                                                        \
         , A0                                                                  \
         >::type                                                               \
operator Op                                                                    \
(                                                                              \
  A0 & a0,                                                                     \
  int                                                                          \
)                                                                              \
{                                                                              \
  A0 const that = a0;                                                          \
  operator Op(a0);                                                             \
  return that;                                                                 \
}                                                                              \
/**/

#define BOOST_SIMD_OVERLOAD_BINARY_OP(Tag, Op)                                 \
namespace tag { struct Tag; }                                                  \
template<class A0, class A1>                                                   \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
lazy_enable_if< mpl::and_< is_value<A0>, is_value<A1> >                        \
              , dispatch::meta::                                               \
                call<tag::Tag(A0 const&, A1 const&)>                           \
              >::type                                                          \
operator Op                                                                    \
(                                                                              \
  A0 const & a0,                                                               \
  A1 const & a1                                                                \
)                                                                              \
{                                                                              \
  return typename dispatch::make_functor<tag::Tag, A0>::type()(a0, a1);        \
}                                                                              \
/**/

#define BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN(Tag, Op)                          \
BOOST_SIMD_OVERLOAD_BINARY_OP(Tag, Op)                                         \
template<class A0, class A1>                                                   \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
enable_if< mpl::and_< is_value<A0>, is_value<A1> >                             \
         , A0&                                                                 \
         >::type                                                               \
operator BOOST_PP_CAT(Op, =)                                                   \
(                                                                              \
  A0       & a0,                                                               \
  A1 const & a1                                                                \
)                                                                              \
{                                                                              \
  a0 = operator Op(a0, a1);                                                    \
  return a0;                                                                   \
}                                                                              \
template<class A0, class A1>                                                   \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
enable_if< mpl::and_< is_value<A0>, is_value<A1> >                             \
         , A0 const&                                                           \
         >::type                                                               \
operator BOOST_PP_CAT(Op, =)                                                   \
(                                                                              \
  A0 const & a0,                                                               \
  A1 const & a1                                                                \
)                                                                              \
{                                                                              \
  a0 = operator Op(a0, a1);                                                    \
  return a0;                                                                   \
}                                                                              \
/**/

namespace boost { namespace simd
{
  template<class T>
  struct is_value
   : mpl::or_< boost::dispatch::details::is_mpl_integral<T>
             , boost::is_fundamental<T>
             , meta::is_native<T>
             , proto::is_expr<T>
             >
  {
  };

  // unary operators
  BOOST_SIMD_OVERLOAD_UNARY_OP( unary_plus_  ,  + )
  BOOST_SIMD_OVERLOAD_UNARY_OP( unary_minus_ ,  - )
  BOOST_SIMD_OVERLOAD_UNARY_OP( complement_  ,  ~ )
  BOOST_SIMD_OVERLOAD_UNARY_OP( logical_not_ ,  ! )
  BOOST_SIMD_OVERLOAD_UNARY_OP_INC( plus_    , ++ )
  BOOST_SIMD_OVERLOAD_UNARY_OP_INC( minus_   , -- )

  // binary operators
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( bitwise_and_ , &  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( bitwise_or_  , |  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( bitwise_xor_ , ^  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( plus_        , +  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( minus_       , -  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( divides_     , /  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( multiplies_  , *  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( modulo_      , %  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( shift_left_  , << )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN( shift_right_ , >> )
  BOOST_SIMD_OVERLOAD_BINARY_OP( logical_and_        , && )
  BOOST_SIMD_OVERLOAD_BINARY_OP( logical_or_         , || )

  // comparison operators
  BOOST_SIMD_OVERLOAD_BINARY_OP( is_equal_           , == )
  BOOST_SIMD_OVERLOAD_BINARY_OP( is_not_equal_       , != )
  BOOST_SIMD_OVERLOAD_BINARY_OP( is_less_            , <  )
  BOOST_SIMD_OVERLOAD_BINARY_OP( is_greater_         , >  )
  BOOST_SIMD_OVERLOAD_BINARY_OP( is_less_equal_      , <= )
  BOOST_SIMD_OVERLOAD_BINARY_OP( is_greater_equal_   , >= )
} }

#undef BOOST_SIMD_OVERLOAD_UNARY_OP
#undef BOOST_SIMD_OVERLOAD_UNARY_OP_INC
#undef BOOST_SIMD_OVERLOAD_BINARY_OP
#undef BOOST_SIMD_OVERLOAD_BINARY_OP_ASSIGN

#endif
