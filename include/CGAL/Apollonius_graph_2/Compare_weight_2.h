// Copyright (c) 2003,2004,2006  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/releases/CGAL-3.9-branch/Apollonius_graph_2/include/CGAL/Apollonius_graph_2/Compare_weight_2.h $
// $Id: Compare_weight_2.h 63970 2011-06-08 06:31:19Z mkaravel $
// 
//
// Author(s)     : Menelaos Karavelas <mkaravel@iacm.forth.gr>



#ifndef CGAL_APOLLONIUS_GRAPH_2_COMPARE_WEIGHT_2_H
#define CGAL_APOLLONIUS_GRAPH_2_COMPARE_WEIGHT_2_H

#include <CGAL/Apollonius_graph_2/basic.h>

//--------------------------------------------------------------------

namespace CGAL {

namespace ApolloniusGraph_2 {

template<class K>
class Compare_weight_2
{
public:
  typedef K                               Kernel;
  typedef typename K::Site_2              Site_2;

  typedef typename K::Comparison_result   result_type;
  typedef Site_2                          argument_type;

  inline
  result_type operator()(const Site_2& s1, const Site_2& s2) const
  {
    return CGAL::compare(s1.weight(), s2.weight());
  }
};

//--------------------------------------------------------------------

} //namespace ApolloniusGraph_2

} //namespace CGAL

#endif // CGAL_APOLLONIUS_GRAPH_2_COMPARE_WEIGHT_2_H
