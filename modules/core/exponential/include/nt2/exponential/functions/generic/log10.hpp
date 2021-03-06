//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_GENERIC_LOG10_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_GENERIC_LOG10_HPP_INCLUDED

#include <nt2/exponential/functions/log10.hpp>
#include <nt2/exponential/functions/scalar/impl/logs.hpp>
#include <nt2/exponential/functions/simd/common/impl/logs.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <boost/dispatch/meta/as_floating.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_, tag::cpu_
                            , (A0)
                            , (generic_< arithmetic_<A0> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::log10(nt2::tofloat(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log10_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    typedef typename boost::simd::meta::is_native<A0>::type is_native_t;
    NT2_FUNCTOR_CALL(1)
    {
      return details::logarithm<A0,is_native_t>::log10(a0);
    }
  };
} }


#endif
