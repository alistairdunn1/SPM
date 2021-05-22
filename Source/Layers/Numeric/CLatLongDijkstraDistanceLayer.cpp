//============================================================================
// Name        : CLatLongDijkstraDistanceLayer.cpp
// Author      : A.Dunn & C. Marsh
// Date        : 16/10/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================
//
// C++ implementation of LatLongDijkstra Algorithm based on code from:
//    http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm
// October 2014
//

// Local Headers
#include "CLatLongDijkstraDistanceLayer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/DefinedValues.h"
#include "../../World/CWorld.h"
#include "../CLayerManager.h"
#include "Base/CNumericLayer.h"

//**********************************************************************
// CLatLongDijkstraDistanceLayer::CLatLongDijkstraDistanceLayer()
// Default Constructor
//**********************************************************************
CLatLongDijkstraDistanceLayer::CLatLongDijkstraDistanceLayer()
{
  sType = PARAM_LAT_LONG_DIJKSTRA_DISTANCE;
  dInfiniteDistance = 1e100;
  dDistanceToSelf = 0;

  // Register User allowed parameters
  pParameterList->registerAllowed(PARAM_LONG_LAYER);
  pParameterList->registerAllowed(PARAM_LAT_LAYER);
}

//**********************************************************************
// double CLatLongDijkstraDistanceLayer::getLong(int RowIndex, int ColIndex)
// Get The Long Value From our LatLongDijkstraDistance Layer
//**********************************************************************
double CLatLongDijkstraDistanceLayer::getLong(int RowIndex, int ColIndex)
{
  double dLong = pLongLayer->getValue(RowIndex, ColIndex);
  return dLong;
}

//**********************************************************************
// double CLatLongDijkstraDistanceLayer::getLat(int RowIndex, int ColIndex)
// Get The Lat Value From our LatLongDijkstraDistance Layer
//**********************************************************************
double CLatLongDijkstraDistanceLayer::getLat(int RowIndex, int ColIndex)
{
  double dLat = pLatLayer->getValue(RowIndex, ColIndex);
  return dLat;
}

//**********************************************************************
// double CLatLongDijkstraDistanceLayer::getValue(int RowIndex, int ColIndex, int TargetRow=0, int TargetCol=0)
// Get The Value Fromo ur LatLongDijkstraDistance Layer
//**********************************************************************
double CLatLongDijkstraDistanceLayer::getValue(int RowIndex, int ColIndex, int TargetRow = 0, int TargetCol = 0)
{
  try
  {
    // Check
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_LAYER_HEIGHT);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_LAYER_WIDTH);

    return mGrid[RowIndex][ColIndex][TargetRow][TargetCol];
  }
  catch (string &Ex)
  {
    Ex = "CLatLongDijkstraDistanceLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CLatLongDijkstraDistanceLayer::deg2rad(const double deg)
// Convert degrees to radians
//**********************************************************************
double CLatLongDijkstraDistanceLayer::deg2rad(double deg)
{
  double dResult = deg / 180.0 * PI;
  return dResult;
}

//**********************************************************************
// double CLatLongDijkstraDistanceLayer::haversine(const double long1, const double lat1, const double long2, const double lat2)
// calculate distance using the haversine formula
//**********************************************************************
double CLatLongDijkstraDistanceLayer::haversine(const double long1, const double lat1, const double long2, const double lat2)
{

  // Convert to radians
  double dLong1 = deg2rad(long1);
  double dLat1 = deg2rad(lat1);
  double dLong2 = deg2rad(long2);
  double dLat2 = deg2rad(lat2);

  // Haversine formula
  double dR = 6371; // Earth mean radius [km]
  double dDeltaLong = (dLong2 - dLong1);
  double dDeltaLat = (dLat2 - dLat1);
  double dA = pow(sin(dDeltaLat * 0.5), 2.0) + cos(dLat1) * cos(dLat2) * pow(sin(dDeltaLong * 0.5), 2.0);

  return dR * 2.0 * asin(std::min(1.0, sqrt(dA))); // return distance in kilometres
}

//**********************************************************************
// void CLatLongDijkstraDistanceLayer::validate()
// Validate our LatLongDijkstraDistance Lyer
//**********************************************************************
void CLatLongDijkstraDistanceLayer::validate()
{
  try
  {

    sLatLayer = pParameterList->getString(PARAM_LAT_LAYER);
    sLongLayer = pParameterList->getString(PARAM_LONG_LAYER);

    // Base
    CNumericLayer::validate();
  }
  catch (string &Ex)
  {
    Ex = "CLatLongDijkstraDistanceLayer.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CLatLongDijkstraDistanceLayer::build()
// build
//**********************************************************************
void CLatLongDijkstraDistanceLayer::build()
{
  try
  {

    // Get our Layers and validate values
    pLatLayer = CLayerManager::Instance()->getNumericLayer(sLatLayer);
    pLongLayer = CLayerManager::Instance()->getNumericLayer(sLongLayer);

    for (int i = 0; i < iHeight; ++i)
    {
      for (int j = 0; j < iWidth; ++j)
      {
        double dLong = getLong(i, j);
        double dLat = getLat(i, j);
        if (dLat < -90)
          CError::errorLessThan(PARAM_LAT_LAYER, "-90");
        if (dLat > 90)
          CError::errorGreaterThan(PARAM_LAT_LAYER, "90");
        if (dLong < 0)
          CError::errorLessThan(PARAM_LONG_LAYER, "0");
        if (dLong > 360)
          CError::errorGreaterThan(PARAM_LONG_LAYER, "360");
      }
    }

    makeGraph();

    // Fill The Grid With The LatLongDijkstraDistances
    for (int i = 0; i < iHeight; ++i)
    {
      for (int j = 0; j < iWidth; ++j)
      {
        vector<double> vDist = calculate((i * iWidth) + j);
        for (int k = 0; k < iHeight; ++k)
        {
          for (int l = 0; l < iWidth; ++l)
          {
            mGrid[i][j][k][l] = vDist[(k * iWidth) + l];
          }
        }
      }
    }
  }
  catch (string &Ex)
  {
    Ex = "CLatLongDijkstraDistanceLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CLatLongDijkstraDistanceLayer::makeGraph()
// makeGraph
//**********************************************************************
void CLatLongDijkstraDistanceLayer::makeGraph()
{

  // Initialise vvGraph of vertex distances
  vvGraph.resize(iHeight * iWidth);
  for (int i = 0; i < (iHeight * iWidth); ++i)
  {
    for (int j = 0; j < (iHeight * iWidth); ++j)
    {
      vvGraph[i].push_back(0);
    }
  }

  // Get our base Layer Pointer
  sLayer = pWorld->getBaseLayer();
  CLayerManager *pLayerManager = CLayerManager::Instance();
  pLayer = pLayerManager->getNumericLayer(sLayer);

  // Populate the graph of vertex distances
  // Assumes adjacent cells are traversable but base cells that are not enabled are not
  for (int i = 0; i < iHeight; ++i)
  {
    for (int j = 0; j < iWidth; ++j)
    {
      int iRow = (i * iWidth) + j;
      pSource = pWorld->getBaseSquare(i, j);
      for (int k = 0; k < iHeight; ++k)
      {
        for (int l = 0; l < iWidth; ++l)
        {
          int iCol = (k * iWidth) + l;
          pSink = pWorld->getBaseSquare(k, l);
          if (pSource->getEnabled())
          {
            if (pSink->getEnabled())
            {
              double dLong1 = getLong(i, j);
              double dLat1 = getLat(i, j);
              double dLong2 = getLong(k, l);
              double dLat2 = getLat(k, l);
              if (k == (i - 1) && l == (j - l))
                vvGraph[iRow][iCol] = haversine(dLong1, dLat1, dLong2, dLat2); // top-left
              else if (k == (i + 0) && l == (j - 1))
                vvGraph[iRow][iCol] = haversine(dLong1, dLat1, dLong2, dLat2); // top
              else if (k == (i + 1) && l == (j - 1))
                vvGraph[iRow][iCol] = haversine(dLong1, dLat1, dLong2, dLat2); // top-right
              else if (k == (i - 1) && l == (j + 0))
                vvGraph[iRow][iCol] = haversine(dLong1, dLat1, dLong2, dLat2); // left
              else if (k == (i + 0) && l == (j + 0))
                vvGraph[iRow][iCol] = haversine(dLong1, dLat1, dLong2, dLat2); // centre
              else if (k == (i + 1) && l == (j + 0))
                vvGraph[iRow][iCol] = haversine(dLong1, dLat1, dLong2, dLat2); // right
              else if (k == (i - 1) && l == (j + 1))
                vvGraph[iRow][iCol] = haversine(dLong1, dLat1, dLong2, dLat2); // bottom-left
              else if (k == (i + 0) && l == (j + 1))
                vvGraph[iRow][iCol] = haversine(dLong1, dLat1, dLong2, dLat2); // bottom
              else if (k == (i + 1) && l == (j + 1))
                vvGraph[iRow][iCol] = haversine(dLong1, dLat1, dLong2, dLat2); // bottom-right
              else
                vvGraph[iRow][iCol] = dInfiniteDistance; // not an adjacent cell
            }
            else
              vvGraph[iRow][iCol] = dInfiniteDistance; // sink not enabled - movement not allowed - distance set to infinite
          }
          else
            vvGraph[iRow][iCol] = dInfiniteDistance; // source not enabled - movement not allowed - distance set to infinite
        }
      }
    }
  }
  // debug code
  // for (int i=0; i < (int)vvGraph.size(); ++i) {
  //   for (int j=0; j < (int)vvGraph[i].size(); ++j) {
  //     std::cerr << vvGraph[i][j] << " ";
  //   }
  //   std::cerr<< "\n";
  // }
  // std::cerr<< "\n";
}

//**********************************************************************
// int CLatLongDijkstraDistanceLayer::minDistance( vector <double> vDist, vectror<bool> vSptSet)
// utility function
//**********************************************************************
int CLatLongDijkstraDistanceLayer::minDistance(vector<double> vDist, vector<bool> vSptSet)
{
  // Initialize min value
  double dMin = dInfiniteDistance;
  int iMinIndex = 0;
  int iV = vDist.size();
  for (int v = 0; v < iV; ++v)
  {
    if (vSptSet[v] == false && vDist[v] <= dMin)
    {
      dMin = vDist[v];
      iMinIndex = v;
    }
  }
  return (iMinIndex);
}

//**********************************************************************
// int CLatLongDijkstraDistanceLayer::calculate( )
// utility function
//**********************************************************************
vector<double> CLatLongDijkstraDistanceLayer::calculate(int iSource)
{
  try
  {

    int iV = iHeight * iWidth;
    // The output array.  vDist[i] will hold the shortest distance from src to i. Initialise as infinite distancew
    vector<double> vDist(iV, dInfiniteDistance);
    // vSptSet[i] will true if vertex i is included in shortest path tree or shortest distance fromiSource to i is finalized. Initialise as false
    vector<bool> vSptSet(iV, false);
    // And the other variables required
    int iU = 0;

    // Distance of source vertex from itself is always 0
    vDist[iSource] = dDistanceToSelf;

    // Find shortest path for all vertices
    for (int i = 0; i < (iV - 1); ++i)
    {
      // Pick the minimum distance vertex from the set of vertices not yet processed. iU is always equal to iSource in first iteration.
      iU = minDistance(vDist, vSptSet);

      //Mark the picked vertex as processed
      vSptSet[iU] = true;

      // Update vDist value of the adjacent vertices of the picked vertex.
      for (int v = 0; v < iV; ++v)
      {
        // Update vDist[v] only if is not in vSptSet, there is an edge from iU to v, and total weight of path from iSource to v through iU is smaller than current value of vDist[v]
        if (!vSptSet[v] && vvGraph[iU][v] && vDist[iU] != 1e100 && (vDist[iU] + vvGraph[iU][v]) < vDist[v])
        {
          vDist[v] = vDist[iU] + vvGraph[iU][v];
        }
      }
    }
    // return the constructed distance array for iSource
    return (vDist);
  }
  catch (string &Ex)
  {
    Ex = "CLatLongDijkstraDistanceLayer.calculate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CLatLongDijkstraDistanceLayer::rebuild()
// rebuild
//**********************************************************************
void CLatLongDijkstraDistanceLayer::rebuild()
{
  try
  {
  }
  catch (string &Ex)
  {
    Ex = "CLatLongDijkstraDistanceLayer.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CLatLongDijkstraDistanceLayer::~CLatLongDijkstraDistanceLayer()
// Default De-Constructor
//**********************************************************************
CLatLongDijkstraDistanceLayer::~CLatLongDijkstraDistanceLayer()
{
}
