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
// INRIA Sophia-Antipolis (France), Max-Planck-Institute Saarbrucken
// (Germany), RISC Linz (Austria), and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.1
// release_date  : 1998, July 24
//
// file          : include/CGAL/IO/Polyhedron_inventor_ostream.h
// package       : Polyhedron_IO (1.9)
// chapter       : $CGAL_Chapter: Support Library ... $
// source        : polyhedron_io.fw
// revision      : $Revision: 1.6 $
// revision_date : $Date: 1998/06/03 20:34:54 $
// author(s)     : Lutz Kettner
//
// coordinator   : Herve Bronnimann
//
// Print a Polyhedron_3 in Inventor file format (.iv)
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_IO_POLYHEDRON_INVENTOR_OSTREAM_H
#define CGAL_IO_POLYHEDRON_INVENTOR_OSTREAM_H 1
#ifndef CGAL_IO_INVENTOR_OSTREAM_H
#include <CGAL/IO/Inventor_ostream.h>
#endif // CGAL_IO_INVENTOR_OSTREAM_H
#ifndef CGAL_IO_FILE_WRITER_INVENTOR_H
#include <CGAL/IO/File_writer_inventor.h>
#endif // CGAL_IO_FILE_WRITER_INVENTOR_H
#ifndef CGAL_IO_GENERIC_PRINT_POLYHEDRON_H
#include <CGAL/IO/generic_print_polyhedron.h>
#endif // CGAL_IO_GENERIC_PRINT_POLYHEDRON_H
#ifndef CGAL_POLYHEDRON_3_H
#include <CGAL/Polyhedron_3.h>
#endif

template <class Traits, class HDS>
CGAL_Inventor_ostream_base&
operator<< ( CGAL_Inventor_ostream_base& out,
             const CGAL_Polyhedron_3<Traits,HDS>& P) {
    CGAL_File_writer_inventor  writer;
    CGAL_generic_print_polyhedron( out.os(), P, writer);
    return out;
}
#endif // CGAL_IO_POLYHEDRON_INVENTOR_OSTREAM_H //
// EOF //