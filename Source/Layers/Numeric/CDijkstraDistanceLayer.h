//============================================================================
// Name        : CDijkstraDistanceLayer.h
// Author      : A.Dunn & C. Marsh
// Date        : 16/10/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================
#ifndef CDIJKSTRADISTANCELAYER_H_
#define CDIJKSTRADISTANCELAYER_H_

// Local Headers
#include "Base/CNumericLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CDijkstraDistanceLayer : public CNumericLayer {
public:
  // Functions
  CDijkstraDistanceLayer();
  virtual ~CDijkstraDistanceLayer();
  CLayer* clone() { return (new CDijkstraDistanceLayer(*this)); }
  double  getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);
  double  getCellLength() { return dCellLength; }
  void    validate();
  void    build();
  void    rebuild();

protected:
  void           makeGraph();
  int            minDistance(vector<double> vDist, vector<bool> vSptSet);
  vector<double> calculate(int iSource);

  map<unsigned, map<unsigned, map<unsigned, map<unsigned, double>>>> mGrid;

  vector<vector<double>> vvGraph;
  double                 dCellLength;
  CNumericLayer*         pLayer;
  string                 sLayer;
  CWorldSquare*          pSink;
  CWorldSquare*          pSource;

  double dInfiniteDistance;
  double dDistanceToSelf;
};

#endif /*CDIJKSTRADISTANCELAYER_H_*/
