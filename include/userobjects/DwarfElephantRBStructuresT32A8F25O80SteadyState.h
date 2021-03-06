/*
 * The structures are defined for an parabolic PDE with the following restrictions:.
 *  1. The number of thetas is equal to 32 (T32) and the number of Aq to eight (A8).
 *  2. The problem contains 25 Fq (F25) and 80 outputs (O80).
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

#include "DwarfElephantRBStructuresThetaEqualMu0.h"
#include "DwarfElephantRBStructuresThetaEqualMu1.h"
#include "DwarfElephantRBStructuresThetaEqualMu2.h"
#include "DwarfElephantRBStructuresThetaEqualMu3.h"
#include "DwarfElephantRBStructuresThetaEqualMu4.h"
#include "DwarfElephantRBStructuresThetaEqualMu5.h"
#include "DwarfElephantRBStructuresThetaEqualMu6.h"
#include "DwarfElephantRBStructuresThetaEqualMu7.h"
#include "DwarfElephantRBStructuresThetaEqualMu8.h"
#include "DwarfElephantRBStructuresThetaEqualMu0TimesMu8.h"
#include "DwarfElephantRBStructuresThetaEqualMu1TimesMu8.h"
#include "DwarfElephantRBStructuresThetaEqualMu2TimesMu8.h"
#include "DwarfElephantRBStructuresThetaEqualMu3TimesMu8.h"
#include "DwarfElephantRBStructuresThetaEqualMu4TimesMu8.h"
#include "DwarfElephantRBStructuresThetaEqualMu5TimesMu8.h"
#include "DwarfElephantRBStructuresThetaEqualMu6TimesMu8.h"
#include "DwarfElephantRBStructuresThetaEqualMu7TimesMu8.h"
#include "DwarfElephantRBStructuresThetaEqualMu0TimesMu9.h"
#include "DwarfElephantRBStructuresThetaEqualMu1TimesMu9.h"
#include "DwarfElephantRBStructuresThetaEqualMu2TimesMu9.h"
#include "DwarfElephantRBStructuresThetaEqualMu3TimesMu9.h"
#include "DwarfElephantRBStructuresThetaEqualMu4TimesMu9.h"
#include "DwarfElephantRBStructuresThetaEqualMu5TimesMu9.h"
#include "DwarfElephantRBStructuresThetaEqualMu6TimesMu9.h"
#include "DwarfElephantRBStructuresThetaEqualMu7TimesMu9.h"
#include "DwarfElephantRBStructuresThetaEqualMu0TimesMu10.h"
#include "DwarfElephantRBStructuresThetaEqualMu1TimesMu10.h"
#include "DwarfElephantRBStructuresThetaEqualMu2TimesMu10.h"
#include "DwarfElephantRBStructuresThetaEqualMu3TimesMu10.h"
#include "DwarfElephantRBStructuresThetaEqualMu4TimesMu10.h"
#include "DwarfElephantRBStructuresThetaEqualMu5TimesMu10.h"
#include "DwarfElephantRBStructuresThetaEqualMu6TimesMu10.h"
#include "DwarfElephantRBStructuresThetaEqualMu7TimesMu10.h"


// Forward Declarations
namespace libMesh
{
  class RBThetaExpansion;
}

struct DwarfElephantRBT32A8F25O80SteadyStateExpansion : RBThetaExpansion
{
  DwarfElephantRBT32A8F25O80SteadyStateExpansion()
  {
    // Setting up the RBThetaExpansion object
    attach_A_theta(&_theta_a_0);
    attach_A_theta(&_theta_a_1);
    attach_A_theta(&_theta_a_2);
    attach_A_theta(&_theta_a_3);
    attach_A_theta(&_theta_a_4);
    attach_A_theta(&_theta_a_5);
    attach_A_theta(&_theta_a_6);
    attach_A_theta(&_theta_a_7);

    attach_F_theta(&_rb_theta);
    attach_F_theta(&_theta_f_0);
    attach_F_theta(&_theta_f_1);
    attach_F_theta(&_theta_f_2);
    attach_F_theta(&_theta_f_3);
    attach_F_theta(&_theta_f_4);
    attach_F_theta(&_theta_f_5);
    attach_F_theta(&_theta_f_6);
    attach_F_theta(&_theta_f_7);
    attach_F_theta(&_theta_f_8);
    attach_F_theta(&_theta_f_9);
    attach_F_theta(&_theta_f_10);
    attach_F_theta(&_theta_f_11);
    attach_F_theta(&_theta_f_12);
    attach_F_theta(&_theta_f_13);
    attach_F_theta(&_theta_f_14);
    attach_F_theta(&_theta_f_15);
    attach_F_theta(&_theta_f_16);
    attach_F_theta(&_theta_f_17);
    attach_F_theta(&_theta_f_18);
    attach_F_theta(&_theta_f_19);
    attach_F_theta(&_theta_f_20);
    attach_F_theta(&_theta_f_21);
    attach_F_theta(&_theta_f_22);
    attach_F_theta(&_theta_f_23);

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
  DwarfElephantThetaEqualMu0 _theta_a_0;
  DwarfElephantThetaEqualMu1 _theta_a_1;
  DwarfElephantThetaEqualMu2 _theta_a_2;
  DwarfElephantThetaEqualMu3 _theta_a_3;
  DwarfElephantThetaEqualMu4 _theta_a_4;
  DwarfElephantThetaEqualMu5 _theta_a_5;
  DwarfElephantThetaEqualMu6 _theta_a_6;
  DwarfElephantThetaEqualMu7 _theta_a_7;
  DwarfElephantThetaEqualMu0TimesMu8 _theta_f_0;
  DwarfElephantThetaEqualMu1TimesMu8 _theta_f_1;
  DwarfElephantThetaEqualMu2TimesMu8 _theta_f_2;
  DwarfElephantThetaEqualMu3TimesMu8 _theta_f_3;
  DwarfElephantThetaEqualMu4TimesMu8 _theta_f_4;
  DwarfElephantThetaEqualMu5TimesMu8 _theta_f_5;
  DwarfElephantThetaEqualMu6TimesMu8 _theta_f_6;
  DwarfElephantThetaEqualMu7TimesMu8 _theta_f_7;
  DwarfElephantThetaEqualMu0TimesMu9 _theta_f_8;
  DwarfElephantThetaEqualMu1TimesMu9 _theta_f_9;
  DwarfElephantThetaEqualMu2TimesMu9 _theta_f_10;
  DwarfElephantThetaEqualMu3TimesMu9 _theta_f_11;
  DwarfElephantThetaEqualMu4TimesMu9 _theta_f_12;
  DwarfElephantThetaEqualMu5TimesMu9 _theta_f_13;
  DwarfElephantThetaEqualMu6TimesMu9 _theta_f_14;
  DwarfElephantThetaEqualMu7TimesMu9 _theta_f_15;
  DwarfElephantThetaEqualMu0TimesMu10 _theta_f_16;
  DwarfElephantThetaEqualMu1TimesMu10 _theta_f_17;
  DwarfElephantThetaEqualMu2TimesMu10 _theta_f_18;
  DwarfElephantThetaEqualMu3TimesMu10 _theta_f_19;
  DwarfElephantThetaEqualMu4TimesMu10 _theta_f_20;
  DwarfElephantThetaEqualMu5TimesMu10 _theta_f_21;
  DwarfElephantThetaEqualMu6TimesMu10 _theta_f_22;
  DwarfElephantThetaEqualMu7TimesMu10 _theta_f_23;
  RBTheta _rb_theta;         // Default RBTheta object, simply returns one.
};
