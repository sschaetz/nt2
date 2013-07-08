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
#ifndef NT2_SDK_BENCH_MEASURE_ABSOLUTE_TIME_HPP_INCLUDED
#define NT2_SDK_BENCH_MEASURE_ABSOLUTE_TIME_HPP_INCLUDED

#include <nt2/sdk/bench/measure.hpp>
#include <string>

namespace nt2
{
  class workbench;

  template<typename Stat>
  struct absolute_time : nt2::measure
  {
    NT2_TEST_BENCHMARK_DECL
    virtual double run( workbench*
                      , details::times_set const& t
                      , details::cycles_set const&
                      ) const
    {
      return Stat::evaluate(t) * 1e-6;
    }

    std::string unit() const
    {
      return "second" + Stat::unit();
    }
  };
}

#endif
