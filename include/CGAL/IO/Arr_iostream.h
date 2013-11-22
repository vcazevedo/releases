// Copyright (c) 2005-2007 Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Arrangement_on_surface_2/include/CGAL/IO/Arr_iostream.h $
// $Id: Arr_iostream.h 40195 2007-09-05 09:51:34Z ophirset $
// 
//
// Author(s)     : Ron Wein           <wein@post.tau.ac.il>
//                 (based on old version by Michal Meyerovitch and Ester Ezra)

#ifndef CGAL_ARR_IOSTREAM_H
#define CGAL_ARR_IOSTREAM_H

/*! \file
 * Definition of the I/O operators for the class-template
 * Arrangement_on_surface_2<GeomTraits,TopTraits>.
 */

#include <CGAL/Arrangement_on_surface_2.h>
#include <CGAL/IO/Arr_text_formatter.h>
#include <CGAL/IO/Arrangement_2_writer.h>
#include <CGAL/IO/Arrangement_2_reader.h>
#include <iostream>

CGAL_BEGIN_NAMESPACE

/*!
 * Write an arrangement to an output stream using a given formatter.
 * \param arr The arrangement.
 * \param os The output stream.
 * \param format The formatter.
 */
template <class GeomTraits, class TopTraits, class Formatter>
std::ostream&
    write (const Arrangement_on_surface_2<GeomTraits,TopTraits>& arr,
           std::ostream& os, 
           Formatter& format)
{
  typedef Arrangement_on_surface_2<GeomTraits,TopTraits>  Arrangement_2;
  typedef Arrangement_2_writer<Arrangement_2>             Arr_writer;

  Arr_writer      writer (arr);

  format.set_out (os);
  writer (format);
  return (os);
}

/*!
 * Output operator (importer).
 * \param os The output stream.
 * \param arr The arrangement.
 */
template <class GeomTraits, class TopTraits>
std::ostream&
    operator<< (std::ostream& os, 
                const Arrangement_on_surface_2<GeomTraits,TopTraits>& arr)
{
  typedef Arrangement_on_surface_2<GeomTraits,TopTraits>  Arrangement_2;
  typedef Arrangement_2_writer<Arrangement_2>             Arr_writer;
  typedef Arr_text_formatter<Arrangement_2>               Text_formatter;

  Text_formatter text_format (os);
  Arr_writer      writer (arr);

  writer (text_format);
  return (os);
}

/*!
 * Read an arrangement from an input stream using a given formatter.
 * \param arr The arrangement.
 * \param os The output stream.
 * \param format The formatter.
 */
template <class GeomTraits, class TopTraits, class Formatter>
std::istream&
    read (Arrangement_on_surface_2<GeomTraits,TopTraits>& arr,
          std::istream& is, 
          Formatter& format)
{
  typedef Arrangement_on_surface_2<GeomTraits,TopTraits>  Arrangement_2;
  typedef Arrangement_2_reader<Arrangement_2>             Arr_reader;

  Arr_reader      reader(arr);

  format.set_in (is);
  reader (format);
  return (is);
}

/*!
 * Output operator (exporter).
 * \param is The input stream.
 * \param arr The arrangement.
 */
template <class GeomTraits, class TopTraits>
std::istream&
    operator>> (std::istream& is, 
                Arrangement_on_surface_2<GeomTraits,TopTraits>& arr)
{
  typedef Arrangement_on_surface_2<GeomTraits,TopTraits>  Arrangement_2;
  typedef Arrangement_2_reader<Arrangement_2>             Arr_reader;
  typedef Arr_text_formatter<Arrangement_2>               Text_formatter;

  Text_formatter text_format (is);
  Arr_reader      reader(arr);
  
  reader (text_format);
  return (is);
}

CGAL_END_NAMESPACE

#endif
