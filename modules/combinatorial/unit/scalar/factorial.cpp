//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 combinatorial toolbox - factorial/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of combinatorial components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 07/03/2011
/// 
#include <nt2/toolbox/combinatorial/include/factorial.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>


NT2_TEST_CASE_TPL ( factorial_real__1_0,  NT2_REAL_TYPES)
{
  
  using nt2::factorial;
  using nt2::tag::factorial_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<factorial_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(factorial(nt2::Inf<T>()), nt2::Inf<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Nan<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Three<T>()), nt2::Six<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Two<T>()), nt2::Two<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Zero<T>()), nt2::One<T>(), 0);
} // end of test for real_

NT2_TEST_CASE_TPL ( factorial_integer__1_0,  NT2_INTEGRAL_TYPES)
{
  
  using nt2::factorial;
  using nt2::tag::factorial_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<factorial_(T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(factorial(nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Thousand<T>()), nt2::Valmax<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Three<T>()), nt2::Six<T>(), 0);
  NT2_TEST_ULP_EQUAL(factorial(nt2::Zero<T>()), nt2::One<T>(), 0);
} // end of test for integer_
