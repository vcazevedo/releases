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
// file          : include/CGAL/Inverse_index.h
// package       : STL_Extension (1.17)
// chapter       : $CGAL_Chapter: STL Extensions for CGAL $
// source        : stl_extension.fw
// revision      : $Revision: 1.12 $
// revision_date : $Date: 1998/10/08 14:35:33 $
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// Inverse_Index adaptor enumerates sequences.
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_INVERSE_INDEX_H
#define CGAL_INVERSE_INDEX_H 1
#ifndef CGAL_CIRCULATOR_H
#include <CGAL/circulator.h>  // Needed for circulator categories.
#endif // CGAL_CIRCULATOR_H
#ifndef CGAL_PROTECT_MAP_H
#include <map.h>
#define CGAL_PROTECT_MAP_H
#endif // CGAL_PROTECT_MAP_H

template < class IC>
class CGAL_Inverse_index {

// DEFINITION
//
// The class CGAL_Inverse_index<IC,T> constructs an inverse index for a
// given range [i,j) of two iterators or circulators of type `IC' with the
// value type `T'. The first element I in the
// range [i,j) has the index 0. Consecutive elements are numbered
// incrementally. The inverse index provides a query for a given iterator
// or circulator k to retrieve its index number. For random access
// iterators or circulators, it is done in constant time by subtracting i.
// For other iterator categories, an STL `map' is used, which results in a
// log j-i query time. A comparison operator `operator<' is needed for
// `T*'.
//
// CREATION

protected:
    typedef map< const void*, size_t, less<const void*> > Index;
    Index   _index;
    IC      start;
    typedef typename Index::iterator        Index_iterator;
    typedef typename Index::const_iterator  Index_const_iterator;
    typedef typename Index::value_type      Item;

public:
    void _init_index( IC i, const IC& j, input_iterator_tag);
    void _init_index( const IC& i, const IC& j, forward_iterator_tag){
        _init_index( i, j, input_iterator_tag());
    }
    void _init_index( const IC& i, const IC& j,bidirectional_iterator_tag){
        _init_index( i, j, input_iterator_tag());
    }
    void _init_index( const IC& i, const IC& j,
                      CGAL_Forward_circulator_tag){
        _init_index( i, j, input_iterator_tag());
    }
    void _init_index( const IC& i, const IC& j,
                      CGAL_Bidirectional_circulator_tag){
        _init_index( i, j, input_iterator_tag());
    }
    void _init_index( const IC&, const IC&, random_access_iterator_tag){}
    void _init_index( const IC&, const IC&,
                      CGAL_Random_access_circulator_tag){}
    void init_index( const IC& i, const IC& j) {
        _init_index( i, j, iterator_category( i));
    }


    void push_back( const IC& k, input_iterator_tag) {
        size_t d = _index.size();
        _index[ &*k] = d;
    }
    void push_back( const IC& k, forward_iterator_tag){
        push_back( k, input_iterator_tag());
    }
    void push_back( const IC& k, bidirectional_iterator_tag){
        push_back( k, input_iterator_tag());
    }
    void push_back( const IC& k, CGAL_Forward_circulator_tag){
        push_back( k, input_iterator_tag());
    }
    void push_back( const IC& k, CGAL_Bidirectional_circulator_tag){
        push_back( k, input_iterator_tag());
    }
    void push_back( const IC&, random_access_iterator_tag){}
    void push_back( const IC&, CGAL_Random_access_circulator_tag){}


#ifndef CGAL_CFG_NO_LAZY_INSTANTIATION
    size_t find( const IC& k, random_access_iterator_tag) const {
        return size_t(k - start);
    }
    size_t find( const IC& k, CGAL_Random_access_circulator_tag) const {
        return size_t(k - start);
    }
#endif
    size_t find( const IC& k, input_iterator_tag) const {
        // returns inverse index of k.
        Index_const_iterator i = _index.find( &*k);
        CGAL_assertion( i != _index.end());
        return (*i).second;
    }
    size_t find( const IC& k, forward_iterator_tag) const {
        return find( k, input_iterator_tag());
    }
    size_t find( const IC& k, bidirectional_iterator_tag) const {
        return find( k, input_iterator_tag());
    }
    size_t find( const IC& k, CGAL_Forward_circulator_tag) const {
        return find( k, input_iterator_tag());
    }
    size_t find( const IC& k, CGAL_Bidirectional_circulator_tag) const {
        return find( k, input_iterator_tag());
    }

    typedef IC      iterator;
    typedef IC      Circulator;
    typedef size_t  size_type;

    CGAL_Inverse_index() : start(IC()) {}
        // invalid index.

    CGAL_Inverse_index( const IC& i) : start(i) {};
        // empty inverse index initialized to start at i.

    CGAL_Inverse_index( const IC& i, const IC& j) : start(i) {
        // inverse index initialized with range [i,j).
        init_index( i, j);
    }

// OPERATIONS

    size_t operator[]( const IC& k) const {
        // returns inverse index of k.
#ifndef CGAL_CFG_NO_ITERATOR_TRAITS
        typedef typename iterator_traits<IC>::iterator_category category;
        return find( k, category());
#else
        return find( k, iterator_category( k));
#endif
    }

    void push_back( const IC& k) {
        // adds k at the end of the indices.
        push_back( k, iterator_category( k));
    }
};

template < class IC>
void
CGAL_Inverse_index< IC>::_init_index( IC i, const IC& j,
                                     input_iterator_tag) {
    size_t n = 0;
    Index_iterator hint = _index.begin();
    if ( ! CGAL_is_empty_range( i, j)) {
        do {
            hint = _index.insert( hint, Item( &*i, n));
            n++;
        } while ((++i) != (j));
    }
}
#endif // CGAL_INVERSE_INDEX_H //
// EOF //
