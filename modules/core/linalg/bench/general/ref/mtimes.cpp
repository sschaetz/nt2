
//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/sdk/bench/benchmark.hpp>

template<typename T> NT2_EXPERIMENT(mtimes_test)
{
  public:
  mtimes_test( std::size_t m, std::size_t n, double d = 3)
        : NT2_EXPRIMENT_CTOR(d,"cycles/elements")
        , height(m-1), width(n+1)
  {}

  virtual void run() const
  {
    T alpha = 1;
    T beta  = 0;

    nt2::details::gemm( "N", "N", &height, &height, &width, &alpha
                      , a1.raw(), &height, a2.raw(), &width
                      , &beta, a3.raw(), &height
                      );
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    /// HxW * W*H means H*W*W ops
    return r.first/double(height*width*width);
  }

  virtual void info(std::ostream& os) const { os << "("<< height << "x" << width << ")"; }

  virtual void reset() const
  {
    a1 = nt2::rand(height , width );
    a2 = nt2::rand(width  , height);
    a3 = nt2::zeros(height);
  }

  private:
  nt2_la_int            height,width;
  mutable nt2::table<T> a1,a2,a3;
};

NT2_RUN_EXPERIMENT_TPL( mtimes_test, (float)(double), (4  ,  4) );
NT2_RUN_EXPERIMENT_TPL( mtimes_test, (float)(double), (16 , 16) );
NT2_RUN_EXPERIMENT_TPL( mtimes_test, (float)(double), (64 , 64) );
NT2_RUN_EXPERIMENT_TPL( mtimes_test, (float)(double), (256,256) );
