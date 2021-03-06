//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TRIL_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TRIL_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief tril generic tag

      Represents the tril function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct tril_ : ext::elementwise_<tril_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<tril_> parent;
    };
  }

  /*!
    @brief Apply a lower-triangular masking to an expression

    Apply a mask on an expression that evaluates to 0 everywhere except on the
    lower triangular part of @c a0.

    @param a0 Expression to mask.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::tril_, tril, 1)


  /*!
    @brief Apply an offset lower-triangular masking to an expression

    Apply a mask on an expression that evaluates to 0 everywhere except on the
    lower triangular part of @c a0 and @c a1 subdiagonal.

    @param a0 Expression to mask.
    @param a1 Diagonal offset to the mask.
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::tril_, tril, 2)
}

#endif
