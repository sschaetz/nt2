//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//=============================================================================
#ifndef NT2_CORE_FUNCTIONS_FLIPUD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FLIPUD_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the flipud function
**/

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/size_as.hpp>
#include <nt2/core/container/dsl/size.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for flipud functor
    **/
    struct flipud_ : ext::elementwise_<flipud_>
    {
      typedef ext::elementwise_<flipud_> parent;
    };
  }

  /*!
    @brief Flip an expression around the horizontal axis

    Return an expression which columns are in reverse order of the input

    @param  a0 Expression to flip
    @return the flipped expression
  **/
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::flipud_       , flipud, 1)
}

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  template<class Domain, int N, class Expr>
  struct  size_of<nt2::tag::flipud_,Domain,N,Expr>
        : meta::size_as<Expr,0>
  {};
} }

#endif
