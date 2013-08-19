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
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/table.hpp>

// Sum workbench
template<typename Container>
struct sum_workbench : public nt2::nary_range< Container, 2 >
{
  typedef nt2::nary_range<Container,2> parent;

  sum_workbench ( std::size_t mn, std::size_t mx)
                : parent(mn,mx,-100,100,nt2::geometric(2))
                , along(1), init(mn)
  {}

  virtual void setup()
  {
    parent::setup();
    if(parent::exhausted)
    {
      along++;
      parent::sz = init;
      parent::exhausted = (along > 2) && (parent::sz > parent::sx);
    }
  }

  virtual void describe(std::ostream& os)  const
  {
    os << "(" << parent::size() << ") @" << along;
  }

  std::size_t along, init;
};

NT2_STATEFUL_BENCHMARK_WITH_METRIC_TPL
( sum_table
, (nt2::max_duration)((3.))
, ((sum_workbench< nt2::table<T> >))(( 2,4096 ))
, (nt2::cycles_per_element<nt2::stat::median_>)
, (float)(double)
)
{
  work::a1 = nt2::sum(work::a0,work::along);
}

// NT2_STATEFUL_BENCHMARK_WITH_METRIC_TPL
// ( sum_vector
// , (nt2::max_duration)((3.))
// , ((nt2::nary_range< std::vector<T>,3 >))
//   (( 2,4096, -100, 100, nt2::geometric(2)))
// , (nt2::cycles_per_element<nt2::stat::median_>)
// , (float)(double)
// )
// {
//   for(std::size_t i=0; i<work::size(); ++i)
//     work::a2[i]  = work::a1[i] + work::a0[i];
// }

// #define NT2_SUM_EXP(T,D,N)                                        \
// NT2_RUN_EXPERIMENT_TPL( sum_over, ((T,D)), (1<<N,1<<N) )          \
// NT2_RUN_EXPERIMENT_TPL( sum_over, ((T,D)), ((1<<N)-1,(1<<N)-1 ) ) \
// NT2_RUN_EXPERIMENT_TPL( sum_over, ((T,D)), (1   ,1<<N) )          \
// NT2_RUN_EXPERIMENT_TPL( sum_over, ((T,D)), (1<<N,1   ) )          \
// /**/
