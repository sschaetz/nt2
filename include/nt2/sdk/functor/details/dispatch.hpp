
/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_DISPATCH_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_DISPATCH_HPP_INCLUDED

#include <boost/mpl/at.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/push_back.hpp>
#include <nt2/sdk/functor/hierarchy.hpp>
#include <nt2/sdk/functor/meta/hierarchy.hpp>
#include <nt2/sdk/functor/meta/hierarchy_of.hpp>
#include <nt2/sdk/functor/meta/find_type.hpp>
#include <nt2/sdk/functor/details/enable_dispatch.hpp>

////////////////////////////////////////////////////////////////////////////////
// Local macro to generate the fall-through dispatch overload
////////////////////////////////////////////////////////////////////////////////
#define M0(z,n,t) meta::unknown_<BOOST_PP_CAT(A,n)> const&

#define NT2_DEFAULT_UNKNOWN_DISPATCH(z,n,t)                       \
template<class Tag, class Site, BOOST_PP_ENUM_PARAMS(n,class A)>  \
nt2::ext::call<Tag(tag::unknown_),Site>                           \
dispatch(Tag const&, Site const&, BOOST_PP_ENUM(n,M0,~) \
        , details::eater = details::eater()                                                   \
        );         \
/**/

#define NT2_DISPATCH_ARG(z,n,t) nt2::meta::BOOST_PP_SEQ_ELEM(n,t) const&
#define NT2_DISPATCH_TAG(z,n,t) typename nt2::meta::BOOST_PP_SEQ_ELEM(n,t)::type

#define NT2_REGISTER_DISPATCH(Tag,Site,Seq)                                 \
namespace nt2 { namespace details {                                         \
template<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Seq),class A)>              \
nt2::ext::                                                                  \
call<Tag(BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),NT2_DISPATCH_TAG,Seq)),Site>  \
dispatch( Tag const&, Site const&                                           \
        , BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),NT2_DISPATCH_ARG,Seq)        \
        , details::eater = details::eater()                                 \
        );                                                                  \
} }                                                                         \
/**/

namespace nt2 { namespace details
{
  struct eater {};

  //////////////////////////////////////////////////////////////////////////////
  // Default dispatch overload set for catching calls to unsupported functor
  // overload or unregistered types.
  //////////////////////////////////////////////////////////////////////////////
  BOOST_PP_REPEAT_FROM_TO(1,4,NT2_DEFAULT_UNKNOWN_DISPATCH,~)
} }

#undef M0
#undef NT2_DEFAULT_UNKNOWN_DISPATCH


////////////////////////////////////////////////////////////////////////////////
// Local macro to generate the dispatch selector
////////////////////////////////////////////////////////////////////////////////
#define M0(z,n,t) BOOST_PP_CAT(elem,n)()
/**/

#define NT2_DISPATCH_TYPES(z,n,t)                                               \
typedef typename strip<BOOST_PP_CAT(A,n)>::type BOOST_PP_CAT(arg,n);            \
typedef typename hierarchy_of<BOOST_PP_CAT(arg,n)>::type  BOOST_PP_CAT(elem,n); \
/**/

#define NT2_DISPATCH_CALL(z,n,t)                                                    \
template<class Tag, BOOST_PP_ENUM_PARAMS(n,class A), class Site>                    \
struct dispatch_call<Tag(BOOST_PP_ENUM_PARAMS(n,A)), Site>                          \
{                                                                                   \
  BOOST_PP_REPEAT(n,NT2_DISPATCH_TYPES,~)                                           \
  BOOST_TYPEOF_NESTED_TYPEDEF_TPL ( nested                                          \
                                  , details::                                       \
                                    dispatch( Tag(), Site(), BOOST_PP_ENUM(n,M0,~),details::eater()) \
                                  )                                                 \
  typedef typename nested::type                             type;                   \
};                                                                                  \
/**/

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // dispatch_call finds the proper call overload for evaluating a given
  // functor over a set of types on a given site
  //////////////////////////////////////////////////////////////////////////////
  template<class Sig, class Site> struct dispatch_call;
  BOOST_PP_REPEAT_FROM_TO(1,2,NT2_DISPATCH_CALL,~)
} }

#undef M0
#undef NT2_DISPATCH_TYPES
#undef NT2_DISPATCH_CALL






namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // Default dispatch just forward the type
  //////////////////////////////////////////////////////////////////////////////
  template<class Tag,class Category,class Info = void>
  struct dispatch : boost::mpl::_1 {};
} }

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Try to match a type onto an existing hierarchy
  //////////////////////////////////////////////////////////////////////////////
  template<class Tag,class Category, class Info>
  struct  make_list
  {
    typedef boost::mpl::if_ < meta::
                              enable_dispatch<Tag,Category,boost::mpl::_2,Info>
                            , boost::mpl::push_back < boost::mpl::_1
                                                    , boost::mpl::_2
                                                    >
                            , boost::mpl::_1
                            > selector;

    typedef typename  boost::mpl::fold< functors::hierarchies
                                      , boost::mpl::vector<>
                                      , selector
                                      >::type type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Build a call<> type by trying to fit a dispatched type either on a direct
  // call<> specialization or a hierarchical call<>
  //////////////////////////////////////////////////////////////////////////////
  template<class Tag,class Base,class Category,class Info>
  struct build_caller
  {
    typedef meta::find_type < typename Base::type
                            , typename details::make_list < Tag
                                                          , Category
                                                          , Info
                                                          >::type
                            >        hierarchized;
    typedef typename
          boost::mpl::eval_if < meta::enable_dispatch < Tag
                                                      , Category
                                                      , typename Base::type
                                                      , Info
                                                      >
                              , Base
                              , hierarchized
                              >::type  hierarchy_type;

    typedef functors::call<Tag,Category,hierarchy_type,Info> type;
  };
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For any given Tag in a given Category, construct the call<> able to process
  // the current function call over said category of type by selecting the proper
  // call<> specialization among all externals specializations available.
  //////////////////////////////////////////////////////////////////////////////
  template<class Tag, class Category,class Info>
  struct dispatch
  {
    typedef functors::dispatch<Tag,Category,Info> dispatcher;

    template<class Sig> struct result;

    #define M0(z,n,t) typename strip<BOOST_PP_CAT(t,n)>::type

    #define M1(z,n,t)                                                             \
    template<class This,BOOST_PP_ENUM_PARAMS(n,class A)>                          \
    struct result<This(BOOST_PP_ENUM_PARAMS(n,A))>                                \
    {                                                                             \
      typedef BOOST_PP_CAT(boost::mpl::apply,n) < dispatcher                      \
                                                , BOOST_PP_ENUM(n,M0,A)           \
                                                >                           base; \
      typedef typename details::build_caller<Tag,base,Category,Info>::type  type; \
    };                                                                            \
    /**/

    BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M1,~)

    #undef M1
    #undef M0
  };
} }

#endif
