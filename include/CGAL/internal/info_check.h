// Copyright (c) 2010   GeometryFactory (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/next/Triangulation_3/include/CGAL/internal/info_check.h $
// $Id: info_check.h 63930 2011-06-07 08:20:54Z sloriot $
//
//
// Author(s)     : Sebastien Loriot
//

#ifndef CGAL_INTERNAL_INFO_CHECK_H
#define CGAL_INTERNAL_INFO_CHECK_H

#include <boost/mpl/has_xxx.hpp>

namespace CGAL {

namespace internal{

BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(Has_typedef_Info,Info,false)  
 
template <class T,bool has_info=Has_typedef_Info<T>::value>
 struct Info_check{
 struct type{};
};

template <class T>
struct Info_check<T,true>{
 typedef typename T::Info type;
};

} } //namespace CGAL::internal

#endif //CGAL_INTERNAL_INFO_CHECK_H
