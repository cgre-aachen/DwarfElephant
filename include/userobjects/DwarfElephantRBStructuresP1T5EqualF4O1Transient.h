 /**
  * The structures are defined for an parabolic PDE with the following restrictions:
  *  1. The parameter dimension p is equal to one (P1).
  *  2. The number of thetas is equal to five (T5).
  *  3. Theta is equal to mu (for implementing other relationships,please
  *     follow the structure of these implementation for a general usability)
  *     (Equal).
  *  4. The problem contains three load vector (F3) and one output (O1).
  *
  * The structures defined are:
  * 1. Theta --> parameter-dependent part of the PDE
  * 2. RBThetaExpansion
  */
///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBSTRUCTURESP1T5EQUALF4O1TRANSIENT_H
#define DWARFELEPHANTRBSTRUCTURESP1T5EQUALF4O1TRANSIENT_H

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/transient_rb_theta_expansion.h"
#include "libmesh/transient_rb_assembly_expansion.h"

#include "DwarfElephantRBStructuresA00ThetaIsConstantP1.h"
#include "DwarfElephantRBStructuresA0ThetaEqualMuP1.h"
#include "DwarfElephantRBStructuresA0ThetaNormMu0P1.h"
#include "DwarfElephantRBStructuresA0ThetaNormMu1P1.h"
#include "DwarfElephantRBStructuresA0ThetaNormMu3P1.h"
#include "DwarfElephantRBStructuresA1ThetaEqualMuP1.h"
#include "DwarfElephantRBStructuresA1ThetaNormMu0P1.h"
#include "DwarfElephantRBStructuresA1ThetaNormMu1P1.h"
#include "DwarfElephantRBStructuresA1ThetaNormMu3P1.h"
#include "DwarfElephantRBStructuresA2ThetaEqualMuP1.h"
#include "DwarfElephantRBStructuresA2ThetaNormMu0P1.h"
#include "DwarfElephantRBStructuresA2ThetaNormMu1P1.h"
#include "DwarfElephantRBStructuresA2ThetaNormMu3P1.h"
#include "DwarfElephantRBStructuresA3ThetaEqualMuP1.h"
#include "DwarfElephantRBStructuresA3ThetaNormMu0P1.h"
#include "DwarfElephantRBStructuresA3ThetaNormMu1P1.h"
#include "DwarfElephantRBStructuresA3ThetaNormMu3P1.h"
#include "DwarfElephantRBStructuresA4ThetaEqualMuP1.h"
#include "DwarfElephantRBStructuresA4ThetaNormMu0P1.h"
#include "DwarfElephantRBStructuresA4ThetaNormMu1P1.h"
#include "DwarfElephantRBStructuresA4ThetaNormMu3P1.h"


// Forward Declarations
namespace libMesh
{
  class RBTransientBThetaExpansion;
}

///----------------------------RBTHETAEXPANSION-----------------------------
/**
 * Attaches the stiffness matrix and the theta object to a structure of the
 * type RBThetatExpansion.
 *
 */

struct DwarfElephantRBP1T5EqualF4O1TransientExpansion : TransientRBThetaExpansion
{
  DwarfElephantRBP1T5EqualF4O1TransientExpansion()
  {
        // Setting up the RBThetaExpansion object
    attach_M_theta(&_theta_a_00);
    attach_M_theta(&_rb_theta);

    attach_A_theta(&_theta_a_0);
    attach_A_theta(&_theta_a_1);
    attach_A_theta(&_theta_a_2);
    attach_A_theta(&_theta_a_3);
    attach_A_theta(&_theta_a_4);

    attach_F_theta(&_theta_a_0);
    attach_F_theta(&_theta_a_1);
    attach_F_theta(&_theta_a_2);
    attach_F_theta(&_rb_theta);

    attach_output_theta(&_rb_theta);

  }
  // Member Variables
  DwarfElephantThetaA00Constant _theta_a_00;
  DwarfElephantThetaA0NormMu3 _theta_a_0;
  DwarfElephantThetaA1NormMu3 _theta_a_1;
  DwarfElephantThetaA2NormMu3 _theta_a_2;
  DwarfElephantThetaA3NormMu3 _theta_a_3;
  DwarfElephantThetaA4NormMu3 _theta_a_4;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBSTRUCTURESP1T5EQUALF4O1Transient_H
