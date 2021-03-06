/**
 * The structures are defined for an parabolic PDE with the following restrictions:.
 *  1. The number of thetas is equal to two (T2) and the number of Aq to two (A2).
 *  2. The problem contains three Fq (F3) and ten outputs (O10).
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
#include "DwarfElephantRBStructuresThetaEqualMu1.h"
#include "DwarfElephantRBStructuresThetaEqualMu2.h"
#include "DwarfElephantRBStructuresThetaEqualMu3.h"


// Forward Declarations
namespace libMesh
{
  class RBThetaExpansion;
}

struct DwarfElephantRBT2A2F3O10SteadyStateExpansion : RBThetaExpansion
{
  DwarfElephantRBT2A2F3O10SteadyStateExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_A_theta(&_rb_theta);
    attach_A_theta(&_theta_a_0);

    attach_F_theta(&_rb_theta);
    attach_F_theta(&_theta_a_0);
    attach_F_theta(&_theta_a_1);

    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
    attach_output_theta(&_rb_theta);
  }
  // Member Variables
  DwarfElephantThetaConstant _theta_a_00;
  DwarfElephantThetaEqualMu0 _theta_a_0;
  DwarfElephantThetaEqualMu1 _theta_a_1;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};
