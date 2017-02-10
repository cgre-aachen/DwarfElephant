/**
 * Shale inherits from the MOOSE class  Material and overrides
 * computeQpProperties.
 * Within the class Shale the typical rock properties of a shale are stored.
 */

 ///-------------------------------------------------------------------------
#ifndef SHALE_H
#define SHALE_H

///---------------------------------INCLUDES--------------------------------
// MOOSE includes
#include "Material.h"

///-------------------------------------------------------------------------
// Forward Declarations
class Shale;

///----------------------------INPUT PARAMETERS-----------------------------
template<>
InputParameters validParams<Shale>();

///-------------------------------------------------------------------------
class Shale : public Material
{

//----------------------------------PUBLIC----------------------------------
public:
  Shale(const InputParameters & parameters);

//--------------------------------PROTECTED---------------------------------
protected:

  /* Methods */
  virtual void computeQpProperties() override;

  /* Attributes */
  // The thermal conductivity (lambda)
  MaterialProperty<Real> & _lambda;

  // RB parameters for the thermal conductivity
  MaterialProperty<RealVectorValue> & _rb_lambda;
};

///-------------------------------------------------------------------------
#endif //SHALE_H
