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
#include <nt2/sdk/bench/suite.hpp>
#include <nt2/sdk/bench/details/overheads.hpp>
#include <nt2/sdk/bench/experiment.hpp>
#include <nt2/sdk/bench/workbench.hpp>
#include <nt2/sdk/bench/protocol.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <iomanip>

namespace nt2
{
  benchmark_suite::~benchmark_suite()
  {
    std::cout <<  std::string(86,'-') << std::endl;

    // Clean all experiment's workbench and destroy the experiments
    BOOST_FOREACH( experiment* xp, experiments_ )
    {
      dynamic_cast<workbench*>(xp)->clean();
      delete xp;
    }
  }

  // RUN ALL THE EXPERIMENTS !
  void benchmark_suite::run()
  {
    std::cout << "[Benchmark]\t[Desc.]\t[Measure]\t[Unit]" << std::endl;
    std::cout <<  std::string(86,'-') << std::endl;

    // Run every experiment with the current protocol
    BOOST_FOREACH( experiment* xp, experiments_ )
    {
      workbench* wb = dynamic_cast<workbench*>(xp);
      protocol* p = dynamic_cast<protocol*>(xp);

      // Until the workbench is not exhausted
      do
      {
        wb->setup();
        p->run(xp);
        std::cout << std::flush;
      } while(!wb->exhausted);
    }
  }

  experiment* benchmark_suite::push_back(experiment* e)
  {
    if(e) experiments_.push_back(e);
    return e;
  }

  // Global benchmark_suite
  benchmark_suite benchmarker_;

  // Put an experiment in the benchmark suite
  NT2_TEST_BENCHMARK_DECL experiment* register_benchmark(experiment* e)
  {
    return benchmarker_.push_back(e);
  }
}

// Prebuilt main
NT2_TEST_BENCHMARK_DECL int main(int argc, const char** argv)
{
  std::cout << "CTEST_FULL_OUTPUT" << std::endl;

  if(argc > 1 && !strcmp(argv[1], "--verbose"))
  {
    nt2::details::display_overheads();
  }

  nt2::benchmarker_.run();
}
