/*
 * Omu_Integrator.h --
 *   -- abstract base class
 *   -- integrate system equations over a discrete stage
 *
 * rf, 10/2/96
 * E. Arnold 2000-03-29 _rtol, _atol
 */

/*
    Copyright (C) 1997--2000  Ruediger Franke

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

#ifndef Omu_Integrator_H
#define Omu_Integrator_H

#include <If_Float.h>
#include <If_List.h>
#include <If_Class.h>

#include "Omu_Program.h"
#include "Omu_Vars.h"

IF_BASE_DECLARE(Omu_Integrator);

//--------------------------------------------------------------------------
class Omu_Integrator {

 public:

  Omu_Integrator();
  virtual ~Omu_Integrator();

  virtual void init_stage(int k,
			  const Omu_States &x, const Omu_Vector &u,
			  bool sa = false);
  virtual void init_sample(int kk, double tstart, double tend);
  virtual void solve(int kk, double tstart, double tend,
		     const Omu_States &x, const Omu_Vector &u,
		     Omu_Program *sys, VECP xt,
		     MATP Sx = MNULL, MATP Su = MNULL) = 0;

  virtual char *name() = 0;

 protected:

  int		_kk;
  int		_nxt;	// number of continuous-time variables
  int		_nd;	// number of discrete-time states
  int		_nv;	// number of expansion variables
  int		_nx;	// number of states treated by optimizer (nx=nxt-nv)
  int		_nu;	// number of control parameters
  bool		_sa;

  /**
   * Boolean to indicate if sensitivities should be considered
   * in error test (default: false).
   */
  bool		_serr;

  /**
   * Number of continuous states during integration (nxt-nd),
   * i.e. total number minus discrete states.
   */
  int		_n;

  /**
   * Number of parameters during integration (nd+nu),
   * i.e. discrete-time states and controls
   */
  int		_m;

  If_List	_ifList;

  /**
   * Constant stepsize to be taken by integator.
   * For stepsize>0, an integrator takes ceil((tend-tstart)/stepsize)
   * equidistant steps in the sampling interval [tstart,tend].
   * Default: 0.0, i.e. integrator chooses own stepsize.
   */
  double	_stepsize;

  /**
   * Relative integration error (only for variable stepsize).
   */
  double        _rtol;

  /**
   * Absolute integration error (only for variable stepsize).
   */
  double        _atol;

  int		_res_evals;	// number of residual evaluations
  int		_sen_evals;	// number of sensitivity evaluations
  int		_jac_evals;	// number of Jacobian evaluations
};  

#endif
