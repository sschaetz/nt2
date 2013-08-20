#if !BOOST_PP_IS_ITERATING
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
#ifndef NT2_SDK_BENCH_WORKBENCH_NARY_RANGE_HPP_INCLUDED
#define NT2_SDK_BENCH_WORKBENCH_NARY_RANGE_HPP_INCLUDED

#include <nt2/sdk/bench/workbench.hpp>
#include <nt2/sdk/unit/details/prng.hpp>
#include <nt2/sdk/bench/workbench/stepper.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <boost/function.hpp>
#include <nt2/table.hpp>
#include <iostream>

#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

namespace nt2
{
  namespace details
  {
    template<typename T>
    void resizer( T& c, std::size_t sz)
    {
      c.resize(sz*sz);
    }

    template<typename T, typename S>
    void resizer( nt2::table<T,S>& c, std::size_t sz)
    {
      c.resize(nt2::of_size(sz,sz));
    }

    template<typename T> std::size_t sizer( T const& c )
    {
      return c.size();
    }

    template<typename T, typename S>
    std::size_t sizer( nt2::table<T,S> const& c )
    {
      return nt2::numel(c);
    }
  }

  template<typename Container, std::size_t Arity> struct nary_range;

  #define   BOOST_PP_FILENAME_1 "nt2/sdk/bench/workbench/nary_range.hpp"
  #define   BOOST_PP_ITERATION_LIMITS (1, 10)
  #include  BOOST_PP_ITERATE()
}

#endif

#else

  #define N BOOST_PP_ITERATION()
  #define M0(z,n,t) details::resizer(a##n,sz);
  #define M1(z,n,t) nt2::roll(a##n,rmin, rmax);
  #define M2(z,n,t) Container a##n;

  template<typename Container>
  struct nary_range<Container,N> : nt2::workbench
  {
    template<typename Stepper>
    nary_range( std::size_t mn = 1, std::size_t mx = 1000
              , double rmn = -100, double rmx = 100
              , Stepper s = nt2::geometric(10.)
              )
              : sz(mn), sx(mx), init(mn)
              , rmin(rmn), rmax(rmx)
              , stepper_(s)
    {}

    virtual void setup(bool reset)
    {
      sz = reset ? init : stepper_(sz);

      BOOST_PP_REPEAT(N,M0,~)
      BOOST_PP_REPEAT(N,M1,~)
    }

    virtual bool exhausted() const
    {
      return sz >= sx;
    }

    virtual std::size_t size() const { return details::sizer(a0); }

    virtual void describe(std::ostream& os) const
    {
      os  << "(" << sz << " x " << sz << ")" << std::flush;
    }

    BOOST_PP_REPEAT(N,M2,~)

    protected:
    std::size_t sz,sx,init;
    double rmin, rmax;
    boost::function<std::size_t(std::size_t)> stepper_;
  };

#undef N
#undef M0
#undef M1
#undef M2

#endif
