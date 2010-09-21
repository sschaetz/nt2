//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_MADD_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_MADD_HPP_INCLUDED


namespace nt2 { namespace functors
{

  //  no special validate for madd

  /////////////////////////////////////////////////////////////////////////////
  // Compute madd(const A0& a0, const A1& a1, const A2& a2)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<madd_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct result<This(A0,A1,A2)> :
      boost::result_of<meta::arithmetic(A0,A1,A2)>{};

    NT2_FUNCTOR_CALL(3)
    {
       //PUT CODE HERE//
       return a0*a1+a2;
    }
  };
} }


      
#endif
