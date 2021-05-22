//============================================================================
// Name        : CategoryTransition.h
// Author      : A.Dunn
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================
#ifdef TEST
#ifndef CATEGORYTRANSITION_H_
#define CATEGORYTRANSITION_H_

const string category_transition =
    "@process category_transition\n"
    "type category_transition\n"
    "from immature\n"
    "to mature\n"
    "years 1994 1995\n"
    "layers Tag1994 tag1995\n"
    "selectivities TagSel TagSel\n"

    "@layer Tag1994\n"
    "data 20\n"

    "@layer Tag1995\n"
    "data 10\n"

    "@selectivity TagSel\n"
    "type double_normal\n"
    "mu 8\n"
    "sigma_l 3\n"
    "sigma_r 10\n";

#endif /* CATEGORYTRANSITIONRATE_H_ */
#endif /* TEST */
