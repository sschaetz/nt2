//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_REMAINDER_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_REMAINDER_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
   /*!
      @brief  remainder generic tag

      Represents the remainder function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct remainder_ : ext::elementwise_<remainder_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<remainder_> parent;
    };
  }
  /*!
    Computes the remainder of division.
    The return value is a0-n*a1, where n is the value a0/a1,
    rounded to the nearest integer (using round2even).

    @par semantic:
    For any given value @c x, @c y of type @c T:

    @code
    T r = remainder(x, y);
    @endcode

    For floating point values the code is equivalent to:

    @code
    T r = x-divround2even(x, y)*y;
    @endcode

    @par Note:

    As r can be negative, @c remainder is not defined for unsigned types.

    @par Alias

    @c drem

    @param  a0
    @param  a1

    @return      a value of the same type as the input.

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::remainder_, remainder, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::remainder_, drem, 2)
    BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::remainder_, remround2even, 2)
} }

#endif


