// Copyright (c) 2003  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/releases/CGAL-3.9-branch/Polyhedron/demo/Polyhedron/opengl_tools.h $
// $Id: opengl_tools.h 64013 2011-06-09 13:15:31Z lrineau $
// 
//
// Author(s)     : Laurent Rineau <laurent.rineau__CGAL@normalesup.org>

#ifndef CGAL_OPENGL_TOOLS_H
#define CGAL_OPENGL_TOOLS_H

#include <CGAL/gl.h>

namespace CGAL {
namespace GL {

class Color {
  GLfloat c[4];
public:
  Color() {
    ::glGetFloatv(GL_COLOR, &c[0]);
  }
  ~Color() {
    set_rgb_color(c[0], c[1], c[2], c[3]);
  }
  void set_rgb_color(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.f) {
    ::glColor4f(r, g, b, a);
  }
}; // end class Color;

class Point_size {
  GLfloat ps;
public:
  Point_size() {
    ::glGetFloatv(GL_POINT_SIZE, &ps);
  }
  ~Point_size() {
    set_point_size(ps);
  }
  void set_point_size(GLfloat v) {
    ::glPointSize(v);
  }
}; // end class Point_size

} // end namespace GL
} // end namespace CGAL

#endif // not CGAL_OPENGL_TOOLS_H
