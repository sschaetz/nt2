//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_ONEO_90_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_ONEO_90_HPP_INCLUDED

#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Oneo_90, double
                                , 0, 0x3c360b61         //1/90
                                , 0x3f86c16c16c16c17ll  //1/90
                                );
    NT2_FUNCTION_DECLARE(Oneo_90)
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Oneo_90, Oneo_90);
}

#endif
