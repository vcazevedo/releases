// Copyright (c) 2008  INRIA Sophia-Antipolis (France).
// All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Installation/config/testfiles/CGAL_CFG_NO_STATEMENT_EXPRESSIONS.cpp $
// $Id: CGAL_CFG_NO_STATEMENT_EXPRESSIONS.cpp 49022 2009-04-29 20:03:21Z spion $
//
// Author(s)     : Sylvain Pion

//| If a compiler does not support statement expressions (a GCC extension)
//| CGAL_CFG_NO_STATEMENT_EXPRESSIONS is set. 

#undef NDEBUG
#include <cassert>

int main()
{
  int i = ({ int j = 2; j+j; });
  assert(i == 4);
  return 0;
}
