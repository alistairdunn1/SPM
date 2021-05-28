//============================================================================
// Name        : AgeingError.h
// Author      : S.Rasmussen
// Date        : 27/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef AGEINGERROR_H_
#define AGEINGERROR_H_

const string ageingerror_normal
    = "@ageing_error normal\n"
      "type normal\n"
      "cv 0.1\n";

const string ageingerror_offbyone
    = "@ageing_error off_by_one\n"
      "type off_by_one\n"
      "p1 0.05\n"
      "p2 0.10\n";

#endif /* AGEINGERROR_H_ */
#endif /* TEST */
