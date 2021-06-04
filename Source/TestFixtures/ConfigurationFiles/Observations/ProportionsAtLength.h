//============================================================================
// Name        : ProportionsAtLength.h
// Author      :
// Date        :
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
//============================================================================
#ifdef TEST
#ifndef PROPORTIONSATLENGTH_H_
#define PROPORTIONSATLENGTH_H_

const string proportions_at_length_observation
    = "@observation proportions_at_length_observation\n"
      "type proportions_at_length\n"
      "year 2008\n"
      "time_step step_one\n"
      "categories immature + mature + spawning\n"
      "selectivities constant constant constant\n"
      "length_bins 0 20 40 60 80 100 120\n"
      "tolerance 0.01\n"
      "layer string_layer\n"
      "obs AreaA 0.1 0.2 0.3 0.2 0.1 0.1\n"
      "obs AreaB 0.2 0.3 0.2 0.1 0.1 0.1\n"
      "obs AreaC 0.3 0.4 0.0 0.1 0.1 0.1\n"
      "obs AreaD 0.4 0.5 0.0 0.1 0.0 0.0\n"
      "obs AreaE 0.3 0.3 0.1 0.1 0.1 0.1\n"
      "obs AreaF 0.4 0.4 0.1 0.1 0.0 0.0\n"
      "error_value AreaB 120\n"
      "error_value AreaA 100\n"
      "error_value AreaD 140\n"
      "error_value AreaE 150\n"
      "error_value AreaC 130\n"
      "error_value AreaF 160\n"
      "likelihood multinomial\n"
      "delta 1e-11\n";

const string proportions_at_length_observation_with_compound_categories
    = "@observation proportions_at_length_observation_with_compound_categories\n"
      "type proportions_at_length\n"
      "year 2008\n"
      "time_step step_one\n"
      "categories immature mature + spawning\n"
      "selectivities constant constant constant\n"
      "length_bins 0 20 40 60 80 100 120\n"
      "tolerance 0.01\n"
      "layer string_layer\n"
      "obs AreaA 0.025 0.050 0.175 0.025 0.050 0.175 0.025 0.050 0.175 0.025 0.050 0.175 \n"
      "obs AreaB 0.025 0.050 0.175 0.025 0.050 0.175 0.025 0.050 0.175 0.025 0.050 0.175 \n"
      "obs AreaC 0.025 0.050 0.175 0.025 0.050 0.175 0.025 0.050 0.175 0.025 0.050 0.175 \n"
      "obs AreaD 0.025 0.050 0.175 0.025 0.050 0.175 0.025 0.050 0.175 0.025 0.050 0.175 \n"
      "obs AreaE 0.025 0.050 0.175 0.025 0.050 0.175 0.025 0.050 0.175 0.025 0.050 0.175 \n"
      "obs AreaF 0.025 0.050 0.175 0.025 0.050 0.175 0.025 0.050 0.175 0.025 0.050 0.175 \n"
      "error_value AreaC 130\n"
      "error_value AreaD 140\n"
      "error_value AreaB 120\n"
      "error_value AreaA 100\n"
      "error_value AreaE 150\n"
      "error_value AreaF 160\n"
      "likelihood multinomial\n"
      "delta 1e-11\n";

#endif /* PROPORTIONSATAGE_H_ */
#endif /* TEST */
