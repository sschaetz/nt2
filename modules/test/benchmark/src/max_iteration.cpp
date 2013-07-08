//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//         Copyright 2012        Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/bench/max_iteration.hpp>
#include <nt2/sdk/bench/details/measure.hpp>
#include <nt2/sdk/bench/experiment.hpp>
#include <nt2/sdk/bench/workbench.hpp>
#include <nt2/sdk/bench/measure.hpp>
#include <nt2/sdk/timing/now.hpp>
#include <boost/foreach.hpp>
#include <iostream>

namespace nt2
{
  NT2_TEST_BENCHMARK_DECL
  max_iteration::max_iteration(std::size_t i) : iteration_(i)
  {

  }

  NT2_TEST_BENCHMARK_DECL max_iteration::~max_iteration() {}

  NT2_TEST_BENCHMARK_DECL
  void max_iteration::run(experiment* e)
  {
    details::times_set  times_;
    details::cycles_set cycles_;

    workbench* w = dynamic_cast<workbench*>(e);

    for(std::size_t i=0;i<iteration_;++i)
    {
      time_quantum_t const time_start  ( time_quantum() );
      cycles_t       const cycles_start( read_cycles() );

      e->body();

      cycles_t       const cycles_end( read_cycles() );
      time_quantum_t const time_end  ( time_quantum() );

      cycles_t       const burned_cycles( cycles_end - cycles_start );
      time_quantum_t const elapsed_time ( time_end   - time_start   );

      times_( to_microseconds(elapsed_time) );
      cycles_(burned_cycles);

      w->reset();
    }

    BOOST_FOREACH( measure* m, w->measures_ )
    {
      std::cout << e->name << "\t";
      w->describe(std::cout);
      std::cout << "\t" << m->run(w,times_,cycles_)
                << "\t" << m->unit() << std::endl;
    }
  }
}
