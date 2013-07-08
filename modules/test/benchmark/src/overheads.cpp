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
#include <nt2/sdk/bench/details/overheads.hpp>
#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/bench/workbench.hpp>
#include <nt2/sdk/bench/experiment.hpp>
#include <nt2/sdk/bench/max_duration.hpp>
#include <nt2/sdk/bench/details/measure.hpp>
#include <nt2/sdk/bench/stat/average.hpp>
#include <nt2/sdk/bench/stat/median.hpp>
#include <nt2/sdk/bench/stat/min.hpp>
#include <nt2/sdk/bench/stat/max.hpp>
#include <boost/array.hpp>
#include <iostream>

namespace nt2 { namespace details
{
  // Overhead experiment - just do nothing
  struct overhead_xp : experiment, max_duration, workbench
  {
    overhead_xp() : experiment(""), max_duration(0.), workbench() {}
    virtual void body() {}
  };

  // Overhead offsets:
  // http://www.motherboardpoint.com/rdtsc-performance-different-x86-archs-t166722.html
  static std::pair<double, double> calculate_overhead()
  {
    overhead_xp xp;

    time_quantum_t const total_duration( to_timequantums(250000) );
    time_quantum_t       duration      (0);

    details::quantum_set  times_;
    details::cycles_set cycles_;

    do
    {
      time_quantum_t const time_start  ( time_quantum() );
      cycles_t       const cycles_start( read_cycles() );

      xp.body();

      cycles_t       const cycles_end( read_cycles() );
      time_quantum_t const time_end  ( time_quantum() );

      cycles_t       const burned_cycles( cycles_end - cycles_start );
      time_quantum_t const elapsed_time ( time_end   - time_start   );

      times_( elapsed_time );
      cycles_(burned_cycles);

      duration += elapsed_time;
    } while( duration < total_duration );

    return std::make_pair ( boost::accumulators::median(cycles_)
                          , boost::accumulators::median(times_)
                          );
  }

  static std::pair<double,double> const ior(calculate_overhead());

  double  const cycles_overhead(ior.first);
  double  const quantums_overhead(ior.second);

  NT2_TEST_BENCHMARK_DECL void display_overheads()
  {
    std::cout << "Overheads:\t"
              << cycles_overhead << " - " << quantums_overhead
              << std::endl;
  }
} }
