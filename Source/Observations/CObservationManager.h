//============================================================================
// Name        : CObservationManager.h
// Author      : S.Rasmussen
// Date        : 17/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : This class is responsible for maintaining a list of our
//       Observations. Like all Manager it is responsible for the validate
//       and execute calls to the children.
//
//       In order for the Minimiser (ADOLC) to work correctly, we must
//       provide a score back after each run through our model that relates
//       to how accurate our model was against the observations. This allows
//       the minimiser to change the parameters to find a better fit. The
//       Observations are the main comparison against the results to get this
//       score (Objective Value). Once the model has been completed, the
//       score for each Observation is added (Objective Function) and the
//       result if passed to the minimiser.
//
// $Date$
//============================================================================
#ifndef COBSERVATIONMANAGER_H_
#define COBSERVATIONMANAGER_H_

// Local Headers
#include "../BaseClasses/CBaseManager.h"

// Classes
class CObservation;

//**********************************************************************
//
//
//**********************************************************************
class CObservationManager : public CBaseManager
{
public:
  static CObservationManager *Instance();
  static void Destroy();
  void clone(CObservationManager *Manager);
  void addObservation(CObservation *pObservation);
  void fillVector(vector<CObservation *> &list);
  CObservation *getObservation(string label);
  void validate();
  void build();
  void prepare(int year, int step);
  void execute(int year, int step);
  virtual ~CObservationManager();

protected:
  // Functions
  CObservationManager();

  // Variables
  vector<CObservation *> vObservationList;

private:
  static boost::thread_specific_ptr<CObservationManager> clInstance;
};

#endif /*COBSERVATIONMANAGER_H_*/
