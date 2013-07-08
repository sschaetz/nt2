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
#ifndef NT2_SDK_BENCH_MAX_ITERATION_HPP_INCLUDED
#define NT2_SDK_BENCH_MAX_ITERATION_HPP_INCLUDED

#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/bench/protocol.hpp>

namespace nt2
{
  class experiment;

  struct BOOST_SYMBOL_VISIBLE max_iteration : protocol
  {
    NT2_TEST_BENCHMARK_DECL max_iteration(std::size_t i);
    NT2_TEST_BENCHMARK_DECL virtual ~max_iteration();
    NT2_TEST_BENCHMARK_DECL virtual void run(experiment* e);

    private:
    std::size_t iteration_;
  };
}

#endif
