//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_MAKE_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_MAKE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_make make
 *
 * \par Description
 * TODO Put description here
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/make.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::make_(A0,A0)>::type
 *     make(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of make
 * \param a1 the second parameter of make
 *
 * \return a value of the common type of the parameters
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag make_ of functor make
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct make_ : ext::unspecified_<make_> { typedef ext::unspecified_<make_> parent; };
    BOOST_SIMD_FUNCTION_DECLARE(make_)
  }

  #define M1(z,n,t) static_cast<typename meta::scalar_of<T>::type>(a##n)

  #define M0(z,n,t)                                                                        \
  template<class T, BOOST_PP_ENUM_PARAMS(n, class A)> BOOST_DISPATCH_FORCE_INLINE          \
  T make(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a))                                      \
  {                                                                                        \
    return boost::dispatch::meta::dispatch_call<tag::make_>::call(                         \
      boost::dispatch::meta::as_hierarchy(                                                 \
        boost::dispatch::meta::as_<T>()                                                    \
      )                                                                                    \
    )(BOOST_PP_ENUM(n, M1, ~));                                                            \
  }

  BOOST_SIMD_PP_REPEAT_POWER_OF_2(M0, ~)
  #undef M0
  #undef M1
} }

#endif
