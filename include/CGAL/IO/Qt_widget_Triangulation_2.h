// Copyright (c) 1997-2000  Utrecht University (The Netherlands),
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
// $Source: /CVSROOT/CGAL/Packages/Qt_widget/include/CGAL/IO/Qt_widget_Triangulation_2.h,v $
// $Revision: 1.9.2.1 $ $Date: 2003/11/07 13:40:36 $
// $Name: CGAL_3_0_1  $
//
// Author(s)     : Radu Ursu <rursu@sophia.inria.fr>


#ifndef CGAL_QT_WIDGET_TRIANGULATION_2_H
#define CGAL_QT_WIDGET_TRIANGULATION_2_H

#include <CGAL/IO/Qt_widget.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/apply_to_range.h>


namespace CGAL {

template <class Gt, class Tds>
class Draw_triangulation {
private:
  const Triangulation_2<Gt, Tds>& t;
  Qt_widget& w;
public:
  Draw_triangulation(const Triangulation_2<Gt, Tds>& _t, Qt_widget& _w)
    : t(_t), w(_w)
  {}
  void operator()(typename Triangulation_2<Gt, Tds>::Face_handle fh)
  {
    for (int i=0; i<3; i++)
      if (fh < fh->neighbor(i) || t.is_infinite(fh->neighbor(i)))
        w << t.segment(fh,i);
  }
};


template < class Gt, class Tds>
Qt_widget&
operator<<(Qt_widget& w,  const Triangulation_2<Gt, Tds> &t)
{
  if (t.dimension()<2) {
    t.draw_triangulation(w);
    return w;
  }
  typedef typename Triangulation_2<Gt, Tds>::Point OpPoint;
  w.lock();
  Draw_triangulation<Gt, Tds> draw(t, w);
  apply_to_range(t, OpPoint(w.x_min(), w.y_max()), 
                 OpPoint(w.x_max(), w.y_min()), draw);
  w.unlock();
  return w;
}


}// end namespace CGAL

#endif
