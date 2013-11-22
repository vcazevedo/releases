// Copyright (c) 1998-2003  ETH Zurich (Switzerland).
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
// $Source: /CVSROOT/CGAL/Packages/Matrix_search/include/CGAL/Dynamic_matrix.h,v $
// $Revision: 1.58 $ $Date: 2003/09/29 08:41:44 $
// $Name: CGAL_3_0_1  $
//
// Author(s)     : Michael Hoffmann <hoffmann@inf.ethz.ch>

#if ! (CGAL_DYNAMIC_MATRIX_H)
#define CGAL_DYNAMIC_MATRIX_H 1

#include <CGAL/Optimisation/assertions.h>

CGAL_BEGIN_NAMESPACE

template < class Matrix >
class Dynamic_matrix
// adaptor for a matrix class
// to allow replacement of columns in constant time
// and extraction of all even rows in linear time
{
public:
  typedef std::vector< int >        CoordContainer;
  typedef Dynamic_matrix< Matrix >  ThisMatrixClass;
  typedef typename Matrix::Value    Value;

  Dynamic_matrix( const Matrix& m, int r_p = 0)
  : matrix( &m),
    column_indices( m.number_of_columns()),
    row_power( r_p),
    row_offset( (1 << r_p) - 1)
  {
    for ( unsigned int i( 0); i < column_indices.size(); ++i)
      column_indices[i] = i;
  }

  int
  number_of_rows() const
  {
    return ( matrix->number_of_rows() + row_offset) >> row_power;
  }

  int
  number_of_columns() const
  { return column_indices.size(); }

  Value
  operator()( int r, int c) const
  {
    CGAL_optimisation_precondition( r >= 0 && r < number_of_rows());
    CGAL_optimisation_precondition( c >= 0 && c < number_of_columns());
    return (*matrix)( r << row_power, column_indices[c]);
  }

  Value
  operator()( std::pair< int, int > p) const
  {
    return (*this)( p.first, p.second);
  }

  void
  replace_column( int o, int n)
  {
    CGAL_optimisation_precondition( o >= 0 && o < number_of_columns());
    CGAL_optimisation_precondition( n >= 0 && n < number_of_columns());
    column_indices[o] = column_indices[n];
  }

  void
  shrink_to_quadratic_size()
  {
    CGAL_optimisation_precondition( number_of_columns() >= number_of_rows());
    column_indices.erase( column_indices.begin() + number_of_rows(),
                          column_indices.end());
    CGAL_optimisation_postcondition( number_of_columns() == number_of_rows());
  }

private:
  Dynamic_matrix( const Matrix* m, const CoordContainer& c_i, int r_p)
  : matrix( m),
    column_indices( c_i),
    row_power( r_p),
    row_offset( (1 << r_p) - 1)
  {}

public:
  ThisMatrixClass*
  extract_all_even_rows() const
  {
    return new ThisMatrixClass( matrix, column_indices, row_power + 1);
  }

private:
  const Matrix*  matrix;
  CoordContainer column_indices;
  int            row_power;
  int            row_offset;
};

template < class Matrix >
inline
Dynamic_matrix< Matrix >
dynamic_matrix( const Matrix& m)
{ return Dynamic_matrix< Matrix >( m); }

CGAL_END_NAMESPACE

#endif // ! (CGAL_DYNAMIC_MATRIX_H)
// ----------------------------------------------------------------------------
// ** EOF
// ----------------------------------------------------------------------------

