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
#ifndef NT2_SDK_BENCH_MEASURE_CYCLES_PER_ELEMENT_HPP_INCLUDED
#define NT2_SDK_BENCH_MEASURE_CYCLES_PER_ELEMENT_HPP_INCLUDED

#include <nt2/sdk/bench/measure.hpp>
#include <string>

namespace nt2
{
  class workbench;

  template<typename Stat>
  struct cycles_per_element : nt2::measure
  {
    NT2_TEST_BENCHMARK_DECL
    virtual double run( workbench* w
                      , details::times_set const&
                      , details::cycles_set const& c
                      ) const
    {
      return Stat::evaluate(c) / w->size();
    }

    std::string unit() const
    {
      return "cycles/elements" + Stat::unit();
    }
  };
}

#endif
