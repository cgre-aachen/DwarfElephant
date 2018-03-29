///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBSTRUCTURESA1THETANORMMU1P1_H
#define DWARFELEPHANTRBSTRUCTURESA1THETANORMMU1P1_H

///---------------------------------INCLUDES--------------------------------
// libMesh includes (RB package)
#include "libmesh/rb_theta.h"
#include "libmesh/rb_assembly_expansion.h"


// Forward Declarations
namespace libMesh
{
  class RBParameters;
  class RBTheta;
}

///-----------------------------------THETA---------------------------------
/**
 * Please take the name convention of this package for the mu object into
 * account to ensure a gernal useability of your class.
 */

struct DwarfElephantThetaA1NormMu1 : RBTheta
{
  virtual Number evaluate (const RBParameters & _mu)
  {
    return _mu.get_value("mu_1")/_mu.get_value("mu_1");
  }
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBSTRUCTURESA1THETANORMMU1P1_H
