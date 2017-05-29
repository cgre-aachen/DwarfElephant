/**
 * In this class subclasses of the RBEvaluation and
 * RBConstruction class are introduced.
 *
 * DwarfElephantRBEvaluation: requires only the definition of the lower
 * coercivity constant. The value is here specified for a three layer
 * problem.
 *
 * DwarfElephantRBConstruction: In order to construct the RB System with the
 * DwarfElephantRBEvaluation subclass the method build_rb_evaluation needs to be
 * overriden.
 *
 * NOTE: ENSURE THAT THE CLASS IS INHERITING FROM THE CORRECT RBSTRUCTURES.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTRBCLASSESSTEADYSTATE_H
#define DWARFELEPHANTRBCLASSESSTEADYSTATE_H

///---------------------------------INCLUDES--------------------------------
//#if defined(LIBMESH_HAVE_SLEPC) && defined(LIBMESH_HAVE_GLPK)

// libMesh includes
#include "libmesh/sparse_matrix.h"
#include "libmesh/petsc_matrix.h"

// libMesh includes (RB package)
#include "libmesh/rb_evaluation.h"
#include "libmesh/rb_construction.h"
#include "libmesh/rb_scm_construction.h"
#include "libmesh/rb_scm_evaluation.h"

///-------------------------------------------------------------------------
// MOOSE includes (DwarfElephant package)
#include "CacheBoundaries.h"
#include "RBStructuresP1Theta3ThetaEqualMuSteadyState.h"
#include "RBStructuresP1Theta5ThetaEqualMuSteadyState.h"

#include "FEProblemBase.h"
#include "DwarfElephantInitializeRBSystem.h"

// Forward Declarations
namespace libMesh
{
  template <typename T> class SparseMatrix;
  template <typename T> class PetscMatrix;

  class EquationSystems;
  class RBConstruction;
  class RBEvaluation;
}

//using libMesh::RBSCMConstruction;
//using libMesh::RBSCMEvaluation;

class DwarfElephantInitializeRBSystem;

///-----------------------DWARFELEPHANTRBCONSTRUCTION-----------------------
class DwarfElephantRBConstructionSteadyState : public RBConstruction
{

//---------------------------------PUBLIC-----------------------------------
public:

  // Constructor
  DwarfElephantRBConstructionSteadyState (EquationSystems & es,
                        const std::string & name_in,
                        const unsigned int number_in)
    : Parent(es, name_in, number_in)
  {}

  // Destructor
  virtual ~DwarfElephantRBConstructionSteadyState () { }

  // Type of the system
  typedef DwarfElephantRBConstructionSteadyState _sys_type;

  // Type of the parent
  typedef RBConstruction Parent;

  // Initialize data structure
  virtual void init_data()
  {
    u_var = this->add_variable ("u", libMesh::FIRST);

    Parent::init_data();
  }
//
//  void update_residual_terms(bool compute_inner_products)
//{
//  LOG_SCOPE("update_residual_terms()", "RBConstruction");
//
//  unsigned int RB_size = get_rb_evaluation().get_n_basis_functions();
//
//  for(unsigned int q_a=0; q_a<get_rb_theta_expansion().get_n_A_terms(); q_a++)
//    {
//      for(unsigned int i=(RB_size-delta_N); i<RB_size; i++)
//        {
//          // Initialize the vector in which we'll store the representor
//          if(!get_rb_evaluation().Aq_representor[q_a][i])
//            {
//              get_rb_evaluation().Aq_representor[q_a][i] = (NumericVector<Number>::build(this->comm()).release());
//              get_rb_evaluation().Aq_representor[q_a][i]->init(this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
//            }
//
//          libmesh_assert(get_rb_evaluation().Aq_representor[q_a][i]->size()       == this->n_dofs()       &&
//                         get_rb_evaluation().Aq_representor[q_a][i]->local_size() == this->n_local_dofs() );
//
//          rhs->zero();
//          get_Aq(q_a)->vector_mult(*rhs, get_rb_evaluation().get_basis_function(i));
//          rhs->scale(-1.);
//
////          if (!is_quiet())
////            {
////              libMesh::out << "Starting solve [q_a][i]=[" << q_a <<"]["<< i << "] in RBConstruction::update_residual_terms() at "
////                           << Utility::get_timestamp() << std::endl;
////            }
//
//          solve_for_matrix_and_rhs(*inner_product_solver, *inner_product_matrix, *rhs);
//
//          if (assert_convergence)
//            check_convergence(*inner_product_solver);
////
//          if (!is_quiet())
//            {
////              libMesh::out << "Finished solve [q_a][i]=[" << q_a <<"]["<< i << "] in RBConstruction::update_residual_terms() at "
////                           << Utility::get_timestamp() << std::endl;
//              libMesh::out << this->n_linear_iterations() << " iterations, final residual "
//                           << this->final_linear_residual() << std::endl;
//            }
//
//          // Store the representor
//          *get_rb_evaluation().Aq_representor[q_a][i] = *solution;
//        }
//    }
//
//  // Now compute and store the inner products (if requested)
//  if (compute_inner_products)
//    {
//
//      for(unsigned int q_f=0; q_f<get_rb_theta_expansion().get_n_F_terms(); q_f++)
//        {
//          inner_product_matrix->vector_mult(*inner_product_storage_vector,*Fq_representor[q_f]);
//
//          for(unsigned int q_a=0; q_a<get_rb_theta_expansion().get_n_A_terms(); q_a++)
//            {
//              for(unsigned int i=(RB_size-delta_N); i<RB_size; i++)
//                {
//                  get_rb_evaluation().Fq_Aq_representor_innerprods[q_f][q_a][i] =
//                    inner_product_storage_vector->dot(*get_rb_evaluation().Aq_representor[q_a][i]);
//                }
//            }
//        }
//
//      unsigned int q=0;
//      for(unsigned int q_a1=0; q_a1<get_rb_theta_expansion().get_n_A_terms(); q_a1++)
//        {
//          for(unsigned int q_a2=q_a1; q_a2<get_rb_theta_expansion().get_n_A_terms(); q_a2++)
//            {
//              for(unsigned int i=(RB_size-delta_N); i<RB_size; i++)
//                {
//                  for(unsigned int j=0; j<RB_size; j++)
//                    {
//                      inner_product_matrix->vector_mult(*inner_product_storage_vector, *get_rb_evaluation().Aq_representor[q_a2][j]);
//                      get_rb_evaluation().Aq_Aq_representor_innerprods[q][i][j] =
//                        inner_product_storage_vector->dot(*get_rb_evaluation().Aq_representor[q_a1][i]);
//
//                      if(i != j)
//                        {
//                          inner_product_matrix->vector_mult(*inner_product_storage_vector, *get_rb_evaluation().Aq_representor[q_a2][i]);
//                          get_rb_evaluation().Aq_Aq_representor_innerprods[q][j][i] =
//                            inner_product_storage_vector->dot(*get_rb_evaluation().Aq_representor[q_a1][j]);
//                        }
//                    }
//                }
//              q++;
//            }
//        }
//    } // end if (compute_inner_products)
//}
//
//  void enrich_RB_space()
//{
//  LOG_SCOPE("enrich_RB_space()", "RBConstruction");
//
//  NumericVector<Number> * new_bf = NumericVector<Number>::build(this->comm()).release();
//  new_bf->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
//  *new_bf = *solution;
//
//  for(unsigned int index=0; index<get_rb_evaluation().get_n_basis_functions(); index++)
//    {
//      inner_product_matrix->vector_mult(*inner_product_storage_vector, *new_bf);
//
//      Number scalar =
//        inner_product_storage_vector->dot(get_rb_evaluation().get_basis_function(index));
//      new_bf->add(-scalar, get_rb_evaluation().get_basis_function(index));
//    }
//
//  // Normalize new_bf
//  inner_product_matrix->vector_mult(*inner_product_storage_vector, *new_bf);
//  Number new_bf_norm = std::sqrt( inner_product_storage_vector->dot(*new_bf) );
//
//  libMesh::out << "Norm bf: " << new_bf_norm << std::endl;
//
//  if(new_bf_norm == 0.)
//    {
//      new_bf->zero(); // avoid potential nan's
//    }
//  else
//    {
//      new_bf->scale(1./new_bf_norm);
//    }
//
//  // load the new basis function into the basis_functions vector.
//  get_rb_evaluation().basis_functions.push_back( new_bf );
//}

//  Real train_reduced_basis(const bool resize_rb_eval_data=true)
//{
//  LOG_SCOPE("train_reduced_basis()", "RBConstruction");
//
//  int count = 0;
//
//  // initialize rb_eval's parameters
//  get_rb_evaluation().initialize_parameters(*this);
//
//  // possibly resize data structures according to Nmax
//  if(resize_rb_eval_data)
//    {
//      get_rb_evaluation().resize_data_structures(get_Nmax());
//    }
//
//  // Clear the Greedy param list
//  for (std::size_t i=0; i<get_rb_evaluation().greedy_param_list.size(); i++)
//    get_rb_evaluation().greedy_param_list[i].clear();
//
//  get_rb_evaluation().greedy_param_list.clear();
//
//  Real training_greedy_error;
//
//
//  // If we are continuing from a previous training run,
//  // we might already be at the max number of basis functions.
//  // If so, we can just return.
//  if(get_rb_evaluation().get_n_basis_functions() >= get_Nmax())
//    {
//      libMesh::out << "Maximum number of basis functions reached: Nmax = "
//                   << get_Nmax() << std::endl;
//      return 0.;
//    }
//
//
//  // Compute the dual norms of the outputs if we haven't already done so
//  compute_output_dual_innerprods();
//
//  // Compute the Fq Riesz representor dual norms if we haven't already done so
//  compute_Fq_representor_innerprods();
//
//  libMesh::out << std::endl << "---- Performing Greedy basis enrichment ----" << std::endl;
//  Real initial_greedy_error = 0.;
//  bool initial_greedy_error_initialized = false;
//  while(true)
//    {
//      libMesh::out << std::endl << "---- Basis dimension: "
//                   << get_rb_evaluation().get_n_basis_functions() << " ----" << std::endl;
//
//      if( count > 0 || (count==0 && use_empty_rb_solve_in_greedy) )
//        {
//          libMesh::out << "Performing RB solves on training set" << std::endl;
//          training_greedy_error = compute_max_error_bound();
////
////          Real mesh_scale = 1./50.;
////          training_greedy_error *= mesh_scale;
//
//          libMesh::out << "Maximum error bound is " << training_greedy_error << std::endl << std::endl;
//
//          // record the initial error
//          if (!initial_greedy_error_initialized)
//            {
//              initial_greedy_error = training_greedy_error;
//              initial_greedy_error_initialized = true;
//            }
//
//          // Break out of training phase if we have reached Nmax
//          // or if the training_tolerance is satisfied.
//          if (greedy_termination_test(training_greedy_error, initial_greedy_error, count))
//            break;
//        }
//
//      libMesh::out << "Performing truth solve at parameter:" << std::endl;
//      print_parameters();
//
//      // Update the list of Greedily selected parameters
//      this->update_greedy_param_list();
//
//      // Perform an Offline truth solve for the current parameter
//      truth_norm = truth_solve(-1);
//      libMesh::out << "Truth norm:" << truth_norm << std::endl;
//
//      // Add orthogonal part of the snapshot to the RB space
//      libMesh::out << "Enriching the RB space" << std::endl;
//      enrich_RB_space();
//
//      update_system();
//
//      // Increment counter
//      count++;
//    }
//  this->update_greedy_param_list();
//
//  return training_greedy_error;
//}
//
//  void compute_Fq_representor_innerprods(bool compute_inner_products=true)
//{
//
//  // Skip calculations if we've already computed the Fq_representors
//  if(!Fq_representor_innerprods_computed)
//    {
//      // Only log if we get to here
//      LOG_SCOPE("compute_Fq_representor_innerprods()", "RBConstruction");
//
//      for(unsigned int q_f=0; q_f<get_rb_theta_expansion().get_n_F_terms(); q_f++)
//        {
//          if(!Fq_representor[q_f])
//            {
//              Fq_representor[q_f] = (NumericVector<Number>::build(this->comm()).release());
//              Fq_representor[q_f]->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
//            }
//
//          libmesh_assert(Fq_representor[q_f]->size()       == this->n_dofs()       &&
//                         Fq_representor[q_f]->local_size() == this->n_local_dofs() );
//
//          rhs->zero();
//          rhs->add(1., *get_Fq(q_f));
//
////          if (!is_quiet())
////            libMesh::out << "Starting solve q_f=" << q_f
////                         << " in RBConstruction::update_residual_terms() at "
////                         << Utility::get_timestamp() << std::endl;
//
//          solve_for_matrix_and_rhs(*inner_product_solver, *inner_product_matrix, *rhs);
//
//          if (assert_convergence)
//            check_convergence(*inner_product_solver);
//
////          if (!is_quiet())
////            {
////              libMesh::out << "Finished solve q_f=" << q_f
////                           << " in RBConstruction::update_residual_terms() at "
////                           << Utility::get_timestamp() << std::endl;
////
////              libMesh::out << this->n_linear_iterations()
////                           << " iterations, final residual "
////                           << this->final_linear_residual() << std::endl;
////            }
//
//          *Fq_representor[q_f] = *solution;
//        }
//
//      if (compute_inner_products)
//        {
//          unsigned int q=0;
//
//          for(unsigned int q_f1=0; q_f1<get_rb_theta_expansion().get_n_F_terms(); q_f1++)
//            {
//              inner_product_matrix->vector_mult(*inner_product_storage_vector, *Fq_representor[q_f1]);
//
//              for(unsigned int q_f2=q_f1; q_f2<get_rb_theta_expansion().get_n_F_terms(); q_f2++)
//                {
//                  Fq_representor_innerprods[q] = inner_product_storage_vector->dot(*Fq_representor[q_f2]);
//
//                  q++;
//                }
//            }
//        } // end if (compute_inner_products)
//
//      Fq_representor_innerprods_computed = true;
//    }
//
//  get_rb_evaluation().Fq_representor_innerprods = Fq_representor_innerprods;
//}
//
//
//  Real rb_X_norm(const unsigned int N)
//{
//   UniquePtr< NumericVector<Number> > RB_sol = NumericVector<Number>::build(this->comm());
//   RB_sol->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
//
//   UniquePtr< NumericVector<Number> > temp = NumericVector<Number>::build(this->comm());
//   temp->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
//
//   for(unsigned int i=0; i<N; i++)
//   {
//     RB_sol->add(get_rb_evaluation().RB_solution(i), get_rb_evaluation().get_basis_function(i));
//   }
//
//   inner_product_matrix->vector_mult(*temp, *RB_sol);
//
//   Real rb_X_norm_sq = RB_sol->dot(*temp);
//
//   libMesh::out << std::sqrt( libmesh_real(rb_X_norm_sq) ) << std::endl;
//
//   return std::sqrt( libmesh_real(rb_X_norm_sq) );
//}
//
//  Real compute_residual_dual_norm(const unsigned int N)
//{
//   LOG_SCOPE("compute_residual_dual_norm()", "RBConstruction");
//
//   // Put the residual in rhs in order to compute the norm of the Riesz representor
//   // Note that this only works in serial since otherwise each processor will
//   // have a different parameter value during the Greedy training.
//
//   UniquePtr< NumericVector<Number> > RB_sol = NumericVector<Number>::build(this->comm());
//   RB_sol->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
//
//   UniquePtr< NumericVector<Number> > temp = NumericVector<Number>::build(this->comm());
//   temp->init (this->n_dofs(), this->n_local_dofs(), false, PARALLEL);
//
//   for(unsigned int i=0; i<N; i++)
//   {
//     RB_sol->add(get_rb_evaluation().RB_solution(i), get_rb_evaluation().get_basis_function(i));
//   }
//
//   this->truth_assembly();
//   matrix->vector_mult(*temp, *RB_sol);
//   rhs->add(-1., *temp);
//
//   // Then solve to get the Reisz representor
//   matrix->zero();
//   matrix->add(1., *inner_product_matrix);
////   if(constrained_problem)
////     matrix->add(1., *constraint_matrix);
//
//   solution->zero();
//   solve();
//   // Make sure we didn't max out the number of iterations
//   if( (this->n_linear_iterations() >=
//        this->get_equation_systems().parameters.get<unsigned int>("linear solver maximum iterations")) &&
//       (this->final_linear_residual() >
//        this->get_equation_systems().parameters.get<Real>("linear solver tolerance")) )
//   {
//     libmesh_error_msg("Warning: Linear solver may not have converged! Final linear residual = "
//                       << this->final_linear_residual() << ", number of iterations = "
//                       << this->n_linear_iterations());
//   }
//
//   inner_product_matrix->vector_mult(*inner_product_storage_vector, *solution);
//
//   Real slow_residual_norm_sq = solution->dot(*inner_product_storage_vector);
//
//   return std::sqrt( libmesh_real(slow_residual_norm_sq) );
//}


//  Real truth_norm;
  unsigned int u_var;

};

///------------------------DWARFELEPHANTRBEVALUATION------------------------
class DwarfElephantRBEvaluationSteadyState : public RBEvaluation
{

//---------------------------------PUBLIC-----------------------------------
public:
  DwarfElephantRBEvaluationSteadyState(const libMesh::Parallel::Communicator & comm, FEProblemBase & fe_problem):
    RBEvaluation(comm),
    fe_problem(fe_problem)
  {
    set_rb_theta_expansion(_rb_theta_expansion);
  }

//    virtual Real get_stability_lower_bound()
//  {
//    _rb_scm_eval->set_parameters(get_parameters());
//    return _rb_scm_eval->get_SCM_LB();
//  }

  virtual Real get_stability_lower_bound()
  {
    const RBParameters & mu = get_parameters();

    Real min_mu = mu.get_value("mu_0");

    for (unsigned int  i = 1; i != mu.n_parameters(); i++)
    {
      const std::string mu_name = "mu_" + std::to_string(i);
      Real min_mu_i = std::min(min_mu, mu.get_value(mu_name));

      if (min_mu_i < min_mu)
        min_mu = min_mu_i;
    }

    return min_mu;
  }

//  Real rb_solve(unsigned int N)
//{
//  LOG_SCOPE("rb_solve()", "RBEvaluation");
//
//  if(N > get_n_basis_functions())
//    libmesh_error_msg("ERROR: N cannot be larger than the number of basis functions in rb_solve");
//
//  const RBParameters & mu = get_parameters();
//
//  // Resize (and clear) the solution vector
//  RB_solution.resize(N);
//
//  // Assemble the RB system
//  DenseMatrix<Number> RB_system_matrix(N,N);
//  RB_system_matrix.zero();
//
//  DenseMatrix<Number> RB_Aq_a;
//  for(unsigned int q_a=0; q_a<_rb_theta_expansion.get_n_A_terms(); q_a++)
//    {
//      RB_Aq_vector[q_a].get_principal_submatrix(N, RB_Aq_a);
//
//      RB_system_matrix.add(_rb_theta_expansion.eval_A_theta(q_a, mu), RB_Aq_a);
//    }
//
//  // Assemble the RB rhs
//  DenseVector<Number> RB_rhs(N);
//  RB_rhs.zero();
//
//  DenseVector<Number> RB_Fq_f;
//  for(unsigned int q_f=0; q_f<_rb_theta_expansion.get_n_F_terms(); q_f++)
//    {
//      RB_Fq_vector[q_f].get_principal_subvector(N, RB_Fq_f);
//
//      RB_rhs.add(_rb_theta_expansion.eval_F_theta(q_f, mu), RB_Fq_f);
//    }
//
//  // Solve the linear system
//  if(N > 0)
//    {
//      RB_system_matrix.lu_solve(RB_rhs, RB_solution);
//    }
//
//  // Evaluate RB outputs
//  DenseVector<Number> RB_output_vector_N;
//  for(unsigned int n=0; n<_rb_theta_expansion.get_n_outputs(); n++)
//    {
//      RB_outputs[n] = 0.;
//      for(unsigned int q_l=0; q_l<_rb_theta_expansion.get_n_output_terms(n); q_l++)
//        {
//          RB_output_vectors[n][q_l].get_principal_subvector(N, RB_output_vector_N);
//          RB_outputs[n] += _rb_theta_expansion.eval_output_theta(n,q_l,mu)*RB_output_vector_N.dot(RB_solution);
//        }
//    }
//
//  if(evaluate_RB_error_bound) // Calculate the error bounds
//    {
//      const DwarfElephantInitializeRBSystem & _initial_userobj = fe_problem.getUserObject<DwarfElephantInitializeRBSystem>("initializeRBSystem");
////      _initial_userobj._rb_con_ptr;
//      DwarfElephantRBConstructionSteadyState & sys_rb = fe_problem.es().get_system<DwarfElephantRBConstructionSteadyState>("RBSystem");
//      TransientNonlinearImplicitSystem & sys = fe_problem.es().get_system<TransientNonlinearImplicitSystem>("rb0");
//
//      // Evaluate the dual norm of the residual for RB_solution_vector
//
//      use_relative_bound_in_greedy = false;
////      // slower but less error prone error bound (does not work in parallel)
////      Real epsilon_N = sys_rb.compute_residual_dual_norm(N);
//
//      // faster but more error prone error bound (does work in parallel)
//      Real epsilon_N = compute_residual_dual_norm(N);
//
//      Real rb_norm = sys_rb.rb_X_norm(N);
//
//      // Get lower bound for coercivity constant
//      const Real alpha_LB = get_stability_lower_bound();
//      // alpha_LB needs to be positive to get a valid error bound
//      libmesh_assert_greater ( alpha_LB, 0. );
//
//      // Evaluate the (absolute) error bound
//      Real abs_error_bound = epsilon_N / residual_scaling_denom(alpha_LB);
//
//      if (use_relative_bound_in_greedy)
//        abs_error_bound /= rb_norm;
//
//      // Now compute the output error bounds
//      for(unsigned int n=0; n<_rb_theta_expansion.get_n_outputs(); n++)
//        {
//          RB_output_error_bounds[n] = abs_error_bound * eval_output_dual_norm(n, mu);
//        }
//
//      return abs_error_bound;
//    }
//  else // Don't calculate the error bounds
//    {
//      // Just return -1. if we did not compute the error bound
//      return -1.;
//    }
//}
//
//Real compute_residual_dual_norm(const unsigned int N)
//{
//  LOG_SCOPE("compute_residual_dual_norm()", "RBEvaluation");
//
//  const RBParameters & mu = get_parameters();
//
//  // Use the stored representor inner product values
//  // to evaluate the residual norm
//  Number residual_norm_sq = 0.;
//  Number residual_norm_sq_FF = 0.;
//  Number residual_norm_sq_FA = 0.;
//  Number residual_norm_sq_AA = 0.;
//
//  unsigned int q=0;
//  for(unsigned int q_f1=0; q_f1<_rb_theta_expansion.get_n_F_terms(); q_f1++)
//    {
//      for(unsigned int q_f2=q_f1; q_f2<_rb_theta_expansion.get_n_F_terms(); q_f2++)
//        {
//          Real delta = (q_f1==q_f2) ? 1. : 2.;
////          Real delta = 1.;
//          residual_norm_sq += delta * libmesh_real(
//                                                   _rb_theta_expansion.eval_F_theta(q_f1, mu)
//                                                   * libmesh_conj(_rb_theta_expansion.eval_F_theta(q_f2, mu)) * Fq_representor_innerprods[q] );
//
//          residual_norm_sq_FF = delta * libmesh_real(
//                                                     _rb_theta_expansion.eval_F_theta(q_f1, mu)
//                                                     * libmesh_conj(_rb_theta_expansion.eval_F_theta(q_f2, mu)) * Fq_representor_innerprods[q] );
//
//  libMesh::out << residual_norm_sq_FF << std::endl;
////          libMesh::out << "F-F: " << std::to_string(q) << ": " <<residual_norm_sq_FF << std::endl;
//          q++;
//        }
//    }
//
////    libMesh::out << "F-F: " <<residual_norm_sq_FF << std::endl;
//
//  for(unsigned int q_f=0; q_f<_rb_theta_expansion.get_n_F_terms(); q_f++)
//    {
//      for(unsigned int q_a=0; q_a<_rb_theta_expansion.get_n_A_terms(); q_a++)
//        {
//          for(unsigned int i=0; i<N; i++)
//            {
//              Real delta = 2.;
//              residual_norm_sq +=
//                delta * libmesh_real( _rb_theta_expansion.eval_F_theta(q_f, mu) *
//                                      libmesh_conj(_rb_theta_expansion.eval_A_theta(q_a, mu)) *
//                                      libmesh_conj(RB_solution(i)) * Fq_Aq_representor_innerprods[q_f][q_a][i] );
//
//              residual_norm_sq_FA =
//                delta * libmesh_real( _rb_theta_expansion.eval_F_theta(q_f, mu) *
//                                      libmesh_conj(_rb_theta_expansion.eval_A_theta(q_a, mu)) *
//                                      libmesh_conj(RB_solution(i)) * Fq_Aq_representor_innerprods[q_f][q_a][i] );
//
////                                      libMesh::out << "F-A: " << std::to_string(q_f) << ": " <<residual_norm_sq_FA << std::endl;
//
//            }
//        }
//    }
////libMesh::out << "F-A: " <<residual_norm_sq_FA << std::endl;
//
//  q=0;
//  for(unsigned int q_a1=0; q_a1<_rb_theta_expansion.get_n_A_terms(); q_a1++)
//    {
//      for(unsigned int q_a2=q_a1; q_a2<_rb_theta_expansion.get_n_A_terms(); q_a2++)
//        {
//          Real delta = (q_a1==q_a2) ? 1. : 2.;
////          Real delta = 1.;
//
//          for(unsigned int i=0; i<N; i++)
//            {
//              for(unsigned int j=0; j<N; j++)
//                {
//                  residual_norm_sq +=
//                    delta * libmesh_real( libmesh_conj(_rb_theta_expansion.eval_A_theta(q_a1, mu)) *
//                                          _rb_theta_expansion.eval_A_theta(q_a2, mu) *
//                                          libmesh_conj(RB_solution(i)) * RB_solution(j) * Aq_Aq_representor_innerprods[q][i][j] );
//
//                  residual_norm_sq_AA =
//                    delta * libmesh_real( libmesh_conj(_rb_theta_expansion.eval_A_theta(q_a1, mu)) *
//                                          _rb_theta_expansion.eval_A_theta(q_a2, mu) *
//                                          libmesh_conj(RB_solution(i)) * RB_solution(j) * Aq_Aq_representor_innerprods[q][i][j] );
//                }
//            }
//
//          libMesh::out << "A-A: " <<residual_norm_sq_AA << std::endl;
//          q++;
//        }
//    }
//
////   libMesh::out << "A-A: " <<residual_norm_sq_AA << std::endl;
////   libMesh::out << "F-F + F-A + A-A: " <<residual_norm_sq_FF+residual_norm_sq_FA+residual_norm_sq_AA << std::endl;
//
//  if(libmesh_real(residual_norm_sq) < 0.)
//    {
//      //    libMesh::out << "Warning: Square of residual norm is negative "
//      //                 << "in RBSystem::compute_residual_dual_norm()" << std::endl;
//
//      //     Sometimes this is negative due to rounding error,
//      //     but when this occurs the error is on the order of 1.e-10,
//      //     so shouldn't affect error bound much...
//      residual_norm_sq = std::abs(residual_norm_sq);
//    }
//
//  return std::sqrt( libmesh_real(residual_norm_sq) );
//}

//  RBSCMEvaluation * _rb_scm_eval;
  FEProblemBase & fe_problem;
  RBP1Theta3ThetaEqualMuExpansionSteadyState _rb_theta_expansion;
};

//#endif // LIBMESH_HAVE_SLEPC && LIBMESH_HAVE_GLPK
///-------------------------------------------------------------------------
#endif // DWARFELEPHANTRBCLASSESSTEADYSTATE_H