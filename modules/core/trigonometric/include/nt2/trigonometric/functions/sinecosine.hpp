//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
  @file
  @brief Definition of sinecosine function
**/

#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SINECOSINE_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SINECOSINE_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for sinecosine function
    template < class T > struct sinecosine_ : ext::elementwise_< sinecosine_<T> >
    {
      typedef ext::elementwise_< sinecosine_<T> > parent;
    };
 NT2_FUNCTION_DECLARE(sinecosine_)
  }
  /*!
    @brief sinecosine

    @c sinecosine compute simultaneously the  templatized sine and cosine of the input

    @param a0 angle in radian

    @return A Fusion Sequence containing the  templatized sine and cosine of @c a0
  **/

  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinecosine_<A0>, sinecosine, (A1 const&), 2)


  /*!
    @brief sinecosine

    @c sinecosine compute simultaneously the templatized sine and cosine of the input

    @param a0 angle in radian
    @param a1 L-Value that will receive the  templatized sine off @c a0

    @return A Fusion Sequence containing the  templatized cosine of @c a0
  **/

    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinecosine_<A0>, sinecosine, (A1 const&)(A2&),3)

  /*!
    @brief  sinecosine

    @c sinecosine compute simultaneously the templatized sine and cosine of the input

    @param a0 angle in radian
    @param a1 L-Value that will receive the templatized sined off @c a0
    @param a1 L-Value that will receive the templatized cosine off @c a0

  **/
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinecosine_<A0>, sinecosine, (A1 const&)(A2&)(A2&),3)


    }

#endif
