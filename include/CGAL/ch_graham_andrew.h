// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/ch_graham_andrew.h
// package       : Convex_hull_2 (3.34)
// revision      : $Revision: 1.5 $
// revision_date : $Date: 2001/12/05 15:16:14 $
// author(s)     : Stefan Schirra
//
// coordinator   : MPI, Saarbruecken
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================


#ifndef CGAL_CH_GRAHAM_ANDREW_H
#define CGAL_CH_GRAHAM_ANDREW_H

#include <CGAL/basic.h>
#include <iterator>


CGAL_BEGIN_NAMESPACE

// computes the sorted sequence of extreme points which are not left 
// of $pq$ and reports this sequence in a range starting at |result|,
// where $p$ is the value of |first| and $q$ is the value of |last| $-1$.
// The sequence reported starts with $p$, point $q$ is omitted.
// {\it Precondition:} The points in [|first|,|last|) are sorted with respect
// to $pq$ and the range [|first|,|last|) contains at least two different 
// points.
// {\sc traits}: uses |Traits::Leftturn_2| operating on the 
// point type |Traits::Point_2|.
template <class BidirectionalIterator, class OutputIterator, class Traits>
OutputIterator
ch_graham_andrew_scan( BidirectionalIterator first,
                       BidirectionalIterator last,
                       OutputIterator        result,
                       const Traits& ch_traits );

template <class BidirectionalIterator, class OutputIterator>
inline
OutputIterator
ch_graham_andrew_scan( BidirectionalIterator first,
                       BidirectionalIterator last,
                       OutputIterator        result )
{ 
    typedef std::iterator_traits<BidirectionalIterator> ITraits;
    typedef typename ITraits::value_type          value_type;
    typedef CGAL::Kernel_traits<value_type>       KTraits;
    typedef typename KTraits::Kernel              Kernel;
    return ch_graham_andrew_scan( first, last, result, Kernel()); 
}

template <class BidirectionalIterator, class OutputIterator, class Traits>
OutputIterator
ch__ref_graham_andrew_scan( BidirectionalIterator first,
                            BidirectionalIterator last,
                            OutputIterator&       result,
                            const Traits&         ch_traits);


// same as |convex_hull_2(first,last,result)|.
// {\sc traits}: uses |Traits::Point_2|, |Traits::Leftturn_2|
// and |Traits::Less_xy_2|.
template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_graham_andrew( InputIterator  first,
                  InputIterator  last,
                  OutputIterator result,
                  const Traits&  ch_traits );

template <class InputIterator, class OutputIterator>
inline
OutputIterator
ch_graham_andrew( InputIterator  first,
                  InputIterator  last,
                  OutputIterator result )
{ 
    typedef std::iterator_traits<InputIterator>   ITraits;
    typedef typename ITraits::value_type          value_type;
    typedef CGAL::Kernel_traits<value_type>       KTraits;
    typedef typename KTraits::Kernel              Kernel;
    return ch_graham_andrew( first, last, result, Kernel()); 
}



template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_lower_hull_scan( InputIterator  first,
                    InputIterator  last,
                    OutputIterator result,
                    const Traits&  ch_traits);

template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_upper_hull_scan( InputIterator  first,
                    InputIterator  last,
                    OutputIterator result,
                    const Traits&  ch_traits);

CGAL_END_NAMESPACE

#ifdef CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION
#include <CGAL/ch_graham_andrew.C>
#endif // CGAL_CFG_NO_AUTOMATIC_TEMPLATE_INCLUSION

#endif // CGAL_CH_GRAHAM_ANDREW_H

