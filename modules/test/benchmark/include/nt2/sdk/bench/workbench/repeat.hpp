//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_WORKBENCH_REPEAT_HPP_INCLUDED
#define NT2_SDK_BENCH_WORKBENCH_REPEAT_HPP_INCLUDED

#include <cstddef>
#include <iostream>

namespace nt2
{
  template<typename ParentWorkbench>
  struct repeat : public ParentWorkbench
  {
    typedef ParentWorkbench parent;

    repeat( ParentWorkbench const& p
          , std::size_t mn, std::size_t mx
          , std::size_t s = 1
          )
          : parent(p), iteration(mn), stop(mx), step(s)
    {}

    virtual void setup(bool status)
    {
      if(!status && parent::exhausted())
      {
        iteration+=step;
        status = true;
      }

      parent::setup(status);
    }

    virtual bool exhausted() const
    {
      return iteration > stop;
    }

    virtual void describe(std::ostream& os)  const
    {
      os << "{" << iteration << "}" << std::flush;
      parent::describe(os);
    }

    std::size_t iteration,stop,step;
  };
}

#endif
