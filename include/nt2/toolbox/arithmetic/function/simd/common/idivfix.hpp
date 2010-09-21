//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_IDIVFIX_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_IDIVFIX_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/rdivide.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for idivfix

  /////////////////////////////////////////////////////////////////////////////
  // Compute idivfix(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<idivfix_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (real_,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,        real_){ return trunc(a0/a1);    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,  arithmetic_){ return rdivide(a0, a1);    }
  };
} }

      
#endif
