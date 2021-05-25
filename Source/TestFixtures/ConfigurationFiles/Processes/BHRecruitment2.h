//============================================================================
// Name        : BHRecruitment2.h
// Author      : A.Dunn
// Date        : 25/05/2021
// Copyright   : 
//============================================================================
#ifdef TEST
#ifndef BHRECRUITMENT2_H_
#define BHRECRUITMENT2_H_

const string bh_recruitment2 =
    "@process bh_recruitment2\n"
    "type bh_recruitment2\n"
    "categories immature\n"
    "proportions 1.0\n"
    "age 1\n"
    "ssb ssb\n"
    "b0 phase1\n"
    "ssb_offset 1\n"
	"values 100 50 60 40 110 120 120 120 120 120 120 120 100 100 100\n"
	"years 1993-2007\n"
    "standardise_recruitment_years 1994-2006\n"
    "steepness 0.75\n"

    "@initialisation_phase phase1\n"
    "years 200\n"
    "time_steps phaseA\n"
    "lambda 1e-10\n"
    "lambda_years 100 125 150 175 200\n"

    "@time_step phaseA\n"
    "processes ageing bh_recruitment2 maturation mortality\n"

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

#endif /* BHRECRUITMENT2_H_ */
#endif /* TEST */
