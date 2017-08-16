 /**
  * The structures are defined for an parabolic PDE with the following restrictions:
  *  1. The parameter dimension p is equal to one (P1).
  *  2. The number of thetas is equal to two (T2).
  *  3. Theta is equal to mu (for implementing other relationships,please
  *     follow the structure of these implementation for a general usability)
  *     (Equal).
  *  4. The problem contains one load vector (F1) and one output (O1).
  *
  * The structures defined are:
  * 1. Theta --> parameter-dependent part of the PDE
  * 2. RBThetaExpansion
  */
///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBSTRUCTURESP1T2EQUALF1O1TRANSIENT_H
#define DWARFELEPHANTRBSTRUCTURESP1T2EQUALF1O1TRANSIENT_H

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/transient_rb_theta_expansion.h"
#include "libmesh/transient_rb_assembly_expansion.h"

#include "DwarfElephantRBStructuresA00ThetaIsConstantP1.h"
#include "DwarfElephantRBStructuresA0ThetaEqualMuP1.h"
#include "DwarfElephantRBStructuresA1ThetaEqualMuP1.h"


// Forward Declarations
namespace libMesh
{
 // class RBParameters;
 // class RBTheta;
  class RBTransientBThetaExpansion;
}

///----------------------------RBTHETAEXPANSION-----------------------------
/**
 * Attaches the stiffness matrix and the theta object to a structure of the
 * type RBThetatExpansion.
 *
 */

struct DwarfElephantRBP1T2EqualF1O1TransientExpansion : TransientRBThetaExpansion
{
  DwarfElephantRBP1T2EqualF1O1TransientExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_M_theta(&_rb_theta);

    attach_A_theta(&_theta_a_0);
    attach_A_theta(&_theta_a_1);

    attach_F_theta(&_rb_theta);

    attach_output_theta(&_rb_theta);

  }
  // Member Variables
  DwarfElephantThetaA0 _theta_a_0;
  DwarfElephantThetaA1 _theta_a_1;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBSTRUCTURESP1T2EQUALF1O1Transient_H