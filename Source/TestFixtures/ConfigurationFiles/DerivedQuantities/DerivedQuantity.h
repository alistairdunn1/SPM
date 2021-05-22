//============================================================================
// Name        : DerivedQuantity.h
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef DERIVEDQUANTITY_H_
#define DERIVEDQUANTITY_H_

const string derived_quantity =
    "@derived_quantity derived_quantity\n"
    "type abundance\n"
    "time_step step_one\n"
    "categories immature mature spawning\n"
    "layer double\n"
    "selectivities constant constant constant\n";

const string derived_quantity_ssb =
    "@derived_quantity ssb\n"
    "type abundance\n"
    "time_step step_one\n"
    "categories mature\n"
    "layer double_one\n"
    "selectivities constant\n";

#endif /* DERIVEDQUANTITY_H_ */
#endif /* TEST */
