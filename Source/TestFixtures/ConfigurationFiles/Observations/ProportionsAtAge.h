//============================================================================
// Name        : ProportionsAtAge.h
// Author      : S.Rasmussen
// Date        : 28/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef PROPORTIONSATAGE_H_
#define PROPORTIONSATAGE_H_

const string proportions_at_age_observation
    = "@observation proportions_at_age_observation\n"
      "type proportions_at_age\n"
      "year 2008\n"
      "time_step step_one\n"
      "categories immature + mature + spawning\n"
      "selectivities constant constant constant\n"
      "min_age 5\n"
      "max_age 7\n"
      "tolerance 0.01\n"
      "age_plus_group True\n"
      "layer string_layer\n"
      "obs AreaA 0.1 0.2 0.7\n"
      "obs AreaB 0.2 0.3 0.5\n"
      "obs AreaC 0.3 0.4 0.3\n"
      "obs AreaD 0.4 0.5 0.1\n"
      "obs AreaE 0.3 0.3 0.4\n"
      "obs AreaF 0.4 0.4 0.2\n"
      "error_value AreaB 1200\n"
      "error_value AreaA 1000\n"
      "error_value AreaD 1400\n"
      "error_value AreaE 1500\n"
      "error_value AreaC 1300\n"
      "error_value AreaF 1600\n"
      "likelihood multinomial\n"
      "delta 1e-11\n";

const string proportions_at_age_observation_with_compound_categories
    = "@observation proportions_at_age_observation_with_compound_categories\n"
      "type proportions_at_age\n"
      "year 2008\n"
      "time_step step_one\n"
      "categories immature mature + spawning\n"
      "selectivities constant constant constant\n"
      "min_age 5\n"
      "max_age 7\n"
      "tolerance 0.01\n"
      "age_plus_group True\n"
      "layer string_layer\n"
      "obs AreaA 0.05 0.10 0.35 0.05 0.10 0.35 \n"
      "obs AreaB 0.10 0.15 0.25 0.10 0.15 0.25 \n"
      "obs AreaC 0.15 0.20 0.15 0.15 0.20 0.15 \n"
      "obs AreaD 0.20 0.25 0.05 0.20 0.25 0.05 \n"
      "obs AreaE 0.15 0.15 0.20 0.15 0.15 0.20 \n"
      "obs AreaF 0.20 0.20 0.10 0.20 0.20 0.10 \n"
      "error_value AreaC 1300\n"
      "error_value AreaD 1400\n"
      "error_value AreaB 1200\n"
      "error_value AreaA 1000\n"
      "error_value AreaE 1500\n"
      "error_value AreaF 1600\n"
      "likelihood multinomial\n"
      "delta 1e-11\n"
      "ageing_error normal\n";

const string proportions_at_age_observation_with_normal
    = "@observation proportions_at_age_observation_with_normal\n"
      "type proportions_at_age\n"
      "year 2008\n"
      "time_step step_one\n"
      "categories immature + mature + spawning\n"
      "selectivities constant constant constant\n"
      "min_age 5\n"
      "max_age 7\n"
      "tolerance 0.01\n"
      "age_plus_group True\n"
      "layer string_layer\n"
      "obs AreaA 0.1 0.2 0.7\n"
      "obs AreaB 0.2 0.3 0.5\n"
      "obs AreaC 0.3 0.4 0.3\n"
      "obs AreaD 0.4 0.5 0.1\n"
      "obs AreaE 0.3 0.3 0.4\n"
      "obs AreaF 0.4 0.4 0.2\n"
      "error_value AreaC 1300\n"
      "error_value AreaA 1000\n"
      "error_value AreaB 1200\n"
      "error_value AreaD 1400\n"
      "error_value AreaE 1500\n"
      "error_value AreaF 1600\n"
      "likelihood multinomial\n"
      "delta 1e-11\n"
      "ageing_error normal\n";

const string proportions_at_age_observation_with_off_by_one
    = "@observation proportions_at_age_observation_with_off_by_one\n"
      "type proportions_at_age\n"
      "year 2008\n"
      "time_step step_one\n"
      "categories immature + mature + spawning\n"
      "selectivities constant constant constant\n"
      "min_age 5\n"
      "max_age 7\n"
      "tolerance 0.01\n"
      "age_plus_group True\n"
      "layer string_layer\n"
      "obs AreaA 0.1 0.2 0.7\n"
      "obs AreaC 0.3 0.4 0.3\n"
      "obs AreaB 0.2 0.3 0.5\n"
      "obs AreaD 0.4 0.5 0.1\n"
      "obs AreaE 0.3 0.3 0.4\n"
      "obs AreaF 0.4 0.4 0.2\n"
      "error_value AreaA 1000\n"
      "error_value AreaD 1400\n"
      "error_value AreaE 1500\n"
      "error_value AreaB 1200\n"
      "error_value AreaC 1300\n"
      "error_value AreaF 1600\n"
      "likelihood multinomial\n"
      "delta 1e-11\n"
      "ageing_error off_by_one\n";

#endif /* PROPORTIONSATAGE_H_ */
#endif /* TEST */
