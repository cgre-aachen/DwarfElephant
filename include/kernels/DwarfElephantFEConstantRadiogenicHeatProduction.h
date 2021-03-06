/**
 * This Kernel is implements a constant radiogenic heat production using the full
 * Finite Element solution. It is included in this package for validation
 * purposes.
 */

///-------------------------------------------------------------------------
#ifndef DWARFELEPHANTFECONSTANTRADIOGENICHEATPRODUCTION_H
#define DWARFELEPHANTFECONSTANTRADIOGENICHEATPRODUCTION_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes
#include "Kernel.h"

///-------------------------------------------------------------------------
// Forward Declarations
class DwarfElephantFEConstantRadiogenicHeatProduction;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<DwarfElephantFEConstantRadiogenicHeatProduction>();

///This Kernel is implements a constant radiogenic heat production using the full Finite Element solution. It is included in this package for validation purposes.
class DwarfElephantFEConstantRadiogenicHeatProduction : public Kernel
{
//----------------------------------PUBLIC----------------------------------
public:
  DwarfElephantFEConstantRadiogenicHeatProduction(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Real _radiogenic_heat_production;
  Real _norm_value_radiogenic_heat_production;

  bool _transient;

  Real _density;
  Real _specific_heat;
  Real _norm_value_density;
  Real _norm_value_specific_heat;
};

///-------------------------------------------------------------------------
#endif // DWARFELEPHANTFECONSTANTRADIOGENICHEATPRODUCTION_H
