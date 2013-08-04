//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_DETAILS_NAMESPACE_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_DETAILS_NAMESPACE_HPP_INCLUDED

// Namespace-related helpers
#define BOOST_DISPATCH_NS_(s,data,elem) elem ::
#define BOOST_DISPATCH_NS(seq) :: BOOST_PP_SEQ_FOR_EACH(BOOST_DISPATCH_NS_, ~, seq)

#define BOOST_DISPATCH_CLOSE_(s,data,elem) }
#define BOOST_DISPATCH_CLOSE(seq) BOOST_PP_SEQ_FOR_EACH(BOOST_DISPATCH_CLOSE_, ~, seq)

#define BOOST_DISPATCH_REOPEN_(s,data,elem) namespace elem {
#define BOOST_DISPATCH_REOPEN(seq) BOOST_PP_SEQ_FOR_EACH(BOOST_DISPATCH_REOPEN_, ~, seq)

#endif
