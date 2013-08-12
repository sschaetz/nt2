//==============================================================================
// Local macro to generate the fall-through dispatch overload
// What the fuck with adl_helper ? Well, as pointed out by Johannes Schaub
// it is mandated by the standard so ADL kicks in on resolving calls to
// dispatching without having to order them BEFORE the actual dispatch_call
// class definitions. Without it, the whole system brittles.
//==============================================================================
//==============================================================================
// Actual dispatching mechanism implementation
//==============================================================================
namespace boost { namespace dispatch { namespace meta
{
  struct adl_helper {};
  //============================================================================
  // Default dispatch overload set for catching calls to unsupported functor
  // overload or unregistered types.
  //============================================================================
  template< class Tag, class Site > BOOST_FORCEINLINE boost::dispatch::meta:: implement<tag::unknown_, Site, Tag()> dispatching ( meta::unknown_<Tag>, meta::unknown_<Site> , adl_helper = adl_helper() ) { boost::dispatch::meta::implement<tag::unknown_, Site , Tag() > that; return that; } template< class Tag, class Site , class A0> BOOST_FORCEINLINE boost::dispatch::meta:: implement<tag::unknown_, Site, Tag(A0)> dispatching ( meta::unknown_<Tag>, meta::unknown_<Site> , meta::unknown_<A0> , adl_helper = adl_helper() ) { boost::dispatch::meta::implement<tag::unknown_, Site , Tag(A0) > that; return that; } template< class Tag, class Site , class A0 , class A1> BOOST_FORCEINLINE boost::dispatch::meta:: implement<tag::unknown_, Site, Tag(A0 , A1)> dispatching ( meta::unknown_<Tag>, meta::unknown_<Site> , meta::unknown_<A0> , meta::unknown_<A1> , adl_helper = adl_helper() ) { boost::dispatch::meta::implement<tag::unknown_, Site , Tag(A0 , A1) > that; return that; } template< class Tag, class Site , class A0 , class A1 , class A2> BOOST_FORCEINLINE boost::dispatch::meta:: implement<tag::unknown_, Site, Tag(A0 , A1 , A2)> dispatching ( meta::unknown_<Tag>, meta::unknown_<Site> , meta::unknown_<A0> , meta::unknown_<A1> , meta::unknown_<A2> , adl_helper = adl_helper() ) { boost::dispatch::meta::implement<tag::unknown_, Site , Tag(A0 , A1 , A2) > that; return that; } template< class Tag, class Site , class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE boost::dispatch::meta:: implement<tag::unknown_, Site, Tag(A0 , A1 , A2 , A3)> dispatching ( meta::unknown_<Tag>, meta::unknown_<Site> , meta::unknown_<A0> , meta::unknown_<A1> , meta::unknown_<A2> , meta::unknown_<A3> , adl_helper = adl_helper() ) { boost::dispatch::meta::implement<tag::unknown_, Site , Tag(A0 , A1 , A2 , A3) > that; return that; } template< class Tag, class Site , class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE boost::dispatch::meta:: implement<tag::unknown_, Site, Tag(A0 , A1 , A2 , A3 , A4)> dispatching ( meta::unknown_<Tag>, meta::unknown_<Site> , meta::unknown_<A0> , meta::unknown_<A1> , meta::unknown_<A2> , meta::unknown_<A3> , meta::unknown_<A4> , adl_helper = adl_helper() ) { boost::dispatch::meta::implement<tag::unknown_, Site , Tag(A0 , A1 , A2 , A3 , A4) > that; return that; } template< class Tag, class Site , class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE boost::dispatch::meta:: implement<tag::unknown_, Site, Tag(A0 , A1 , A2 , A3 , A4 , A5)> dispatching ( meta::unknown_<Tag>, meta::unknown_<Site> , meta::unknown_<A0> , meta::unknown_<A1> , meta::unknown_<A2> , meta::unknown_<A3> , meta::unknown_<A4> , meta::unknown_<A5> , adl_helper = adl_helper() ) { boost::dispatch::meta::implement<tag::unknown_, Site , Tag(A0 , A1 , A2 , A3 , A4 , A5) > that; return that; }
} } }
//==============================================================================
// Local macro to generate the dispatch selector
//==============================================================================
/**/
namespace boost { namespace dispatch { namespace meta
{
  //==============================================================================
  // dispatch_call finds the proper call overload for evaluating a given
  // functor over a set of types on a given site
  //==============================================================================
  template<class Tag>
  struct dispatch_call_default
  {
    template<class A0 = void , class A1 = void , class A2 = void , class A3 = void , class A4 = void , class A5 = void>
    struct apply;
    template<class A0> struct apply <A0> { typedef typename default_site<Tag>::type Site; BOOST_DISPATCH_TYPEOF_ ( dispatching ( (typename meta::hierarchy_of<Tag>::type()) , (typename meta::hierarchy_of<Site>::type()) , (A0()) , adl_helper() ) , type ) }; template<class A0> BOOST_FORCEINLINE static typename apply<A0>::type call(A0 const &a0) { return typename apply<A0>::type(); } template<class A0 , class A1> struct apply <A0 , A1> { typedef typename default_site<Tag>::type Site; BOOST_DISPATCH_TYPEOF_ ( dispatching ( (typename meta::hierarchy_of<Tag>::type()) , (typename meta::hierarchy_of<Site>::type()) , (A0()) , (A1()) , adl_helper() ) , type ) }; template<class A0 , class A1> BOOST_FORCEINLINE static typename apply<A0 , A1>::type call(A0 const &a0 , A1 const &a1) { return typename apply<A0 , A1>::type(); } template<class A0 , class A1 , class A2> struct apply <A0 , A1 , A2> { typedef typename default_site<Tag>::type Site; BOOST_DISPATCH_TYPEOF_ ( dispatching ( (typename meta::hierarchy_of<Tag>::type()) , (typename meta::hierarchy_of<Site>::type()) , (A0()) , (A1()) , (A2()) , adl_helper() ) , type ) }; template<class A0 , class A1 , class A2> BOOST_FORCEINLINE static typename apply<A0 , A1 , A2>::type call(A0 const &a0 , A1 const &a1 , A2 const &a2) { return typename apply<A0 , A1 , A2>::type(); } template<class A0 , class A1 , class A2 , class A3> struct apply <A0 , A1 , A2 , A3> { typedef typename default_site<Tag>::type Site; BOOST_DISPATCH_TYPEOF_ ( dispatching ( (typename meta::hierarchy_of<Tag>::type()) , (typename meta::hierarchy_of<Site>::type()) , (A0()) , (A1()) , (A2()) , (A3()) , adl_helper() ) , type ) }; template<class A0 , class A1 , class A2 , class A3> BOOST_FORCEINLINE static typename apply<A0 , A1 , A2 , A3>::type call(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3) { return typename apply<A0 , A1 , A2 , A3>::type(); } template<class A0 , class A1 , class A2 , class A3 , class A4> struct apply <A0 , A1 , A2 , A3 , A4> { typedef typename default_site<Tag>::type Site; BOOST_DISPATCH_TYPEOF_ ( dispatching ( (typename meta::hierarchy_of<Tag>::type()) , (typename meta::hierarchy_of<Site>::type()) , (A0()) , (A1()) , (A2()) , (A3()) , (A4()) , adl_helper() ) , type ) }; template<class A0 , class A1 , class A2 , class A3 , class A4> BOOST_FORCEINLINE static typename apply<A0 , A1 , A2 , A3 , A4>::type call(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4) { return typename apply<A0 , A1 , A2 , A3 , A4>::type(); } template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> struct apply { typedef typename default_site<Tag>::type Site; BOOST_DISPATCH_TYPEOF_ ( dispatching ( (typename meta::hierarchy_of<Tag>::type()) , (typename meta::hierarchy_of<Site>::type()) , (A0()) , (A1()) , (A2()) , (A3()) , (A4()) , (A5()) , adl_helper() ) , type ) }; template<class A0 , class A1 , class A2 , class A3 , class A4 , class A5> BOOST_FORCEINLINE static typename apply<A0 , A1 , A2 , A3 , A4 , A5>::type call(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5) { return typename apply<A0 , A1 , A2 , A3 , A4 , A5>::type(); }
  };
  template<class Tag>
  struct dispatch_call : dispatch_call_default<Tag>
  {
  };
  template<class T>
  typename meta::hierarchy_of<T const>::type as_hierarchy(T const&)
  {
    return typename meta::hierarchy_of<T const>::type();
  }
  template<class T>
  typename meta::hierarchy_of<T>::type as_hierarchy(T&)
  {
    return typename meta::hierarchy_of<T>::type();
  }
} } }
