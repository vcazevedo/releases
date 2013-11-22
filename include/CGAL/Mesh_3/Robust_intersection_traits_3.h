// Copyright (c) 2009 INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.7-branch/Mesh_3/include/CGAL/Mesh_3/Robust_intersection_traits_3.h $
// $Id: Robust_intersection_traits_3.h 57355 2010-07-07 07:30:34Z stayeb $
//
//
// Author(s)     : Stephane Tayeb
//
//******************************************************************************
// File Description : 
//******************************************************************************

#ifndef CGAL_MESH_3_ROBUST_INTERSECTION_TRAITS_3_H
#define CGAL_MESH_3_ROBUST_INTERSECTION_TRAITS_3_H

#include <CGAL/Cartesian_converter.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>


namespace CGAL {

namespace Mesh_3 {


template < typename K_ >
class Robust_intersection_3
{
public:
  typedef typename K_::FT                             FT;
  
  typedef typename K_::Triangle_3                       Triangle_3;
  typedef typename K_::Line_3                       Line_3;
  typedef typename K_::Ray_3                       Ray_3;
  typedef typename K_::Segment_3                       Segment_3;
  
  typedef Object                                 result_type;
  
  typedef Exact_predicates_exact_constructions_kernel   EK;
  typedef Cartesian_converter<typename K_::Kernel, EK>    To_exact;
  typedef Cartesian_converter<EK, typename K_::Kernel>    Back_from_exact;
  
  template<class T1, class T2>
  Object operator() (const T1& t, const T2& s) const
  {
    // Switch to exact
    To_exact to_exact;
    Back_from_exact back_from_exact;
    EK::Intersect_3 exact_intersection = EK().intersect_3_object();
    
    Object object = exact_intersection(to_exact(t), to_exact(s));
    
    if ( const EK::Point_3* p = object_cast<EK::Point_3>(&object) )
      return make_object(back_from_exact(*p));
    else if ( const EK::Segment_3* seg = object_cast<EK::Segment_3>(&object) )
      return make_object(back_from_exact(*seg));
    else 
      return Object();
  }
};



/**
 * @struct Robust_intersection_traits_3
 */
template<class K_>
struct Robust_intersection_traits_3
: public K_
{
  typedef Robust_intersection_3<K_> Intersect_3;
  
  Intersect_3
  intersect_3_object() const
  {
    return Intersect_3();
  }
  
};


} // end namespace Mesh_3
  
} //namespace CGAL

#endif // CGAL_MESH_3_ROBUST_INTERSECTION_TRAITS_3_H
