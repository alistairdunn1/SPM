//============================================================================
// Name        : Estimation.h
// Author      : S.Rasmussen
// Date        : 29/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef ESTIMATION_H_
#define ESTIMATION_H_

const string basic_estimation
    = "@estimation\n"
      "minimiser gammadiff\n"
      "@minimiser gammadiff\n"
      "type numerical_differences\n"
      "tolerance 0.002\n"
      "covariance False\n"
      "@minimiser de\n"
      "type de_solver\n"
      "covariance False\n"
      "@estimate\n"
      "parameter process[category_transition_rate].proportions(1)\n"
      "lower_bound 0.1\n"
      "upper_bound 1.0\n"
      "type uniform\n";

#endif /* ESTIMATION_H_ */
#endif /* TEST */
