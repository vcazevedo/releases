// ======================================================================
//
// Copyright (c) 2001 The CGAL Consortium

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
// - A commercial license is available through Algorithmic Solutions
//   (http://www.algorithmic-solutions.com). 
// - Commercial users may apply for an evaluation license by writing to
//   (Andreas.Fabri@geometryfactory.com). 
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-2.3 (patch 1)
// release_date  : 2001, November 09
//
// file          : include/CGAL/convex_hull_3.h
// package       : Convex_hull_3 (2.29)
// chapter       : Convex Hulls and Extreme Points
//
// revision      : $Revision: 1.18 $
// revision_date : $Date: 2001/10/30 09:58:52 $
//
// author(s)     : Susan Hert
//               : Amol Prakash
//
// coordinator   : MPI (Susan Hert)
//
// implementation: 3D convex hull via quickhull algorithm
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_CONVEX_HULL_3_H
#define CGAL_CONVEX_HULL_3_H

#include <CGAL/basic.h>
#include <CGAL/Unique_hash_map.h>
#include <CGAL/algorithm.h> 
#include <CGAL/convex_hull_2.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/Convex_hull_traits_3.h>
#include <CGAL/functional.h>
#include <iostream>
#include <algorithm>
#include <utility>
#include <list>
#include <vector>

#ifndef CH_NO_POSTCONDITIONS
#include <CGAL/convexity_check_3.h>
#endif // CH_NO_POSTCONDITIONS


namespace CGAL {


template<class HDS, class ForwardIterator>
class Build_coplanar_poly : public Modifier_base<HDS> {
 public:
  Build_coplanar_poly(ForwardIterator i, ForwardIterator j) 
    {
      start = i;
      end = j;
    }
  void operator()( HDS& hds) {
    Polyhedron_incremental_builder_3<HDS> B(hds,true);
    ForwardIterator iter = start;
    int count = 0;
    while (iter != end)
      {
	count++;
	iter++;
      }
    B.begin_surface(count, 1, 2*count);
    iter = start;
    while (iter != end)
      {
	B.add_vertex(*iter);
	iter++;
      }
    iter = start;
    B.begin_facet();
    int p = 0;
    while (p < count)
      {
	B.add_vertex_to_facet(p);
	p++;
      }
    B.end_facet();
    B.end_surface();
  }
 private:
  ForwardIterator start;
  ForwardIterator end;    
};

template <class Vector_3>
int max_coordinate(const Vector_3& v)
{
   if (CGAL_NTS abs(v.x()) >= CGAL_NTS abs(v.y()))
   {
      if (CGAL_NTS abs(v.x()) >= CGAL_NTS abs(v.z())) return 0;
      return 2;
   }
   else
   {
      if (CGAL_NTS abs(v.y()) >= CGAL_NTS abs(v.z())) return 1;
      return 2;
   }
}

template <class InputIterator, class Plane_3, class Polyhedron_3, class Traits>
void coplanar_3_hull(InputIterator first, InputIterator beyond,
                     Plane_3 plane, Polyhedron_3& P, const Traits& traits)
{
  typedef typename Traits::R                     R;
  typedef typename Traits::Point_3               Point_3;
  typedef typename Traits::Vector_3              Vector_3;
  
  std::list<Point_3> CH_2;
  typedef typename std::list<Point_3>::iterator  CH_2_iterator;
  typedef typename Traits::Construct_orthogonal_vector_3
                                                   Construct_normal_vec;
  Construct_normal_vec c_normal = 
                          traits.construct_orthogonal_vector_3_object();
  Vector_3 normal = c_normal(plane);
  int max_coord = max_coordinate(normal);
  switch (max_coord)
  {
     case 0:
     {
       convex_hull_points_2(first, beyond, std::back_inserter(CH_2),
            Convex_hull_projective_yz_traits_2<Point_3>());
       break;
     }
     case 1:
     {
       convex_hull_points_2(first, beyond, std::back_inserter(CH_2),
            Convex_hull_projective_xz_traits_2<Point_3>());
       break;
     }
     case 2:
     {
       convex_hull_points_2(first, beyond, std::back_inserter(CH_2),
            Convex_hull_projective_xy_traits_2<Point_3>());
       break;
     }
     default:
       break;
  }
  typedef typename Polyhedron_3::Halfedge_data_structure HDS;

  Build_coplanar_poly<HDS,CH_2_iterator> poly(CH_2.begin(),CH_2.end());
  P.delegate(poly);
}


//
// visible is the set of facets visible from point  and reachable from
// start_facet.
//
template <class Facet_handle, class Traits>
void
find_visible_set(const typename Traits::Point_3& point, 
                 Facet_handle start_facet,
                 std::list<Facet_handle>& visible,
                 const Traits& traits)
{
   typedef typename Facet_handle::value_type                  Facet;
   typedef typename Facet::Halfedge_around_facet_circulator   Halfedge_circ;

   typename Traits::Has_on_positive_side_3 has_on_positive_side =
            traits.has_on_positive_side_3_object();

   visible.clear();
   typename std::list<Facet_handle>::iterator  vis_it;
   CGAL::Unique_hash_map<Facet_handle, bool> visited(false);
   visible.push_back(start_facet);
   visited[start_facet] = true;
   Facet_handle current;
   for (vis_it = visible.begin(); vis_it != visible.end(); vis_it++)
   {
      // check all the neighbors of the current facet to see if they have 
      // already been visited or not and if not whether they are visible 
      // or not.
      current = *vis_it; 
      Halfedge_circ hdl_init = (*current).facet_begin();
      Halfedge_circ hdl_curr = hdl_init;
      do
      {
          // the facet on the other side of the current halfedge
          Facet_handle f = (*(*hdl_curr).opposite()).facet();
          // if haven't already seen this facet
          if ( !visited[f] )
          {
             visited[f] = true;
             if ( has_on_positive_side((*f).plane(), point) )  // is visible
             {
               visible.push_back(f);
             }
          }
          hdl_curr++;
      }
      while (hdl_curr != hdl_init);
   }
}

template <class Facet_handle, class Traits>
typename Traits::Point_3
farthest_outside_point(Facet_handle f_handle, 
                       std::list<typename Traits::Point_3>& outside_set,
                       const Traits& traits)
{
   typedef typename Traits::Point_3               Point_3;
   typedef typename std::list<Point_3>::iterator     Outside_set_iterator;

   CGAL_assertion(!outside_set.empty());
   typename Traits::Less_signed_distance_to_plane_3 less_dist_to_plane =
            traits.less_signed_distance_to_plane_3_object();
   Outside_set_iterator farthest_it =
          std::max_element(outside_set.begin(),
                           outside_set.end(), 
                           bind_1(less_dist_to_plane, (*f_handle).plane()));

   return *farthest_it;
}

template <class Facet_handle>
void compute_plane_equation(Facet_handle f) 
{
   typedef typename Facet_handle::value_type         Facet;
   typedef typename Facet::Halfedge_handle           Halfedge_handle;
   typedef typename Facet::Plane_3                   Plane_3;

   Halfedge_handle h = (*f).halfedge();
   (*f).plane() = Plane_3(h->opposite()->vertex()->point(),
                          h->vertex()->point(),
                          h->next()->vertex()->point());
}

template <class Facet_handle, class Traits>
void     
partition_outside_sets(const std::list<Facet_handle>& new_facets,
        std::list<typename Traits::Point_3>& vis_outside_set, 
        CGAL::Unique_hash_map<Facet_handle, 
                       std::list<typename Traits::Point_3> >& outside_sets,
        std::list<Facet_handle>& pending_facets, 
        const Traits& traits)
{
   typename std::list<Facet_handle>::const_iterator        f_list_it;
   typename std::list<typename Traits::Point_3>::iterator  point_it;

   typename Traits::Has_on_positive_side_3 has_on_positive_side =
           traits.has_on_positive_side_3_object();

   // walk through all the new facets and check each unassigned outside point
   // to see if it belongs to the outside set of this new facet.
   for (f_list_it = new_facets.begin(); f_list_it != new_facets.end();
        f_list_it++)
   {
      compute_plane_equation(*f_list_it);
      for (point_it = vis_outside_set.begin(); 
           point_it != vis_outside_set.end();)
      {
        if ( has_on_positive_side((*(*f_list_it)).plane(), *point_it) )
        {
           outside_sets[(*f_list_it)].push_back(*point_it);
           point_it = vis_outside_set.erase(point_it);
        }
        else
           point_it++;
     }
   }
   // put all the new facets with non-empty outside sets in the pending facets
   // list.
   for (f_list_it = new_facets.begin(); f_list_it != new_facets.end(); 
        f_list_it++)
   {
      if (!outside_sets[*f_list_it].empty())
         pending_facets.push_back(*f_list_it);
   }
}

template <class Polyhedron_3, class Traits>
void 
ch_quickhull_3_scan( 
        Polyhedron_3& P,
        std::list<typename Polyhedron_3::Facet_handle>& pending_facets,
        CGAL::Unique_hash_map<typename Polyhedron_3::Facet_handle, 
                   std::list<typename Traits::Point_3> >& outside_sets,
        const Traits& traits)
{
  typedef typename Polyhedron_3::Halfedge_handle          Halfedge_handle;
  typedef typename Polyhedron_3::Halfedge_iterator        Halfedge_iterator;
  typedef typename Polyhedron_3::Facet_handle             Facet_handle;
  typedef typename Traits::Point_3			  Point_3;
  typedef std::list<Point_3>                              Outside_set;
  typedef typename std::list<Point_3>::iterator           Outside_set_iterator;

  std::list<Facet_handle>                     visible_set;
  typename std::list<Facet_handle>::iterator  vis_set_it;
  Outside_set                                 vis_outside_set;
  Halfedge_iterator                           hole_halfedge;
  Halfedge_handle                             new_pt_halfedge;


  while (!pending_facets.empty())
  {
     vis_outside_set.clear();

     Facet_handle f_handle = pending_facets.back();
     pending_facets.pop_back();
     Point_3 farthest_pt = 
          farthest_outside_point(f_handle, outside_sets[f_handle], traits);

     find_visible_set(farthest_pt, f_handle, visible_set, traits);
     // for each visible facet
     for (vis_set_it = visible_set.begin(); vis_set_it != visible_set.end();
          vis_set_it++)
     {
        //   add its outside set to the global outside set list
        std::copy(outside_sets[*vis_set_it].begin(),
                  outside_sets[*vis_set_it].end(),
                  std::back_inserter(vis_outside_set));
        //   delete this visible facet
        P.erase_facet((*(*vis_set_it)).halfedge());
        outside_sets[*vis_set_it].clear();
     }
     for (hole_halfedge = P.halfedges_begin(); 
          hole_halfedge != P.halfedges_end() && !(*hole_halfedge).is_border();
          hole_halfedge++) 
     {}
     CGAL_assertion(hole_halfedge->is_border());
     CGAL_assertion(hole_halfedge->next()->is_border());
     // add a new facet and vertex to the surface.  This is the first
     // new facet to be added.
     new_pt_halfedge = P.add_vertex_and_facet_to_border(hole_halfedge, 
                                                      (*hole_halfedge).next());
     // associate the farthest point with the new vertex. 
     (*(*new_pt_halfedge).vertex()).point() = farthest_pt;
     CGAL_assertion( !new_pt_halfedge->is_border() );
     CGAL_assertion( new_pt_halfedge->opposite()->is_border() );

     std::list<Facet_handle>  new_facets;
     new_facets.push_back(new_pt_halfedge->facet());
     Halfedge_handle start_hole_halfedge = new_pt_halfedge->opposite()->prev();
     CGAL_assertion( start_hole_halfedge->is_border() );
     CGAL_assertion( start_hole_halfedge->vertex()->point() == farthest_pt );

     // need to move to second next halfedge to get to a point where a 
     // triangular facet can be created
     Halfedge_handle curr_halfedge = start_hole_halfedge->next()->next();
     CGAL_assertion( curr_halfedge->is_border() );

     Halfedge_handle new_halfedge;

     // now walk around all the border halfedges and add a facet incident to
     // each one to connect it to the farthest point
     while (curr_halfedge->next() != start_hole_halfedge)
     {
        new_halfedge = 
               P.add_facet_to_border(start_hole_halfedge, curr_halfedge);
        CGAL_assertion( !new_halfedge->is_border() );
        CGAL_assertion( new_halfedge->opposite()->is_border() );
        new_facets.push_back(new_halfedge->facet());

        // once the new facet is added curr->next() will be the next halfedge
        // on this facet (i.e., not a border halfedge), so the next border
        // halfedge will be the one after the opposite of the new halfedge
        curr_halfedge = new_halfedge->opposite()->next();
        CGAL_assertion( curr_halfedge->is_border() );
     }
     // fill in the last triangular hole with a facet
     new_halfedge = P.fill_hole(curr_halfedge);
     new_facets.push_back(new_halfedge->facet());

     // now partition the set of outside set points among the new facets.
     partition_outside_sets(new_facets, vis_outside_set, outside_sets,
                            pending_facets, traits);
  }   
}

template <class Polyhedron_3, class Traits>
void non_coplanar_quickhull_3(std::list<typename Traits::Point_3>& points,
                              Polyhedron_3& P, const Traits& traits)
{
  typedef typename Polyhedron_3::Facet_handle             Facet_handle;
  typedef typename Polyhedron_3::Facet_iterator           Facet_iterator;
  typedef typename Traits::Point_3                        Point_3;
  typedef CGAL::Unique_hash_map<Facet_handle, std::list<Point_3> >   
                                                          Outside_set_map;
  typedef typename std::list<Point_3>::iterator           P3_iterator;

  std::list<Facet_iterator> pending_facets;

  Facet_iterator f_it;

  typename Traits::Has_on_positive_side_3 has_on_positive_side =
           traits.has_on_positive_side_3_object();

  Outside_set_map outside_sets;

  // for each facet, look at each unassigned point and decide if it belongs
  // to the outside set of this facet.
  for (f_it = P.facets_begin(); f_it != P.facets_end(); f_it++)
  {
     compute_plane_equation(f_it);
     for (P3_iterator point_it = points.begin() ; point_it != points.end();)
     {
        if ( has_on_positive_side((*f_it).plane(), *point_it) )
        {
           outside_sets[f_it].push_back(*point_it);
           point_it = points.erase(point_it);
        }
        else
           point_it++;
     }
  }
  // add all the facets with non-empty outside sets to the set of facets for
  // further consideration
  for (f_it = P.facets_begin(); f_it != P.facets_end(); f_it++)
     if (!outside_sets[f_it].empty())
       pending_facets.push_back(f_it);
  ch_quickhull_3_scan(P, pending_facets, outside_sets, traits);

  CGAL_ch_expensive_postcondition(all_points_inside(first,beyond,P,traits));
  CGAL_ch_postcondition(is_strongly_convex_3(P, traits));
}

template <class Polyhedron_3, class Traits>
void
ch_quickhull_polyhedron_3(std::list<typename Traits::Point_3>& points, 
        typename std::list<typename Traits::Point_3>::iterator point1_it, 
        typename std::list<typename Traits::Point_3>::iterator point2_it, 
        typename std::list<typename Traits::Point_3>::iterator point3_it, 
        Polyhedron_3& P,
        const Traits& traits)
{
  typedef typename Traits::Point_3	  		  Point_3;  
  typedef typename Traits::Plane_3		      	  Plane_3;
  typedef typename std::list<Point_3>::iterator           P3_iterator;

  // found three points that are not collinear, so construct the plane defined
  // by these points and then find a point that has maximum distance from this
  // plane.   
  typename Traits::Construct_plane_3 construct_plane =
         traits.construct_plane_3_object();
  Plane_3 plane = construct_plane(*point3_it, *point2_it, *point1_it);
  typedef typename Traits::Less_signed_distance_to_plane_3      Dist_compare; 
  Dist_compare compare_dist = 
                traits.less_signed_distance_to_plane_3_object();
  
  typename Traits::Coplanar_3  coplanar = traits.coplanar_3_object(); 
  // find both min and max here since using signed distance.  If all points
  // are on the negative side of ths plane, the max element will be on the
  // plane.
  std::pair<P3_iterator, P3_iterator> min_max;
  min_max = CGAL::min_max_element(points.begin(), points.end(), 
                                  bind_1(compare_dist, plane),
                                  bind_1(compare_dist, plane));
  P3_iterator max_it;
  if (coplanar(*point1_it, *point2_it, *point3_it, *min_max.second))
     max_it = min_max.first;
  else
     max_it = min_max.second;

  // if the maximum distance point is on the plane then all are coplanar
  if (coplanar(*point1_it, *point2_it, *point3_it, *max_it)) 
     coplanar_3_hull(points.begin(), points.end(), plane, P, traits);
  else
  {
     P.make_tetrahedron(*point1_it, *point2_it, *point3_it, *max_it);
     points.erase(point1_it);
     points.erase(point2_it);
     points.erase(point3_it);
     points.erase(max_it);
     if (!points.empty())
        non_coplanar_quickhull_3(points, P, traits);
  }
}

template <class InputIterator, class Traits>
void
convex_hull_3(InputIterator first, InputIterator beyond, 
              Object& ch_object, const Traits& traits)
{  
  typedef typename Traits::Point_3	  		  Point_3;  
  typedef typename Traits::Plane_3		      	  Plane_3;
  typedef std::list<Point_3>                              Point_3_list;
  typedef typename Point_3_list::iterator                 P3_iterator;
  typedef std::pair<P3_iterator,P3_iterator>              P3_iterator_pair;

  if (first == beyond)    // No point
    return;

  Point_3_list points(first, beyond);
  
  unsigned int size = points.size();
  
  if ( size == 1 )                // 1 point 
  {
      ch_object = make_object(*points.begin());
      return;
  }
  else if ( size == 2 )           // 2 points 
  {
      typedef typename Traits::Segment_3                 Segment_3;  
      typename Traits::Construct_segment_3 construct_segment =
             traits.construct_segment_3_object();
      Segment_3 seg = construct_segment(*points.begin(), *(++points.begin()));
      ch_object = make_object(seg);
      return;
  }
  else if ( size == 3 )           // 3 points 
  {
      typedef typename Traits::Triangle_3                Triangle_3;  
      typename Traits::Construct_triangle_3 construct_triangle =
             traits.construct_triangle_3_object();
      Triangle_3 tri = construct_triangle(*(points.begin()), 
                                          *(++points.begin()),
                                          *(--points.end()));
      ch_object = make_object(tri);
      return;
  }

  // at least 4 points 
  typename Traits::Collinear_3 collinear = traits.collinear_3_object();
  
  P3_iterator point1_it = points.begin();
  P3_iterator point2_it = points.begin();
  point2_it++;
  P3_iterator point3_it = points.end();
  point3_it--;

  // find three that are not collinear
  while (point2_it != points.end() && 
         collinear(*point1_it,*point2_it,*point3_it))
    point2_it++;
  

  // all are collinear, so the answer is a segment
  if (point2_it == points.end())
  {
     typedef typename Traits::Less_distance_to_point_3      Less_dist; 

     Less_dist less_dist = traits.less_distance_to_point_3_object();
     P3_iterator_pair endpoints = 
      min_max_element(points.begin(), points.end(), 
                      bind_1(less_dist, *points.begin()), 
                      bind_1(less_dist, *points.begin()));

     typename Traits::Construct_segment_3 construct_segment =
            traits.construct_segment_3_object();
     typedef typename Traits::Segment_3                 Segment_3;  

     Segment_3 seg = construct_segment(*endpoints.first, *endpoints.second);
     ch_object = make_object(seg);
     return;
  }

  typename Traits::Polyhedron_3 P;

  // result will be a polyhedron
  ch_quickhull_polyhedron_3(points, point1_it, point2_it, point3_it,
                            P, traits);
  ch_object = make_object(P);
}

template <class InputIterator>
void convex_hull_3(InputIterator first, InputIterator beyond, 
		   Object& ch_object)
{
   typedef typename std::iterator_traits<InputIterator>::value_type Point_3;
   CGAL_ch_quickhull_obj_3(first, beyond, ch_object,
                           reinterpret_cast<Point_3*>(0));

}

template <class InputIterator, class R>
void CGAL_ch_quickhull_obj_3(InputIterator first, InputIterator beyond, 
		             Object& ch_object, Point_3<R>*)
{
   convex_hull_3(first, beyond, ch_object, Convex_hull_traits_3<R>());
}

template <class InputIterator, class Polyhedron_3, class Traits>
void convex_hull_3(InputIterator first, InputIterator beyond, 
                   Polyhedron_3& polyhedron,  const Traits& traits)
{  
  typedef typename Traits::Point_3	  		  Point_3;  
  typedef typename Traits::Plane_3		      	  Plane_3;
  typedef std::list<Point_3>                              Point_3_list;
  typedef typename Point_3_list::iterator                 P3_iterator;

  Point_3_list points(first, beyond);
  CGAL_ch_precondition(points.size() > 3);

  // at least 4 points 
  typename Traits::Collinear_3 collinear = traits.collinear_3_object();
  
  P3_iterator point1_it = points.begin();
  P3_iterator point2_it = points.begin();
  point2_it++;
  P3_iterator point3_it = points.end();
  point3_it--;

  // find three that are not collinear
  while (point2_it != points.end() && 
         collinear(*point1_it,*point2_it,*point3_it))
    point2_it++;
  
  CGAL_ch_precondition_msg(point2_it != points.end(), 
        "All points are collinear; cannot construct polyhedron.");
  
  polyhedron.clear();
  // result will be a polyhedron
  ch_quickhull_polyhedron_3(points, point1_it, point2_it, point3_it,
                            polyhedron, traits);
}

template <class InputIterator, class Polyhedron_3>
void convex_hull_3(InputIterator first, InputIterator beyond, 
                   Polyhedron_3& polyhedron)
{
   typedef typename std::iterator_traits<InputIterator>::value_type Point_3;
   CGAL_ch_quickhull_poly_3(first, beyond, polyhedron,
                                   reinterpret_cast<Point_3*>(0));

}

template <class InputIterator, class Polyhedron_3, class R>
void CGAL_ch_quickhull_poly_3(InputIterator first, InputIterator beyond, 
		              Polyhedron_3& polyhedron, Point_3<R>*)
{
   convex_hull_3(first, beyond, polyhedron, Convex_hull_traits_3<R>());
}


} // namespace CGAL

#endif // CGAL_CONVEX_HULL_3_H
