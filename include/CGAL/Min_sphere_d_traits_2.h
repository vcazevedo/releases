// ======================================================================
//
// Copyright (c) 1997 The CGAL Consortium
//
// This software and related documentation is part of the
// Computational Geometry Algorithms Library (CGAL).
//
// Every use of CGAL requires a license. Licenses come in three kinds:
//
// - For academic research and teaching purposes, permission to use and
//   copy the software and its documentation is hereby granted free of  
//   charge, provided that
//   (1) it is not a component of a commercial product, and
//   (2) this notice appears in all copies of the software and
//       related documentation.
// - Development licenses grant access to the source code of the library 
//   to develop programs. These programs may be sold to other parties as 
//   executable code. To obtain a development license, please contact
//   the CGAL Consortium (at cgal@cs.uu.nl).
// - Commercialization licenses grant access to the source code and the
//   right to sell development licenses. To obtain a commercialization 
//   license, please contact the CGAL Consortium (at cgal@cs.uu.nl).
//
// This software and documentation is provided "as-is" and without
// warranty of any kind. In no event shall the CGAL Consortium be
// liable for any damage of any kind.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Free University of Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany) Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// release       : CGAL-1.2
// release_date  : 1999, January 18
//
// chapter       : $CGAL_Chapter: Optimisation $
// file          : include/CGAL/Min_sphere_d_traits_2.h
// package       : Min_sphere_d (1.9)
// source        : web/Optimisation/Min_sphere_d.aw
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1999/01/08 10:38:24 $
// author(s)     : Sven Sch�nherr
//                 Bernd G�rtner
//
// coordinator   : ETH Zurich (Bernd G�rtner)
//
// implementation: dD Smallest Enclosing Sphere
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_MIN_SPHERE_D_TRAITS_2_H
#define CGAL_MIN_SPHERE_D_TRAITS_2_H

// Class declarations
// ==================

// Class interface and implementation
// ==================================
// includes
#ifndef CGAL_PROTECT_ITERATOR_H
#include <iterator.h>
#define CGAL_PROTECT_ITERATOR_H
#endif

#ifndef CGAL_POINT_2_H
#include <CGAL/Point_2.h>
#endif

#ifndef CGAL_REP_DISTINGUISHER_H
#include <CGAL/Rep_distinguisher.h>
#endif

template <class R>
class CGAL_Point_2_iterator :
    public input_iterator<typename R::RT, ptrdiff_t>
{
    private:
        typedef typename R::RT                      RT;
        typedef CGAL_Point_2<R>                     Point;

        typename R::Rep_tag                         tag;

        Point                                       p;
        int                                         pos;

    public:
        CGAL_Point_2_iterator ()
        {}

        CGAL_Point_2_iterator (const Point& point, int position = 0)
            : p(point), pos(position)
        {}

        // assignment; not actually necessary but explicitly defined
        // to please egcs
        CGAL_Point_2_iterator& operator= (const CGAL_Point_2_iterator& i)
        {
            p = i.p;
            pos = i.pos;
            return *this;
        }

        CGAL_Point_2_iterator operator++() // prefix
        {
            ++pos;
            return (*this);
        }

        CGAL_Point_2_iterator operator++(int dummy) // postfix
        {
            CGAL_Point_2_iterator it(p, pos++);
            return it;
        }

        RT operator*()
        {
            return dereference (tag);
        }

        RT dereference (CGAL_Cartesian_tag t)
        {
            switch (pos) {
                case 0:
                    return p.x();
                case 1:
                    return p.y();
                default:
                    CGAL_optimisation_assertion(false);
                    return RT(0);
            }
        }

        RT dereference (CGAL_Homogeneous_tag t)
        {
            switch (pos) {
                case 0:
                    return p.hx();
                case 1:
                    return p.hy();
                case 2:
                    return p.hw();
                default:
                    CGAL_optimisation_assertion(false);
                    return RT(0);
            }
        }


};


template <class R>
class CGAL_DA_2
{
    private:
        typedef typename R::RT              RT;
        typedef CGAL_Point_2<R>             Point;

        typename R::Rep_tag                 tag;
        bool                                check;

    public:
        typedef CGAL_Point_2_iterator<R>    InputIterator;

        // construction
        CGAL_DA_2 (bool checked = false)
            : check (checked)
        {}

        // get_dimension
        // -----------------------------------------------------------
        int get_dimension (const Point& p) const
        {
            return 2;
        }

        // get_begin
        // -----------------------------------------------------------
        InputIterator get_begin (const Point& p) const
        {
            if (check)
                CGAL_optimisation_assertion (correctly_accesses (p));
            return InputIterator (p);
        }

        // set
        // -----------------------------------------------------------
        void set (Point& p, RT* first, RT* last) const
        {
            if (last-first==2)
                p = CGAL_Point_2<R>(*first, *(first+1));
            else
                p = CGAL_Point_2<R>(*first, *(first+1), *(first+2));
        }

        // check
        bool correctly_accesses (const Point& p) const
        {
            return correctly_accesses (p, tag);
        }

        bool correctly_accesses (const Point& p, CGAL_Cartesian_tag t)
        const
        {
            InputIterator it(p);
            for (int i=0; i<2; ++i, ++it)
                if (p.cartesian(i) != *it)
                    return false;
            return true;
        }

        bool correctly_accesses (const Point& p, CGAL_Homogeneous_tag t)
        const
        {
            InputIterator it(p);
            for (int i=0; i<3; ++i, ++it)
                if (p.homogeneous(i) != *it) return false;
            return true;
        }
};


template <class _R>
class CGAL_Min_sphere_d_traits_2
{
    public:
        typedef _R                          R;
        typedef CGAL_Point_2<R>             Point;
        typedef CGAL_DA_2<R>                DA;

        DA                                  da;

        CGAL_Min_sphere_d_traits_2 (bool checked = false)
            : da (checked)
        {}
};



#endif // CGAL_MIN_SPHERE_D_TRAITS_2_H

// ===== EOF ==================================================================

