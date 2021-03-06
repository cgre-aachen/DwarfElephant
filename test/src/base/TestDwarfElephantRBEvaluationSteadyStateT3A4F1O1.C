/**
 * In this class subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * NOTE: ENSURE THAT THE CLASS IS USING THE CORRECT RBSTRUCTURES.
 */

 //-------------------------------------------------------------------------
 #include "TestDwarfElephantRBEvaluationSteadyStateT3A4F1O1.h"

TestDwarfElephantRBEvaluationSteadyStateT3A4F1O1::TestDwarfElephantRBEvaluationSteadyStateT3A4F1O1(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem):
    DwarfElephantRBEvaluationSteadyState(comm, fe_problem),
    fe_problem(fe_problem)
{
  set_rb_theta_expansion(_rb_theta_expansion);
}
