//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 elliptic toolbox - ellik/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of elliptic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 21/02/2011
///
#include <nt2/elliptic/include/functions/ellik.hpp>
#include <boost/simd/sdk/simd/native.hpp>
extern "C" {long double cephes_ellikl(long double,long double);}
#include <nt2/trigonometric/constants.hpp>

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
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/splat.hpp>



NT2_TEST_CASE_TPL ( ellik_real__2_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::ellik;
  using nt2::tag::ellik_;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::call<ellik_(vT,vT)>::type r_t;
  typedef typename nt2::meta::call<ellik_(T,T)>::type sr_t;



  // specific values tests
  NT2_TEST_ULP_EQUAL(ellik(nt2::One<vT>(),nt2::splat<vT>(0))[0], nt2::One<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(ellik(nt2::Pio_2<vT>(),nt2::splat<vT>(0))[0], nt2::Pio_2<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(ellik(nt2::Zero<vT>(),nt2::splat<vT>(0))[0], nt2::Zero<sr_t>(), 0);
} // end of test for floating_
