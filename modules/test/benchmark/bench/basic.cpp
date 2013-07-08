//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/measure/cycles_per_element.hpp>
#include <nt2/sdk/bench/workbench/nary_range.hpp>
#include <nt2/sdk/bench/workbench/stepper.hpp>
#include <nt2/sdk/bench/max_iteration.hpp>
#include <nt2/sdk/bench/max_duration.hpp>
#include <nt2/sdk/bench/stat/average.hpp>
#include <nt2/sdk/bench/stat/median.hpp>
#include <nt2/sdk/bench/stat/min.hpp>
#include <nt2/sdk/bench/stat/max.hpp>
#include <cmath>

// - Regular benchmarks
NT2_BENCHMARK(empty, (nt2::max_duration)((0.25)) )
{

}

NT2_BENCHMARK(sleepy, (nt2::max_iteration)((5)) )
{
  sleep(1);
}

NT2_BENCHMARK_WITH_METRIC( empty_i
                  , (nt2::max_iteration)((100000))
                  , (nt2::cycles_per_element<nt2::stat::min_>)
                    (nt2::cycles_per_element<nt2::stat::max_>)
                  )
{

}

NT2_BENCHMARK_WITH_METRIC( empty_c
                  , (nt2::max_duration)((0.25))
                  , (nt2::cycles_per_element<nt2::stat::min_>)
                    (nt2::cycles_per_element<nt2::stat::average_>)
                    (nt2::cycles_per_element<nt2::stat::median_>)
                    (nt2::cycles_per_element<nt2::stat::max_>)
                  )
{

}

// - Template benchmarks
NT2_BENCHMARK_TPL(init,(nt2::max_duration)((0.25)),(int)(float)(double))
{
  T input = T(0.);
  input++;
}

NT2_BENCHMARK_WITH_METRIC_TPL ( init_i
                              , (nt2::max_iteration)
                                ((100000))
                              , (nt2::cycles_per_element<nt2::stat::min_>)
                                (nt2::cycles_per_element<nt2::stat::max_>)
                              , (int)(float)(double)
                              )
{
  T input = T(0.);
  input++;
}

NT2_STATEFUL_BENCHMARK_WITH_METRIC_TPL ( cosinus
                                , (nt2::max_duration)((1))
                                , ((nt2::nary_range<std::vector<T>,2>))
                                  (
                                    ( 2,256
                                    , -3.14159, 3.14159
                                    , nt2::geometric(2.5)
                                    )
                                  )
                                , (nt2::cycles_per_element<nt2::stat::median_>)
                                , (float)(double)
                                )
{
  for(std::size_t i=0;i<work::size();++i)
    work::a0[i] = std::cos(work::a1[i]);
}
