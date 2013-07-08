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
#ifndef NT2_SDK_BENCH_BENCHMARK_HPP_INCLUDED
#define NT2_SDK_BENCH_BENCHMARK_HPP_INCLUDED

#include <boost/dispatch/preprocessor/strip.hpp>
#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/bench/suite.hpp>
#include <nt2/sdk/bench/measure.hpp>
#include <nt2/sdk/bench/workbench.hpp>
#include <nt2/sdk/bench/experiment.hpp>
#include <nt2/sdk/bench/stat/average.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <nt2/sdk/config/type_lists.hpp>
#include <nt2/sdk/bench/measure/absolute_time.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>

/// INTERNAL ONLY
#define NT2_BENCH_WORKBENCH_TYPE(W) BOOST_DISPATCH_PP_STRIP(BOOST_PP_SEQ_ELEM(0,W))

/// INTERNAL ONLY
#define NT2_BENCH_WORKBENCH_CTOR(W) BOOST_PP_SEQ_ELEM(1,W)

/// INTERNAL ONLY
#define NT2_BENCH_PROTOCOL_TYPE(W) BOOST_DISPATCH_PP_STRIP(BOOST_PP_SEQ_ELEM(0,W))

/// INTERNAL ONLY
#define NT2_BENCH_PROTOCOL_CTOR(W) BOOST_PP_SEQ_ELEM(1,W)

/// INTERNAL ONLY
#define NT2_NAMED_BENCH_CLASS(ID,NAME,PROTOCOL,WORKBENCH)                      \
struct ID : nt2::experiment                                                    \
            , NT2_BENCH_WORKBENCH_TYPE(PROTOCOL)                               \
            , NT2_BENCH_WORKBENCH_TYPE(WORKBENCH)                              \
{                                                                              \
  typedef NT2_BENCH_WORKBENCH_TYPE(PROTOCOL)  protocol;                        \
  typedef NT2_BENCH_WORKBENCH_TYPE(WORKBENCH) work;                            \
  ID()  : nt2::experiment( NAME )                                              \
          , protocol  NT2_BENCH_PROTOCOL_CTOR(PROTOCOL)                        \
          , work      NT2_BENCH_WORKBENCH_CTOR(WORKBENCH)                      \
  {}                                                                           \
  virtual void body();                                                         \
  static  nt2::experiment* self_;                                              \
};                                                                             \
/**/

#define NT2_BENCH_CLASS(NAME,PROTOCOL,WORKBENCH)                               \
NT2_NAMED_BENCH_CLASS(NAME,nt2::type_id<NAME>(),PROTOCOL,WORKBENCH)            \
/**/

/// INTERNAL ONLY
#define NT2_TPL_BENCH(z,n,text)                                                \
template<>                                                                     \
nt2::experiment* BOOST_PP_TUPLE_ELEM(3,0,text)                                 \
                <BOOST_PP_SEQ_ELEM(n,BOOST_PP_TUPLE_ELEM(3,2,text))>::self_    \
= nt2::register_benchmark(new  BOOST_PP_TUPLE_ELEM(3,0,text)                   \
                          <BOOST_PP_SEQ_ELEM(n,BOOST_PP_TUPLE_ELEM(3,2,text))> \
                          )                                                    \
BOOST_PP_SEQ_FOR_EACH(NT2_PP_MEASURE,_,BOOST_PP_TUPLE_ELEM(3,1,text));         \
/**/

/// INTERNAL ONLY
#define NT2_BENCH_REG(NAME)                                                    \
nt2::experiment*                                                               \
NAME::self_  =  nt2::register_benchmark(new NAME)                              \
/**/

/// INTERNAL ONLY
#define NT2_PP_MEASURE(r,d,e) ->add_measure(new e)                             \
/**/

/*!
  @brief Define a benchmark with a custom workbench and metrics

  Setup the boilerplate code for registering a benchmark into the benchmark
  system using a custom workbench and a set of metrics.

  @param NAME       Unique ID of the current benchmark
  @param PROTOCOL   Preprocessor sequence of protocol type and parameters
  @param WORKBENCH  Preprocessor sequence of workbench type and parameters
  @param MEASURES   Preprocessor sequence of measure types
**/
#define NT2_STATEFUL_BENCHMARK_WITH_METRIC(NAME,PROTOCOL,WORKBENCH,MEASURES)   \
NT2_BENCH_CLASS(NAME,PROTOCOL,WORKBENCH)                                       \
NT2_BENCH_REG(NAME)                                                            \
                BOOST_PP_SEQ_FOR_EACH(NT2_PP_MEASURE,_,MEASURES);              \
                                                                               \
void NAME::body()                                                              \
/**/

/*!
  @brief Define a benchmark with a custom workbench

  Setup the boilerplate code for registering a benchmark into the benchmark
  system using a custom workbench

  @param NAME       Unique ID of the current benchmark
  @param PROTOCOL   Preprocessor sequence of protocol type and parameters
  @param WORKBENCH  Preprocessor sequence of workbench type and parameters
**/
#define NT2_STATEFUL_BENCHMARK(NAME,PROTOCOL,WORKBENCH)                        \
NT2_STATEFUL_BENCHMARK_WITH_METRIC( NAME,PROTOCOL,WORKBENCH                    \
                                  , (nt2::absolute_time<nt2::stat::average_>)  \
                                  )                                            \
/**/

/*!
  @brief Define a benchmark with metrics

  Setup the boilerplate code for registering a benchmark into the benchmark
  system using one or multiple metrics for measurement.

  @param NAME     Unique ID of the current benchmark
  @param PROTOCOL Preprocessor sequence of protocol type and parameters
  @param MEASURES Preprocessor sequence of measure types
**/
#define NT2_BENCHMARK_WITH_METRIC(NAME,PROTOCOL,MEASURES)                      \
NT2_STATEFUL_BENCHMARK_WITH_METRIC(NAME,PROTOCOL,(nt2::workbench)(()),MEASURES)\
/**/

/*!
  @brief Define a simple benchmark

  Setup the boilerplate code for registering a benchmark into the benchmark
  system

  @param NAME     Unique ID of the current benchmark
  @param PROTOCOL Preprocessor sequence of protocol type and parameters
**/
#define NT2_BENCHMARK(NAME,PROTOCOL)                                           \
NT2_BENCHMARK_WITH_METRIC ( NAME, PROTOCOL                                     \
                          , (nt2::absolute_time<nt2::stat::average_>)          \
                          )                                                    \
/**/

/*!
  @brief Define a benchmark template with a custom workbench and metrics

  Setup the boilerplate code for registering a set of benchmarks into the
  benchmark system by instantiating a template code with a given set of types,
  a custom workbench and a set of metrics.

  @param NAME       Unique ID of the current benchmark
  @param PROTOCOL   Preprocessor sequence of protocol type and parameters
  @param WORKBENCH  Preprocessor sequence of workbench type and parameters
  @param MEASURES   Preprocessor sequence of measure types
  @param TYPES      Preprocessor sequence of types to instantiate the benchmark
**/
#define NT2_STATEFUL_BENCHMARK_WITH_METRIC_TPL(NAME,PROTOCOL,WORK,MEASURES,TYPES) \
template<typename T>                                                              \
NT2_BENCH_CLASS(NAME,PROTOCOL,WORK)                                               \
BOOST_PP_REPEAT ( BOOST_PP_SEQ_SIZE(TYPES)                                        \
                , NT2_TPL_BENCH                                                   \
                , (NAME,MEASURES,TYPES)                                           \
                )                                                                 \
template<typename T> void NAME<T>::body()                                         \
/**/

/*!
  @brief Define a benchmark template with a custom workbench

  Setup the boilerplate code for registering a set of benchmarks into the
  benchmark system by instantiating a template code with a given set of types
  and a custom workbench

  @param NAME       Unique ID of the current benchmark
  @param PROTOCOL   Preprocessor sequence of protocol type and parameters
  @param WORKBENCH  Preprocessor sequence of workbench type and parameters
  @param TYPES    Preprocessor sequence of types to instantiate the benchmark
**/

#define NT2_STATEFUL_BENCHMARK_TPL(NAME,PROTOCOL,MEASURES,TYPES)               \
NT2_STATEFUL_BENCHMARK_WITH_METRIC_TPL ( NAME,PROTOCOL,(nt2::workbench)(()) \
                                , MEASURES,TYPES\
                                )\
/**/

/*!
  @brief Define a benchmark template with metrics

  Setup the boilerplate code for registering a set of benchmarks into the
  benchmark system by instantiating a template code with a given set of types
  and using one or multiple metrics for measurement.

  @param NAME     Unique ID of the current benchmark
  @param PROTOCOL Preprocessor sequence of protocol type and parameters
  @param MEASURES Preprocessor sequence of measure types
  @param TYPES    Preprocessor sequence of types to instantiate the benchmark
**/
#define NT2_BENCHMARK_WITH_METRIC_TPL(NAME,PROTOCOL,MEASURES,TYPES)            \
NT2_STATEFUL_BENCHMARK_TPL(NAME,PROTOCOL,MEASURES,TYPES)                       \
/**/

/*!
  @brief Define a benchmark template

  Setup the boilerplate code for registering a set of benchmarks into the
  benchmark system by instantiating a template code with a given set of types.

  @param NAME     Unique ID of the current benchmark
  @param PROTOCOL Preprocessor sequence of protocol type and parameters
  @param TYPES    Preprocessor sequence of types to instantiate the benchmark
**/
#define NT2_BENCHMARK_TPL(NAME,PROTOCOL,TYPES)                                 \
NT2_BENCHMARK_WITH_METRIC_TPL ( NAME, PROTOCOL                                 \
                              , (nt2::absolute_time<nt2::stat::average_>)      \
                              , TYPES                                          \
                              )                                                \
/**/

#endif
