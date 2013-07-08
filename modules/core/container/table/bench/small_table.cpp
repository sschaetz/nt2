//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/measure/cycles_per_element.hpp>
#include <nt2/sdk/bench/workbench/nary_range.hpp>
#include <nt2/sdk/bench/max_duration.hpp>
#include <nt2/sdk/bench/stat/median.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/table.hpp>

NT2_STATEFUL_BENCHMARK_WITH_METRIC_TPL
( small_table
, (nt2::max_duration)((3.))
, ((nt2::nary_range< nt2::table<T>, 3 >))
  (( 2,4096, -3.1415/4., 3.1415/4., nt2::geometric(2)))
, (nt2::cycles_per_element<nt2::stat::median_>)
, (float)(double)
)
{
  work::a2  = nt2::sqrt ( nt2::cos(work::a0)/nt2::sin(work::a0)
                        + work::a1*work::a1/work::a0
                        );
}

NT2_STATEFUL_BENCHMARK_WITH_METRIC_TPL
( small_vector
, (nt2::max_duration)((3.))
, ((nt2::nary_range< std::vector<T>,3 >))
  (( 2,4096, -3.1415/4., 3.1415/4., nt2::geometric(2)))
, (nt2::cycles_per_element<nt2::stat::median_>)
, (float)(double)
)
{
  for(std::size_t i=0; i<work::size(); ++i)
    work::a2[i] = std::sqrt ( std::cos(work::a0[i])/std::sin(work::a0[i])
                            + work::a1[i]*work::a1[i]/work::a0[i]
                            );
}
