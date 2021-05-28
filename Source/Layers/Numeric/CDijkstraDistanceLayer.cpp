//============================================================================
// Name        : CDijkstraDistanceLayer.cpp
// Author      : A.Dunn & C. Marsh
// Date        : 16/10/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================
//
// C++ implementation of Dijkstra Algorithm based on code from:
//    http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm
// October 2014
//

// Local Headers
#include "CDijkstraDistanceLayer.h"

#include "../../Helpers/CError.h"
#include "../../World/CWorld.h"
#include "../CLayerManager.h"
#include "Base/CNumericLayer.h"

//**********************************************************************
// CDijkstraDistanceLayer::CDijkstraDistanceLayer()
// Default Constructor
//**********************************************************************
CDijkstraDistanceLayer::CDijkstraDistanceLayer() {
  sType             = PARAM_DIJKSTRA_DISTANCE;
  dInfiniteDistance = 1e100;
  dDistanceToSelf   = 0;
}

//**********************************************************************
// double CDijkstraDistanceLayer::getValue(int RowIndex, int ColIndex, int TargetRow=0, int TargetCol=0)
// Get The Value Fromo ur DijkstraDistance Layer
//**********************************************************************
double CDijkstraDistanceLayer::getValue(int RowIndex, int ColIndex, int TargetRow = 0, int TargetCol = 0) {
  try {
    // Check
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_LAYER_HEIGHT);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_LAYER_WIDTH);

    return mGrid[RowIndex][ColIndex][TargetRow][TargetCol];
  } catch (string& Ex) {
    Ex = "CDijkstraDistanceLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDijkstraDistanceLayer::validate()
// Validate our DijkstraDistance Lyer
//**********************************************************************
void CDijkstraDistanceLayer::validate() {
  try {
    // Base
    CNumericLayer::validate();

    // Assign parameters
    dCellLength = pWorld->getCellLength();
  } catch (string& Ex) {
    Ex = "CDijkstraDistanceLayer.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDijkstraDistanceLayer::build()
// build
//**********************************************************************
void CDijkstraDistanceLayer::build() {
  try {
    makeGraph();

    // Fill The Grid With The DijkstraDistances
    for (int i = 0; i < iHeight; ++i) {
      for (int j = 0; j < iWidth; ++j) {
        vector<double> vDist = calculate((i * iWidth) + j);
        for (int k = 0; k < iHeight; ++k) {
          for (int l = 0; l < iWidth; ++l) {
            mGrid[i][j][k][l] = vDist[(k * iWidth) + l];
          }
        }
      }
    }
  } catch (string& Ex) {
    Ex = "CDijkstraDistanceLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDijkstraDistanceLayer::makeGraph()
// makeGraph
//**********************************************************************
void CDijkstraDistanceLayer::makeGraph() {
  // Initialise vvGraph of vertex distances
  vvGraph.resize(iHeight * iWidth);
  for (int i = 0; i < (iHeight * iWidth); ++i) {
    for (int j = 0; j < (iHeight * iWidth); ++j) {
      vvGraph[i].push_back(0);
    }
  }

  // Get our base Layer Pointer
  sLayer                       = pWorld->getBaseLayer();
  CLayerManager* pLayerManager = CLayerManager::Instance();
  pLayer                       = pLayerManager->getNumericLayer(sLayer);

  // Populate the graph of vertex distances
  // Assumes adjacent cells are traversable but base cells that are not enabled are not
  for (int i = 0; i < iHeight; ++i) {
    for (int j = 0; j < iWidth; ++j) {
      int iRow = (i * iWidth) + j;
      pSource  = pWorld->getBaseSquare(i, j);
      for (int k = 0; k < iHeight; ++k) {
        for (int l = 0; l < iWidth; ++l) {
          int iCol = (k * iWidth) + l;
          pSink    = pWorld->getBaseSquare(k, l);
          if (pSource->getEnabled()) {
            if (pSink->getEnabled()) {
              if (k == (i - 1) && l == (j - l))
                vvGraph[iRow][iCol] = sqrt(2 * dCellLength);  // top-left
              else if (k == (i + 0) && l == (j - 1))
                vvGraph[iRow][iCol] = dCellLength;  // top
              else if (k == (i + 1) && l == (j - 1))
                vvGraph[iRow][iCol] = sqrt(2 * dCellLength);  // top-right
              else if (k == (i - 1) && l == (j + 0))
                vvGraph[iRow][iCol] = dCellLength;  // left
              else if (k == (i + 0) && l == (j + 0))
                vvGraph[iRow][iCol] = dDistanceToSelf;  // centre
              else if (k == (i + 1) && l == (j + 0))
                vvGraph[iRow][iCol] = dCellLength;  // right
              else if (k == (i - 1) && l == (j + 1))
                vvGraph[iRow][iCol] = sqrt(2 * dCellLength);  // bottom-left
              else if (k == (i + 0) && l == (j + 1))
                vvGraph[iRow][iCol] = dCellLength;  // bottom
              else if (k == (i + 1) && l == (j + 1))
                vvGraph[iRow][iCol] = sqrt(2 * dCellLength);  // bottom-right
              else
                vvGraph[iRow][iCol] = dInfiniteDistance;  // not an adjacent cell
            } else
              vvGraph[iRow][iCol] = dInfiniteDistance;  // sink not enabled - movement not allowed - distance set to infinite
          } else
            vvGraph[iRow][iCol] = dInfiniteDistance;  // source not enabled - movement not allowed - distance set to infinite
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
// int CDijkstraDistanceLayer::minDistance( vector <double> vDist, vectror<bool> vSptSet)
// utility function
//**********************************************************************
int CDijkstraDistanceLayer::minDistance(vector<double> vDist, vector<bool> vSptSet) {
  // Initialize min value
  double dMin      = dInfiniteDistance;
  int    iMinIndex = 0;
  int    iV        = vDist.size();
  for (int v = 0; v < iV; ++v) {
    if (vSptSet[v] == false && vDist[v] <= dMin) {
      dMin      = vDist[v];
      iMinIndex = v;
    }
  }
  return (iMinIndex);
}

//**********************************************************************
// int CDijkstraDistanceLayer::calculate( )
// utility function
//**********************************************************************
vector<double> CDijkstraDistanceLayer::calculate(int iSource) {
  try {
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
    for (int i = 0; i < (iV - 1); ++i) {
      // Pick the minimum distance vertex from the set of vertices not yet processed. iU is always equal to iSource in first iteration.
      iU = minDistance(vDist, vSptSet);

      // Mark the picked vertex as processed
      vSptSet[iU] = true;

      // Update vDist value of the adjacent vertices of the picked vertex.
      for (int v = 0; v < iV; ++v) {
        // Update vDist[v] only if is not in vSptSet, there is an edge from iU to v, and total weight of path from iSource to v through iU is smaller than current value of vDist[v]
        if (!vSptSet[v] && vvGraph[iU][v] && vDist[iU] != 1e100 && (vDist[iU] + vvGraph[iU][v]) < vDist[v]) {
          vDist[v] = vDist[iU] + vvGraph[iU][v];
        }
      }
    }
    // return the constructed distance array for iSource
    return (vDist);
  } catch (string& Ex) {
    Ex = "CDijkstraDistanceLayer.calculate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDijkstraDistanceLayer::rebuild()
// rebuild
//**********************************************************************
void CDijkstraDistanceLayer::rebuild() {
  try {
  } catch (string& Ex) {
    Ex = "CDijkstraDistanceLayer.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CDijkstraDistanceLayer::~CDijkstraDistanceLayer()
// Default De-Constructor
//**********************************************************************
CDijkstraDistanceLayer::~CDijkstraDistanceLayer() {}
