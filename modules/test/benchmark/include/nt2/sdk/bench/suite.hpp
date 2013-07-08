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
#ifndef NT2_SDK_BENCH_SUITE_HPP_INCLUDED
#define NT2_SDK_BENCH_SUITE_HPP_INCLUDED

#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/error/exception.hpp>
#include <boost/foreach.hpp>
#include <vector>

namespace nt2
{
  class experiment;

  /*!
    @brief Main benchmark aggregate

    benchmark_suite centralizes the logic of registering and running benchmarks.
  **/
  class benchmark_suite
  {
    public:

    /// Destructor
    ~benchmark_suite();

    /// Entry point of a benchmarks session
    void run();

    /// Add a benchmark to the current suite
    experiment* push_back(experiment* e);

    private:
    std::vector<experiment*> experiments_;
  };

  /// Register a benchmark into the suite
  NT2_TEST_BENCHMARK_DECL experiment* register_benchmark(experiment* e);
}

/// INTERNAL ONLY
NT2_TEST_BENCHMARK_DECL int main(int argc, const char** argv);

#endif
