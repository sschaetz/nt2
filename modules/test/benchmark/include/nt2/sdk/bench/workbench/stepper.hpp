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
#ifndef NT2_SDK_BENCH_WORKBENCH_STEPPER_HPP_INCLUDED
#define NT2_SDK_BENCH_WORKBENCH_STEPPER_HPP_INCLUDED

namespace nt2
{
  /*!
    @brief Arithmetic stepper for dynamic sized workbench.

    arithmetic is a function object suitable for initializing range
    based workbench. It performs an arithmetic progression of step @c s
    on the range size.
  **/
  struct arithmetic
  {
    /*!
      @brief Constructor
      @param s Progression step
    **/
    inline arithmetic(double s = 1) : step_(s) {}

    /// INTERNAL ONLY
    inline std::size_t operator()(std::size_t s)
    {
      return std::size_t(s+step_);
    }

    /// INTERNAL ONLY
    double step_;
  };

  /*!
    @brief Geometric stepper for dynamic sized workbench.

    arithmetic is a function object suitable for initializing range
    based workbench. It performs an geometric progression of factor @c s
    on the range size.
  **/
  struct geometric
  {
    /*!
      @brief Constructor
      @param s Progression factor
    **/
    inline geometric(double f) : factor_(f) {}

    /// INTERNAL ONLY
    inline std::size_t operator()(std::size_t s)
    {
      return std::size_t(s * factor_);
    }

    /// INTERNAL ONLY
    double factor_;
  };
}

#endif
