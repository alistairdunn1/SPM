//============================================================================
// Name        : ProportionsByCategory.h
// Author      : S.Rasmussen
// Date        : 29/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef PROPORTIONSBYCATEGORY_H_
#define PROPORTIONSBYCATEGORY_H_

const string proportions_by_category_observation =
    "@observation proportions_by_category_observation\n"
    "type proportions_by_category\n"
    "year 2008\n"
    "time_step step_one\n"
    "categories immature\n"
    "categories2 mature spawning\n"
    "selectivities constant\n"
    "selectivities2 constant constant\n"
    "min_age 5\n"
    "max_age 7\n"
    "age_plus_group True\n"
    "layer string_layer\n"
    "obs AreaA 0.1 0.2 0.7\n"
    "obs AreaB 0.2 0.3 0.5\n"
    "obs AreaC 0.3 0.4 0.3\n"
    "obs AreaD 0.4 0.5 0.1\n"
    "obs AreaE 0.3 0.3 0.4\n"
    "obs AreaF 0.4 0.4 0.2\n"
    "error_value AreaC 1300 1400 1500\n"
    "error_value AreaB 1200 1300 1400\n"
    "error_value AreaA 1000 1100 1200\n"
    "error_value AreaD 1400 1500 1600\n"
    "error_value AreaE 1500 1500 1500\n"
    "error_value AreaF 1600 200 2000\n"
    "likelihood binomial\n"
    "delta 1e-11\n";

#endif /* PROPORTIONSBYCATEGORY_H_ */
#endif /* TEST */
