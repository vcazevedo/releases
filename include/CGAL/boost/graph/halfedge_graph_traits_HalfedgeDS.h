// Copyright (c) 2007  GeometryFactory (France).  All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.7-branch/BGL/include/CGAL/boost/graph/halfedge_graph_traits_HalfedgeDS.h $
// $Id: halfedge_graph_traits_HalfedgeDS.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Andreas Fabri, Fernando Cacciola

#ifndef CGAL_BOOST_GRAPH_HALFEDGE_GRAPH_TRAITS_HALFEDGEDS_H
#define CGAL_BOOST_GRAPH_HALFEDGE_GRAPH_TRAITS_HALFEDGEDS_H

#include <boost/config.hpp>
#include <boost/iterator_adaptors.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>

#include <CGAL/basic.h>

namespace CGAL {

template < class HDS >
class HDS_all_undirected_edges_const_iterator 
  : public HDS_all_edges_iterator_base<HDS,typename HDS::Edge_const_iterator,typename HDS::Halfedge_const_handle>
{
  typedef HDS_all_edges_iterator_base<HDS,typename HDS::Edge_const_iterator,typename HDS::Halfedge_const_handle> Base ;
  
public:

  typedef typename HDS::Edge_const_iterator Iterator;

  HDS_all_undirected_edges_const_iterator() {}
  HDS_all_undirected_edges_const_iterator( Iterator j) : Base(j) {}
};

template < class HDS >
class HDS_all_undirected_edges_iterator 
  : public HDS_all_edges_iterator_base<HDS,typename HDS::Edge_iterator,typename HDS::Halfedge_handle>
{
  typedef HDS_all_edges_iterator_base<HDS,typename HDS::Edge_iterator,typename HDS::Halfedge_handle> Base ;
  
public:

  typedef typename HDS::Edge_iterator Iterator;

  HDS_all_undirected_edges_iterator() {}
  HDS_all_undirected_edges_iterator( Iterator j) : Base(j) {}
};


template <class HDS_>
struct HDS_halfedge_graph_traits
{
public :
  
  typedef HDS_ HDS;
  
  typedef HDS_all_undirected_edges_iterator<HDS> undirected_edge_iterator;
  
  typedef typename HDS::Vertex::Point Point ;
};

} //namespace CGAL

#endif // CGAL_BOOST_GRAPH_HALFEDGE_GRAPH_TRAITS_HALFEDGEDS_H
