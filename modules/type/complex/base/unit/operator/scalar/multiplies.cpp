//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 complex.operator toolbox - multiplies/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.operator components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <nt2/include/functions/multiplies.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/mone.hpp>

NT2_TEST_CASE_TPL ( multiplies_real__2_0, BOOST_SIMD_REAL_TYPES)
{

  using nt2::multiplies;
  using nt2::tag::multiplies_;
  typedef std::complex<T> cT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<multiplies_(cT,cT)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;

  NT2_TEST_EQUAL(nt2::multiplies(cT(nt2::Inf<T>(),  nt2::Zero<T>()), cT(nt2::Zero<T>(), nt2::Zero<T>())), cT(nt2::Nan<T>(),  nt2::Zero<T>()));
  NT2_TEST_EQUAL(nt2::multiplies(cT(nt2::Inf<T>(),  nt2::Zero<T>()), cT(nt2::Zero<T>(), nt2::Inf<T>())),  cT(nt2::Zero<T>(), nt2::Inf<T>() ));
  NT2_TEST_EQUAL(nt2::multiplies(cT(nt2::Inf<T>(),  nt2::Zero<T>()), cT(nt2::One<T>(),  nt2::Zero<T>())), cT(nt2::Inf<T>(),  nt2::Zero<T>()));
  NT2_TEST_EQUAL(nt2::multiplies(cT(nt2::Inf<T>(),  nt2::Zero<T>()), cT(nt2::Inf<T>(),  nt2::Zero<T>())), cT(nt2::Inf<T>(),  nt2::Zero<T>()));
  NT2_TEST_EQUAL(nt2::multiplies(cT(nt2::Inf<T>(),  nt2::Inf<T>()),  cT(nt2::Inf<T>(),  nt2::Zero<T>())), cT(nt2::Inf<T>(),  nt2::Inf<T>() ));
  NT2_TEST_EQUAL(nt2::multiplies(cT(nt2::Inf<T>(),  nt2::Zero<T>()), cT(nt2::Inf<T>(),  nt2::Inf<T>())),  cT(nt2::Inf<T>(),  nt2::Inf<T>() ));
  NT2_TEST_EQUAL(nt2::multiplies(cT(nt2::Inf<T>(),  nt2::Inf<T>()),  cT(nt2::Inf<T>(),  nt2::Inf<T>())),  cT(nt2::Nan<T>(),  nt2::Inf<T>() ));
  NT2_TEST_EQUAL(nt2::multiplies(cT(nt2::Inf<T>(),  nt2::Zero<T>()), cT(nt2::One<T>(),  nt2::Zero<T>())), cT(nt2::Inf<T>(),  nt2::Zero<T>()));
  NT2_TEST_EQUAL(nt2::multiplies(cT(nt2::Inf<T>(),  nt2::Zero<T>()), cT(nt2::One<T>(),  nt2::Inf<T>())),  cT(nt2::Inf<T>(),  nt2::Inf<T>() ));
  NT2_TEST_EQUAL(nt2::multiplies(cT(nt2::Inf<T>(),  nt2::Zero<T>()), cT(nt2::One<T>(),  nt2::One<T>())),  cT(nt2::Inf<T>(),  nt2::Inf<T>() ));
  NT2_TEST_EQUAL(nt2::multiplies(cT(nt2::Inf<T>(),  nt2::Inf<T>()),  cT(nt2::One<T>(),  nt2::Zero<T>())), cT(nt2::Inf<T>(),  nt2::Inf<T>() ));
  NT2_TEST_EQUAL(nt2::multiplies(cT(nt2::One<T>(),  nt2::Zero<T>()), cT(nt2::Inf<T>(),  nt2::Inf<T>())) , cT(nt2::Inf<T>(),  nt2::Inf<T>() ));
  NT2_TEST_EQUAL(nt2::multiplies(cT(nt2::Inf<T>(),  nt2::Inf<T>()),  cT(nt2::One<T>(),  nt2::One<T>())),  cT(nt2::Nan<T>(),  nt2::Inf<T>() ));
  NT2_TEST_EQUAL(nt2::multiplies(cT(nt2::One<T>(),  nt2::Inf<T>()),  cT(nt2::Zero<T>(),  nt2::One<T>())),  cT(nt2::Minf<T>(),  nt2::One<T>() ));
  NT2_TEST_EQUAL(nt2::multiplies(cT(nt2::Inf<T>(),  nt2::One<T>()),  cT(nt2::Zero<T>(),  nt2::One<T>())),  cT(nt2::Mone<T>(),  nt2::Inf<T>() ));

}

NT2_TEST_CASE_TPL ( complex_complex, BOOST_SIMD_REAL_TYPES)
{
  using nt2::multiplies;
  using nt2::tag::multiplies_;
  typedef std::complex<T> cT;

  // specific values tests
  const T inf = nt2::Inf<T>();
  const T nan = nt2::Nan<T>();
  const T zer = nt2::Zero<T>();
  const T deu = nt2::Two<T>();

  NT2_TEST_EQUAL(nt2::multiplies(cT(inf, zer), cT(deu, zer)),  cT(inf, zer));
  NT2_TEST_EQUAL(nt2::multiplies(cT(deu, zer), cT(inf, zer)),  cT(inf, zer));
  NT2_TEST_EQUAL(nt2::multiplies(cT(inf, zer), cT(zer, zer)),  cT(nan, zer));
  NT2_TEST_EQUAL(nt2::multiplies(cT(zer, zer), cT(inf, zer)),  cT(nan, zer));
  NT2_TEST_EQUAL(nt2::multiplies(cT(zer, inf), cT(zer, zer)),  cT(zer, nan));
  NT2_TEST_EQUAL(nt2::multiplies(cT(zer, zer), cT(zer, inf)),  cT(zer, nan));
  NT2_TEST_EQUAL(nt2::multiplies(cT(inf, inf), cT(inf, inf)),  cT(nan, inf));
  NT2_TEST_EQUAL(nt2::multiplies(cT(inf,-inf), cT(inf, inf)),  cT(inf, nan));
  NT2_TEST_EQUAL(nt2::multiplies(cT(inf, inf), cT(deu, zer)),  cT(inf, inf));
  NT2_TEST_EQUAL(nt2::multiplies(cT(deu, zer), cT(inf, inf)),  cT(inf, inf));
  NT2_TEST_EQUAL(nt2::multiplies(cT(inf, inf), cT(zer, deu)),  cT(-inf, inf));
  NT2_TEST_EQUAL(nt2::multiplies(cT(zer, deu), cT(inf, inf)),  cT(-inf, inf));
  NT2_TEST_EQUAL(nt2::multiplies(cT(zer, inf), cT(zer, deu)),  cT(-inf, zer));
  NT2_TEST_EQUAL(nt2::multiplies(cT(zer, deu), cT(zer, inf)),  cT(-inf, zer));
}



NT2_TEST_CASE_TPL ( complex_real, BOOST_SIMD_REAL_TYPES)
{
  using nt2::multiplies;
  using nt2::tag::multiplies_;
  typedef std::complex<T> cT;

  // specific values tests
  const T inf = nt2::Inf<T>();
  const T nan = nt2::Nan<T>();
  const T zer = nt2::Zero<T>();
  const T deu = nt2::Two<T>();

  NT2_TEST_EQUAL(nt2::multiplies(cT(inf, zer), T(deu)),  cT(inf, zer));
  NT2_TEST_EQUAL(nt2::multiplies(cT(deu, zer), T(inf)),  cT(inf, zer));
  NT2_TEST_EQUAL(nt2::multiplies(cT(inf, zer), T(zer)),  cT(nan, zer));
  NT2_TEST_EQUAL(nt2::multiplies(cT(zer, zer), T(inf)),  cT(nan, zer));
  NT2_TEST_EQUAL(nt2::multiplies(cT(zer, inf), T(zer)),  cT(zer, nan));
  NT2_TEST_EQUAL(nt2::multiplies(cT(zer, zer), T(zer)),  cT(zer, zer));
  NT2_TEST_EQUAL(nt2::multiplies(cT(inf, inf), T(inf)),  cT(inf, inf));
  NT2_TEST_EQUAL(nt2::multiplies(cT(inf, inf), T(deu)),  cT(inf, inf));
  NT2_TEST_EQUAL(nt2::multiplies(cT(inf, inf), T(zer)),  cT(nan, nan));
  NT2_TEST_EQUAL(nt2::multiplies(cT(zer, deu), T(inf)),  cT(zer, inf));
  NT2_TEST_EQUAL(nt2::multiplies(cT(zer, inf), T(zer)),  cT(zer, nan));
  NT2_TEST_EQUAL(nt2::multiplies(cT(zer, deu), T(zer)),  cT(zer, zer));
  NT2_TEST_EQUAL(nt2::multiplies(cT(zer, zer), T(zer)),  cT(zer, zer));
  NT2_TEST_EQUAL(nt2::multiplies(cT(zer, zer), T(inf)),  cT(nan, zer));
}
NT2_TEST_CASE_TPL ( real_complex, BOOST_SIMD_REAL_TYPES)
{
  using nt2::multiplies;
  using nt2::tag::multiplies_;
  typedef std::complex<T> cT;

  // specific values tests
  const T inf = nt2::Inf<T>();
  const T nan = nt2::Nan<T>();
  const T zer = nt2::Zero<T>();
  const T deu = nt2::Two<T>();

  NT2_TEST_EQUAL(nt2::multiplies(T(deu), cT(inf, zer)),  cT(inf, zer));
  NT2_TEST_EQUAL(nt2::multiplies(T(inf), cT(deu, zer)),  cT(inf, zer));
  NT2_TEST_EQUAL(nt2::multiplies(T(zer), cT(inf, zer)),  cT(nan, zer));
  NT2_TEST_EQUAL(nt2::multiplies(T(inf), cT(zer, zer)),  cT(nan, zer));
  NT2_TEST_EQUAL(nt2::multiplies(T(zer), cT(zer, inf)),  cT(zer, nan));
  NT2_TEST_EQUAL(nt2::multiplies(T(zer), cT(zer, zer)),  cT(zer, zer));
  NT2_TEST_EQUAL(nt2::multiplies(T(inf), cT(inf, inf)),  cT(inf, inf));
  NT2_TEST_EQUAL(nt2::multiplies(T(deu), cT(inf, inf)),  cT(inf, inf));
  NT2_TEST_EQUAL(nt2::multiplies(T(zer), cT(inf, inf)),  cT(nan, nan));
  NT2_TEST_EQUAL(nt2::multiplies(T(inf), cT(zer, deu)),  cT(zer, inf));
  NT2_TEST_EQUAL(nt2::multiplies(T(zer), cT(zer, inf)),  cT(zer, nan));
  NT2_TEST_EQUAL(nt2::multiplies(T(deu), cT(zer, inf)),  cT(zer, inf));
  NT2_TEST_EQUAL(nt2::multiplies(T(zer), cT(zer, deu)),  cT(zer, zer));
  NT2_TEST_EQUAL(nt2::multiplies(T(zer), cT(zer, zer)),  cT(zer, zer));
  NT2_TEST_EQUAL(nt2::multiplies(T(inf), cT(zer, zer)),  cT(nan, zer));
}
