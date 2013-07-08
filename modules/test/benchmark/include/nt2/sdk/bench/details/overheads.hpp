//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//         Copyright 2012        Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_DETAILS_OVERHEADS_HPP_INCLUDED
#define NT2_SDK_BENCH_DETAILS_OVERHEADS_HPP_INCLUDED

#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/timing/now.hpp>
#include <boost/array.hpp>

namespace nt2 { namespace details
{
  NT2_TEST_BENCHMARK_DECL extern double const cycles_overhead;
  NT2_TEST_BENCHMARK_DECL extern double const quantums_overhead;

  NT2_TEST_BENCHMARK_DECL void display_overheads();
} }

#endif
