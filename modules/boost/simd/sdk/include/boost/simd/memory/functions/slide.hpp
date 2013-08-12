//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SLIDE_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief slide generic tag

      Represents the slide function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct slide_ : tag::formal_
    {
      /// @brief Parent hierarchy
      typedef tag::formal_ parent;
    };
    BOOST_SIMD_FUNCTION_DECLARE(slide_)
  }

  /*!
    @brief Compute a shifted value


    @par Semantic:

    @tparam Misalignment
    @param  a0
    @param  a1
  **/
  template<int Misalignement, typename A0, typename A1>
  BOOST_FORCEINLINE
  BOOST_DISPATCH_MAKE_CALL_TYPE(tag::slide_, slide_, 3, (A0 const&, A1 const&, mpl::int_<Misalignement> const&))
  slide(A0 const& a0, A1 const& a1)
  {
    return BOOST_DISPATCH_MAKE_CALL(tag::slide_, slide_, 3, (a0, a1, mpl::int_<Misalignement>()));
  }
} }

#endif
