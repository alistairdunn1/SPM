//============================================================================
// Name        : CLatLongDistanceLayer.h
// Author      : A.Dunn
// Date        : 11/08/2014
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CLATLONGDISTANCELAYER_H_
#define CLATLONGDISTANCELAYER_H_

// Local Headers
#include "Base/CNumericLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CLatLongDistanceLayer : public CNumericLayer {
public:
  // Functions
  CLatLongDistanceLayer();
  virtual ~CLatLongDistanceLayer();
  CLayer* clone() { return (new CLatLongDistanceLayer(*this)); }
  double  getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);
  double  getLong(int RowIndex, int ColIndex);
  double  getLat(int RowIndex, int ColIndex);
  void    validate();
  void    build();
  void    rebuild();

protected:
  string                                                             sLatLayer;
  string                                                             sLongLayer;
  CNumericLayer*                                                     pLatLayer;
  CNumericLayer*                                                     pLongLayer;
  map<unsigned, map<unsigned, map<unsigned, map<unsigned, double>>>> mGrid;
  double                                                             deg2rad(double deg);
  double                                                             haversine(const double long1, const double lat1, const double long2, const double lat2);
};

#endif /*CLATLONGDISTANCELAYER_H_*/
