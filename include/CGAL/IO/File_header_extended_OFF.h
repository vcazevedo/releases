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
// file          : include/CGAL/IO/File_header_extended_OFF.h
// package       : Polyhedron_IO (3.11)
// chapter       : Support Library
//
// revision      : $Revision: 1.2 $
// revision_date : $Date: 2001/12/17 12:40:54 $
//
// author(s)     : Lutz Kettner
// coordinator   : INRIA, Sophia Antipolis
//
// Extended file header information of an object file format (OFF) file
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_IO_FILE_HEADER_EXTENDED_OFF_H
#define CGAL_IO_FILE_HEADER_EXTENDED_OFF_H 1
#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif
#ifndef CGAL_PROTECT_IOSTREAM
#include <iostream>
#define CGAL_PROTECT_IOSTREAM
#endif

CGAL_BEGIN_NAMESPACE

class  File_header_extended_OFF {
    bool     m_verbose;     // Print error messages if true.
    bool     m_polyhedral_surface;
    int      m_halfedges;
    bool     m_triangulated;
    bool     m_non_empty_facets;
    bool     m_terrain;
    bool     m_normalized_to_sphere;
    double   m_radius;
    bool     m_rounded;
    int      m_rounded_bits;
    bool     m_off_header;
    char     m_suffix[20];
    char     m_format_name[20];
public:
    typedef  File_header_extended_OFF  Self;
    File_header_extended_OFF( bool verbose = false)
    :   m_verbose               ( verbose),
        m_polyhedral_surface    ( false),
        m_halfedges             ( 0),
        m_triangulated          ( false),
        m_non_empty_facets      ( false),
        m_terrain               ( false),
        m_normalized_to_sphere  ( false),
        m_radius                ( 0.0),
        m_rounded               ( false),
        m_rounded_bits          ( 0),
        m_off_header            ( true)
    {}
    // Access:
    bool   verbose()              const { return m_verbose; }
    bool   polyhedral_surface()   const { return m_polyhedral_surface; }
    int    halfedges()            const { return m_halfedges; }
    int    size_of_halfedges()    const { return m_halfedges; }
    bool   triangulated()         const { return m_triangulated; }
    bool   non_empty_facets()     const { return m_non_empty_facets; }
    bool   terrain()              const { return m_terrain; }
    bool   normalized_to_sphere() const { return m_normalized_to_sphere; }
    double radius()               const { return m_radius; }
    bool   rounded()              const { return m_rounded; }
    int    rounded_bits()         const { return m_rounded_bits; }
    bool   off_header()           const { return m_off_header; }
    // Derived predicates about the file format.
    bool   is_OFF()               const { return m_off_header; }
    bool   is_POL()               const;
    bool   is_CBP()               const;
    bool   is_TRN()               const;
    int    is_CBPn()              const;
    int    is_TRNn()              const;
    // The proper file suffix with respect to file format.
    const char* suffix() const;
    // The proper format name.
    const char* format_name() const;
    // Set values:
    void   set_verbose( bool b)              { m_verbose            = b; }
    void   set_polyhedral_surface( bool b)   { m_polyhedral_surface = b; }
    void   set_halfedges( int h)             { m_halfedges          = h; }
    void   set_triangulated( bool b)         { m_triangulated       = b; }
    void   set_non_empty_facets( bool b)     { m_non_empty_facets   = b; }
    void   set_terrain( bool b)              { m_terrain            = b; }
    void   set_normalized_to_sphere( bool b) { m_normalized_to_sphere = b;}
    void   set_radius( double d)             { m_radius             = d; }
    void   set_rounded( bool b)              { m_rounded            = b; }
    void   set_rounded_bits( int i)          { m_rounded_bits       = i; }
    void   set_off_header( bool b)           { m_off_header         = b; }
    Self&  operator+=( const Self& header); // union of two headers
};

// Write extended header incl. CGAL/ENDCBP keywords.
std::ostream& operator<<( std::ostream& out,
                          const File_header_extended_OFF& h);

// Scan extended header. The CBP keyword must be read already.
std::istream& operator>>( std::istream& in, File_header_extended_OFF& h);

// istream modifier skips chars until end of line.
inline std::istream& skip_until_EOL( std::istream& in) {
    char c;
    while ( in.get(c) && c != '\n')
        ;
    return in;
}

// istream modifier that checks for OFF comments and removes them.
inline std::istream& skip_comment_OFF( std::istream& in) {
    char c;
    while( (in >> c) && c == '#')
        in >> skip_until_EOL;
    in.putback(c);
    return in;
}

CGAL_END_NAMESPACE
#endif // CGAL_IO_FILE_HEADER_EXTENDED_OFF_H //
// EOF //
