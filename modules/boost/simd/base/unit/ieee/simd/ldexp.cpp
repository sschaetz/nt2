//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/ldexp.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

NT2_TEST_CASE_TPL ( ldexp_real__2_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::ldexp;
  using boost::simd::tag::ldexp_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<ldexp_(vT,ivT)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;

  for(unsigned int i = 0; i < cardinal_of<vT>::value; ++i)
    {
      NT2_TEST_EQUAL( boost::simd::ldexp( boost::simd::One<vT>()
                                        , boost::simd::Two<ivT>()
                                        )[i]
                    , boost::simd::ldexp( boost::simd::One<T>()
                                        , boost::simd::Two<iT>()
                                        )
                    );
    }
}
