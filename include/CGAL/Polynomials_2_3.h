// Copyright (c) 2005-2006  INRIA Sophia-Antipolis (France).
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
// Partially supported by the IST Programme of the EU as a Shared-cost
// RTD (FET Open) Project under Contract No  IST-2000-26473 
// (ECG - Effective Computational Geometry for Curves and Surfaces) 
// and a STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.7-branch/Algebraic_kernel_for_spheres/include/CGAL/Polynomials_2_3.h $
// $Id: Polynomials_2_3.h 56667 2010-06-09 07:37:13Z sloriot $
//
// Author(s) : Monique Teillaud <Monique.Teillaud@sophia.inria.fr>
//             Sylvain Pion
//             Pedro Machado
//             Julien Hazebrouck
//             Damien Leroy

#ifndef CGAL_ALGEBRAIC_KERNEL_POLYNOMIALS_2_3_H
#define CGAL_ALGEBRAIC_KERNEL_POLYNOMIALS_2_3_H

#include <CGAL/enum.h>

namespace CGAL {

// polynomials of the form (X-a)^2 + (Y-b)^2 + (Z-c)^2 - R^2
template < typename FT_ >
class Polynomial_for_spheres_2_3
{
  FT_ rep[4]; // stores a, b, c, R^2
  
public:
  
  typedef FT_ FT;
  
  Polynomial_for_spheres_2_3(){}
  
  Polynomial_for_spheres_2_3(const FT & a, const FT & b, const FT & c, const FT & rsq)
  { 
    rep[0]=a;
    rep[1]=b;
    rep[2]=c;
    rep[3]=rsq;
  }

  const FT & a() const
  { return rep[0]; }

  const FT & b() const
  { return rep[1]; }
  
  const FT & c() const
  { return rep[2]; }
  
  const FT & r_sq() const
  { return rep[3]; }

  bool empty_space() const {
    return is_negative(r_sq());
  }

  bool isolated_point() const {
    return is_zero(r_sq());
  }

};

template < typename FT >
inline
bool 
operator == ( const Polynomial_for_spheres_2_3<FT> & p1,
	      const Polynomial_for_spheres_2_3<FT> & p2 )
{
  return( (p1.a() == p2.a()) && 
	  (p1.b() == p2.b()) &&
	  (p1.c() == p2.c()) &&
	  (p1.r_sq() == p2.r_sq()) );
}

} //namespace CGAL

#endif //CGAL_ALGEBRAIC_KERNEL_POLYNOMIALS_2_3_H
