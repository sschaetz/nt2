//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_MAX_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_SSE2_MAX_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/arithmetic/functions/max.hpp>
#include <boost/simd/include/functions/simd/is_unord.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/sdk/config/compiler.hpp>
#include <boost/simd/sdk/config.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::max_, boost::simd::tag::sse2_, (A0)
                            , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                              ((simd_<double_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
#if !defined(BOOST_SIMD_NO_NANS) && defined(BOOST_SIMD_COMPILER_GCC)
      // workaround for GCC bug #57057
      return if_else(is_unord(a0, a1), a1, A0(_mm_max_pd(a0, a1)));
#else
      return _mm_max_pd(a0,a1);
#endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::max_, boost::simd::tag::sse2_, (A0)
                            , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                              ((simd_<single_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
#if !defined(BOOST_SIMD_NO_NANS) && defined(BOOST_SIMD_COMPILER_GCC)
      // workaround for GCC bug #57057
      return if_else(is_unord(a0, a1), a1, A0(_mm_max_ps(a0, a1)));
#else
      return _mm_max_ps(a0,a1);
#endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::max_, boost::simd::tag::sse2_, (A0)
                            , ((simd_<int16_<A0>,boost::simd::tag::sse_>))
                              ((simd_<int16_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_max_epi16(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::max_, boost::simd::tag::sse2_, (A0)
                            , ((simd_<uint8_<A0>,boost::simd::tag::sse_>))
                              ((simd_<uint8_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
         return _mm_max_epu8(a0,a1);
    }
  };
} } }

#endif
#endif
