//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/workbench/nary_range.hpp>
#include <nt2/sdk/bench/measure/absolute_time.hpp>
#include <nt2/sdk/bench/stat/median.hpp>
#include <nt2/sdk/bench/stat/min.hpp>
#include <nt2/sdk/bench/max_duration.hpp>

#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/table.hpp>

#include <cstdio>
#include <cmath>

void raw_function(double* y, double* a, double* b, std::size_t n)
{
  for(std::size_t i = 0; i < n; ++i)
  {
    double v = a[i] - b[i];
    y[i] = std::exp( (v * v) * 0.5 );
  }
}

NT2_STATEFUL_BENCHMARK_WITH_METRIC
( using_raw_C
, (nt2::max_duration)((1.5))
, (( nt2::nary_range<std::vector<double>,3> ))
  (( 2000,4000,0,1,nt2::geometric(2) ))
, (nt2::absolute_time<nt2::stat::median_>)
  (nt2::absolute_time<nt2::stat::min_>)
)
{
  raw_function(&work::a0[0],&work::a1[0],&work::a2[0],work::size());
}

NT2_STATEFUL_BENCHMARK_WITH_METRIC
( per_element
, (nt2::max_duration)((1.5))
, (( nt2::nary_range<nt2::table<double>,3> ))
  (( 2000,4000,0,1,nt2::geometric(2) ))
, (nt2::absolute_time<nt2::stat::median_>)
  (nt2::absolute_time<nt2::stat::min_>)
)
{
  for(std::size_t j = 1; j <= 2000; ++j)
  {
    for(std::size_t i = 1; i <= 2000; ++i)
    {
      double v = work::a1(i, j) - work::a2(i, j);
      work::a0(i, j) = std::exp( (v * v) * 0.5 );
    }
  }
}

NT2_STATEFUL_BENCHMARK_WITH_METRIC
( per_matrix
, (nt2::max_duration)((1.5))
, (( nt2::nary_range<nt2::table<double>,3> ))
  (( 2000,4000,0,1,nt2::geometric(2) ))
, (nt2::absolute_time<nt2::stat::median_>)
  (nt2::absolute_time<nt2::stat::min_>)
)
{
  work::a0 = nt2::exp(nt2::sqr(work::a1 - work::a2) * 0.5);
}

NT2_STATEFUL_BENCHMARK_WITH_METRIC
( per_column
, (nt2::max_duration)((1.5))
, (( nt2::nary_range<nt2::table<double>,3> ))
  (( 2000,4000,0,1,nt2::geometric(2) ))
, (nt2::absolute_time<nt2::stat::median_>)
  (nt2::absolute_time<nt2::stat::min_>)
)
{
  using nt2::_;

  for(std::size_t j = 1; j <= 2000; ++j)
  {
    work::a0(_,j) = nt2::exp(nt2::sqr(work::a1(_,j) - work::a2(_,j)) * 0.5);
  }
}
