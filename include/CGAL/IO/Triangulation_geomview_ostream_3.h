// Copyright (c) 2000  INRIA Sophia-Antipolis (France).
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
// $Source: /CVSROOT/CGAL/Packages/Triangulation_3/include/CGAL/IO/Triangulation_geomview_ostream_3.h,v $
// $Revision: 1.9 $ $Date: 2003/09/18 10:26:34 $
// $Name:  $
//
// Author(s)     : Sylvain Pion <Sylvain.Pion@sophia.inria.fr>

#ifndef CGAL_IO_TRIANGULATION_GEOMVIEW_OSTREAM_3_H
#define CGAL_IO_TRIANGULATION_GEOMVIEW_OSTREAM_3_H

#include <CGAL/IO/Geomview_stream.h>
#include <CGAL/Triangulation_3.h>

// TODO :
// - Check the correctness when dimension < 3.
// - Use the stream color instead of built-in constant/random.
// - If interfaces were more similar, we could think of sharing 2d and 3d ?

CGAL_BEGIN_NAMESPACE

// This one is to show the edges of a 3D triangulation.
template < class GT, class TDS >
void
show_triangulation_edges(Geomview_stream &gv, const Triangulation_3<GT,TDS> &T)
{
  // Header.
  gv.set_ascii_mode();
  gv << "(geometry " << gv.get_new_id("triangulationedge")
     << " {appearance {}{ SKEL \n"
     << T.number_of_vertices() << T.number_of_finite_edges() << "\n";

  // Finite vertices coordinates.
  std::map<typename Triangulation_3<GT, TDS>::Vertex_handle, int> V;
  int inum = 0;
  for( typename Triangulation_3<GT, TDS>::Finite_vertices_iterator
      vit = T.finite_vertices_begin(); vit != T.finite_vertices_end(); ++vit) {
    V[vit] = inum++;
    gv << vit->point() << "\n";
  }
  
  // Finite edges indices.
  for( typename Triangulation_3<GT, TDS>::Finite_edges_iterator
	  eit = T.finite_edges_begin(); eit != T.finite_edges_end(); ++eit) {
      gv << 2
         << V[(*eit).first->vertex((*eit).second)]
         << V[(*eit).first->vertex((*eit).third)]
         << "\n"; // without color.
      // << 4 << drand48() << drand48() << drand48() << 1.0; // random color.
  }
}

template < class GT, class TDS >
Geomview_stream&
operator<<( Geomview_stream &gv, const Triangulation_3<GT,TDS> &T)
{
    if (gv.get_wired()) {
        // We draw the edges.
        bool ascii_bak = gv.get_ascii_mode();
        bool raw_bak = gv.set_raw(true);

        show_triangulation_edges(gv, T);

        // Footer.
        gv << "}})";

        gv.set_raw(raw_bak);
        gv.set_ascii_mode(ascii_bak);
    }
    else {
        // We draw the facets.
        std::vector<typename GT::Triangle_3> triangles;

        for (typename Triangulation_3<GT, TDS>::Finite_facets_iterator
	     fit = T.finite_facets_begin(); fit != T.finite_facets_end();
	     ++fit)
            triangles.push_back(T.triangle(*fit));

        gv.draw_triangles(triangles.begin(), triangles.end());
    }
    return gv;
}

CGAL_END_NAMESPACE

#endif // CGAL_IO_TRIANGULATION_GEOMVIEW_OSTREAM_3_H
