//============================================================================
// Name        : BHRecruitment.h
// Author      : S.Rasmussen A.Dunn
// Date        : 19/07/2013
// Copyright   : Copyright NIWA Science �2013 - www.niwa.co.nz
//============================================================================
#ifdef TEST
#ifndef BHRECRUITMENT_H_
#define BHRECRUITMENT_H_

const string bh_recruitment =
    "@process bh_recruitment\n"
    "type bh_recruitment\n"
    "categories immature\n"
    "proportions 1.0\n"
    "r0 100\n"
    "age 1\n"
    "ssb ssb\n"
    "b0 phase1\n"
    "ssb_offset 1\n"
    "standardise_ycs_years 1994-2006\n"
    "ycs_values 1.0 0.5 0.6 0.4 1.1 1.2 1.2 1.2 1.2 1.2 1.2 1.2 1.0 1.0 1.0\n"
    "steepness 0.75\n"

    "@initialisation_phase phase1\n"
    "years 200\n"
    "time_steps phaseA\n"
    "lambda 1e-10\n"
    "lambda_years 100 125 150 175 200\n"

    "@time_step phaseA\n"
    "processes ageing bh_recruitment maturation mortality\n"

    "@process maturation\n"
    "type category_transition_rate\n"
    "from immature\n"
    "to mature\n"
    "proportions 1.0\n"
    "selectivities maturation\n"

    "@process mortality\n"
    "type constant_mortality_rate\n"
    "categories immature mature\n"
    "m 0.15 0.15\n"
    "selectivities one one\n"

    "@selectivity one\n"
    "type constant\n"
    "c 1\n"

    "@selectivity maturation\n"
    "type logistic_producing\n"
    "l 1\n"
    "h 10\n"
    "a50 3\n"
    "ato95 3\n"

    "@process ageing\n"
    "type ageing\n"
    "categories immature mature\n";

#endif /* BHRECRUITMENT_H_ */
#endif /* TEST */
