#ifndef _USRPARMS_H_
#define _USRPARMS_H_
/*
   ----------------------------------------------------------------
   File usrparms.h of ADOL-C version 1.8.6        as of Feb/14/2000
   ----------------------------------------------------------------

   usrparms.h contains the parameters which might affect 
   the performance of the ADOL-C system.  Intended to be tweeked by
   users and local maintainence personal.

   Last changes:
     20000214 olvo   The defininition of the macro USE_CALLOC
                     forces the ADOL-C allocation routines
                     to use 'calloc' instead of 'malloc'.
                     This may help in case of problems with
                     uninitialized memory as reported by Andreas
                     Waechter from CMU.
       981130 olvo   Fortran types
       981030 olvo   bufsize --> BUFSIZE & TBUFSIZE
       980723 olvo   new: DIAG_OUT as standard output  
                          FNAME3   as vs output 
   ---------------------------------------------------------------- 
*/

/****************************************************************************/
/* Buffer size for tapes                                                    */
#define BUFSIZE  524288   /* 16384, 65536 or  524288  */


/****************************************************************************/
/* Buffer size for temporary Taylor store                                   */
#define TBUFSIZE 524288    /* 16384, 65536 or  524288  */


/****************************************************************************/
/* ADOL-C data types                                                        */
#define locint      unsigned short   
#define revreal     double


/****************************************************************************/
/* Definionion of inf and NaN                                               */ 
#define inf_num     1.0  /* don't undefine these;  on non-IEEE machines */
#define inf_den     0.0  /* change the values to get small fractions    */
#define non_num     0.0  /* (inf_num/inf_den) and (non_num/non_den)     */
#define non_den     0.0  /* respectively, see the documentation         */


/****************************************************************************/
/* File names                                                               */
#define FNAME3       "_adol-vs_tape"
#define FNAME2       "_adol-rl_tape."
#define FNAME1       "_adol-in_tape."
#define FNAME        "_adol-op_tape."


/****************************************************************************/
/* Enable/disable DEBUG for hard debugging                                  */
/* #define DEBUG */ 


/****************************************************************************/
/* Enable/disable asinh, acosh,atanh, erf                                   */ 
/* #define ATRIG_ERF */     


/****************************************************************************/
/* Standard output used for diagnostics by ADOL-C,                          */
/* e.g. stdout or stderr or whatever file identifier                        */
#define DIAG_OUT stdout


/****************************************************************************/
/* Types used by Fortran callable versions of functions */
#define fint long 
#define fdouble double


/****************************************************************************/
/* Use 'calloc' instead of 'malloc' in ADOL-C allocation routines */
/* If you have any trouble with uninitialized memory then uncomment the
   macro definition! */
/* #define USE_CALLOC */
#define USE_CALLOC 


/****************************************************************************/
/* That's all                                                               */
#endif


