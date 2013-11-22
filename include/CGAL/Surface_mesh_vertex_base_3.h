// Copyright (c) 2006-2007  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.7-branch/Surface_mesher/include/CGAL/Surface_mesh_vertex_base_3.h $
// $Id: Surface_mesh_vertex_base_3.h 37876 2007-04-03 13:59:17Z lrineau $
//
// Author(s)     : Laurent Rineau

#ifndef CGAL_SURFACE_MESH_VERTEX_BASE_3_H
#define CGAL_SURFACE_MESH_VERTEX_BASE_3_H

#include <CGAL/Triangulation_vertex_base_3.h>
#include <CGAL/Complex_2_in_triangulation_vertex_base_3.h>

namespace CGAL {

  template < class GT, class Vb = Triangulation_vertex_base_3 <GT> > 
  class Surface_mesh_vertex_base_3 
    : public Complex_2_in_triangulation_vertex_base_3<GT, Vb> {    
    
  public:
    typedef Surface_mesh_vertex_base_3 <GT, Vb> Self;
    
    template < class TDS3 >
    struct Rebind_TDS {
      typedef typename Vb::template Rebind_TDS<TDS3>::Other  Vb3;
      typedef Surface_mesh_vertex_base_3 <GT, Vb3> Other;
    };
    
  public:  
    Surface_mesh_vertex_base_3()
      : Complex_2_in_triangulation_vertex_base_3<GT, Vb>()
    {}
  };  // end Surface_mesh_vertex_base_3

}  // namespace CGAL

#endif  // CGAL_SURFACE_MESH_CELL_BASE_3_H
