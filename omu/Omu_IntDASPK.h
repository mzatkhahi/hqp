/*
 * Omu_IntDASPK.h --
 *   -- integrate DAE over a stage using DASPK3.0
 *      (derived from earlier Omu_IntDASPKSO implementation)
 *
 * rf, 10/2/96
 */

/*
    Copyright (C) 1996--2000  Ruediger Franke and Hartmut Linke

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; 
    version 2 of the License.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library (file COPYING.LIB);
    if not, write to the Free Software Foundation, Inc.,
    59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef Omu_IntDASPK_H
#define Omu_IntDASPK_H

#include "Omu_Integrator.h"

/*
 * FORTRAN data types
 */

#ifdef fint
#undef fint
#endif
#define fint int

#ifdef freal
#undef freal
#endif
#define freal double

//--------------------------------------------------------------------------
class Omu_IntDASPK: public Omu_Integrator {

 public:

  Omu_IntDASPK();
  ~Omu_IntDASPK();

  char *name() {return "DASPK";}

  // override interface routine of Omu_Integrator
  void init_stage(int k,
		  const Omu_States &x, const Omu_Vector &u,
		  bool sa);
  void solve(int kk, double tstart, double tend,
	     const Omu_States &x, const Omu_Vector &u,
	     Omu_Program *sys, VECP xt,
	     MATP Sx, MATP Su);

  // routines called by DASPK
  void res(freal *t, freal *x, freal *xprime,
	   freal *delta, fint *ires, freal *rpar, fint *ipar,
	   freal *senpar);

  void jac(freal *t, freal *y, freal *yprime,
	   freal *pd, freal *cj, freal *rpar, fint *ipar,
	   freal *senpar, fint *ijac);

 private:

  void		realloc();
  void		init_options(const Omu_States &x);

  // backing store sys and current stage
  Omu_Program	*_sys;

  // variables for DASPK
  int		_mu;	// upper semi-bandwidth
  int		_ml;	// lower semi-bandwidth
  int    	_lwp;
  int     	_liwp;
  int    	_lwp_basic;

  VECP		_y;
  VECP		_yprime;
  IVECP		_info;
  VECP		_rwork;
  IVECP		_iwork;
  VECP		_rpar;
  IVECP		_ipar;
  VECP		_senpar;

  /**
   * User given semi-bandwidth of Jacobian (default: -1).
   * If a value >= 0 is specified, then it is used instead
   * of the automatic detection.
   */
  int		_jac_sbw;

  /**
   * User specification to allow banded solver (default: true).
   * Banded solvers are used if _banded is true, _jac_sbw < 0,
   * and if the automatic detection indicates that the problem
   * can be solved more efficiently in this way.
   */
  bool		_banded;
  bool		_banded_solver;	// use banded solver or preconditioner

  /**
   * User specification if Krylov iterative solver should be used
   * instead of direct solver (default: false).
   */
  bool		_krylov;

  /**
   * User specification if a preconditioner should be used
   * by the Krylov iterative solver (default: true).
   * A banded preconditioner is used if the problem is treated banded.
   * Otherwise an incomplete LU factorization is used.
   */
  bool		_krylov_prec;

  /**
   * User defined fixed number of steps.
   * (default: 0, i.e. variable step size based on _rtol and _atol)
   */
  int		_nsteps;

  // vectors and matrices for low level _sys->continuous callback
  VECP		_cx;
  VECP		_cu;
  VECP		_cxp;
  VECP		_cF;
  MATP		_cFx;
  MATP		_cFu;
  MATP		_cFxp;
  // seed derivatives for calculating sensitivity equations
  MATP		_Xx;
  MATP		_Xu;
  MATP		_Xxp;
  MATP		_Xup;
  MATP		_Yx;
  MATP		_Yu;
};  

#endif
