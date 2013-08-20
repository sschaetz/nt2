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
#ifndef NT2_SDK_BENCH_NARY_WORKBENCH_HPP_INCLUDED
#define NT2_SDK_BENCH_NARY_WORKBENCH_HPP_INCLUDED

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/workbench.hpp>
#include <nt2/sdk/unit/details/prng.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/meta/result_of.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <iostream>
#include <vector>

#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

namespace nt2
{
  template< typename Function
          , std::size_t Arity
          , BOOST_PP_ENUM_BINARY_PARAMS ( 5
                                        , typename Arg
                                        , = void BOOST_PP_INTERCEPT
                                        )
          >
  struct nary_workbench;

  #define   BOOST_PP_FILENAME_1 "nt2/sdk/bench/workbench/nary_workbench.hpp"
  #define   BOOST_PP_ITERATION_LIMITS (1, 5)
  #include  BOOST_PP_ITERATE()
}

#endif

#else

  #define N BOOST_PP_ITERATION()

  #define T0(z,n,t)                                                            \
  typedef typename boost::dispatch::meta::scalar_of<Arg##n>::type type_##n;    \
  /**/

  #define T1(z,n,t) in##n.resize(size_);

  #define M0(z,n,t) type_##n min##n, type_##n max##n
  #define M1(z,n,t) min_##n(min##n), max_##n(max##n)
  #define M2(z,n,t) type_##n min_##n, max_##n;

  #define M3(z,n,t)                                                            \
   (boost::simd::meta::cardinal_of<Arg##n>::value != 1)                        \
  ? boost::simd::meta::cardinal_of<Arg##n>::value                              \
  :                                                                            \
  /**/

  #define M4(z,n,t) roll(in##n, min_##n, max_##n);
  #define M5(z,n,t) std::vector<type_##n> in##n;

  template<typename Function
          , BOOST_PP_ENUM_PARAMS(N, typename Arg)
          >
  struct  nary_workbench<Function,N, BOOST_PP_ENUM_PARAMS(N,Arg)>
        : workbench
  {
    // Computes scalar version of Args so we know what to store in in_i
    BOOST_PP_REPEAT(N,T0,~)

    // Result type
    typedef typename boost::dispatch::meta
            ::result_of<Function(BOOST_PP_ENUM_PARAMS(N,type_))>::type   out_t;

    // How many stuff to process
    static const std::size_t card = BOOST_PP_REPEAT(N, M3, ~) 1;

    // Constructor
    nary_workbench( std::size_t sz, BOOST_PP_ENUM(N,M0,~) )
                  : size_(sz), BOOST_PP_ENUM(N,M1,~)
    {}

    virtual void setup(bool)
    {
      out.resize(size_/card);
      BOOST_PP_REPEAT(N,T1,~)
      BOOST_PP_REPEAT(N,M4,~)
    }

    virtual std::size_t size()                      const { return size_; }
    virtual void        describe(std::ostream& os)  const { os << size_;  }

    std::vector<out_t>  out;
    BOOST_PP_REPEAT(N,M5,~)

    private:
    std::size_t size_;
    BOOST_PP_REPEAT(N,M2,~)
  };

  #undef N
  #undef T0
  #undef T1
  #undef M0
  #undef M1
  #undef M2
  #undef M3
  #undef M4
  #undef M5
#endif
