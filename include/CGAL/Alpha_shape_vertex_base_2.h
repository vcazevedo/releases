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
// file          : include/CGAL/Alpha_shape_vertex_base_2.h
// package       : Alpha_shapes_2 (11.19)
// source        : $RCSfile: Alpha_shape_vertex_base_2.h,v $
// revision      : $Revision: 1.2 $
// revision_date : $Date: 1999/11/05 16:37:23 $
// author(s)     : Tran Kai Frank DA
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec>)
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_ALPHA_SHAPE_VERTEX_BASE_2_H
#define CGAL_ALPHA_SHAPE_VERTEX_BASE_2_H

#include <utility>
#include <CGAL/Triangulation_vertex_base_2.h>

//-------------------------------------------------------------------
CGAL_BEGIN_NAMESPACE
//-------------------------------------------------------------------

template <class Gt>
class Alpha_shape_vertex_base_2 : public
Triangulation_vertex_base_2<Gt> 
{

private:
  typedef typename Gt::Coord_type Coord_type;
  typedef std::pair< Coord_type, Coord_type > Interval2;

public:
  typedef typename Triangulation_vertex_base_2<Gt>::Point Point;
  
  Alpha_shape_vertex_base_2()
    : Triangulation_vertex_base_2<Gt>() 
    {}
  
  Alpha_shape_vertex_base_2(const Point & p)
    : Triangulation_vertex_base_2<Gt>(p) 
    {}
  
  Alpha_shape_vertex_base_2(const Point & p, void* f)
    : Triangulation_vertex_base_2<Gt>(p, f) 
    {}


private:

  Interval2 I;

public:

  inline Interval2 get_range() 
    {
      return I;
    }

  inline void set_range(Interval2 Inter)
    {  
      I = Inter;
    }

};

//-------------------------------------------------------------------
CGAL_END_NAMESPACE
//-------------------------------------------------------------------

#endif //ALPHA_SHAPE_VERTEX_BASE_2_H
