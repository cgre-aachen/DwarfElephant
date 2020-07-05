/* This UserObject is required to initialitze the RB system structure
 * and transfer for the steady state case.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTINITIALIZERBSYSTEMSTEADYSTATE_H
#define DWARFELEPHANTINITIALIZERBSYSTEMSTEADYSTATE_H

///---------------------------------INCLUDES--------------------------------
//libMesh includes
#include "libmesh/equation_systems.h"
#include "libmesh/sparse_matrix.h"
#include "libmesh/petsc_matrix.h"
#include "libmesh/petsc_vector.h"

// MOOSE includes
#include "GeneralUserObject.h"
#include "DisplacedProblem.h"
#include "MooseMesh.h"
#include "MooseVariable.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantSystem.h"
#include "DwarfElephantRBClassesSteadyState.h"

///-------------------------------------------------------------------------
// Forward Declarations
namespace libMesh
{
  class EquationSystems;
  template <typename T> class SparseMatrix;
  template <typename T> class PetscMatrix;
  template <typename T> class PetscVector;
}

class MooseMesh;
class DwarfElephantSystem;
class DwarfElephantRBConstructionSteadyState;
class DwarfElephantRBEvaluationSteadyState;
class DwarfElephantInitializeRBSystemSteadyState;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantInitializeRBSystemSteadyState>();

///This UserObject is required to initialitze the RB system structure and transfer for the steady state case.
class DwarfElephantInitializeRBSystemSteadyState :
  public GeneralUserObject
{

//----------------------------------PUBLIC----------------------------------
  public:
    DwarfElephantInitializeRBSystemSteadyState(const InputParameters & params);

    /* Methods */

    // Initializes all required matrices and vectors for the RB solve.
    void initializeOfflineStage();

    void processParameters();

    // Initializes the RB System.
    virtual void initialize() override;

    // Method not used in this UserObject.
    virtual void execute() override;

    // Method not used in this UserObject.
    virtual void finalize() override;

    std::vector<std::vector<NumericVector <Number> *> > getOutputs() const {return _outputs;}

    DwarfElephantRBConstructionSteadyState * get_rb_con_ptr() const {return _rb_con_ptr;}

    unsigned int getQa() const {return _qa;}
    unsigned int getQf() const {return _qf;}
    std::vector<unsigned int> getQl() const {return _ql;}
    SparseMatrix <Number> * getInnerProductMatrix() const {return _inner_product_matrix;}
    std::vector<SparseMatrix <Number> *> getJacobianSubdomain() const {return _jacobian_subdomain;}
    std::vector<NumericVector <Number> *> getResiduals() const {return _residuals;}
    bool getOfflineStage() const {return _offline_stage;}

//--------------------------------PROTECTED---------------------------------
  protected:

    /* Attributes */
    bool _use_displaced;
    bool _offline_stage;

    unsigned int _n_outputs;
    unsigned int _qa;
    unsigned int _qf;
    std::vector<unsigned int> _ql;

    std::vector<Real> _continuous_parameter_min_values;
    std::vector<Real> _continuous_parameter_max_values;
    std::vector<Real> _discrete_parameter_values_in;

    std::string _system_name;
//    std::string _parameters_filename;     //only required if one wants to read the data over the GetPot class from libMesh directly
    std::vector<std::string> _continuous_parameters;
    std::vector<std::string> _discrete_parameters;
    std::map< std::string, std::vector<Real> > _discrete_parameter_values;

    EquationSystems & _es;
    MooseMesh * _mesh_ptr;
    TransientNonlinearImplicitSystem * _sys;
    DwarfElephantRBConstructionSteadyState * _rb_con_ptr;

    SparseMatrix <Number> * _inner_product_matrix;
    std::vector<SparseMatrix <Number> *> _jacobian_subdomain;
    std::vector<NumericVector <Number> *> _residuals;
    std::vector<std::vector<NumericVector <Number> *> > _outputs;
};
///-------------------------------------------------------------------------
#endif // DWARFELEPHANTINITIALIZERBSYSTEMSTEADYSTATE_H
