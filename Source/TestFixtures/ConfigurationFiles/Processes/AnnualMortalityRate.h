//============================================================================
// Name        : AnnualMortalityRate.h
// Author      : S.Rasmussen
// Date        : 21/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef ANNUALMORTALITYRATE_H_
#define ANNUALMORTALITYRATE_H_

const string annual_mortality_rate =
    "@process annual_mortality_rate\n"
    "type annual_mortality_rate\n"
    "categories spawning mature\n"
    "selectivities logistic_producing logistic_producing\n"
    "years 1994 1996 1998 2000 2002 2004 2006 2008\n"
    "m 0.5 0.4 0.3 0.4 0.5 0.8 0.3 0.2\n";

#endif /* ANNUALMORTALITYRATE_H_ */
#endif /* TEST */
