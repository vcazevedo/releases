// Copyright (c) 1997-2003  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source: /CVSROOT/CGAL/Packages/Interval_arithmetic/include/CGAL/Arithmetic_filter/predicates/in_smallest_orthogonalcircle_ftC2.h,v $
// $Revision: 1.41 $ $Date: 2004/01/18 12:06:27 $
// $Name:  $
//
// Author(s)     : Sylvain Pion

// This file is automatically generated by
// scripts/filtered_predicates_generator.pl

#ifndef CGAL_ARITHMETIC_FILTER_IN_SMALLEST_ORTHOGONALCIRCLE_FTC2_H
#define CGAL_ARITHMETIC_FILTER_IN_SMALLEST_ORTHOGONALCIRCLE_FTC2_H

#include <CGAL/Profile_counter.h>

CGAL_BEGIN_NAMESPACE
template <class ET> class Lazy_exact_nt;
CGAL_END_NAMESPACE

CGAL_BEGIN_NAMESPACE

template < class CT, class ET, bool Protected, class Cache >
/* CGAL_MEDIUM_INLINE */
Bounded_side
in_smallest_orthogonalcircleC2(
    const Filtered_exact <CT, ET, Dynamic, Protected, Cache> &px,
    const Filtered_exact <CT, ET, Dynamic, Protected, Cache> &py,
    const Filtered_exact <CT, ET, Dynamic, Protected, Cache> &pw,
    const Filtered_exact <CT, ET, Dynamic, Protected, Cache> &qx,
    const Filtered_exact <CT, ET, Dynamic, Protected, Cache> &qy,
    const Filtered_exact <CT, ET, Dynamic, Protected, Cache> &qw,
    const Filtered_exact <CT, ET, Dynamic, Protected, Cache> &tx,
    const Filtered_exact <CT, ET, Dynamic, Protected, Cache> &ty,
    const Filtered_exact <CT, ET, Dynamic, Protected, Cache> &tw)
{
  try
  {
    CGAL_PROFILER("IA in_smallest_orthogonalcircleC2 calls");
    Protect_FPU_rounding<Protected> Protection;
    return in_smallest_orthogonalcircleC2(
		px.interval(),
		py.interval(),
		pw.interval(),
		qx.interval(),
		qy.interval(),
		qw.interval(),
		tx.interval(),
		ty.interval(),
		tw.interval());
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    CGAL_PROFILER("IA in_smallest_orthogonalcircleC2 failures");
    Protect_FPU_rounding<!Protected> Protection(CGAL_FE_TONEAREST);
    return in_smallest_orthogonalcircleC2(
		px.exact(),
		py.exact(),
		pw.exact(),
		qx.exact(),
		qy.exact(),
		qw.exact(),
		tx.exact(),
		ty.exact(),
		tw.exact());
  }
}

template < class ET >
/* CGAL_MEDIUM_INLINE */
Bounded_side
in_smallest_orthogonalcircleC2(
    const Lazy_exact_nt<ET> &px,
    const Lazy_exact_nt<ET> &py,
    const Lazy_exact_nt<ET> &pw,
    const Lazy_exact_nt<ET> &qx,
    const Lazy_exact_nt<ET> &qy,
    const Lazy_exact_nt<ET> &qw,
    const Lazy_exact_nt<ET> &tx,
    const Lazy_exact_nt<ET> &ty,
    const Lazy_exact_nt<ET> &tw)
{
  try
  {
    CGAL_PROFILER("Lazy IA in_smallest_orthogonalcircleC2 calls");
    Protect_FPU_rounding<true> Protection;
    return in_smallest_orthogonalcircleC2(
		px.interval(),
		py.interval(),
		pw.interval(),
		qx.interval(),
		qy.interval(),
		qw.interval(),
		tx.interval(),
		ty.interval(),
		tw.interval());
  } 
  catch (Interval_nt_advanced::unsafe_comparison)
  {
    CGAL_PROFILER("Lazy IA in_smallest_orthogonalcircleC2 failures");
    Protect_FPU_rounding<false> Protection(CGAL_FE_TONEAREST);
    return in_smallest_orthogonalcircleC2(
		px.exact(),
		py.exact(),
		pw.exact(),
		qx.exact(),
		qy.exact(),
		qw.exact(),
		tx.exact(),
		ty.exact(),
		tw.exact());
  }
}

CGAL_END_NAMESPACE

#endif // CGAL_ARITHMETIC_FILTER_IN_SMALLEST_ORTHOGONALCIRCLE_FTC2_H
