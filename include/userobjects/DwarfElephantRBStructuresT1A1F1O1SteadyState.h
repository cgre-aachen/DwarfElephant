/**
 * The structures are defined for an parabolic PDE with the following restrictions:.
 *  1. The number of thetas is equal to one (T1) and the number of Aq to one (A1).
 *  2. The problem contains one Fq (F1) and one output (O1).
 *
 * The structures defined are:
 * 1. Theta --> parameter-dependent part of the PDE
 * 2. RBThetaExpansion
 */

///-------------------------------------------------------------------------
#pragma once

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"

#include "DwarfElephantRBStructuresThetaConstant.h"
#include "DwarfElephantRBStructuresThetaEqualMu0.h"


// Forward Declarations
namespace libMesh
{
  class RBThetaExpansion;
}

struct DwarfElephantRBT1A1F1O1SteadyStateExpansion : RBThetaExpansion
{
  DwarfElephantRBT1A1F1O1SteadyStateExpansion()
  {
    attach_A_theta(&_theta_a_0);

    attach_F_theta(&_rb_theta);

    attach_output_theta(&_rb_theta);

  }
  // Member Variables
  DwarfElephantThetaEqualMu0 _theta_a_0;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};
