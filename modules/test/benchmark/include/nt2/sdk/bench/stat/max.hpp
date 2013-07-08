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
#ifndef NT2_SDK_BENCH_STAT_MAX_HPP_INCLUDED
#define NT2_SDK_BENCH_STAT_MAX_HPP_INCLUDED

#include <nt2/sdk/bench/workbench.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <string>

namespace nt2 { namespace stat
{
  struct max_
  {
    template<typename Data> static double evaluate(Data const d)
    {
      return boost::accumulators::max(d);
    }

    static std::string unit() { return " (max.)"; }
  };
} }

#endif
