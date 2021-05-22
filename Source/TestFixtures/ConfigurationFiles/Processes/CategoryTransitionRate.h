//============================================================================
// Name        : CategoryTransitionRate.h
// Author      : S.Rasmussen
// Date        : 20/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef CATEGORYTRANSITIONRATE_H_
#define CATEGORYTRANSITIONRATE_H_

const string category_transition_rate =
    "@process category_transition_rate\n"
    "type category_transition_rate\n"
    "from immature\n"
    "to mature\n"
    "proportions 0.5\n"
    "selectivities logistic_producing\n";

const string category_transition_rate_spawn =
    "@process category_transition_rate_spawn\n"
    "type category_transition_rate\n"
    "from mature\n"
    "to spawning\n"
    "proportions 0.37\n"
    "selectivities logistic_producing\n";

const string category_transition_rate_both =
    "@process category_transition_rate_both\n"
    "type category_transition_rate\n"
    "from immature mature\n"
    "to mature spawning\n"
    "proportions 0.5 0.37\n"
    "selectivities logistic_producing logistic_producing\n";

#endif /* CATEGORYTRANSITIONRATE_H_ */
#endif /* TEST */
