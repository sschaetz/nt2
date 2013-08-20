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
#ifndef NT2_SDK_BENCH_WORKBENCH_HPP_INCLUDED
#define NT2_SDK_BENCH_WORKBENCH_HPP_INCLUDED

#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/bench/details/measure.hpp>
#include <string>
#include <iosfwd>

namespace nt2
{
  class measure;

  // Workbench  : data to use by an experiment
  class BOOST_SYMBOL_VISIBLE workbench
  {
    public:

    NT2_TEST_BENCHMARK_DECL workbench();
    NT2_TEST_BENCHMARK_DECL virtual ~workbench();

    NT2_TEST_BENCHMARK_DECL virtual void        setup(bool);
    NT2_TEST_BENCHMARK_DECL virtual bool        exhausted() const;
    NT2_TEST_BENCHMARK_DECL virtual void        reset();
    NT2_TEST_BENCHMARK_DECL virtual void        clean();
    NT2_TEST_BENCHMARK_DECL virtual std::size_t size() const;
    NT2_TEST_BENCHMARK_DECL virtual void describe(std::ostream&) const;

    NT2_TEST_BENCHMARK_DECL void add_measure(measure* w);

    std::vector<measure*> measures_;

    protected:
    bool exhausted_;
  };
}

#endif
