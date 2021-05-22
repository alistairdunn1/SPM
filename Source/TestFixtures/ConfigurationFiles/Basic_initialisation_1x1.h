//============================================================================
// Name        : Basic_1x1.h
// Author      : S.Rasmussen
// Date        : 20/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef BASIC_INIT_1X1_H_
#define BASIC_INIT_1X1_H_

const string basic_initialisation_1x1 =
    "@model\n"
    "nrows 1\n"
    "ncols 1\n"
    "layer base\n"
    "categories immature mature\n"
    "age_size vonB vonB\n"
    "min_age 1\n"
    "max_age 10\n"
    "age_plus_group True\n"
    "initial_year 1994\n"
    "current_year 2008\n"
    "cell_length 1\n"
    "initialisation_phases phase1\n"
    "time_steps step_one\n"
    "@layer base\n"
    "type numeric\n"
    "data 1\n";

#endif /* BASIC_INIT_1X1_H_ */
#endif /* TEST */
