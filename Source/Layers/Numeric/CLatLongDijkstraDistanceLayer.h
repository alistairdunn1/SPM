//============================================================================
// Name        : CLatLongDijkstraDistanceLayer.h
// Author      : A.Dunn & C. Marsh
// Date        : 16/10/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================
#ifndef CLATLONGDIJKSTRADISTANCELAYER_H_
#define CLATLONGDIJKSTRADISTANCELAYER_H_

// Local Headers
#include "Base/CNumericLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CLatLongDijkstraDistanceLayer : public CNumericLayer
{
public:
  // Functions
  CLatLongDijkstraDistanceLayer();
  virtual ~CLatLongDijkstraDistanceLayer();
  CLayer *clone() { return (new CLatLongDijkstraDistanceLayer(*this)); }
  double getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);
  void validate();
  void build();
  void rebuild();
  double getLong(int RowIndex, int ColIndex);
  double getLat(int RowIndex, int ColIndex);

protected:
  void makeGraph();
  int minDistance(vector<double> vDist, vector<bool> vSptSet);
  vector<double> calculate(int iSource);

  map<unsigned, map<unsigned, map<unsigned, map<unsigned, double>>>> mGrid;

  vector<vector<double>> vvGraph;
  double dCellLength;
  CNumericLayer *pLayer;
  string sLayer;
  CWorldSquare *pSink;
  CWorldSquare *pSource;

  double dInfiniteDistance;
  double dDistanceToSelf;

  string sLatLayer;
  string sLongLayer;
  CNumericLayer *pLatLayer;
  CNumericLayer *pLongLayer;
  double deg2rad(double deg);
  double haversine(const double long1, const double lat1, const double long2, const double lat2);
};

#endif /*CLATLONGDIJKSTRADISTANCELAYER_H_*/
