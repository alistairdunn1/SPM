//============================================================================
// Name        : DerivedQuantityByCell.h
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef DERIVEDQUANTITYBYCELL_H_
#define DERIVEDQUANTITYBYCELL_H_

const string derived_quantity_by_cell_abundance =
    "@derived_quantity_by_cell derived_quantity_by_cell_abundance\n"
    "type abundance\n"
    "time_step step_one\n"
    "categories immature mature spawning\n"
    "layer double\n"
    "selectivities constant constant constant\n";

const string derived_quantity_by_cell_biomass =
    "@derived_quantity_by_cell derived_quantity_by_cell_biomass\n"
    "type biomass\n"
    "time_step step_one\n"
    "categories immature mature spawning\n"
    "layer double\n"
    "selectivities constant constant constant\n";

#endif /* DERIVEDQUANTITYBYCELL_H_ */
#endif /* TEST */
