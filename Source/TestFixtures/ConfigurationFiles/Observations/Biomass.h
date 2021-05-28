//============================================================================
// Name        : Biomass.h
// Author      : S.Rasmussen
// Date        : 27/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef BIOMASS_H_
#define BIOMASS_H_

const string biomass_observation
    = "@observation biomass_observation\n"
      "type biomass\n"
      "year 2008\n"
      "time_step step_one\n"
      "categories immature mature spawning\n"
      "selectivities constant constant constant\n"
      "layer string_layer\n"
      "catchability catchability_basic\n"
      "obs AreaA 60.0\n"
      "obs AreaC 20.0\n"
      "obs AreaB 40.0\n"
      "obs AreaD 20.0\n"
      "obs AreaE 20.0\n"
      "obs AreaF 20.0\n"
      "error_value AreaC 0.13\n"
      "error_value AreaD 0.14\n"
      "error_value AreaA 0.10\n"
      "error_value AreaB 0.12\n"
      "error_value AreaE 0.15\n"
      "error_value AreaF 0.16\n"
      "likelihood lognormal\n"
      "delta 1e-11\n";

const string biomass_observation_simulate
    = "@observation biomass_observation_simulate\n"
      "type biomass\n"
      "year 2008\n"
      "time_step step_one\n"
      "categories immature mature spawning\n"
      "selectivities constant constant constant\n"
      "layer string_layer\n"
      "catchability catchability_basic\n"
      "obs AreaC 20.0\n"
      "obs AreaD 20.0\n"
      "obs AreaE 20.0\n"
      "obs AreaF 20.0\n"
      "error_value AreaA 0.10\n"
      "error_value AreaD 0.14\n"
      "error_value AreaE 0.15\n"
      "obs AreaA 60.0\n"
      "obs AreaB 40.0\n"
      "error_value AreaB 0.12\n"
      "error_value AreaC 0.13\n"
      "error_value AreaF 0.16\n"
      "likelihood lognormal\n"
      "delta 1e-11\n";

#endif /* BIOMASS_H_ */
#endif /* TEST */
