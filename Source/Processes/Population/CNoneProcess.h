//============================================================================
// Name        : CNoneProcess.h
// Author      :
// Date        :
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CNONEPROCESS_H_
#define CNONEPROCESS_H_

// Local Headers
#include "../CProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CNoneProcess : public CProcess
{
public:
	// Functions
	CNoneProcess();
	virtual ~CNoneProcess();
	CProcess *clone() { return new CNoneProcess(*this); }
	void validate();
	void build();
	void execute();
};

#endif /*CNONEPROCESS_H_*/
