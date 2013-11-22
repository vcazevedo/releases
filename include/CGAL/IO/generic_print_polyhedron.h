// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
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
// file          : include/CGAL/IO/generic_print_polyhedron.h
// package       : Polyhedron_IO (1.11)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.8 $
// revision_date : $Date: 1998/10/08 22:46:22 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// A generic writer for polyhedral surfaces parameterized by file format
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_GENERIC_PRINT_POLYHEDRON_H
#define CGAL_IO_GENERIC_PRINT_POLYHEDRON_H 1
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

#ifndef CGAL_POLYHEDRON_3_H
#include <CGAL/Polyhedron_3.h>
#endif

#ifndef CGAL_INVERSE_INDEX_H
#include <CGAL/Inverse_index.h>
#endif

#ifndef CGAL_PROTECT_IOSTREAM_H
#include <iostream.h>
#define CGAL_PROTECT_IOSTREAM_H
#endif // CGAL_PROTECT_IOSTREAM_H

template <class Traits, class HDS, class Writer>
void
CGAL_generic_print_polyhedron( ostream& out,
                              const CGAL_Polyhedron_3<Traits,HDS>& P,
                              Writer& writer) {
    // writes P to `out' in the format provided by `writer'.
    typedef CGAL_Polyhedron_3<Traits,HDS>                    Poly;
    typedef typename Poly::Vertex                           Vertex;
    typedef typename Poly::Size                             Size;
    typedef typename Poly::Vertex_const_iterator            VCI;
    typedef typename Poly::Facet_const_iterator             FCI;
    typedef typename Poly::Halfedge_around_facet_const_circulator
                                                            HFCC;
    // Print header.
    writer.write_header( out,
                         P.size_of_vertices(),
                         P.size_of_halfedges(),
                         P.size_of_facets());
    for( VCI vi = P.vertices_begin(); vi != P.vertices_end(); ++vi) {
        writer.write_vertex( (*vi).point().x(),
                             (*vi).point().y(),
                             (*vi).point().z());
    }
    typedef CGAL_Inverse_index< VCI> Index;
    Index index( P.vertices_begin(), P.vertices_end());
    writer.write_facet_header();

    for( FCI fi = P.facets_begin(); fi != P.facets_end(); ++fi) {
        HFCC hc = (*fi).facet_begin();
        HFCC hc_end = hc;
        size_t n = CGAL_circulator_size( hc);
        CGAL_assertion( n >= 3);
        writer.write_facet_begin( n);
        do {
            writer.write_facet_vertex_index( index[ VCI((*hc).vertex())]);
            ++hc;
        } while( hc != hc_end);
        writer.write_facet_end();
    }
    writer.write_footer();
}
#endif // CGAL_IO_GENERIC_PRINT_POLYHEDRON_H //
// EOF //
