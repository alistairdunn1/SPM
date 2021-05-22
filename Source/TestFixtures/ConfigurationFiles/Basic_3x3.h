//============================================================================
// Name        : Basic_3x3.h
// Author      : S.Rasmussen
// Date        : 27/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef BASIC_3X3_H_
#define BASIC_3X3_H_

const string basic_3x3 =
    "@model\n"
    "nrows 3\n"
    "ncols 3\n"
    "layer base\n"
    "categories immature mature spawning\n"
    "age_size vonB vonB vonB\n"
    "min_age 1\n"
    "max_age 10\n"
    "age_plus_group True\n"
    "initial_year 1994\n"
    "current_year 2008\n"
    "cell_length 1\n"
    //"initialisation_phases Phase1 Phase2\n"
    "time_steps step_one\n"
    "@layer base\n"
    "type numeric\n"
    "data 1 1 1 1 1 1 1 1 1\n";

#endif /* BASIC_3X3_H_ */
#endif /* TEST */
