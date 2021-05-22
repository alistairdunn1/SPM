//============================================================================
// Name        : CMovementProcess.cpp
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-10-01 13:36:57 +1300 (Wed, 01 Oct 2008) $
//============================================================================

// Local Headers
#include "CMovementProcess.h"
#include "../../../Helpers/CError.h"

//**********************************************************************
// CMovementProcess::CMovementProcess()
// Default Constructor
//**********************************************************************
CMovementProcess::CMovementProcess()
{
  // Vars
  dProportion = -1.0;
  registerEstimable(PARAM_PROPORTION, &dProportion);
}

//**********************************************************************
// void CMovementProcess::validate()
// Validate
//**********************************************************************
void CMovementProcess::validate()
{
  try
  {
    // BaseValidate
    CProcess::validate();

    // Local Validation
    if (getProportion() == -1.0)
      CError::errorMissing(PARAM_PROPORTION);
  }
  catch (string &Ex)
  {
    Ex = "CMovementProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMovementProcess::build()
// Build
//**********************************************************************
void CMovementProcess::build()
{
  try
  {
    CProcess::build();
  }
  catch (string &Ex)
  {
    Ex = "CMovementProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMovementProcess::execute()
// Execute
//**********************************************************************
void CMovementProcess::execute()
{
#ifndef OPTIMIZE
  try
  {
#endif

    CProcess::execute();
#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CMovementProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CMovementProcess::doMove(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
// Do The Move To RIndex/CIndex
//**********************************************************************
void CMovementProcess::doMove(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
{
#ifndef OPTIMIZE
  try
  {
#endif
    // Get Target Base
    pTargetBase = pWorld->getBaseSquare(RIndex, CIndex);

    // Check if Target-Base Is Usable
    if (!pTargetBase->getEnabled())
      return;

    // Get Target Diff
    pTargetDiff = pWorld->getDifferenceSquare(RIndex, CIndex);

    // Add/Sub Values
    pTargetDiff->addValue(SRIndex, SCIndex, Qty);
    pBaseSquare->subValue(SRIndex, SCIndex, Qty);

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CMovementProcess.doMove(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CMovementProcess::moveUp(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
// Move Amount of Fish Up from World(RowIndex, ColIndex)
//**********************************************************************
void CMovementProcess::moveUp(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
{
#ifndef OPTIMIZE
  try
  {
#endif

    // Can We Move Up?
    if (RIndex == 0)
      return;

    // Do it
    doMove((RIndex - 1), CIndex, SRIndex, SCIndex, Qty);

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CMovementProcess.moveUp(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CMovementProcess::moveDown(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
// Move Amount of Fish Down From World(RowIndex, ColIndex) Square(Row/Col)
//**********************************************************************
void CMovementProcess::moveDown(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
{
#ifndef OPTIMIZE
  try
  {
#endif

    // Can We Move Down?
    if (RIndex == (iWorldHeight - 1))
      return;

    // Do it
    doMove((RIndex + 1), CIndex, SRIndex, SCIndex, Qty);

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CMovementProcess.moveDown(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CMovementProcess::moveLeft(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
// Move Amount of Fish Left From World(RowIndex, ColIndex)
//**********************************************************************
void CMovementProcess::moveLeft(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
{
#ifndef OPTIMIZE
  try
  {
#endif

    // Can We Move Left?
    if (CIndex == 0)
      return;

    // Do it
    doMove(RIndex, (CIndex - 1), SRIndex, SCIndex, Qty);

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CMovementProcess.moveLeft(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CMovementProcess::moveRight(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
// Move Amount of Fish right from World(RowIndex,ColIndex)
//**********************************************************************
void CMovementProcess::moveRight(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty)
{
#ifndef OPTIMIZE
  try
  {
#endif
    // Can We Move Right?
    if (CIndex == (iWorldWidth - 1))
      return;

    // Do it
    doMove(RIndex, (CIndex + 1), SRIndex, SCIndex, Qty);

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CMovementProcess.moveRight(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CMovementProcess::~CMovementProcess()
// Default De-Constructor
//**********************************************************************
CMovementProcess::~CMovementProcess()
{
}
