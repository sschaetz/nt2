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
#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/bench/experiment.hpp>
#include <nt2/sdk/bench/workbench.hpp>

namespace nt2
{
  NT2_TEST_BENCHMARK_DECL
  experiment::experiment(std::string const& n) : name(n) {}

  NT2_TEST_BENCHMARK_DECL experiment::~experiment() {}

  NT2_TEST_BENCHMARK_DECL experiment* experiment::add_measure(measure* m)
  {
    if(m) dynamic_cast<workbench*>(this)->add_measure(m);
    return this;
  }
}
