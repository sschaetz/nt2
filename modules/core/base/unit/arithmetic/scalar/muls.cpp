//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - muls/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 28/11/2010
///
#include <nt2/arithmetic/include/functions/muls.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>


NT2_TEST_CASE_TPL ( muls_signed_int__2_0,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::muls;
  using nt2::tag::muls_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<muls_(T,T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;



  // specific values tests
  NT2_TEST_EQUAL(muls(nt2::Mone<T>(), nt2::Mone<T>()), nt2::One<T>());
  NT2_TEST_EQUAL(muls(nt2::One<T>(), nt2::One<T>()), nt2::One<T>());
  NT2_TEST_EQUAL(muls(nt2::Valmax<T>(), nt2::Valmax<T>()), nt2::Valmax<T>());
  NT2_TEST_EQUAL(muls(nt2::Valmax<T>(),T(2)), nt2::Valmax<T>());
  NT2_TEST_EQUAL(muls(nt2::Valmax<T>(),nt2::Mone<T>()), nt2::Valmin<T>()+nt2::One<T>());
  NT2_TEST_EQUAL(muls(nt2::Valmax<T>(),nt2::One<T>()), nt2::Valmax<T>());
  NT2_TEST_EQUAL(muls(nt2::Valmin<T>(),nt2::Mone<T>()), nt2::Valmax<T>());
  NT2_TEST_EQUAL(muls(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( muls_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{

  using nt2::muls;
  using nt2::tag::muls_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<muls_(T,T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;



  // specific values tests
  NT2_TEST_EQUAL(muls(nt2::One<T>(), nt2::One<T>()), nt2::One<T>());
  NT2_TEST_EQUAL(muls(nt2::Valmax<T>(),T(2)), nt2::Valmax<T>());
  NT2_TEST_EQUAL(muls(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>());
} // end of test for unsigned_int_
