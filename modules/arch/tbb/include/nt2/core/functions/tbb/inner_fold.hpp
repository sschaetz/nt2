//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TBB_INNER_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TBB_INNER_FOLD_HPP_INCLUDED
#if defined(NT2_USE_TBB)

#include <nt2/core/functions/inner_fold.hpp>
#include <nt2/include/functions/inner_fold_step.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>
#include <nt2/sdk/config/cache.hpp>
#include <nt2/sdk/tbb/tbb.hpp>
#include <nt2/sdk/tbb/blocked_range.hpp>
#include <nt2/sdk/tbb/worker.hpp>

#ifndef BOOST_NO_EXCEPTIONS
#include <boost/exception_ptr.hpp>
#endif

#ifndef BOOST_SIMD_NO_SIMD

//==============================================================================
// tbb + SIMD
//==============================================================================
namespace nt2 {

  namespace details
  {
    template<class Site, class A0, class A1, class A2, class A3, class A4>
    struct inner_reduce_simd
    {
      typedef typename A0::value_type value_type;
      typedef boost::simd::native<value_type,BOOST_SIMD_DEFAULT_EXTENSION> target_type;

      inner_reduce_simd( A0& out, A1& in, A2 const& n, A3 const& bop, A4 const& uop
                       , std::size_t const& bound, std::size_t const& ibound)
      : out_(out), in_(in), neutral_(n), bop_(bop), uop_(uop)
      , bound_(bound), ibound_(ibound)
      {}

      void operator()(tbb::blocked_range<std::ptrdiff_t> const& r) const
      {
        std::size_t condition = ibound_/tbb::task_scheduler_init::default_num_threads();
        std::size_t grain = (condition==0)?ibound_:condition;

        for(std::ptrdiff_t j = r.begin(); j < r.end(); ++j)
        {
          std::size_t k = j*bound_;

          nt2::worker<tag::inner_fold_step_,tag::tbb_<Site>,target_type,A1,A2,A3>
          vecworker(in_,neutral_,bop_);


          tbb::parallel_reduce( nt2::blocked_range<std::size_t>(k,k+ibound_,grain)
                              , vecworker
                              );

          nt2::run(out_, j, uop_(vecworker.out_));

          for(std::size_t i = ibound_; i < bound_; ++i)
            nt2::run(out_, j
                    , bop_( nt2::run( out_, j, meta::as_<value_type>())
                                    , nt2::run(in_, i+k, meta::as_<value_type>())));
        }

      }

      A0&                     out_;
      A1&                      in_;
      A2                  neutral_;
      A3                      bop_;
      A4                      uop_;
      std::size_t           bound_;
      std::size_t          ibound_;
    };


  }

  namespace ext
  {
    //============================================================================
    // Generates inner_fold
    //============================================================================
    NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::inner_fold_, nt2::tag::tbb_<Site>
                                 , (A0)(S0)(K0)(A1)(A2)(A3)(A4)(Site)
                                 , (boost::simd::meta::is_vectorizable<typename A0::value_type, BOOST_SIMD_DEFAULT_EXTENSION>)
                                 , ((expr_< container_<K0,unspecified_<A0>, S0 >
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

      BOOST_FORCEINLINE result_type operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop, A4 const& uop ) const
      {

      const std::size_t num_threads( tbb::task_scheduler_init::default_num_threads() );
      extent_type ext = in.extent();
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
      std::size_t bound  = boost::fusion::at_c<0>(ext);

      std::size_t divider = N*num_threads;
      std::size_t ibound = (boost::fusion::at_c<0>(ext)/divider) * divider;
      std::ptrdiff_t obound = nt2::numel(boost::fusion::pop_front(ext));
      std::size_t condition = obound/num_threads;

      std::size_t     grain = (condition == 0)
                              ? obound
                              : condition;


      details::inner_reduce_simd<Site,A0,A1,A2,A3,A4>
      ared( out, in, neutral, bop, uop, bound, ibound);


#ifndef BOOST_NO_EXCEPTIONS
        boost::exception_ptr exception;
        try
        {
#endif
          tbb::parallel_for( tbb::blocked_range<std::ptrdiff_t>(0,obound,grain)
                           , ared
                           );

#ifndef BOOST_NO_EXCEPTIONS
        }
        catch(...)
        {
          // Store exception for late rethrow
          exception = boost::current_exception();
        }

        if(exception)
          boost::rethrow_exception(exception);
#endif
      }

    };
  }
}
#else
//==============================================================================
// tbb + noSIMD
//==============================================================================
namespace nt2
{
  namespace details
  {
    template <class X, class N, class B, class U>
    BOOST_FORCEINLINE typename X::value_type
    inner_fold_step(X const& in, const std::size_t& p, N const& neutral, B const& bop, U const& uop);

    template<class A0, class A1, class A2, class A3, class A4>
    struct inner_reduce_scal
    {
      inner_reduce_scal( A0& out, A1& in, A2 const& n, A3 const& bop, A4 const& uop
                       , std::size_t const& ibound)
      : out_(out), in_(in), neutral_(n), bop_(bop), uop_(uop)
      , ibound_(ibound)
      {}

      void operator()(tbb::blocked_range<std::ptrdiff_t> const& r) const
      {
        for(std::ptrdiff_t j = r.begin(); j < r.end(); ++j)
        {
          std::size_t k = j*ibound_;
          nt2::run(out_, j
                  , details::inner_fold_step( in_
                                            , k
                                            , neutral_
                                            , bop_
                                            , uop_
                                            )
                  );
        }
      }

      A0&                     out_;
      A1&                      in_;
      A2                  neutral_;
      A3                      bop_;
      A4                      uop_;
      std::size_t          ibound_;
    };
  }

  namespace ext
  {
  //============================================================================
  // Generates inner_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::inner_fold_, nt2::tag::tbb_<Site>
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

      const std::size_t grain = obound/tbb::task_scheduler_init::default_num_threads();
      details::inner_reduce_scal<A0,A1,A2,A3,A4> ared( out, in, neutral, bop
                                                      , uop, ibound);
#ifndef BOOST_NO_EXCEPTIONS
      boost::exception_ptr exception;
      try
      {
#endif
        tbb::parallel_for( tbb::blocked_range<std::ptrdiff_t>(0,obound,grain)
                         , ared
                         );
#ifndef BOOST_NO_EXCEPTIONS
      }
      catch(...)
      {
        exception = boost::current_exception();
      }
      if(exception)
        boost::rethrow_exception(exception);
#endif

    }
  };

} }

#endif
#endif
#endif
