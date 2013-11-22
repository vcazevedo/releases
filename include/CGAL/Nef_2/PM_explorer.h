// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

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
// file          : include/CGAL/Nef_2/PM_explorer.h
// package       : Nef_2 (1.18)
// chapter       : Nef Polyhedra
//
// source        : nef_2d/Nef_polyhedron_2.lw
// revision      : $Revision: 1.8 $
// revision_date : $Date: 2001/11/07 16:30:54 $
//
// author(s)     : Michael Seel
// coordinator   : Michael Seel
//
// implementation: Nef polyhedra in the plane
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_PM_EXPLORER_H
#define CGAL_PM_EXPLORER_H

#include <CGAL/basic.h>
#include <CGAL/Nef_2/PM_const_decorator.h>

CGAL_BEGIN_NAMESPACE

/*{\Moptions print_title=yes }*/ 
/*{\Moptions outfile=Explorer.man }*/
/*{\Msubst
PM_explorer#Explorer
}*/
/*{\Manpage {PM_explorer}{}{Plane map exploration}{E}}*/

/*{\Mdefinition An instance |\Mvar| of the data type |\Mname| is a
decorator to explore the structure of the plane map underlying the
Nef polyhedron. It inherits all topological adjacency exploration
operations from |PMConstDecorator|. |\Mname| additionally allows
one to explore the geometric embedding.

The position of each vertex is given by a so-called extended point,
which is either a standard affine point or the tip of a ray touching
an infinimaximal square frame centered at the origin. A vertex |v| is
called a \emph{standard} vertex if its embedding is a \emph{standard}
point and \emph{non-standard} if its embedding is a
\emph{non-standard} point. By the straightline embedding of their
source and target vertices, edges correspond to either affine segments,
rays or lines or are part of the bounding frame.

\displayeps{extsegs}{Extended geometry: standard vertices are marked
by S, non-standard vertices are marked by N. \textbf{A}: The possible
embeddings of edges: an affine segment s1, an affine ray s2, an affine
line s3. \textbf{B}: A plane map embedded by extended geometry: note
that the frame is arbitrarily large, the 6 vertices on the frame are at
infinity, the two faces represent a geometrically unbounded area,
however they are topologically closed by the frame edges. No standard
point can be placed outside the frame.}{10cm}
}*/

/*{\Mgeneralization Topological_explorer}*/

template <typename PMCDEC, typename GEOM>
class PM_explorer : public PMCDEC
{ typedef PMCDEC Base;
  typedef PM_explorer<PMCDEC,GEOM> Self;
  const GEOM* pK;
public:
/*{\Mtypes 4}*/
typedef PMCDEC Topological_explorer;
/*{\Mtypemember The base class.}*/
typedef typename PMCDEC::Plane_map Plane_map;
/*{\Xtypemember equals |PMCDEC::Plane_map|, the underlying plane map type.}*/
typedef GEOM Geometry;
/*{\Xtypemember equals |GEOM|. Add link to GEOM model.\\
\precond |Geometry::Point_2| equals |Plane_map::Point|. }*/
typedef typename GEOM::Standard_point_2 Point;
/*{\Mtypemember the point type of finite vertices.}*/
typedef typename GEOM::Standard_ray_2   Ray;
/*{\Mtypemember the ray type of vertices on the frame.}*/

typedef typename Base::Vertex_const_handle Vertex_const_handle;
typedef typename Base::Halfedge_const_handle Halfedge_const_handle;
typedef typename Base::Face_const_handle Face_const_handle;
typedef typename Base::Vertex_const_iterator Vertex_const_iterator;
typedef typename Base::Halfedge_const_iterator Halfedge_const_iterator;
typedef typename Base::Face_const_iterator Face_const_iterator;
typedef typename Base::Halfedge_around_face_const_circulator
                       Halfedge_around_face_const_circulator;
typedef typename Base::Halfedge_around_vertex_const_circulator
                       Halfedge_around_vertex_const_circulator;
typedef typename Base::Isolated_vertex_const_iterator
                       Isolated_vertex_const_iterator;
typedef typename Base::Hole_const_iterator
                       Hole_const_iterator;


/*{\Mtext Iterators, handles, and circulators are inherited from 
|Topological_explorer|.}*/

/*{\Mcreation 3}*/
/*{\Mtext |\Mname| is copy constructable and assignable. An object
can be obtained via the |Nef_polyhedron_2::explorer()| method of
|Nef_polyhedron_2|.}*/

PM_explorer(const Self& E) : Base(E), pK(E.pK) {}  
Self& operator=(const Self& E) 
{ Base::operator=(E); pK=E.pK; return *this; }

PM_explorer(const Plane_map& P, const Geometry& k = Geometry()) : 
  Base(P), pK(&k) {}
/*{\Xcreate constructs a plane map explorer working on |P| with
geometric predicates used from |k|.}*/

/*{\Moperations 2 }*/

bool is_standard(Vertex_const_handle v) const
/*{\Mop returns true iff |v|'s position is a standard point.}*/
{ return pK->is_standard(Base::point(v)); }

Point point(Vertex_const_handle v) const
/*{\Mop returns the standard point that is the embedding of |v|.
\precond |\Mvar.is_standard(v)|.}*/
{ return pK->standard_point(Base::point(v)); }

Ray ray(Vertex_const_handle v) const
/*{\Mop returns the ray defining the non-standard point on the frame. 
\precond |!\Mvar.is_standard(v)|.}*/
{ return pK->standard_ray(Base::point(v)); }

bool is_frame_edge(Halfedge_const_handle e) const
/*{\Mop returns true iff |e| is part of the infinimaximal frame.}*/
{ return ( face(e) == faces_begin() ||
           face(twin(e)) == faces_begin() ); }

}; // PM_explorer<PMCDEC,GEOM>



CGAL_END_NAMESPACE

#endif // CGAL_PM_EXPLORER_H

