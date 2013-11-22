// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium

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
//
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// file          : include/CGAL/smallest_radius_3.h
// package       : Alpha_shapes_3 (3.16)
// source        : $RCSfile: smallest_radius_3.h,v $
// revision      : $Revision: 1.3 $
// revision_date : $Date: 2001/06/19 14:21:26 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef SMALLEST_RADIUS_3_H
#define SMALLEST_RADIUS_3_H

#include <CGAL/Point_3.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template <class R >
CGAL_KERNEL_MEDIUM_INLINE
typename R::FT
squared_radius_smallest_circumsphere(const Point_3<R> &p,
				     const Point_3<R> &q)
{
  Vector_3<R> v(p - q);
  return typename R::FT ((v*v)/R::FT(4));
}

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif // SMALLEST_RADIUS_3_H
