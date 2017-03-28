///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTINITIALIZERBSYSTEM_H
#define DWARFELEPHANTINITIALIZERBSYSTEM_H

///---------------------------------INCLUDES--------------------------------
//libMesh includes
#include "libmesh/equation_systems.h"
#include "libmesh/sparse_matrix.h"
#include "libmesh/petsc_matrix.h"
#include "libmesh/petsc_vector.h"
#include "libmesh/getpot.h"

// MOOSE includes
#include "GeneralUserObject.h"
#include "DisplacedProblem.h"
#include "MooseMesh.h"

// MOOSE includes (DwarfElephant package)
#include "DwarfElephantRBClasses.h"


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
class DwarfElephantRBConstruction;
class DwarfElephantInitializeRBSystem;

template<>
InputParameters validParams<DwarfElephantInitializeRBSystem>();

class DwarfElephantInitializeRBSystem :
  public GeneralUserObject
{
  public:
    DwarfElephantInitializeRBSystem(const InputParameters & params);

    void initializeOfflineStage();
    void cacheStiffnessMatrixContribution(numeric_index_type i, numeric_index_type j, Real value);

    virtual void initialize() override;
    virtual void execute() override;
    virtual void finalize() override;

  protected:
    bool _use_displaced;
    bool _skip_matrix_assembly_in_rb_system;
    bool _skip_vector_assembly_in_rb_system;
    bool _offline_stage;
    bool _compliant;

    unsigned int _qa;
    unsigned int _qf;
    unsigned int _ql;

    std::string _parameters_filename;

    EquationSystems & _es;
    MooseMesh * _mesh_ptr;
    DwarfElephantRBConstruction * _rb_con_ptr;

    SparseMatrix <Number> * _inner_product_matrix;
    std::vector<SparseMatrix <Number> *> _jacobian_subdomain;
    std::vector<NumericVector <Number> *> _residuals;
    std::vector<NumericVector <Number> *> _outputs;

    std::vector <numeric_index_type> _cached_jacobian_subdomain_contribution_rows;
    std::vector <numeric_index_type> _cached_jacobian_subdomain_contribution_cols;
    std::vector <Real> _cached_jacobian_subdomain_contribution_vals;

    const std::vector<ExecFlagType> & _exec_flags;

    MooseVariable * _variable;
//    Variable * _variable_lib;

    AuxVariableName _variable_name;
//    std::string _variable_name_lib;

    friend class RBKernel;
    friend class RBNodalBC;
    friend class DwarfElephantOfflineStage;
    friend class DwarfElephantOnlineStage;
};
///-------------------------------------------------------------------------
#endif // DWARFELEPHANTINITIALIZERBSYSTEM_H
