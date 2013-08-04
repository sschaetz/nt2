//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_ONEO_5_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_ONEO_5_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_oneo_5 Oneo_5
 *
 * \par Description
 * Constant Oneo_5 = 1/5
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/oneo_5.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::oneo_5_(A0)>::type
 *     Oneo_5();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Oneo_5
 *
 * \return type T value
 *
 *
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag Oneo_5 of functor Oneo_5
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    BOOST_SIMD_CONSTANT_REGISTER( Oneo_5, double, 0
                                , 0x3e4ccccd, 0x3fc999999999999all
                                );
    BOOST_SIMD_FUNCTION_DECLARE(Oneo_5)
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Oneo_5, Oneo_5)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif

