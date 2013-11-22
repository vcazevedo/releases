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
// file          : include/CGAL/Timer.h
// package       : Support_LK (1.18)
// source        : Support_LK/web/Timer.h
// revision      : $Revision: 1.3 $
// revision_date : $Date: 1998/06/02 22:37:52 $ 
// author(s)     : Lutz Kettner
//
// coordinator   : INRIA, Sophia Antipolis
//
// A timer class to measure cpu time of user-processes.
//
// email         : cgal@cs.uu.nl
//
// ======================================================================

#ifndef CGAL_TIMER_H
#define CGAL_TIMER_H 1

#ifndef CGAL_BASIC_H
#include <CGAL/basic.h>
#endif

#ifndef CGAL_PROTECT_STDLIB_H
#include <stdlib.h>
#define CGAL_PROTECT_STDLIB_H
#endif // CGAL_PROTECT_STDLIB_H
#ifndef CGAL_PROTECT_LIMITS_H
#include <limits.h>
#define CGAL_PROTECT_LIMITS_H
#endif // CGAL_PROTECT_LIMITS_H

// used for clock()
#ifndef CGAL_PROTECT_TIME_H
#include <time.h>
#define CGAL_PROTECT_TIME_H
#endif // CGAL_PROTECT_TIME_H


// SECTION: A Timer for User-Process Time
// ========================================================================
// 
// DEFINITION
// 
// A timer `t' of type CGAL_Timer is an object with a state. It is either
// running or it is stopped. The state is controlled with `t.start()'
// and `t.stop()'. The timer counts the time elapsed since its creation
// or last reset. It counts only the time where it is in the running
// state. The time information is given in seconds.

class CGAL_Timer {
private:
    clock_t  elapsed;
    clock_t  started;
    int      _intervals;
    bool     running;

public:
    CGAL_Timer() : elapsed(0), started(0), _intervals(0), running(false) {}

    void     start();
    void     stop ();
    void     reset();
    bool     is_running() const { return running; }

    double   time()       const;
    int      intervals()  const { return _intervals; }
    double   precision()  const { return 0.01; }
    double   max() const        { return 2146.0;}
};


/*****************************************************************************/

// Member functions CGAL_Timer
// ===========================

inline void
CGAL_Timer::start( )
{
    CGAL_assertion( ! running);
    started = clock();
    if (started == (clock_t)-1) {
        // possible on Solaris according to man-page
	cerr << "CGAL_Timer error: clock() returned -1." << endl;
	abort();
    }
    running = true;
    ++ _intervals;
}

inline void
CGAL_Timer::stop( )
{
    CGAL_assertion( running);
    elapsed += clock() - started;
    running  = false;
}

inline void
CGAL_Timer::reset( )
{
    _intervals = 0;
    elapsed = 0;
    if ( running) {
	started = clock();
	++ _intervals;
    }
}

inline double
CGAL_Timer::time() const {
    if ( running) {
	return double( elapsed  + clock() - started) / CLOCKS_PER_SEC;
    }
    return double(elapsed) / CLOCKS_PER_SEC;
}


#endif // CGAL_TIMER_H //
// EOF //
