//============================================================================
// Name        : AdjacentCellMovementProcess.h
// Author      : S.Rasmussen
// Date        : 20/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef ADJACENTCELLMOVEMENT_H_
#define ADJACENTCELLMOVEMENT_H_

const string adjacent_cell_movement =
    "@process adjacent_cell\n"
    "type adjacent_cell\n"
    "categories immature\n"
    "proportion 0.5\n"
    "layer move_gradient\n"
    "selectivities constant\n"
    "@layer move_gradient\n"
    "type numeric\n"
    "data 0 1 1\n"
    "data 1 1 1\n"
    "data 1 1 1\n";

#endif /* ADJACENTCELLMOVEMENT_H_ */
#endif /* TEST */
