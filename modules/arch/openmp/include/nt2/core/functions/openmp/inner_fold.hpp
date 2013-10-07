//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_OPENMP_INNER_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_OPENMP_INNER_FOLD_HPP_INCLUDED
#if defined(_OPENMP) && _OPENMP >= 200203 /* OpenMP 2.0 */

#include <nt2/core/functions/inner_fold.hpp>
#include <nt2/include/functions/inner_fold_step.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>
#include <nt2/sdk/config/cache.hpp>
#include <nt2/sdk/openmp/openmp.hpp>
#include <nt2/sdk/openmp/worker.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif


#ifndef BOOST_SIMD_NO_SIMD
//==============================================================================
// openMP + SIMD
//==============================================================================
namespace nt2 { namespace ext
{
  //============================================================================
  // Generates inner_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF ( nt2::tag::inner_fold_, nt2::tag::openmp_<Site>
                                , (A0)(S0)(K0)(A1)(A2)(A3)(A4)(Site)
                                , ( boost::simd::meta::
                                    is_vectorizable < typename A0::value_type
                                                    , BOOST_SIMD_DEFAULT_EXTENSION
                                                    >
                                  )
                                , ((expr_ < container_<K0,unspecified_<A0>,S0>
                                          , nt2::tag::terminal_
                                          , boost::mpl::long_<0>
                                          >
                                  ))
                                  ((ast_< A1, nt2::container::domain>))
                                  (unspecified_<A2>)
                                  (unspecified_<A3>)
                                  (unspecified_<A4>)
                                )
  {
    typedef void                                                              result_type;
    typedef typename A0::value_type                                           value_type;
    typedef typename boost::remove_reference<A1>::type::extent_type           extent_type;
    typedef boost::simd::native<value_type,BOOST_SIMD_DEFAULT_EXTENSION>      target_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop, A4 const& uop) const
    {
      extent_type ext = in.extent();
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
      std::size_t bound  = boost::fusion::at_c<0>(ext);
      std::size_t ibound = (boost::fusion::at_c<0>(ext)/N) * N;
      std::ptrdiff_t obound = nt2::numel(boost::fusion::pop_front(ext));

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif
      #pragma omp parallel
      {
        #pragma omp for schedule(static)
        for(std::ptrdiff_t j = 0; j < obound; ++j)
        {

           nt2::worker< tag::inner_fold_step_,
                        nt2::tag::openmp_<Site>,
                        target_type,A1,A2,A3     > vecworker(in,neutral,bop);

          std::size_t k = j*bound;
#ifndef BOOST_NO_EXCEPTIONS
          try
          {
#endif
           vecworker(k,ibound);
           value_type s_out = uop(vecworker.out_);

            for(std::size_t i = ibound; i != bound; ++i)
              s_out = bop(s_out, nt2::run(in, i+k, meta::as_<value_type>()));

            nt2::run(out, j, s_out);

#ifndef BOOST_NO_EXCEPTIONS
          }
          catch(...)
          {
            // Store exception for late rethrow
            exception = boost::current_exception();
          }
#endif
        }
      }


#ifndef BOOST_NO_EXCEPTIONS
      if(exception)
        boost::rethrow_exception(exception);
#endif

    }

  };

  } }
#else
//==============================================================================
// openMP + noSIMD
//==============================================================================
namespace nt2 { namespace details
{
  template <class X, class N, class B, class U>
  BOOST_FORCEINLINE typename X::value_type
  inner_fold_step(X const& in, const std::size_t& p, N const& neutral, B const& bop, U const& uop);
 } }

namespace nt2 { namespace ext
{

  //============================================================================
  // Generates inner_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::inner_fold_, nt2::tag::openmp_<Site>
                            , (A0)(A1)(A2)(A3)(A4)(Site)
                            , ((ast_< A0, nt2::container::domain>))
                              ((ast_< A1, nt2::container::domain>))
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                            )
  {
    typedef void                                                               result_type;
    typedef typename A0::value_type                                            value_type;
    typedef typename boost::remove_reference<A1>::type::extent_type            extent_type;

    BOOST_FORCEINLINE result_type operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop, A4 const& uop) const
    {
      extent_type ext = in.extent();
      std::size_t ibound = boost::fusion::at_c<0>(ext);
      std::ptrdiff_t obound = nt2::numel(boost::fusion::pop_front(ext));
      const std::size_t chunk = config::top_cache_line_size()/sizeof(value_type);

#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
#endif
      // - 1D loop nest as no epilogue or special cases occur
      // - static schedule is set on using cache line sized chunks to limit
      // effects of false sharing.
#pragma omp parallel for schedule(static,chunk)
      for(std::ptrdiff_t j = 0; j < obound; ++j)
      {
        std::size_t k = j*ibound;
#ifndef BOOST_NO_EXCEPTIONS
        try
        {
#endif
          nt2::run(out, j, details::inner_fold_step(in,k, neutral, bop, uop));
#ifndef BOOST_NO_EXCEPTIONS
        }
        catch(...)
        {
          exception = boost::current_exception();
        }
#endif
      }

#ifndef BOOST_NO_EXCEPTIONS
      if(exception)
        boost::rethrow_exception(exception);
#endif

    }
  };

} }

#endif
#endif
#endif
