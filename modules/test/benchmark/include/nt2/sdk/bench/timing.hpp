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
#ifndef NT2_SDK_BENCH_TIMING_HPP_INCLUDED
#define NT2_SDK_BENCH_TIMING_HPP_INCLUDED

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/workbench/nary_workbench.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <nt2/sdk/bench/measure/cycles_per_element.hpp>
#include <nt2/sdk/bench/max_duration.hpp>
#include <nt2/sdk/bench/stat/median.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

/// INTERNAL ONLY
#define NT2_TIMING_LOAD(z,n,t)                                                 \
boost::simd::load<typename work::type_##n>(&work::in##n[i])                    \
/**/

/// INTERNAL ONLY
#define NT2_TIMING_RANGE_ELEM(r,d,i,e)                                         \
BOOST_PP_COMMA_IF(i)  BOOST_PP_TUPLE_ELEM(3, 1, e)                             \
                    , BOOST_PP_TUPLE_ELEM(3, 2, e)                             \
/**/

/// INTERNAL ONLY
#define NT2_TIMING_TYPES(r,d,i,e)                                              \
BOOST_PP_COMMA_IF(i) BOOST_DISPATCH_PP_STRIP(BOOST_PP_TUPLE_ELEM(3,0,e))       \
/**/

/// INTERNAL ONLY
#define NT2_TIMING_RANGE( RANGE )                                              \
BOOST_PP_SEQ_FOR_EACH_I(NT2_TIMING_RANGE_ELEM,~,RANGE)                         \
/**/

/// INTERNAL ONLY
#define NT2_TIMING_IMPL(ID, FUNC, RANGE )                                      \
NT2_NAMED_BENCH_CLASS                                                          \
( ID                                                                           \
, nt2::type_id<FUNC(BOOST_PP_SEQ_FOR_EACH_I                                    \
                                    (NT2_TIMING_TYPES,~,RANGE))>()             \
, (nt2::max_duration)((3.))                                                    \
, ((nt2::nary_workbench < boost::dispatch::functor<FUNC>                       \
                        , BOOST_PP_SEQ_SIZE(RANGE)                             \
                        , BOOST_PP_SEQ_FOR_EACH_I                              \
                                    (NT2_TIMING_TYPES,~,RANGE)                 \
                        >                                                      \
  ))                                                                           \
  (( 1000, NT2_TIMING_RANGE(RANGE) ))                                          \
)                                                                              \
NT2_BENCH_REG(ID)                                                              \
BOOST_PP_SEQ_FOR_EACH ( NT2_PP_MEASURE                                         \
                      , _                                                      \
                      , (nt2::cycles_per_element<nt2::stat::median_>)          \
                      );                                                       \
                                                                               \
void ID::body()                                                                \
{                                                                              \
  boost::dispatch::functor<FUNC> func;                                         \
  for(std::size_t i=0, j=0;i<work::size();i+=work::card, j++)                  \
    work::out[j] = func ( BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(RANGE)              \
                                       , NT2_TIMING_LOAD                       \
                                       , ~                                     \
                                       )                                       \
                        );                                                     \
}                                                                              \
/**/

/*!

**/
#define NT2_TIMING(FUNC, RANGE )                                               \
NT2_TIMING_IMPL(BOOST_PP_CAT(experiment_,__COUNTER__),FUNC, RANGE )            \
/**/

#endif
