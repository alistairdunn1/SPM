//============================================================================
// Name        : CRandomNumberGenerator.h
// Author      : S.Rasmussen
// Date        : 7/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CRANDOMNUMBERGENERATOR_H_
#define CRANDOMNUMBERGENERATOR_H_

// Global Headers
#include <boost/random.hpp>

// Local headers
#include "../BaseClasses/CBaseManager.h"

//**********************************************************************
//
//
//**********************************************************************
class CRandomNumberGenerator : public CBaseManager
{
public:
  static CRandomNumberGenerator *Instance();
  void Reset(unsigned new_seed = 12345u);
  static void Destroy();
  void validate();
  void build();
  double getRandomUniform(double min, double max);
  double getRandomUniform_01();
  double getRandomNormal(double mean, double sigma);
  double getRandomStandardNormal();
  double getRandomLogNormal(double mean, double cv);
  double getRandomBinomial(double p, double N);
  double getRandomChiSquare(int df);
  double getRandomGamma(double shape);

protected:
  // Functions
  CRandomNumberGenerator();
  virtual ~CRandomNumberGenerator();
  // Variables
  boost::mt19937 clGenerator;

private:
  static CRandomNumberGenerator *clInstance;
};

#endif /* CRANDOMNUMBERGENERATOR_H_ */
