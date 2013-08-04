//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_CONSTANTS_PIX2_1_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_CONSTANTS_PIX2_1_HPP_INCLUDED

#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

namespace nt2
{
  namespace tag
  {
    // 12.56637061
    BOOST_SIMD_CONSTANT_REGISTER( Pix2_1, double
                                , 1, 0x40c90f00
                                , 0x401921fb54400000LL
                                );
    NT2_FUNCTION_DECLARE(Pix2_1)
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Pix2_1, Pix2_1);
}

#endif
