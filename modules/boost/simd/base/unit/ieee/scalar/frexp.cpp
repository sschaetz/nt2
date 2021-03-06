//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/frexp.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( frexp, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::frexp;
  using boost::simd::tag::frexp_;

  typedef typename boost::dispatch::meta::as_integer<T,signed>::type iT;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<frexp_(T)>::type)
                  , (std::pair<T,iT>)
                  );

  {
    iT e;
    T  m;

    frexp(boost::simd::One<T>(), m, e);
    NT2_TEST_EQUAL(m, boost::simd::Half<T>());
    NT2_TEST_EQUAL(e, boost::simd::One<iT>());
  }

  {
    iT e;
    T  m;

    m = frexp(boost::simd::One<T>(), e);
    NT2_TEST_EQUAL(m, boost::simd::Half<T>());
    NT2_TEST_EQUAL(e, boost::simd::One<iT>());
  }

  {
    iT e;
    T  m;

    boost::fusion::vector_tie(m,e) = frexp(boost::simd::One<T>());
    NT2_TEST_EQUAL(m, boost::simd::Half<T>());
    NT2_TEST_EQUAL(e, boost::simd::One<iT>());
  }

  {
    std::pair<T,iT> p;

    p = frexp(boost::simd::One<T>());
    NT2_TEST_EQUAL(p.first  , boost::simd::Half<T>());
    NT2_TEST_EQUAL(p.second , boost::simd::One<iT>());
  }
}
