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
#include <nt2/sdk/bench/workbench/repeat.hpp>
#include <nt2/sdk/bench/measure/cycles_per_element.hpp>
#include <nt2/sdk/bench/stat/median.hpp>
#include <nt2/sdk/bench/max_duration.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/table.hpp>

NT2_STATEFUL_BENCHMARK_WITH_METRIC_TPL
( sum_table
, (nt2::max_duration)((1.5))
, (( nt2::repeat< nt2::nary_range<nt2::table<T>,2> > ))
  (( nt2::nary_range<nt2::table<T>,2>(4,4096,-100,100,nt2::geometric(2)),1,2))
, (nt2::cycles_per_element<nt2::stat::median_>)
, (float)(double)
)
{
  work::a1 = nt2::sum(work::a0,work::iteration);
}
