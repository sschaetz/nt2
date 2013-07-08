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
#include <nt2/sdk/bench/measure.hpp>
#include <nt2/sdk/bench/workbench.hpp>
#include <boost/foreach.hpp>
#include <iostream>

namespace nt2
{
  NT2_TEST_BENCHMARK_DECL workbench::workbench() : exhausted(false)
  {
  }

  NT2_TEST_BENCHMARK_DECL workbench::~workbench()
  {
    BOOST_FOREACH( measure* m, measures_ ) { delete m; }
  }

  NT2_TEST_BENCHMARK_DECL void workbench::setup()
  {
    exhausted = true;
  }

  NT2_TEST_BENCHMARK_DECL void workbench::reset() {}
  NT2_TEST_BENCHMARK_DECL void workbench::clean() {}

  NT2_TEST_BENCHMARK_DECL std::size_t workbench::size() const
  {
    return 1;
  }

  NT2_TEST_BENCHMARK_DECL void workbench::add_measure(measure* m)
  {
    if(m) measures_.push_back(m);
  }

  NT2_TEST_BENCHMARK_DECL
  void workbench::describe(std::ostream& os) const
  {
    os << "none";
  }
}
