//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_MAP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_MAP_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>




/*!
 * \internal functor \endinternal
 * \ingroup boost_simd_operator
 * \defgroup map map function
 *
 * \par Description
 * TODO Put description here
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/map.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::map_(A0,A0)>::type
 *     map(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 is the first parameter of map
 * \param a1 is the second parameter of map
 * 
 * \return a value of the common type of the parameters
 *  
 * \internal end_functor \endinternal
**/
 
 
namespace boost { namespace simd { namespace tag { struct map_ {}; } } }
  /*!
   * \internal tag \endinternal
   * \file
   * \brief Define the tag map_ of functor map 
   *        in namespace boost::simd::tag
   * \internal end_tag \endinternal
  **/

namespace boost { namespace simd
{
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::map_,map,2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::map_,map,3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::map_,map,4)
} }

#endif
