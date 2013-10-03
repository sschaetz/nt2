//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_FORWARD_SHAPE_HPP_INCLUDED
#define NT2_CORE_SETTINGS_FORWARD_SHAPE_HPP_INCLUDED

namespace nt2
{
  //============================================================================
  /*! The default container shape. Data are laid out in a hypercube
   *  of N dimensions and contains only non-trivial values.
   **/
  //============================================================================

  struct rectangular_;
  struct upper_triangular_    {};
  struct lower_triangular_    {};
  struct band_diagonal_       {};
  struct diagonal_            {};
  struct positive_definite_   {};
  struct uhess_               {};
  struct symmetric_           {};

  namespace tag
  {
    /// @brief Option tag for shape options
    struct shape_;
  }
}

#endif


