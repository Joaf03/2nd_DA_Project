#ifndef INC_2ND_PROJECT_TSPSOLVER_H
#define INC_2ND_PROJECT_TSPSOLVER_H

#include "DataLoader.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class TSPSolver {
public:
    vector<int> solveTSP(const vector<Edge>& edges, int startNode);
    double calculateTourLength(const vector<int>& tour);
    int getMaxNodeIndex();
    void backtrack(double currentLength, vector<int>& currentTour, vector<bool>& visited);
    double getDistance(int source, int destination);

private:
    vector<Edge> edges;
    int startNode;
    int numNodes;
    vector<int> bestTour;
    double bestTourLength;
};

#endif
