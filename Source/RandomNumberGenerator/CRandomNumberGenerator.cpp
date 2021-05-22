//============================================================================
// Name        : CRandomNumberGenerator.cpp
// Author      : S.Rasmussen
// Date        : 7/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <boost/random/uniform_real.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/gamma_distribution.hpp>
#include <boost/random/variate_generator.hpp>

// Local Headers
#include "CRandomNumberGenerator.h"

// Singleton Variable
CRandomNumberGenerator *CRandomNumberGenerator::clInstance = 0;

//**********************************************************************
// CRandomNumberGenerator::CRandomNumberGenerator()
// Default Constructor
//**********************************************************************
CRandomNumberGenerator::CRandomNumberGenerator()
{
  // Set our Seed.
  clGenerator.seed((unsigned int)pConfig->getRandomSeed());
}

//**********************************************************************
// CRandomNumberGenerator* CRandomNumberGenerator::Instance()
// Instance Method - Singleton
//**********************************************************************
CRandomNumberGenerator *CRandomNumberGenerator::Instance()
{
  if (clInstance == 0)
    clInstance = new CRandomNumberGenerator();

  return clInstance;
}

//**********************************************************************
// void CRandomNumberGenerator::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CRandomNumberGenerator::Destroy()
{
  if (clInstance != 0)
  {
    delete clInstance;
    clInstance = 0;
  }
}

//**********************************************************************
// void CRandomNumberGenerator::Reset(unsigned new_seed)
// Reset the random number seed
//**********************************************************************
void CRandomNumberGenerator::Reset(unsigned new_seed)
{
  clGenerator.seed(new_seed);
}

//**********************************************************************
// double CRandomNumberGenerator::getRandomUniform(double min, double max)
// Get a uniform distributed random number
//**********************************************************************
double CRandomNumberGenerator::getRandomUniform(double min, double max)
{

  // Build our Uniform Distribution Generator
  boost::uniform_real<> distUniform(min, max);
  boost::variate_generator<boost::mt19937 &, boost::uniform_real<>> gen(clGenerator, distUniform);

  return gen(); // Generated Number
}

//**********************************************************************
// double CRandomNumberGenerator::getRandomUniform_01()
// Get a uniform distributed random number on range 0 to 1
//**********************************************************************
double CRandomNumberGenerator::getRandomUniform_01()
{
  return getRandomUniform(0.0, 1.0); // Generated Number
}

//**********************************************************************
// double CRandomNumberGenerator::getRandomNormal(double mean, double sigma)
// Get a normal distributed random number
//**********************************************************************
double CRandomNumberGenerator::getRandomNormal(double mean, double sigma)
{

  // Build our Normal Distribution Generator
  boost::normal_distribution<> distNormal(mean, sigma);
  boost::variate_generator<boost::mt19937 &, boost::normal_distribution<>> gen(clGenerator, distNormal);

  return gen(); // Generated Number
}

//**********************************************************************
// double CRandomNumberGenerator::getRandomStandardNormal()
// Get a standard normal distributed random number
//**********************************************************************
double CRandomNumberGenerator::getRandomStandardNormal()
{

  // Build our Normal Distribution Generator
  boost::normal_distribution<> distNormal(0.0, 1.0);
  boost::variate_generator<boost::mt19937 &, boost::normal_distribution<>> gen(clGenerator, distNormal);

  return gen(); // Generated Number
}

//**********************************************************************
// double CRandomNumberGenerator::getRandomLogNormal(double mean, double cv)
// Get a lognormal distributed random number, with mean and c.v.
//**********************************************************************
double CRandomNumberGenerator::getRandomLogNormal(double mean, double cv)
{

  double dLogSigma = sqrt(log(cv * cv + 1.0));
  double dLogMean = log(mean) - (dLogSigma * dLogSigma) / 2.0;

  double result = getRandomNormal(dLogMean, dLogSigma);

  return std::exp(result); // Generated Number
}

//**********************************************************************
// double CRandomNumberGenerator::getRandomBinomial(double p, double N)
// Get a binomial distributed random number, with probabilty p for number N
//**********************************************************************
double CRandomNumberGenerator::getRandomBinomial(double p, double N)
{

  double dCount = 0;

  for (int i = 0; i < std::ceil(N); i++)
  {
    double dTemp = getRandomUniform_01();
    if (dTemp <= p)
      dCount++;
  }

  return (dCount); // Generated Number (NOT a proportion)
}

//**********************************************************************
// double CRandomNumberGenerator::getRandomChiSquare()
// Get a ChiSquare distributed random number
//**********************************************************************
double CRandomNumberGenerator::getRandomChiSquare(int df)
{

  // Build our Normal Distribution Generator
  boost::normal_distribution<> distNormal(0.0, 1.0);
  double dSum = 0.0;
  for (int i = 0; i < df; ++i)
  {
    boost::variate_generator<boost::mt19937 &, boost::normal_distribution<>> gen(clGenerator, distNormal);
    //ChiSq ~ sum of normals squared
    double dNumber = gen();
    dSum += dNumber * dNumber;
  }
  return dSum; // Generated Number
}

//**********************************************************************
// double CRandomNumberGenerator::getRandomGamma()
// Get a Gamma distributed random number
//**********************************************************************
double CRandomNumberGenerator::getRandomGamma(double shape)
{

  // Build our Gamma Distribution Generator
  boost::gamma_distribution<> distGamma(shape);
  boost::variate_generator<boost::mt19937 &, boost::gamma_distribution<>> gen(clGenerator, distGamma);
  double dNumber = gen();
  return dNumber; // Generated Number
}

//**********************************************************************
// void CRandomNumberGenerator::validate()
// Validate RNG
//**********************************************************************
void CRandomNumberGenerator::validate()
{
}

//**********************************************************************
// void CRandomNumberGenerator::build()
// Build our RNG
//**********************************************************************
void CRandomNumberGenerator::build()
{
}

//**********************************************************************
// CRandomNumberGenerator::~CRandomNumberGenerator()
// Destructor
//**********************************************************************
CRandomNumberGenerator::~CRandomNumberGenerator()
{
}
