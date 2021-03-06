//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_DIGAMMA_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_DIGAMMA_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief digamma generic tag

     Represents the digamma function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct digamma_ : ext::elementwise_<digamma_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<digamma_> parent;
    };
  }
  /*!
    Computes digamma function,  i.e. the logarithmic derivative of the \f$\gamma\f$ function

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = digamma(x);
    @endcode

    Computes:  \f$\Psi(a_0) = \frac{\Gamma\^prime(x)}{\Gamma(x}\f$

    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::digamma_, digamma, 1)
}

#endif

