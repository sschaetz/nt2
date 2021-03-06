//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ieee/include/functions/minnummag.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <vector>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/min.hpp>

NT2_TEST_CASE_TPL ( minnummag_real,  NT2_TYPES)
{

  using nt2::minnummag;
  using nt2::tag::minnummag_;
  typedef typename nt2::meta::call<minnummag_(T, T)>::type r_t;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR);
  std::vector<r_t> ref(NR);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  nt2::roll(in2, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] =  (nt2::abs(in1[i]) < nt2::abs(in2[i])) ? in1[i] : (nt2::abs(in1[i]) > nt2::abs(in2[i])) ? in2[i] : nt2::min(in1[i], in2[i]);
  }

  NT2_COVER_ULP_EQUAL(minnummag_, ((T, in1))((T, in2)), ref, 0);
}
