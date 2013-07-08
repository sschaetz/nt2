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
#ifndef NT2_SDK_BENCH_DETAILS_MEASURE_HPP_INCLUDED
#define NT2_SDK_BENCH_DETAILS_MEASURE_HPP_INCLUDED

#include <nt2/sdk/timing/now.hpp>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/count.hpp>

namespace nt2 { namespace details
{
  typedef boost::accumulators::stats< boost::accumulators::tag::mean
                                      , boost::accumulators::tag::median
                                      , boost::accumulators::tag::min
                                      , boost::accumulators::tag::max
                                      , boost::accumulators::tag::count
                                      > stats_t;

  typedef boost::accumulators::accumulator_set<microseconds_t,stats_t>  times_set;
  typedef boost::accumulators::accumulator_set<time_quantum_t,stats_t>  quantum_set;
  typedef boost::accumulators::accumulator_set<cycles_t,stats_t>        cycles_set;
} }

#endif
