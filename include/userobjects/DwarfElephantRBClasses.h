/**
 * In this class simplified subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * DwarfElephantRBEvaluation: requires only the definition of the lower
 * coercivity constant. The value is here specified for a Conduction
 * problem.
 *
 * DwarfElephantRBConstruction: In order to construct the RB System with the
 * RBSimpleEvaluation subclass the method build_rb_evaluation needs to be
 * overriden.
 *
 * NOTE: ENSURE THAT THE CLASS IS INHERITING FROM THE CORRECT RBSTRUCTURES.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBCLASSES_H
#define DWARFELEPHANTRBCLASSES_H

///---------------------------------INCLUDES--------------------------------

//libMesh includes (RB package)
#include "libmesh/rb_evaluation.h"
#include "libmesh/rb_construction.h"

//MOOSE includes (DwarfElephant package)
#include "RBStructuresP1Theta3ThetaEqualMu.h"

// Forward Declarations
namespace libMesh
{
  class EquationSystems;
  class RBConstruction;
  class RBEvaluation;
}

///---------------------------RBSIMPLEEVALUATION----------------------------
class DwarfElephantRBEvaluation : public RBEvaluation
{

//---------------------------------PUBLIC-----------------------------------
public:
  DwarfElephantRBEvaluation(const libMesh::Parallel::Communicator & comm):
    RBEvaluation(comm)
  {
    set_rb_theta_expansion(_rb_theta_expansion);
  }

  virtual Real get_stability_lower_bound()
  {
//    const RBParameters & mu = get_parameters();
////    set_parameters(mu);
//    libMesh::out << mu.get_value("mu_0") << std::endl;
//    return mu.get_value("mu_0");
    return 1.0;
  }

  RBP1Theta3ThetaEqualMuExpansion _rb_theta_expansion;
};

///--------------------------RBSIMPLECONSTRUCTION---------------------------
class DwarfElephantRBConstruction : public RBConstruction
{

//---------------------------------PUBLIC-----------------------------------
public:

  // Constructor
  DwarfElephantRBConstruction (EquationSystems & es,
                        const std::string & name_in,
                        const unsigned int number_in)
    : Parent(es, name_in, number_in)
  {}

  // Destructor
  virtual ~DwarfElephantRBConstruction () { }

  // Type of the system
  typedef DwarfElephantRBConstruction _sys_type;

  // Type of the parent
  typedef RBConstruction Parent;

  // Initialize data structure

 virtual void init_data()
  {
    u_var = this->add_variable ("u", libMesh::FIRST);

    Parent::init_data();
  }

  unsigned int u_var;

  friend class DwarfElephantOfflineStage;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBCLASSES_H
