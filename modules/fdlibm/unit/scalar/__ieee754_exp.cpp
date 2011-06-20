//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 fdlibm toolbox - __ieee754_exp/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of fdlibm components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 03/03/2011
/// 
#include <nt2/toolbox/fdlibm/include/__ieee754_exp.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/exp.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>


NT2_TEST_CASE_TPL ( __ieee754_exp_real__1_0,  NT2_REAL_TYPES)
{
  
  using nt2::fdlibm::__ieee754_exp;
  using nt2::fdlibm::tag::__ieee754_exp_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<__ieee754_exp_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;

} // end of test for real_
