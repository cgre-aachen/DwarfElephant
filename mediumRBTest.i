[Mesh]
  type = GeneratedMesh
  dim = 3
   nx = 1
  ny = 2
  nz = 1
#  nx = 10
#  ny = 6
#  nz = 2
  xmin = 0.0
  xmax = 3000
  ymin = 0.0
  ymax = 700
  zmin = 0.0
  zmax = 1000

#  block_id = '0 1 2'
#  block_name = 'shale_bottom sandstone shale_top'
[]

[MeshModifiers]
active = ''
  [./subdomains]
    type = AssignElementSubdomainID
    subdomain_ids = '0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2'
  [../]
[]

[Variables]
active = 'temperature'
  [./temperature]
  [../]
[]

[AuxVariables]
  [./RB_temperature]
  [../]

  [./A0]
  [../]
[]

[Kernels]
active = 'RBConduction_block0' # RBConduction_block1 RBConduction_block2'
  [./RBConduction_block0]
    type = RBDiffusion
    variable = temperature
    initial_rb_userobject = initializeRBSystem
    block = 0
  [../]

  [./RBConduction_block1]
    type = RBDiffusion
    variable = temperature
    initial_rb_userobject = initializeRBSystem
    block = 1
  [../]

  [./RBConduction_block2]
    type = RBDiffusion
    variable = temperature
    initial_rb_userobject = initializeRBSystem
    block = 2
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
    type = RBDirichletBC
    variable = temperature
    boundary = 'bottom'
    value = 31
    initial_rb_userobject = initializeRBSystem
    cache_stiffness_matrix = cacheStiffnessMatrix
  [../]
  [./top]
    type = RBDirichletBC
    variable = temperature
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
    variable = RB_temperature
    parameters_filename = mediumRBTest.i
    offline_stage = true
    online_stage = true
    store_basis_functions = true
    execute_on = initial
  [../]

  [./stiffnessMatrix]
    type = DwarfElephantOnlineStage
    boundary = 'top bottom'
    variable = temperature
    execute_on = timestep_end
    initial_rb_userobject = initializeRBSystem
  [../]

  [./performRBSystem]
    type = DwarfElephantOfflineStage

    parameters_filename = mediumRBTest.i
    residual_name = Re_non_time

    offline_stage = true
    online_stage = true
    store_basis_functions = true

    online_N = 1
    online_mu = '1.05' # 2.5 1.5'
    variable = RB_temperature

    execute_on = timestep_end
    initial_rb_userobject = initializeRBSystem
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
parameter_names = 'mu_0' # mu_1 mu_2'

# Define the minimum and maximum value of the Theta object
mu_0 = '0.95 1.15'
#mu_1 = '2.2 2.8'
#mu_2 = '0.95 1.15'

# Define the number of training sets for the Greedy-algorithm
n_training_samples = 10

# Optionally:
# Determine whether the training points are generated randomly or deterministically
deterministic_training = false

# Determine whether relative or absolute error bounds are used in the Greedy-algorithm
use_relative_bound_in_greedy = false

quiet_mode =  false

