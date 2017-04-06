[Mesh]
  # Note: It is important that the subdomains ids start with zero.
  #       Additionally, it is necessary that the boundaries are defined like this:
  #       back = 0, bottom = 1, right = 2, top = 3, left = 4, front = 5.
  #       Otherwise the RB method will not work properly.

  file = parallel_model.msh
[]

[Variables]
active = 'temperature'
  [./temperature]
  [../]
[]

[Kernels]
active = 'RBConduction_block0 RBConduction_block1 RBConduction_block2'
  [./RBConduction_block0]
    type = RBDiffusion
    variable = temperature
    initial_rb_userobject = initializeRBSystem
    block = 0
    subdomain = 0
  [../]

  [./RBConduction_block1]
    type = RBDiffusion
    variable = temperature
    initial_rb_userobject = initializeRBSystem
    block = 1
    subdomain = 1
  [../]

  [./RBConduction_block2]
    type = RBDiffusion
    variable = temperature
    initial_rb_userobject = initializeRBSystem
    block = 2
    subdomain = 2
  [../]
 []

[Materials]
active = ''

  [./shale_top]
    type = Shale
    block = 2
  [../]

  [./sandstone]
    type = SandStone
    block = 1
  [../]

  [./shale_bottom]
    type = Shale
    block = 0
  [../]
[]

[BCs]
active = 'bottom top'
  [./bottom]
    type = RBPresetBC
    variable = 'temperature'
    boundary = 'bottom'
    value = 31
    initial_rb_userobject = initializeRBSystem
    cache_stiffness_matrix = cacheStiffnessMatrix
  [../]

  [./top]
    type = RBPresetBC
    variable = 'temperature'
    boundary = 'top'
    value = 10
    initial_rb_userobject = initializeRBSystem
    cache_stiffness_matrix = cacheStiffnessMatrix
  [../]
[]

[Executioner]
  type = Steady
  solve_type = 'PJFNK'

  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_rest'
  petsc_options_value = 'hypre  boomeramg   101'
[]

[Functions]
  [./cacheStiffnessMatrix]
    type = CacheStiffnessMatrix
  [../]
[]

[UserObjects]
active = 'initializeRBSystem performRBSystem'

  [./initializeRBSystem]
    type = DwarfElephantInitializeRBSystem
    parameters_filename = largeRBTest.i
    skip_matrix_assembly_in_rb_system = true
    skip_vector_assembly_in_rb_system = true
    offline_stage = true
    execute_on = initial
  [../]

  [./performRBSystem]
    type = DwarfElephantOfflineStage

    residual_name = Re_non_time

    online_stage = true
    store_basis_functions = true

    online_N = 1
    online_mu = '1.05' #' 2.5' # 1.5'

    skip_matrix_assembly_in_rb_system = true
    skip_vector_assembly_in_rb_system = true

    execute_on = timestep_end
    initial_rb_userobject = initializeRBSystem
    cache_stiffness_matrix = cacheStiffnessMatrix
  [../]
[]

[Outputs]
  exodus = true
  execute_on = 'timestep_end'
#  print_perf_log = true
[]

# ====================== Parameters for the RB approximation ======================

# Maximum number of basis functions that will be generated in the Offline-stage
Nmax = 20

# Name of the parameters
# Please name them mu_0, mu_1, ..., mu_n for the re-usability
parameter_names = 'mu_0' #' mu_1'

# Define the minimum and maximum value of the Theta object
mu_0 = '0.95 2.95'
#mu_1 = '2.2 4.2'

# Define the number of training sets for the Greedy-algorithm
n_training_samples = 100

# Optionally:
# Determine whether the training points are generated randomly or deterministically
deterministic_training = true

# Determine whether relative or absolute error bounds are used in the Greedy-algorithm
use_relative_bound_in_greedy = true

rel_training_tolerance = 1.e-3

quiet_mode =  false
#normalize_rb_bound_in_greedy = true
