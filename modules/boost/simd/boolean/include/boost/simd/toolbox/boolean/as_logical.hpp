//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_AS_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_AS_LOGICAL_HPP_INCLUDED

#include <boost/dispatch/meta/factory_of.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/simd/toolbox/boolean/logical.hpp>

namespace boost { namespace simd { namespace meta
{
  template<class T> 
  struct  as_logical
        : mpl::apply< typename dispatch::meta::factory_of<T>::type
                    , logical< typename dispatch::meta::primitive_of<T>::type >
                    >        
  {};
  
} } }

#endif
