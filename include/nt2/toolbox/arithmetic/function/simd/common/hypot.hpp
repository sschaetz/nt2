//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_HYPOT_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_HYPOT_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/exponent.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/sqrt.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<hypot_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::is_real_convertible<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute hypot(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<hypot_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>  :  meta::as_real<A0>{};


    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (real_,arithmetic_))
    )
    NT2_FUNCTOR_CALL_EVAL_IF(2,       real_)
    {
      typedef typename meta::as_integer<A0, signed>::type int_type;
      typedef ctnts<A0, int_type> cts; 
      A0 x =  abs(a0);
      A0 y =  abs(a1);
      A0 tinf = is_inf(x+y);
      A0 a =  nt2::max(x, y);
      A0 b =  nt2::min(x, y);
      int_type ea =   exponent(a);
      int_type eb  =  exponent(b);
      int_type te1 = is_gt(ea,cts::C1());
      int_type te2 = is_lt(eb,cts::MC1());
      bool te3 = any(te1|te2);
      int_type e = Zero<int_type>();
      if (te3)
      {
        e = sel(te1, cts::MC2(), e);
        e = sel(te2, cts::C1(),e );
        a =  ldexp(a, e);
        b =  ldexp(b, e);
      }
      A0 w = a-b;
      A0 test =  is_gt(w,b);
      A0 t1 = a& cts::M1();
      A0 t2 = a-t1;
      A0 w1_2  = (t1*t1-(b*(-b)-t2*(a+t1)));
      A0 y1 = b& cts::M1();
      A0 y2 = b - y1;
      t1 = simd::native_cast<A0>(simd::native_cast<int_type>(a)+cts::C3()) ;
      t2 = (a+a) - t1;
      A0 w2_2  = (t1*y1-(w*(-w)-(t1*y2+t2*b)));
      w =  sel(test, w1_2, w2_2);
      w = nt2::sqrt(w);
      if (te3) w = ldexp(w, -e);
      return sel(tinf, Inf<A0>(), w);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type; 
      return nt2::hypot(tofloat(a0), tofloat(a1));
    }
  private:
    template < class T, class I = typename meta::as_integer<T, signed>::type>
    struct ctnts;
    template <class I, class CAT> struct ctnts<simd::native<float, CAT>, I>
    {
      typedef I  int_type;
      static inline int_type C1(){ return integral_constant<int_type, 50>();};
      static inline int_type C2(){ return integral_constant<int_type, 60>();};
      static inline int_type MC1(){ return integral_constant<int_type, -50>();};
      static inline int_type MC2(){ return integral_constant<int_type, -60>();};
      static inline int_type C3(){ return integral_constant<int_type, 0x00800000>();};
      static inline int_type M1(){ return integral_constant<int_type, 0xfffff000>();};
    };
    template <class I, class CAT> struct ctnts<simd::native<double, CAT>, I>
    {
      typedef I  int_type;
      static inline int_type C1(){ return integral_constant<int_type, 500>();};
      static inline int_type C2(){ return integral_constant<int_type, 600>();};
      static inline int_type MC1(){ return integral_constant<int_type, -500>();};
      static inline int_type MC2(){ return integral_constant<int_type, -600>();};
      static inline int_type C3(){ return integral_constant<int_type, 0x0010000000000000ll>();}
      static inline int_type M1(){ return integral_constant<int_type, 0xffffffff00000000ll>();};
    };
  };
} }

      
#endif
