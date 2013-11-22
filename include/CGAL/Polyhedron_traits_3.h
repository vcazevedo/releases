// Copyright (c) 1997  ETH Zurich (Switzerland).
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
// $Source: /CVSROOT/CGAL/Packages/Polyhedron/include/CGAL/Polyhedron_traits_3.h,v $
// $Revision: 1.7 $ $Date: 2003/09/18 10:24:57 $
// $Name:  $
//
// Author(s)     : Lutz Kettner  <kettner@mpi-sb.mpg.de>)

#ifndef CGAL_POLYHEDRON_TRAITS_3_H
#define CGAL_POLYHEDRON_TRAITS_3_H 1

#include <CGAL/basic.h>

CGAL_BEGIN_NAMESPACE

template < class Kernel_ >
class Polyhedron_traits_3 {
public:
    typedef Kernel_                   Kernel;
    typedef typename Kernel::Point_3  Point_3;
    typedef typename Kernel::Plane_3  Plane_3;

    typedef typename Kernel::Construct_opposite_plane_3 
                                      Construct_opposite_plane_3;
private:
    Kernel m_kernel;

public:
    Polyhedron_traits_3() {}
    Polyhedron_traits_3( const Kernel& kernel) : m_kernel(kernel) {}

    Construct_opposite_plane_3 construct_opposite_plane_3_object() const {
        return m_kernel.construct_opposite_plane_3_object();
    }
};

CGAL_END_NAMESPACE

#endif // CGAL_POLYHEDRON_TRAITS_3_H //
// EOF //
