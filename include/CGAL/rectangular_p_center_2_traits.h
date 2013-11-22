// ======================================================================
//
// Copyright (c) 1998 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// file          : include/CGAL/rectangular_p_center_2_traits.h
// package       : Matrix_search (1.10)
// chapter       : $CGAL_Chapter: Geometric Optimisation $
// source        : pcenter.aw
// revision      : $Revision: 1.10 $
// revision_date : $Date: 1998/11/26 16:25:41 $
// author(s)     : Michael Hoffmann
//
// coordinator   : ETH Zurich (Bernd Gaertner)
//
// 2-4-Center Computation for Axis-Parallel 2D-Rectangles
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#if ! (CGAL_RECTANGULAR_P_CENTER_2_TRAITS_H)
#define CGAL_RECTANGULAR_P_CENTER_2_TRAITS_H 1

#ifndef CGAL_OPTIMISATION_ASSERTIONS_H
#include <CGAL/optimisation_assertions.h>
#endif // CGAL_OPTIMISATION_ASSERTIONS_H
#ifndef CGAL_ISO_RECTANGLE_2_H
#include <CGAL/Iso_rectangle_2.h>
#endif // CGAL_ISO_RECTANGLE_2_H
#ifndef CGAL_PROTECT_VECTOR_H
#include <vector.h>
#define CGAL_PROTECT_VECTOR_H
#endif // CGAL_PROTECT_VECTOR_H

#if !defined(CGAL_CFG_NO_ITERATOR_TRAITS) && \
  !defined(CGAL_CFG_MATCHING_BUG_2)

#ifndef CGAL_PROTECT_ITERATOR_H
#include <iterator.h>
#define CGAL_PROTECT_ITERATOR_H
#endif // CGAL_PROTECT_ITERATOR_H

#endif // ! (CGAL_CFG_NO_ITERATOR_TRAITS) && ...

#ifdef CGAL_CARTESIAN_REP_H
template < class ForwardIterator,
           class OutputIterator,
           class FT >
inline
OutputIterator
_CGAL_rectangular_p_center_2(
  ForwardIterator f,
  ForwardIterator l,
  OutputIterator o,
  FT& r,
  int p,
  CGAL_Point_2< CGAL_Cartesian< FT > >*)
{
  typedef
    CGAL_Piercing_squares_traits_cartesian< CGAL_Cartesian< FT > >
  PTraits;

  return CGAL_rectangular_p_center_2( f, l, o, r, p, PTraits());
} // CGAL_rectangular_p_center_2( ... )
#endif // CGAL_CARTESIAN_REP_H

#ifdef CGAL_HOMOGENEOUS_REP_H
template < class ForwardIterator,
           class OutputIterator,
#ifdef CGAL_CFG_MATCHING_BUG_1
           class FT,
#endif
           class RT >
inline
OutputIterator
_CGAL_rectangular_p_center_2(
  ForwardIterator f,
  ForwardIterator l,
  OutputIterator o,
#ifndef CGAL_CFG_MATCHING_BUG_1
  CGAL_Homogeneous< RT >::FT& r,
#else
  FT& r,
#endif
  int p,
  CGAL_Point_2< CGAL_Homogeneous< RT > >*)
{
  typedef
    CGAL_Piercing_squares_traits_homogeneous< CGAL_Homogeneous< RT > >
  PTraits;

  return CGAL_rectangular_p_center_2( f, l, o, r, p, PTraits());
} // CGAL_rectangular_p_center_2( ... )
#endif // CGAL_HOMOGENEOUS_REP_H

template < class ForwardIterator, class FT >
struct CGAL__blow_up_iso_square_static_2
{
  void
  operator()( ForwardIterator b, ForwardIterator e, FT v) const
  {
    if ( b != e)
      (*b).set_radius( v / FT( 2));
  }
};
/*
template < class ForwardIterator, class FT, class R >
void
CGAL__rectangle_blow_up_to( ForwardIterator f,
                            ForwardIterator l,
                            FT diameter,
                            CGAL_Iso_rectangle_2< R >*)
{
  for ( ForwardIterator i( f); i != l; ++i) {
    CGAL_Point_2< R > c(
      ((*i).xmin() + (*i).xmax()) / FT( 2),
      ((*i).ymin() + (*i).ymax()) / FT( 2));
    CGAL_Vector_2< R > t( diameter / FT( 2),
                          diameter / FT( 2));
    (*i) = CGAL_Iso_rectangle_2< R >( c - t, c + t);
  }
}
*/


template < class _PiercingFunction >
class CGAL_Pcenter_default_traits {
public:
  typedef _PiercingFunction                            PiercingFunction;
  typedef typename _PiercingFunction::Iso_rectangle_2  Iso_rectangle_2;
  typedef typename _PiercingFunction::Point_2          Point_2;
  typedef typename _PiercingFunction::FT               FT;
  typedef typename _PiercingFunction::X                X;
  typedef typename _PiercingFunction::Y                Y;
  typedef typename _PiercingFunction::Build_point      Build_point;
  typedef typename _PiercingFunction::Build_rectangle  Build_rectangle;
  typedef vector< Iso_rectangle_2 >                    Cont;
  typedef typename Cont::size_type                     size_type;
  typedef typename Cont::iterator                      iterator;
  typedef CGAL__blow_up_iso_square_static_2< iterator, FT >
    Blow_up_rectangles;

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
  template < class InputIterator >
#else
  typedef vector< Point_2 >::iterator                  InputIterator;
  typedef back_insert_iterator< vector< Point_2 > >    OutputIterator;
#endif // CGAL_CFG_NO_MEMBER_TEMPLATES
  CGAL_Pcenter_default_traits(
    InputIterator f,
    InputIterator l,
    const PiercingFunction& pf)
  : _pf( pf)
  {
    CGAL_optimisation_precondition( f != l);
#if !defined(CGAL_CFG_NO_ITERATOR_TRAITS) && \
    !defined(CGAL_CFG_MATCHING_BUG_2)
    typedef typename iterator_traits< InputIterator >::iterator_category
      iterator_category;
    _data_init( f, l, iterator_category());
#else
    _data_init( f, l);
#endif
    CGAL_optimisation_postcondition( !input_data.empty());
  }

  size_type
  number_of_points() const
  { return input_data.size(); }

  bool
  operator()( FT v)
  {
    CGAL_optimisation_assertion( !input_data.empty());
    bool ok;
    this->operator()( v,
                      CGAL_Wastebasket< Point_2 >(),
                      ok);
    return ok;
  }

#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
  template < class OutputIterator >
#else
  CGAL_Wastebasket< Point_2 >
  operator()( FT v, CGAL_Wastebasket< Point_2 > o, bool& ok)
  {
    CGAL_optimisation_assertion( !input_data.empty());
    Blow_up_rectangles blow_it;
    blow_it( input_data.begin(), input_data.end(), v);
    return _pf( input_data.begin(),
                input_data.end(),
                o,
                ok);
  }
#endif // CGAL_CFG_NO_MEMBER_TEMPLATES
  OutputIterator
  operator()( FT v, OutputIterator o, bool& ok)
  {
    CGAL_optimisation_assertion( !input_data.empty());
    Blow_up_rectangles blow_it;
    blow_it( input_data.begin(), input_data.end(), v);
    return _pf( input_data.begin(),
                input_data.end(),
                o,
                ok);
  }

protected:

#if !defined(CGAL_CFG_NO_ITERATOR_TRAITS) && \
  !defined(CGAL_CFG_MATCHING_BUG_2)

  template < class InputIterator >
  void
  _data_init( InputIterator f,
              InputIterator l,
              random_access_iterator_tag)
  {
    input_data.reserve( CGAL_iterator_distance( f, l));
    _data_init( f, l, input_iterator_tag());
  }

  template < class InputIterator, class IteratorCategory >
  void
  _data_init( InputIterator f,
              InputIterator l,
              IteratorCategory)
#else
#ifndef CGAL_CFG_NO_MEMBER_TEMPLATES
  template < class InputIterator >
#endif // CGAL_CFG_NO_MEMBER_TEMPLATES
  void
  _data_init( InputIterator f, InputIterator l)
#endif // ! (CGAL_CFG_NO_ITERATOR_TRAITS) && ...
  {
    while ( f != l) {
      Point_2 p( *(f++));
      input_data.push_back( Build_rectangle()( p));
    }
  } // _data_init( ... )


  // data members:
  PiercingFunction           _pf;
  vector< Iso_rectangle_2 >  input_data;

}; // CGAL_Pcenter_default_traits< PiercingFunction >


#endif // ! (CGAL_RECTANGULAR_P_CENTER_2_TRAITS_H)

// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

